#ifndef ___AFERNA06_MONSTERSTRUCT__
#define ___AFERNA06_MONSTERSTRUCT__


/**
*monsterStruct
*This function takes all the monster elements from the room struct and saves them into 
*another struct.
*IN: struct Rooms**room - this struct is passed to the function
*	int numRooms - this is the number of rooms to be searched
*OUT: returns a dynamically allocated struct
*POST: the struct that created by this funtion is dynamically allocated and must be freed
*ERROR: NA
*/

struct Monsters ** monsterStruct(int numRooms, struct Rooms ** room);

#endif
