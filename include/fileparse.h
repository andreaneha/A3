#ifndef ___AFERNA06_FILEPARSE__
#define ___AFERNA06_FILEPARSE__

/**
*switchElem
*This function recieves a charecter from the text file and returns the corresponding
* charecter that is to be displayed on the nsurses window as per the spec document
*IN: char elem - the charecter in the text file
*OUT: the corresponding charecter to be displayed
*POST: NA
*ERROR: NA
*/

char switchElem(char elem);

/**
*storeDoors
*any string starting with a d is sent to this function and saved into the struct
*IN: char rawDoor[]- the string directly taken from the txt file
*     doorNum - the door number as per the order in the txt file
*     struct Rooms* rooms - the stuct
*OUT: the location of the door saved in the struct
*POST: the struct has the information from the doors
*ERROR: can not handle strings that are not formatted accordingly
*        d<wall direction><positions away from corner>
*/

struct Rooms* storeDoors(char rawDoor[], int doorNum, struct Rooms* room);
/**
*roomDimensions
*first string from text file is sent here.The function converts the 
*string and saves the information info the struct
*IN: char rawDim[]- the string directly taken from the txt file
*     struct Rooms* rooms - the stuct
*OUT: the room dimensions saved in the stuct
*POST: the struct has the information from the doors
*ERROR: can not handle strings that are not formatted accordingly
*        <height>X<width>
*/
struct Rooms* roomDimensions(char rawDim[], struct Rooms * room);

/**
*handleItems
*all items that are not doors or room dimensions are sent here. The function
*corverts the string and saves it into the struct
*IN: char itemLoc[] - the string from the text file
*     itemNum- the order that the item appears in the text file line
*     struct Rooms * room - the struct it will be saved in
*OUT: the struct with items saved in it
*POST: the struct has the information from the doors
*ERROR: can not handle strings that are not formatted accordingly
*        <char><xposition>,<yposition>
*/
struct Rooms* handleItems(char itemLoc[],int itemNum, struct Rooms*room);

/**
*fileParse
*This function recieves a file, opens it and saves the information in a struct. 
*IN: char [] filename - this is the path to the text file that is to be parsed
*OUT: returns a pointer to an array of structs. 
*POST: the program recieves information in the for of an array of structs. 
*   note, this array is dynamic memory that must be freed
*ERROR: NA
*/

struct Rooms ** fileParse(char filename[], int numRooms);

#endif
