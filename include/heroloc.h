#ifndef ___AFERNA06_LOCATEHERO__
#define ___AFERNA06_LOCATEHERO__


/**
*heroLoc
*This function returns the location of the hero, and the room which it exists 
*IN: int numRooms - the total number of rooms. 
*	struct Rooms ** aRoom - the struct that the function will be searching in
*OUT: This function returns the location of the hero, and the room which it exists 
*POST: memory allocated during the operation of this function must be freed
*ERROR: exits entire program if numRooms is out of bounds
*/

int *locateHero(struct Rooms ** aRoom, int numRooms);

#endif
