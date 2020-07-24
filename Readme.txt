---------------------------------------------------------Game Description-----------------------------------------------------------------

Once there was a fox who likes berries, but eagles and dragons were his enemies.
Help the fox in this game to get the berries.

Goal is to avoid the enemies and collect the berries.

There are 3 levels in the game. In each level the enemies speed will be increased and fox have to collect more berries when moved to new level.

Initially fox has 5 lives. If all the lives are gone then game over.

---------------------------------------------------------How to Play----------------------------------------------------------------------

'Right Arrow' - To move fox forward
'Left Arrow' - To move fox backward
'Up Arrow' - To jump the fox
'H' - To see help screen
'Escape' - To pause the game

--------------------------------------------------------Game Navigation Walkthrough-------------------------------------------------------


1) On Starting the Game - Landing page will be displayed with below options:

'Escape' to exit the Game
'Enter' to continue to Game Menu Screen
'Left/Right' Mouse click to continue to Game Menu Screen

2) Game Introduction screen
Introduction about the game.

'Space' to continue

3) If user is on Game Menu Screen, below options are available:

'N' for New Game
'R' for Resume Game
'H' for Help page
'C' for Credits page
'E' for Exit the Game

Mouse click will also work on this screen.


4) If user is on Help page, below option is available:

'Escape' to go back to Game Menu Screen


5) If user is on Credits page, below option is available:

'Escape' to go back to Game Menu Screen


6) If user is playing a game, below options are available:

'Right arrow' to move forward
'Left arrow' to move backward
'Up arrow' to jump upward
'Escape' to pause the game


6) If user paused the game, below options are available:

'R' to continue playing the Game
'H' for Help page
'M' for Game Menu Screen
'Escape' to continue playing the Game

Mouse click will also work on this screen.

Note: At any time user can press 'End' button to forcefully close the game.

-----------------------------------------------------Group Info: with member contribution-------------------------------------------------

Group Name: Fantastic 4

Group Members: 
Karan Saini
Nikita Arora
Rajeswari Cherupillil Eravi
Karan Kalyan Goudagere Kariyappa

Member Contribution:

Karan Saini:
Designed all the pages for the game and implemented the navigation from these pages.

Also implemented transition logic of the levels with Nikita Arora.

Nikita Arora:
Contributed for designing some pages.

Designed layout for the levels and transition from one level to another.

Rajeswari Cherupillil Eravi:
Implemented Linear collision for checking collision with items, enemies and platform/ground. 
Worked to implement Sound as well.

Karan Kalyan Goudagere Kariyappa:
Used sprite sheets for player and enemies. Reading the sprite sheet and used it correctly. 
Worked to implement Sound as well.

Overall its a combined effort from all of us!

--------------------------------------------------Coding Approach------------------------------------------------------------------------

--------------------------------------------------Approach for adding the pages in the game----------------------------------------------


1) Added new class for each of the page

_landingPage
_intro
_gameMenu
_helpPage
_credits
_pause
_endPage

2) Scroll functionality for Landing and Credits page

Stars are scrolling on Landing page
Credits Name are scrolling on Credits page


3) Maintain a flag for each screen so that by giving input correct screen is displayed to user

Flag = 0 - Landing page
Flag = 1 - Game Menu Screen
Flag = 2 - Help page
Flag = 3 - Playing Game
Flag = 4 - Pause page
Flag = 5 - Credits page
Flag = 6 - End win page
Flag = 7 - End lose page
Flag = 8 - Introduction page

4) Added functions in _inputs.h for these pages

  void keyPressed(_level *, _player *);  //player handling
  void keyPressed(_landingPage *);       //input handling for landing page
  void keyPressed(_intro *);             //input handling for introduction page
  void keyPressed(_gameMenu *, ...);     //input handling for game menu page
  void keyPressed(_helpPage *);          //input handling for help page
  void keyPressed(_pause *);             //input handling for pause page
  void keyPressed(_credits *);	         //input handling for credits page
  void keyPressed(_endPage *);           //input handling for end page
  void mouseEventDown(_landingPage *);   //handling mouse clicks for landing page
  void mouseEventDown(_gameMenu *, ...); //handling mouse clicks for game menu page
  void mouseEventDown(_pause *, ...);    //handling mouse clicks for pause page
  void mouseEventDown(_endPage *, ...);  //handling mouse clicks for end page


5) In _inputs.cpp defining these functions according to key pressed and updating the flag value to go to next screen
   And making keys working on the specific screen only. For ex. 'N' will work on Game Menu Screen only


6) In _glScene.cpp, creating pointer to these classes and loading image files for the screen
   Drawing the scene according to the flag value
   Calling functions from _inputs.h so that keys/mouse clicks works for the screens

------------------------------------------Approach for checking collision and creating levels--------------------------------------------

Added new class 
_level

Define the layout of the level
Like platform, items, lives, scores and 3 enemies

Detecting 3 collisions with ground/platform, items and enemies
Using Linear collision to detect

-----------------------------------------------Approach for adding sounds in game--------------------------------------------------------

For Sounds

Added new class
_sounds

used irrklang lib for sounds