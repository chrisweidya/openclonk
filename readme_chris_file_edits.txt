List of file modifications. Revision history history shows the changes, edits and progress made in project. Undocumented effort is spent on research and wading through the game engine.  Repo: https://github.com/chrisweidya/openclonk.git

====================================================================
Project requirements and description.
====================================================================

There are 4 branches. 

Branch descriptions:

exp1 : First version of openclonk with questionnaire for experiment 1.

master: Version with player classification scenario for experiment 2.

exp3: Version with random based PCG algorithm for experiment 2.

exp4: Version with objective based algorithm for experiment 2.

Requirements: A server and a running sql database. Server side web scripts and sql experiment dump files provided in folder "server scripts". Project installation instructions can be found in "chris_how_to_install.txt".

====================================================================
Folders (inclusive of files inside) or files created (Check revision history in github for edits, and files itself for comments):
====================================================================

planet/worlds.ocf - Game scenario files (See readme_chris.txt inside folder for detailed file descriptions in folder).

planet/System.ocg/YeeQuestions.txt - Questions for Yee questionnaire taken from Nick Yee.

src/object/PlayerProfile.cpp and header file - Custom player profile handling and player related functions, including player game variables handling.

src/gui/Questionnaire.cpp - Created questionnaire component in openclonk

src/gui/Survey.cpp - Created survey component in openclonk

src/network/DBConnector.cpp and header file - Connection to SOC database using curl library.

src/network/Client.cpp and header file - (not used) attempts at using boost library for DB connection


====================================================================
Files/folders modified (Check revision history in github for edits) :
====================================================================

planet/System.ocg/LanguageUS.txt - Added many new texts in game.

planet/Objects.ocd/Items.ocd/Weapons.ocd - modified some weapon files for game balancing.

planet/Objects.ocd/Helpers.ocd/Dialogue.ocd/Script.c - Improved dialogue menus to incorporate player choice tracking.

planet/Objects.ocd/Libraries.ocd/Plants.ocd/Tree.ocd/Script.c - incorporated tracking of tree chopping.

planet/Objects.ocd/Vegetation.ocd - Severely reduced chance of tree reproduction to prevent overpopulation of trees faced in game.

planet/Objects.ocd/Clonk.ocd/Script.c - Changed default clonk health values for more survivability and balance.

planet/Objects.ocd/Items.ocd/Resources.ocd/LoamUnlimited.ocd - Created an unlimited loam for in-game debugging purposes.

src/gui/C4StartupMainDlg.cpp - Converted game main menu to the experiment format, including adding of instructions, questionnaire, survey, checks to ensure player has completed questionnaire etc. 

src/gui/C4Startup.cpp - Added questionnaire and survey to startup menu, and exit to menu by default instead of game menu.

src/gui/C4GameOverDlg.cpp - Disabled end round button until player has completed at least 5 rounds.

src/gui/C4KeyboardInput.cpp - Added tracking of keyboard presses.

src/gui/C4MouseControl.cpp - Added tracking of mouse clicks.

src/landscape/simplexnoise.cpp - Modified the simplex noise algorithm for better terrain creation in openclonk by changing frequency and persistence calculation. 

src/control/C4RoundResults.cpp - Added step to parse and send player variables after game completion.

src/game/C4game.h - Added a restart count in the game exit loop to count number of scenario restarts, used as an in-game variable.

src/gamescript/C4gamescript - Extensive modification, added many new game engine function to support game.

src/object/C4ObjectMenu.cpp - Added tracking of player choices in conversations.

src/landscape/C4MapScript.cpp - Extensive modifications, added many helper functions to help create map, including integrating a simplex noise function.