# ProjectMishkan
Interactive Mishkan builder / simulator (See the second half of the book of Exodus)

# Build instructions
 - Install Unreal Engine / Visual Studio Community 2015
 - Pull code base from Git
 - Right click ProjectMishkan.uproject and select Generate Visual Studio Project Files
 - Open ProjectMishkan.sln
 - Build project (for Unreal Editor, to run the game see below)

# Running the game
 - Change the build configuration to DebugGame
 - Cook the game contents by running cook.bat with the following parameters:
   1) The location of the Unreal Engine binaries folder (example C:\Program Files\Epic Games\4.7\Engine\Binaries\Win64\) in quotes
   2) The Target platform (possible values are WindowsNoEditor, WindowsServer, LinuxServer, PS4, XboxOne, IOS, Android)
 - Run the executable created in the Binaries folder
 
 # Localization
 The game framework makes usage of Unreal's localization framework. In order to set it up properly, observe the following guidelines
  - Strings in Game Code
    - A file with strings should write at the top #define LOCTEXT_NAMESPACE "Mishkan" and at the end #undef LOCTEXT_NAMESPACE
    - Use the LOCTEXT(Key, String) macro to generate localizable strings
  - Strings in the Unreal Editor
    - Use 'Text' and not 'String' for any text that the user sees
  - Setting up Localization
    - Enable experimental Localization Dashboard by going to Edit > Editor Preferences > Experimental and under Tools check off "Localization Dashboard"
    - Open the dashboard by clicking Window > Dashboard
    - Select the already created target 'Game'
    - Scroll to the bottom where it says 'Cultures', here you can choose which languages to support
    - Click the 'Gather' button to find all the Strings that need to be translated
    - Beside each Culture click the Edit Translations button to enter in all the needed translations
    - Click the Count Words button to track how many translations remain
    - Click the Compile All button when finished