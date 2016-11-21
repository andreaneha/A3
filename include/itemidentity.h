#ifndef ___AFERNA06_ITEMIDENTITY__
#define ___AFERNA06_ITEMIDENTITY__


/**
*itemID
*This function recieves a struct and the total number of rooms. Then it checks where
*the curser currently is and returns the location of that item within the array of structs
*IN: struct Rooms* room - this is the struct that will be built
*	int room number - To tell the program how many structs to look through
*OUT: an array in the form of <room.index>, <other.index> where room and other are structs. 
*POST: all function calls use dynamic memory and must be freed
*ERROR: NA
*/

int * itemID(struct Rooms ** room, int numRooms);

#endif




