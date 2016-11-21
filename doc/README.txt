ASSIGNMENT 3
CIS 2500
ANDREA FERNANDES
0808213

COMPILATION
To compile:
- Open Makefile and ensure that a correct text file path is specified beside ./a.out
- Type make into terminal commandline

USAGE
To play a simple game of rouge. User can navigate around the room pick up items, fight with monsters and walk through hallways. 

TESTING
- enter no text files, or enter too many files
- enter invalid files
- put invalid data in text files
- specify for more that 4 doors
- specify an element that is outside of a room
- make sure all valid specified elements appear correctly
- make sure all monsters are moving around correctly
- make sure health points, number of potions, attack ratings, and inventory items are updated immediately
- walk through doors and enter hallways. Make sure that the hero can not walk on blank spaces
- make sure hero does not walk through walls
- monsters should not walk through walls, or doors
- if hero is in the way of a monsters path, the monster does not move. Only hero can initiate combat event. 
- Monsters can not pass through items, and will continue their patrol normally the cycle after bumping into one. 


KNOWN LIMITATIONS
- can not handle text with files incorrect or missing room dimensions 
- can not handle .txt file paths that do not exist - causes a segmentation fault
- does not check size of window. if the terminal window is too small, the display will be strange
- when walking into a room from a hallway, the last "#" turns into a "."

REFERENCES
Standard C documentation:
http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf

random number generator:
http://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
(only the seeding was copied, this was two lines)

ncurses library documentation:
http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/

Most of the code is directly from my second assignment
