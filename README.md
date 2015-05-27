# ProjectMishkan
Interactive Mishkan builder / simulator (See the second half of the book of Exodus)

# Build instructions
 - Install Unreal Engine / Visual Studio Community 2013
 - Pull code base from Git
 - Right click ProjectMishkan.uproject and select Generate Visual Studio Project Files
 - Open ProjectMishkan.sln
 - Build project (for Unreal Editor, to run the game see below)

# Running the game
 - Change the build configuration to DebugGame
 - Cook the game contents by running cook.bat with the following parameters:
   # The location of the Unreal Engine binaries folder (example C:\Program Files\Epic Games\4.7\Engine\Binaries\Win64\) in quotes
   # The Target platform (possible values are WindowsNoEditor, WindowsServer, LinuxServer, PS4, XboxOne, IOS, Android)
 - Run the executable created in the Binaries folder