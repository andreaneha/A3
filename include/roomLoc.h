#ifndef ___AFERNA06_ROOMLOC__
#define ___AFERNA06_ROOMLOC__


/**
*roomLoc
*This function returns the co-ordinates of the top corner of the specified room. 
*IN: int roomNumber - the room that is to be located.
*OUT: returns the co-ordinates of the top corner of the specified room.
*POST: memory allocated during the operation of this function must be freed
*ERROR: exist entire program if roomNumber is out of bounds
*/

int * roomLoc(int roomNumber);

#endif
