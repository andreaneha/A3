#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>

#include"structs.h"
#include"buildLevel.h"
#include"checkChar.h"
#include"fileparse.h"
#include"heroloc.h"
#include"navigate.h"
#include"roomLoc.h"

int drawScreen(struct Rooms * room, int roomNum){
	//initialize screen
	initscr();
	noecho();
	cbreak();
	//declare variables
	int * roomCorner;
	int x;
	int y;
	int i;


	

	//initalize variables
		// roomLoc returns location of topleft corner of the room
	roomCorner = roomLoc(roomNum);
		//this location is where the curser will be set to 
	x = roomCorner[0];
	y = roomCorner[1];
	free(roomCorner);
	move(x,y);
	drawHallways(room, roomNum);



	//draw room walls
	for(i = 0; i <room->width+2; i++)
	{
		move(x,y+i);
		printw("-");
		move(x+room->height+1, y+i);
		printw("-");
	}

	for(i = 1; i<=room->height; i++)
	{
		move(x+i, y);
		printw("|");
		move(x+i, y+room->width+1);
		printw("|");
	}
	
	//draw room floors
	for(i = 0; i<= room->height -1;i++)
	{
		int j;
		for(j = 0; j<= room->width -1; j++)
		{
			move(x+i+1,y+j+1);
			printw(".");
		}
	}
	if(room->numDoors ==0){
		endwin();
		printf("Rooms must have at least one door\n");
		exit(0);
	}
	//place doors
	for(i = 0; i < room->numDoors; i++)
	{

		switch (room->doors[i].wall){
			case 'n':
				if(room->doors[i].position+1 >= room-> width){
					endwin();
					printf("specifications for doors provided in text file fall out of room dimensions\n");
					exit(0);
				}
				move(x,y+room->doors[i].position+1);
				printw("+");
				break;
			case 'e':
				if(room->doors[i].position +1>= room-> height){
					endwin();
					printf("specifications for doors provided in text file fall out of room dimensions\n");
					exit(0);
				}
				move(x+room->doors[i].position +1, y+room->width+1);
				printw("+");
				break;
			case 's':
				if(room->doors[i].position+1 > room-> width){
					endwin();
					printf("specifications for doors provided in text file fall out of room dimensions\n");
					exit(0);
				}
				move(x+room->height+1,y+ room->doors[i].position+1);
				printw("+");
				break;
			case 'w':
				if(room->doors[i].position +1 > room-> height){
					endwin();
					printf("specifications for doors provided in text file fall out of room dimensions\n");
					exit(0);
				}
				move(x+room->doors[i].position +1,y);
				printw("+");
				break;

		}
	}

	//place all other items
	for (i=0;i< room->numOther ; i++)
	{
		move(x + room-> other[i].xlocal +1, y + room-> other[i].ylocal +1);
		printw("%c", room -> other[i].item);

		if(room-> other[i].xlocal +1 > room-> height){
			endwin();
			printf("specifications for items provided in text file fall out of room dimensions");
			exit(0);
		}
		if(room-> other[i].ylocal +1 > room-> width){
			endwin();
			printf("specifications for items provided in text file fall out of room dimensions\n");
			exit(0);
		}
	}

	return 0;
}

int drawHallways(struct Rooms* room, int roomNum){
	// variable Declarations
	int x;
	int y;
	int *roomLocation;
	int maxy;
	int maxx;
	//get size of screen
	getmaxyx(stdscr, maxx, maxy);
	move(maxx, 0);
	// Draw verticle Line
	for(int a=0; a<maxy ; a++){
		move(22, a);
		printw("#");
	}

	roomLocation = roomLoc(roomNum);
	x = roomLocation[0]-1;
	y = roomLocation[1];
	free(roomLocation);
	for(int i=0; i < room->numOther ; i++){
	// for top rooms
	if(roomNum < 3){
	switch (room->doors[i].wall){
		case 'n':
			for(int j = y-1; j <= room->doors[i].position+1+y ; j++){
				move(x, j);
				printw("#");
			}
			for(int j= x; j<=22 ; j++)
			{
				move(j,y-1);
				printw("#");
			}
			break;
		case 'w':
			for(int j = x + room->doors[i].position +2 ; j<=22; j++){
				move(j, y-1);
				printw("#");
			}
			break;
		case 's':
			for(int j = room->height; j<=22; j++){
				move(j,y+room->doors[i].position+1);
				printw("#");
			}
			break;
		case 'e':
			for(int j = room->doors[i].position+3; j<=22;j++){
				move(j, y+room->width+2);
				printw("#");
			}
			break;
	}
	}else{ // bottom rooms
		switch (room->doors[i].wall){
                case 's':
                        for(int j = y-1; j <= room->doors[i].position+1+y ; j++){
                                move(x + room->height +3, j);
                                printw("#");
                        }
                        for(int j= (x + room-> height +3); j>=22 ; j--)
                        {
                                move(j,y-1);
                                printw("#");
                       }
                        break;
                case 'w':
                        for(int j = x + room->doors[i].position +2 ; j>=22; j--){
                                move(j, y-1);
                                printw("#");
                        }
                        break;
                case 'n':
                       break;
                case 'e':
                        for(int j = x + room->doors[i].position+2; j>=22 ; j--){
                                move(j, y+room->width+2);
                                printw("#");
                        }
		break;
		}}
		}

return 0;
}



