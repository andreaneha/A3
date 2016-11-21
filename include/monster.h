#ifndef ___AFERNA06_MONSTER__
#define ___AFERNA06_MONSTER__


/**
*CountMonsters
*This function recieves a struct and counts the number of Monsters present.
*IN: struct Rooms* room - this is the struct that searched
*	int room number - this number will specify how many rooms will be searched
*OUT: returns the number of monsters present in the struct
*POST: NA
*ERROR: NA
*/

int countMonsters(struct Rooms**rooms, int numRooms);

/**
*Patrol
*This function controls the movement pattern of all monsters every cycle.
*IN: struct Monsters-this is the struct that the monsters are saved in.
*	int cycle - this is the number of times the user has pressed a key
*	int numMonsters - this is the number of monsters in the array of structs
*OUT: returns 0
*POST: a room specified by a line in the textfile will be build in the terminal window
*ERROR: NA
*/

int patrol(struct Monsters ** monster, int cycle, int numMonsters);
/**
*combat
*This function is envoked when the hero bumps into a monster. This function determins the 
*outcome of the encounter
*IN: struct Monster ** monster - the struct of monsters that hold the information for each monster
*	int monsterID - identifies the monster that will be in combat 
*OUT: returns a 0 if the hero attacks, or a number to reduce the hero's HP or AR by
*POST: NA
*ERROR: NA
*/

int combat(struct Monsters ** monster, int monsterID);
/**
*monsterID
*This function recieves a struct and searched the struct to find the index of a 
*specific monster, given by the position
*IN: struct Monsters** monster -  the struct that will searched
*	int numMons - the number of Monsters in the struct
*	int xPos - the x position of the monster being searched for
*	int yPos - the y position of the monster being searched for
*OUT: returns the index of the monster
*POST: NA
*ERROR: NA
*/

int monsterID(struct Monsters ** monster, int numMons, int xPos, int yPos);

#endif
