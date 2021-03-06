
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include"structs.h"
#include<time.h>
#include"structs.h"
#include"buildLevel.h"
#include"checkChar.h"
#include"fileparse.h"
#include"heroloc.h"
#include"navigate.h"
#include"roomLoc.h"
#include"monster.h"
#include"monsterstruct.h"
#include"itemidentity.h"



int play(int * heroLoc,int numRooms, struct Rooms ** room)
{
	int currentRoom;
	int * roomLocation;
	int x;
	int goldPoints;
	int potionCount;
	int y;
	int xoffset;
	int yoffset;
	char input;
	int cycle;
	Monsters ** monsters;
	int numMonsters;
	Inventory ** inventory;
	int inventoryCount;
	int heroHealth;
	int attackRating;
	int maxx;
	int maxy;
	getmaxyx(stdscr, maxx, maxy);
	move(0,maxy);




	inventory = (Inventory ** )malloc(5*sizeof(Inventory*));
        if (inventory == NULL)
        {
                printf("out of memory\n");
                exit(1);
        }

	for(int a = 0; a<5 ; a++){
		inventory[a] = (Inventory*)malloc(sizeof(Inventory));
		if (inventory[a] == NULL)
        		{
	                	printf("out of memory\n");
                		exit(1);
        		}

	}

	inventoryCount =0;
	numMonsters = countMonsters(room, numRooms);
	cycle = 0;
	monsters = monsterStruct(numRooms, room);
	currentRoom = heroLoc[2];
	roomLocation = roomLoc(currentRoom);
	x = roomLocation[0];
	y = roomLocation[1];
	free(roomLocation);
	xoffset = heroLoc[0]+1;
	yoffset = heroLoc[1]+1;
	x = x+xoffset;
	y = y+yoffset;
	mvaddch(x,y,'@');
	goldPoints=0;
	potionCount=1;
	attackRating = 5;
	heroHealth = 50;

	while (input!='q')
	{	

		int *itemIdentity;
		time_t t;
		char charCheck;
		int monsIdentity;
		xoffset = 0;
		yoffset = 0;
		input = getch();
		char check;
		int attack;
		switch(input){
			case ('w'):
				xoffset-=1;
				break;
			case('a'):
				yoffset-=1;
				break;
			case('d'):
				yoffset+=1;
				break;
			case('s'):
				xoffset+=1;
				break;
			case('p'):
				if(potionCount > 0){
					potionCount = potionCount-1;
					heroHealth = 50;
					move(0,0);
					clrtoeol();
					printw("Hero recovered full health");
				}
				else{
					move(0,0);
					clrtoeol();
					printw("Out of Potions");
				}
				break;
			default:
				break;
		}
		if (input!='q'){
		charCheck = mvinch(x+xoffset,y+yoffset);

		switch(charCheck)
		{
                	case('<'):
                        	input = 'q';
	                        break;
        	        case('>'):
                	        input = 'q';
                        	break;
			case('!'):
				potionCount++;
                                mvaddch(x,y,'.');
                                x = x+xoffset;
                                y = y+yoffset;
                                mvaddch(x,y,'@');
				break;
	                case('*'):
				srand((unsigned) time(&t));
        	                goldPoints = goldPoints + rand() % 51;
                                mvaddch(x,y,'.');
                                x = x+xoffset;
                                y = y+yoffset;
                                mvaddch(x,y,'@');
				break;
	                case('8'):
				srand((unsigned) time(&t));
        	                goldPoints = goldPoints + 50 + rand() % 201;
                       		mvaddch(x,y,'.');
                       		x = x+xoffset;
                       		y = y+yoffset;
                       		mvaddch(x,y,'@');
                	        break;
	                case('|'):
				move(x,y);
                	       break;
	                case('-'):
				move(x,y);
                	        break;
	                case('A'):
				move(x,y);
				monsIdentity = monsterID(monsters, numMonsters, x+xoffset, y+yoffset);
				attack = combat(monsters, monsIdentity);
				attackRating = attackRating - attack;
				if (attackRating<=0){
					attackRating = 0;
				}
                	        break;
	                case('T'):
				move(x,y);
				monsIdentity = monsterID(monsters, numMonsters, x+xoffset, y+yoffset);
				attack = combat(monsters, monsIdentity);
				heroHealth = heroHealth - attack;
				if (heroHealth<=0){
					input = 'q' ;
				}
                	       break;
	                case('B'):
        	                move(x,y);
				monsIdentity = monsterID(monsters, numMonsters, x+xoffset, y+yoffset);
				combat(monsters, monsIdentity);
				attack = combat(monsters, monsIdentity);
				heroHealth = heroHealth - attack;
				if (heroHealth<=0){
					input = 'q' ;
				}
                	        break;
	                case('S'):
        	                move(x,y);
				attack = combat(monsters, monsIdentity);
				heroHealth = heroHealth - attack;
				if (heroHealth<=0){
					input = 'q' ;
				}
				break;
	                case('Z'):
        	                move(x,y);
				monsIdentity = monsterID(monsters, numMonsters, x+xoffset, y+yoffset);
				attack = combat(monsters, monsIdentity);
				heroHealth = heroHealth - attack;
				if (heroHealth<=0){
					input = 'q' ;
				}
                	        break;
	                case('+'):
		                mvaddch(x,y,'.');
                       		x = x+xoffset;
                       		y = y+yoffset;
                       		mvaddch(x,y,'+');
				move(0,0);
				clrtoeol();
				printw("Hero opened a door");
			case('#'):
				check =mvinch(x,y);
				if(check =='+'){
					mvaddch(x,y,'+');
				}else {
					mvaddch(x,y,'#');
				} 
               			x = x+xoffset;
                       		y = y+yoffset;
                       		mvaddch(x,y,'@');

				break;
			case(']'):
					move(0,0);
					clrtoeol();
                        		mvaddch(x,y,'.');
                        		x = x+xoffset;
                        		y = y+yoffset;
                        		mvaddch(x,y,'@');
					if(inventoryCount<5){
						inventory[inventoryCount] = (Inventory*)malloc(sizeof(Inventory));
						itemIdentity = itemID(room,numRooms);
						move(0,0);
						inventory[inventoryCount]-> type = ']';
						inventory[inventoryCount]-> stat = room[itemIdentity[0]]-> other[itemIdentity[1]].stat;
						printw("Hero picked up '[' item");
						inventoryCount++;
					} else {
						move(0,0);
						printw("Hero stepped on '[' item, and broke it");
					}
					break;
			case(')'):
					move(0,0);
					clrtoeol();
                        		mvaddch(x,y,'.');
                        		x = x+xoffset;
                        		y = y+yoffset;
                        		mvaddch(x,y,'@');
					if(inventoryCount<5){
						itemIdentity = itemID(room,numRooms);
						move(0,0);
						inventory[inventoryCount]-> type = ')';
						inventory[inventoryCount]-> stat = room[itemIdentity[0]]-> other[itemIdentity[1]].stat;
						printw("Hero picked up ')' item");
						inventoryCount++;
					} else {
						move(0,0);
						printw("Hero stepped on ')' item, and broke it");
					}
					break;
				case('('):
					move(0,0);
					clrtoeol();
                        		mvaddch(x,y,'.');
                        		x = x+xoffset;
                        		y = y+yoffset;
                        		mvaddch(x,y,'@');
					if(inventoryCount<5){
						itemIdentity = itemID(room,numRooms);
						move(0,0);
						inventory[inventoryCount]-> type = '(';
						inventory[inventoryCount]-> stat = room[itemIdentity[0]]-> other[itemIdentity[1]].stat;
						printw("Hero picked up '(' item");
						inventoryCount++;
					} else {
						move(0,0);
						printw("Hero stepped on '(' item, and broke it");
					}
					break;
//

				case('.'):
                        		mvaddch(x,y,'.');
                        		x = x+xoffset;
                        		y = y+yoffset;
                        		mvaddch(x,y,'@');
					break;
				default:
					mvaddch(x,y,'@');
					break;
			}

			patrol(monsters, cycle, numMonsters);
			cycle++;
			move(maxx-1, 0);
			printw("Health: %d", heroHealth);
			move(maxx-1, 20);
			printw("Potions: %d", potionCount);
			move(maxx-1, 40);
			printw("Attack: %d", attackRating);
			move(maxx-1, 60);
			printw("Inv: %d/5", inventoryCount);




		}

	}
	clear();
	move(0,0);
	printw("Your gold count is %d\n",goldPoints);
	move(2,0);
	printw("You have %d Potion(s)", potionCount);
	move(4,0);
	printw("Inventory\n");
	for(int b=0 ; b < inventoryCount ; b++){
		if(inventory[b]-> type == ']'){
			printw("%c: %d Defence\n", inventory[b]->type, inventory[b]->stat);
		}else{
			printw("%c: %d Attack\n", inventory[b]->type, inventory[b]->stat);
		}


	}

	move(12,0);

	printw("press enter to close window\n");
	getch();
	endwin();

	

	for(int a = 0; a<5 ; a++){
		free(inventory[a]);
	}
	free(inventory);

	return 0;
}

