/**
 * main
 * Counts the number of lines in the textfile. Sends the textfile to the parsing functions. 
 * Recieves information from the file from a struct type double pointer. Then sends each 
 * struct from the struct array to be drawn on the terminal window. Then calls the function
 * actually allows the user to play the level
 * IN: a .txt file
 * OUT: returns 0
 * POST: NA
 * ERROR: NA
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ncurses.h>
#include"structs.h"
#include"buildLevel.h"
#include"checkChar.h"
#include"fileparse.h"
#include"heroloc.h"
#include"navigate.h"
#include"roomLoc.h"


int main(int argC, char * argV[])
{
	//variables used for function main
	char line[150];
	int roomNum = 0;
	int i;
//	char * input;
	FILE* levelInfo;
	struct Rooms ** aRoom;
	int *heroLoc;
	int filenameSize;
	char *fileExtension;
	int checkFile;

	// check input
	if (argC!=2)
	{
		printf("specify 1 .txt file\n");
		exit(0);
	}
	filenameSize = strlen(argV[1]);
	fileExtension = &argV[1][filenameSize - 4];
	checkFile=strcmp(fileExtension,".txt");
	if (checkFile !=0){
		printf("please enter a valid .txt file\n");
		exit(0);
	}


	// count the number of lines in the text file
	levelInfo = fopen(argV[1], "rt");
	while(fgets(line,1000,levelInfo) != NULL)
	{
		roomNum ++;
	}
	fclose(levelInfo);
	if (roomNum>6)
	{
		printf("please use a text file with only 6 rooms defined\n");
		exit(0);
	}

	//send textfile to file parse store information in an array of structs
	//aRoom points to the allway of structs
	aRoom = fileParse(argV[1], roomNum);


	//draws screen room by room
	for(i=0; i<roomNum;i++)
	{
		drawScreen(aRoom[i],i);
	}


	//find hero
	heroLoc = locateHero(aRoom, roomNum);

	//this is the function that interacts and responds to user
	play(heroLoc, roomNum, aRoom);
	free(heroLoc);

	for(i=0; i<roomNum ; i++)
	{
		free(aRoom[i]);

	}
	free(aRoom);
	//end function
	endwin();

	return 0;


}
