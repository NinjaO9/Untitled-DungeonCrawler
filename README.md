# Untitled-DungeonCrawler
Collaborative assignment for CPTS 122 PA9 - WSU Spring '25

# Detailed Description

This program acts as something like a playtest for a dungeon crawler built in SFML.
Additionally, the program includes an easy way to modify textues and levels, with users being able to create levels and implement textures through the use of a text file.

# How to play

Directional Movement - W,A,S,D (Up,Left,Down,Right)

Attack - Space

# Level Editing guide

Want to make your own level?

- Create a textfile, and name it whatever you want (For example; myLevel.txt) (Make sure the file is in the scope of the project)
- Build a level based off of these symbols:
      **=** - Wall
      **E** - Enemy Spawn
      **S** - Player Spawn
        *   - Exit/Next level tile
  - Additionally, go to the text file level that will be played before your level and add on line 1:
        goto-{your level name}
  - This will tell the level that the next level is your level; for example:
        goto-myLevel.txt
      will cause the current level to switch to 'myLevel.txt' once the current level is completed (exit tile touched)

# Texture adding guide
Want to edit textures?

- Add your image file within the scope of the project
- Go inside of textures.txt and read the comments at the top of the file
- Either add, or replace a texture within the file
- Done!

# Running Test Cases
As per the requirement, there are 5 test cases (0-4)

In order to turn on DEBUG_MODE, go to line 10 in main.cpp and switch the vairiable 'false' to 'true' (or vise-versa to turn it off)

Below (in line 11), there will be a variable that defines the test case that will be played out, wihtin a range of 0-4 being valid numbers.

After adjusting the values to the settings you want, launch the program and then the proper test case will play out.

## Collaborator Names & Lab Sections
David Montes (NinjaO9) - Lab Section 10

Jamie Scott (mrthomaslibrary)- Lab Section 1

Sage Emberlin (Emberlin01)- Lab Section 6

Cody Ray (Cobalt66-exe)- Lab Section 12
