program kmconvert;

{$APPTYPE CONSOLE}

uses
  System.SysUtils,
  Keyman.Developer.System.KeymanConvertMain in 'Keyman.Developer.System.KeymanConvertMain.pas',
  Keyman.Developer.System.ImportWindowsKeyboard in 'Keyman.Developer.System.ImportWindowsKeyboard.pas',
  RegistryKeys in '..\..\..\windows\src\global\delphi\general\RegistryKeys.pas',
  KeymanVersion in '..\..\..\windows\src\global\delphi\general\KeymanVersion.pas',
  utilexecute in '..\..\..\windows\src\global\delphi\general\utilexecute.pas',
  Keyman.Developer.System.KeyboardProjectTemplate in 'Keyman.Developer.System.KeyboardProjectTemplate.pas',
  UKeymanTargets in '..\..\..\windows\src\global\delphi\general\UKeymanTargets.pas',
  utilstr in '..\..\..\windows\src\global\delphi\general\utilstr.pas',
  Unicode in '..\..\..\windows\src\global\delphi\general\Unicode.pas',
  StockFileNames in '..\..\..\windows\src\global\delphi\cust\StockFileNames.pas',
  utilfiletypes in '..\..\..\windows\src\global\delphi\general\utilfiletypes.pas',
  KeyboardParser in '..\TIKE\main\KeyboardParser.pas',
  kmxfile in '..\..\..\windows\src\global\delphi\general\kmxfile.pas',
  kmxfileconsts in '..\..\..\windows\src\global\delphi\general\kmxfileconsts.pas',
  OnlineConstants in '..\..\..\windows\src\global\delphi\productactivation\OnlineConstants.pas',
  ExtShiftState in '..\..\..\windows\src\global\delphi\comp\ExtShiftState.pas',
  utilsystem in '..\..\..\windows\src\global\delphi\general\utilsystem.pas',
  VKeys in '..\..\..\windows\src\global\delphi\general\VKeys.pas',
  WindowsLanguages in '..\..\..\windows\src\global\delphi\general\WindowsLanguages.pas',
  GetOsVersion in '..\..\..\windows\src\global\delphi\general\GetOsVersion.pas',
  CRC32 in '..\..\..\windows\src\global\delphi\general\CRC32.pas',
  KeyNames in '..\..\..\windows\src\global\delphi\general\KeyNames.pas',
  utildir in '..\..\..\windows\src\global\delphi\general\utildir.pas',
  TextFileFormat in '..\TIKE\main\TextFileFormat.pas',
  kpsfile in '..\..\..\windows\src\global\delphi\general\kpsfile.pas',
  PackageInfo in '..\..\..\windows\src\global\delphi\general\PackageInfo.pas',
  JsonUtil in '..\..\..\windows\src\global\delphi\general\JsonUtil.pas',
  VersionInfo in '..\..\..\windows\src\global\delphi\general\VersionInfo.pas',
  PackageFileFormats in '..\..\..\windows\src\global\delphi\general\PackageFileFormats.pas',
  Keyman.Developer.System.Project.ProjectLog in '..\TIKE\project\Keyman.Developer.System.Project.ProjectLog.pas',
  BCP47Tag in '..\..\..\windows\src\global\delphi\general\BCP47Tag.pas',
  Keyman.System.CanonicalLanguageCodeUtils in '..\..\..\windows\src\global\delphi\general\Keyman.System.CanonicalLanguageCodeUtils.pas',
  Keyman.System.LanguageCodeUtils in '..\..\..\windows\src\global\delphi\general\Keyman.System.LanguageCodeUtils.pas',
  Keyman.System.KeyboardJSInfo in '..\..\..\windows\src\global\delphi\keyboards\Keyman.System.KeyboardJSInfo.pas',
  Keyman.System.KeyboardUtils in '..\..\..\windows\src\global\delphi\keyboards\Keyman.System.KeyboardUtils.pas',
  Keyman.System.KMXFileLanguages in '..\..\..\windows\src\global\delphi\keyboards\Keyman.System.KMXFileLanguages.pas',
  Keyman.System.Standards.BCP47SubtagRegistry in '..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.BCP47SubtagRegistry.pas',
  Keyman.System.Standards.BCP47SuppressScriptRegistry in '..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.BCP47SuppressScriptRegistry.pas',
  Keyman.System.Standards.ISO6393ToBCP47Registry in '..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.ISO6393ToBCP47Registry.pas',
  Keyman.System.Standards.LCIDToBCP47Registry in '..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.LCIDToBCP47Registry.pas',
  Keyman.System.RegExGroupHelperRSP19902 in '..\..\..\windows\src\global\delphi\general\Keyman.System.RegExGroupHelperRSP19902.pas',
  Keyman.System.PackageInfoRefreshKeyboards in '..\..\..\windows\src\global\delphi\packages\Keyman.System.PackageInfoRefreshKeyboards.pas',
  Keyman.Developer.System.Project.ProjectFile in '..\TIKE\project\Keyman.Developer.System.Project.ProjectFile.pas',
  Keyman.Developer.System.Project.ProjectFiles in '..\TIKE\project\Keyman.Developer.System.Project.ProjectFiles.pas',
  Keyman.Developer.System.Project.ProjectSaver in '..\TIKE\project\Keyman.Developer.System.Project.ProjectSaver.pas',
  Keyman.Developer.System.Project.ProjectFileType in '..\TIKE\project\Keyman.Developer.System.Project.ProjectFileType.pas',
  mrulist in '..\TIKE\main\mrulist.pas',
  ErrorControlledRegistry in '..\..\..\windows\src\global\delphi\vcl\ErrorControlledRegistry.pas',
  TempFileManager in '..\..\..\windows\src\global\delphi\general\TempFileManager.pas',
  klog in '..\..\..\windows\src\global\delphi\general\klog.pas',
  RedistFiles in '..\TIKE\main\RedistFiles.pas',
  DebugPaths in '..\..\..\windows\src\global\delphi\general\DebugPaths.pas',
  Upload_Settings in '..\..\..\windows\src\global\delphi\general\Upload_Settings.pas',
  Keyman.Developer.System.Project.Project in '..\TIKE\project\Keyman.Developer.System.Project.Project.pas',
  Keyman.Developer.System.Project.ProjectLoader in '..\TIKE\project\Keyman.Developer.System.Project.ProjectLoader.pas',
  Keyman.Developer.System.Project.kmnProjectFile in '..\TIKE\project\Keyman.Developer.System.Project.kmnProjectFile.pas',
  Keyman.Developer.System.Project.kpsProjectFile in '..\TIKE\project\Keyman.Developer.System.Project.kpsProjectFile.pas',
  VisualKeyboard in '..\..\..\windows\src\global\delphi\visualkeyboard\VisualKeyboard.pas',
  VKeyChars in '..\..\..\windows\src\global\delphi\general\VKeyChars.pas',
  VisualKeyboardLoaderBinary in '..\..\..\windows\src\global\delphi\visualkeyboard\VisualKeyboardLoaderBinary.pas',
  VisualKeyboardLoaderXML in '..\..\..\windows\src\global\delphi\visualkeyboard\VisualKeyboardLoaderXML.pas',
  VisualKeyboardSaverBinary in '..\..\..\windows\src\global\delphi\visualkeyboard\VisualKeyboardSaverBinary.pas',
  VisualKeyboardSaverXML in '..\..\..\windows\src\global\delphi\visualkeyboard\VisualKeyboardSaverXML.pas',
  UMD5Hash in '..\..\..\windows\src\global\delphi\general\UMD5Hash.pas',
  Keyman.Developer.System.KMConvertParameters in 'Keyman.Developer.System.KMConvertParameters.pas',
  Keyman.Developer.System.ImportKeyboardDLL in 'Keyman.Developer.System.ImportKeyboardDLL.pas',
  ScanCodeMap in '..\..\..\windows\src\global\delphi\general\ScanCodeMap.pas',
  Keyman.Developer.System.TouchLayoutToVisualKeyboardConverter in 'Keyman.Developer.System.TouchLayoutToVisualKeyboardConverter.pas',
  OnScreenKeyboardData in '..\..\..\windows\src\global\delphi\visualkeyboard\OnScreenKeyboardData.pas',
  TouchLayout in '..\TIKE\oskbuilder\TouchLayout.pas',
  TouchLayoutDefinitions in '..\TIKE\oskbuilder\TouchLayoutDefinitions.pas',
  TouchLayoutUtils in '..\TIKE\oskbuilder\TouchLayoutUtils.pas',
  KeyboardFonts in '..\..\..\windows\src\global\delphi\general\KeyboardFonts.pas',
  Keyman.System.Util.RenderLanguageIcon in '..\..\..\windows\src\global\delphi\ui\Keyman.System.Util.RenderLanguageIcon.pas',
  utilicon in '..\..\..\windows\src\global\delphi\general\utilicon.pas',
  CompileErrorCodes in '..\..\..\windows\src\global\delphi\general\CompileErrorCodes.pas',
  Keyman.Developer.System.ModelProjectTemplate in 'Keyman.Developer.System.ModelProjectTemplate.pas',
  Keyman.Developer.System.Project.modelTsProjectFile in '..\TIKE\project\Keyman.Developer.System.Project.modelTsProjectFile.pas',
  Keyman.Developer.System.Project.wordlistTsvProjectFile in '..\TIKE\project\Keyman.Developer.System.Project.wordlistTsvProjectFile.pas',
  Sentry.Client in '..\..\..\windows\src\ext\sentry\Sentry.Client.pas',
  Sentry.Client.Console in '..\..\..\windows\src\ext\sentry\Sentry.Client.Console.pas',
  sentry in '..\..\..\windows\src\ext\sentry\sentry.pas',
  Keyman.System.KeymanSentryClient in '..\..\..\windows\src\global\delphi\general\Keyman.System.KeymanSentryClient.pas',
  KeymanPaths in '..\..\..\windows\src\global\delphi\general\KeymanPaths.pas',
  Keyman.System.Standards.LangTagsRegistry in '..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.LangTagsRegistry.pas',
  Keyman.Developer.System.Project.UrlRenderer in '..\TIKE\project\Keyman.Developer.System.Project.UrlRenderer.pas',
  Keyman.System.LexicalModelUtils in '..\..\..\windows\src\global\delphi\lexicalmodels\Keyman.System.LexicalModelUtils.pas';

{$R icons.RES}
{$R version.res}
{$R manifest.res}

const
  LOGGER_DEVELOPER_TOOLS_KMCONVERT = TKeymanSentryClient.LOGGER_DEVELOPER_TOOLS + '.kmconvert';
begin
  TKeymanSentryClient.Start(TSentryClientConsole, kscpDeveloper, LOGGER_DEVELOPER_TOOLS_KMCONVERT);
  try
    try
      TKeymanSentryClient.Validate;
      Run;
    except
      on E: Exception do
        if not SentryHandleException(E) then
        begin
          writeln(E.Message);
          ExitCode := 99;
        end;
    end;
  finally
    TKeymanSentryClient.Stop;
  end;
end.