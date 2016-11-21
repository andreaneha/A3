#ifndef ___AFERNA06_NAVIGATE__
#define ___AFERNA06_NAVIGATE__


/**
*play
*This function is the function that the user interacts with. It takes in the input
*from the user and responds accordingly.
*IN: struct Rooms* room - this struct is passed to the function so that it knows the
*          location of all of the doors.
*OUT: returns 0.
*POST: this function exists when the user presses q or steps over < or > charecter
*ERROR: teleporting from door to door causes the top left corner wall to change into
*     a period.
*/

int play(int * heroLoc,int numRooms, struct Rooms ** room);

#endif
