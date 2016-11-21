#ifndef ___AFERNA06_STRUCTS__
#define ___AFERNA06_STRUCTS__

typedef struct Inventory{
	char type;
	int stat;
}Inventory;

typedef struct Monsters{
	char type;
	int healthPoints;
	int attackRating;
	int roomNumber;
	int speed;
	int xPos;
	int yPos;
}Monsters;


typedef struct Rooms{
	int height;
	int width;
	int numDoors;
	struct Doors{
        	char wall;
        	int position;
	}doors[4];
	int numOther;
	struct Other{
		char item;
		int xlocal;
		int ylocal;
		int stat;
	}other[10];
	int numMonsters;

}Room;

#endif
