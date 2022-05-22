program kmconverttest;

{$IFNDEF TESTINSIGHT}
{$APPTYPE CONSOLE}
{$ENDIF}{$STRONGLINKTYPES ON}
uses
  System.SysUtils,
  {$IFDEF TESTINSIGHT}
  TestInsight.DUnitX,
  {$ENDIF }
  DUnitX.Loggers.Console,
  DUnitX.Loggers.Xml.NUnit,
  DUnitX.TestFramework,
  Keyman.Developer.System.Test.KMConvertParametersTest in 'Keyman.Developer.System.Test.KMConvertParametersTest.pas',
  Keyman.Developer.System.KMConvertParameters in '..\..\..\kmconvert\Keyman.Developer.System.KMConvertParameters.pas',
  UKeymanTargets in '..\..\..\..\..\windows\src\global\delphi\general\UKeymanTargets.pas',
  BCP47Tag in '..\..\..\..\..\windows\src\global\delphi\general\BCP47Tag.pas',
  Keyman.System.CanonicalLanguageCodeUtils in '..\..\..\..\..\windows\src\global\delphi\general\Keyman.System.CanonicalLanguageCodeUtils.pas',
  Keyman.System.LanguageCodeUtils in '..\..\..\..\..\windows\src\global\delphi\general\Keyman.System.LanguageCodeUtils.pas',
  Keyman.System.Standards.LangTagsRegistry in '..\..\..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.LangTagsRegistry.pas',
  Keyman.System.KeyboardUtils in '..\..\..\..\..\windows\src\global\delphi\keyboards\Keyman.System.KeyboardUtils.pas',
  Keyman.System.LexicalModelUtils in '..\..\..\..\..\windows\src\global\delphi\lexicalmodels\Keyman.System.LexicalModelUtils.pas',
  utilstr in '..\..\..\..\..\windows\src\global\delphi\general\utilstr.pas',
  Unicode in '..\..\..\..\..\windows\src\global\delphi\general\Unicode.pas',
  GetOsVersion in '..\..\..\..\..\windows\src\global\delphi\general\GetOsVersion.pas',
  Keyman.System.Standards.BCP47SubtagRegistry in '..\..\..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.BCP47SubtagRegistry.pas',
  Keyman.System.Standards.BCP47SuppressScriptRegistry in '..\..\..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.BCP47SuppressScriptRegistry.pas',
  Keyman.System.Standards.ISO6393ToBCP47Registry in '..\..\..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.ISO6393ToBCP47Registry.pas',
  Keyman.System.Standards.LCIDToBCP47Registry in '..\..\..\..\..\windows\src\global\delphi\standards\Keyman.System.Standards.LCIDToBCP47Registry.pas',
  utilfiletypes in '..\..\..\..\..\windows\src\global\delphi\general\utilfiletypes.pas',
  StockFileNames in '..\..\..\..\..\windows\src\global\delphi\cust\StockFileNames.pas';

var
  runner : ITestRunner;
  results : IRunResults;
  logger : ITestLogger;
  nunitLogger : ITestLogger;
begin
{$IFDEF TESTINSIGHT}
  TestInsight.DUnitX.RunRegisteredTests;
  exit;
{$ENDIF}
  try
    //Check command line options, will exit if invalid
    TDUnitX.CheckCommandLine;
    //Create the test runner
    runner := TDUnitX.CreateRunner;
    //Tell the runner to use RTTI to find Fixtures
    runner.UseRTTI := True;
    //tell the runner how we will log things
    //Log to the console window
    logger := TDUnitXConsoleLogger.Create(true);
    runner.AddLogger(logger);
    //Generate an NUnit compatible XML File
    nunitLogger := TDUnitXXMLNUnitFileLogger.Create(TDUnitX.Options.XMLOutputFile);
    runner.AddLogger(nunitLogger);
    runner.FailsOnNoAsserts := False; //When true, Assertions must be made during tests;

    //Run tests
    results := runner.Execute;
    if not results.AllPassed then
      System.ExitCode := EXIT_ERRORS;

    {$IFNDEF CI}
    //We don't want this happening when running under CI.
    if TDUnitX.Options.ExitBehavior = TDUnitXExitBehavior.Pause then
    begin
      System.Write('Done.. press <Enter> key to quit.');
      System.Readln;
    end;
    {$ENDIF}
  except
    on E: Exception do
      System.Writeln(E.ClassName, ': ', E.Message);
  end;
end.