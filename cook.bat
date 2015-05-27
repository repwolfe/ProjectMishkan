rem Execution Arguments: 1) Unreal Engine's Win64 Binaries folder 2) Target Platform to cook for
rem If not provided, default values (which can be edited below) are set

set UnrealExe=UE4Editor.exe
set Project=ProjectMishkan.uproject
set DefaultUnrealLoc="D:\Program Files\Epic Games\4.7\Engine\Binaries\Win64\"

rem Available platforms to target are WindowsNoEditor, WindowsServer, LinuxServer, PS4, XboxOne, IOS, Android
set DefaultTarget=WindowsNoEditor

if [%1] == [] (set UnrealLoc=%DefaultUnrealLoc%) else (set UnrealLoc=%1)

if [%2] == [] (set Target=%DefaultTarget%) else (set Target=%2)

%UnrealLoc%%UnrealExe% %cd%\%Project% -run=cook -targetplatform=%Target%