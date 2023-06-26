import { LDMLKeyboardXMLSourceFileReader, LDMLKeyboard, KMXPlus, CompilerCallbacks, LDMLKeyboardTestDataXMLSourceFile } from '@keymanapp/common-types';
import { CompilerOptions } from './compiler-options.js';
import { CompilerMessages } from './messages.js';
import { BkspCompiler, TranCompiler } from './tran.js';
import { DispCompiler } from './disp.js';
import { KeysCompiler } from './keys.js';
import { LayrCompiler } from './layr.js';
import { LocaCompiler } from './loca.js';
import { MetaCompiler } from './meta.js';
import { NameCompiler } from './name.js';
import { VkeyCompiler } from './vkey.js';
import { VarsCompiler } from './vars.js';
import { StrsCompiler, ElemCompiler, ListCompiler } from './empty-compiler.js';


import LDMLKeyboardXMLSourceFile = LDMLKeyboard.LDMLKeyboardXMLSourceFile;
import KMXPlusFile = KMXPlus.KMXPlusFile;
import DependencySections = KMXPlus.DependencySections;
import { SectionIdent, constants } from '@keymanapp/ldml-keyboard-constants';

export const SECTION_COMPILERS = [
  // These are in dependency order.

  // First the former 'global' sections
  StrsCompiler,
  ListCompiler,
  ElemCompiler,
  // Next, Vars, which depends on others
  VarsCompiler,
  // Now all others:
  BkspCompiler,
  DispCompiler,
  KeysCompiler,
  LayrCompiler,
  LocaCompiler,
  MetaCompiler,
  NameCompiler,
  TranCompiler,
  VkeyCompiler,
];

export class LdmlKeyboardCompiler {
  private readonly callbacks: CompilerCallbacks;
  private readonly options: CompilerOptions;

  constructor (callbacks: CompilerCallbacks, options: CompilerOptions) {
    this.options = {
      debug: false,
      addCompilerVersion: true,
      ...options
    };
    this.callbacks = callbacks;
  }

  private buildSections(source: LDMLKeyboardXMLSourceFile) {
    return SECTION_COMPILERS.map(c => new c(source, this.callbacks));
  }

  /**
   * Loads a LDML Keyboard xml file and compiles into in-memory xml
   * structures.
   * @param filename  input filename, will use callback to load from disk
   * @returns the source file, or null if invalid
   */
  public load(filename: string): LDMLKeyboardXMLSourceFile | null {
    const reader = new LDMLKeyboardXMLSourceFileReader(this.options.readerOptions, this.callbacks);
    const data = this.callbacks.loadFile(filename);
    if(!data) {
      this.callbacks.reportMessage(CompilerMessages.Error_InvalidFile({errorText: 'Unable to read XML file'}));
      return null;
    }
    const source = reader.load(data);
    if(!source) {
      this.callbacks.reportMessage(CompilerMessages.Error_InvalidFile({errorText: 'Unable to load XML file'}));
      return null;
    }
    try {
      if (!reader.validate(source, this.callbacks.loadSchema('ldml-keyboard'))) {
        return null;
      }
    } catch(e) {
      this.callbacks.reportMessage(CompilerMessages.Error_InvalidFile({errorText: e.toString()}));
      return null;
    }

    return source;
  }

  /**
   * Loads a LDML Keyboard test data xml file and compiles into in-memory xml
   * structures.
   * @param filename  input filename, will use callback to load from disk
   * @returns the source file, or null if invalid
   */
    public loadTestData(filename: string): LDMLKeyboardTestDataXMLSourceFile | null {
      const reader = new LDMLKeyboardXMLSourceFileReader(this.options.readerOptions, this.callbacks);
      const data = this.callbacks.loadFile(filename);
      if(!data) {
        this.callbacks.reportMessage(CompilerMessages.Error_InvalidFile({errorText: 'Unable to read XML file'}));
        return null;
      }
      const source = reader.loadTestData(data);
      if(!source) {
        this.callbacks.reportMessage(CompilerMessages.Error_InvalidFile({errorText: 'Unable to load XML file'}));
        return null;
      }
      // TODO-LDML: The unboxed data doesn't match the schema anymore. Skipping validation, for now.

      // try {
      //   if (!reader.validate(source, this.callbacks.loadSchema('ldml-keyboard-test'))) {
      //     return null;
      //   }
      // } catch(e) {
      //   this.callbacks.reportMessage(CompilerMessages.Error_InvalidFile({errorText: e.toString()}));
      //   return null;
      // }

      return source;
    }


  /**
   * Validates that the LDML keyboard source file and lints. Actually just
   * compiles the keyboard and returns `true` if everything is good...
   * @param     source
   * @returns   true if the file validates
   */
  public validate(source: LDMLKeyboardXMLSourceFile): boolean {
    return !!this.compile(source);
  }

  /**
   * Transforms in-memory LDML keyboard xml file to an intermediate
   * representation of a .kmx file.
   * @param   source  in-memory representation of LDML keyboard xml file
   * @returns         KMXPlusFile intermediate file
   */
  public async compile(source: LDMLKeyboardXMLSourceFile): Promise<KMXPlus.KMXPlusFile> {
    const sections = this.buildSections(source);
    let passed = true;

    const kmx = new KMXPlusFile();

    for(let section of sections) {
      if (!await section.init()) {
        passed = false;
        this.callbacks.reportMessage(CompilerMessages.Fatal_SectionInitFailed({sect:section.id}));
        continue;
      }
      if(!section.validate()) {
        passed = false;
        // We'll keep validating other sections anyway, so we get a full set of
        // errors for the keyboard developer.
        continue;
      }
      // clone
      const globalSections : DependencySections = Object.assign({}, kmx.kmxplus);
      const dependencies = section.dependencies;
      Object.keys(constants.section).forEach((sectstr : string) => {
        const sectid : SectionIdent = constants.section[<SectionIdent>sectstr];
        if (dependencies.has(sectid)) {
          /* istanbul ignore if */
          if (!kmx.kmxplus[sectid]) {
            throw new Error(`Internal error: section ${section.id} depends on uninitialized dependency ${sectid}`);
          }
        } else {
          // delete dependencies that aren't referenced
          delete globalSections[sectid];
        }
      });
      const sect = section.compile(globalSections);

      /* istanbul ignore if */
      if(!sect) {
        // This should not happen -- validate() should have told us
        // if something is going to fail to compile
        this.callbacks.reportMessage(CompilerMessages.Fatal_SectionCompilerFailed({sect:section.id}));
        passed = false;
        continue;
      }
      if(kmx.kmxplus[section.id]) {
        throw new Error(`Internal error: section ${section.id} would be assigned twice`);
      }
      kmx.kmxplus[section.id] = sect as any;
    }

    return passed ? kmx : null;
  }
}
