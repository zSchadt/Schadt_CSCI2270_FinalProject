# Schadt_CSCI2270_FinalProject

PASE 1 REQUIREMENT:

I will make a role playing figher game. I am not yet sure of what theme I will choose, but the game will have various levels with a combat system of its own.
I will use graphs as my data structure. Each node in the graph will be a different level with a different difficulty etc. 
I may also implement a linked list as a way of storing certain character traits, but am not completely sure as I have not yet started the code.


PHASE 2 REQUIREMENTS:

Summary:
My game is called "The End". It is a role-playing fighter game where the user can choose to visit, and fight in various towns. You can earn more gold by defeating enemies and clearing a town (no enemies left). The game is never the same, each time the program is run, all of the cities are assigned random locations with different connecting cites and different difficulties. All of the monsters are randomly created as well. Certain limitations were put on the creation of new monsters to keep 'in-game power' reasonable. The difficulty of a town corresponds to how many enemies are there and the reward upon completion of the level.

How to Run:
After completing the introductory steps (your name and character type) you will be presented with a menu that gives you six options:
1. Fight
2. Heal
3. Store
4. Travel
5. Game Statistics
6. Quit
If the user selects the fight option, a short battle will occur where the user will not have control over their characters fighting. Damage is directly related to your characters strength stat. If you lose the battle, you will die and only respawn if you have 100 gold or more (death fee). Your health is not reset after every fight, the user should heal themselves before entering new fights (healing is cheaper than the death fee). If you win a fight, you will be given gold for defeating the enemy and also have the option to take the enemy's item (if they had one). Taking an item will give your character the stats of that item but also take up one inventory space (6 inventory spaces total). Going to the store allows users to buy damage and health enchantments, these enchantments are expensive because they give permanent stats to your character without taking up inventory space. Selecting travel gives the user to travel to all adjacent cities to their current location, or 'fast travel' to any previously visited city (fast travel costs 10 gold). Selecting the Game Statistics option will give the user an overview of what their current situation is; this option pretty much lists all of your stats. And quitting will simply quit, no data is saved.

Dependencies:
This program requires three different text files to run:
1. weapons.txt
2. towns.txt
3. monsterNames.txt

System Requirements:
its c++ code, and computer with a proper compiler can run.
I know for a fact that the files compile and run on Linux.

Group Members:
None

Contributers: 
None

Open Issues and Bugs:
I haven't done any input checking to make sure that the file wont crash if for example the user inputs a character value when I wanted an integer.
Also, I have not done any gold, health or damage balancing. At the moment, the user can become much stronger than they enemy monsters with ease.
Other than that, I have not found any bugs within the project.
