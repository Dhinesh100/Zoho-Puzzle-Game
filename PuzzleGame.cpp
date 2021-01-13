#include<iostream>
#include<conio.h>
#include <unistd.h>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

int** shuffle(int);
int** easy(int**, int);
int** play(int**, int);
int display(int**, int);
boolean isCompleted(int**, int);
int** moveUp(int**, int, int);
int** moveDown(int**, int, int);
int** moveLeft(int**, int, int);
int** moveRight(int**, int, int);
int** move(int**, int, int, int, int, int);
int** undo(int**, int, int);

struct Puzzle
{
	int SpaceRow;
	int SpaceColumn;
	int StepCount;
	int UserStack[10000];
} puzzle;

void gotoxy (int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;											// Used to display welcome screen at the center of console
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}

int main()
{
	gotoxy(40, 13);
	
	char *w = "Hey there! Can you solve the puzzle :)";
	
	for(int iter = 0; iter<38; iter++)
	{
		cout<<w[iter];
		usleep(100000);
	}
	
	usleep(999999);
	
	system("cls");
	
	int size;
	
	cout<<"\nEnter the box size of the box: ";
	cin>>size;
	
	int **box;
	
	box = shuffle(size);
	
	box = play(box, size);

	return 0;
}

int** shuffle(int size)
{
	int count = 1;
	
	int** box = new int*[size];
	
	puzzle.SpaceRow = size-1;									// Shuffles the box before letting user to play
	puzzle.SpaceColumn = size-1;
	
	for(int row=0; row<size; row++)
	{
		box[row] = new int[size];
		for(int column=0; column<size; column++)
		{
			if(row == size-1 && column == size-1)
			{
				box[row][column] = 0;
				break;
			}
			box[row][column] = count++;
		}
	}
	
	box = easy(box, size);
	
	return box;
}

int** easy(int** box, int size)											// Just few amount of shuffles to make the game easier
{	
	for(int shuffle=0; shuffle<20*size; shuffle++)
	{
		int swap = rand() % 4;
		
		if(!((swap == 1 && puzzle.SpaceRow-1 < 0) || (swap == 0 && puzzle.SpaceRow+1 == size) || (swap == 3 && puzzle.SpaceColumn-1 < 0) || (swap == 2 && puzzle.SpaceColumn+1 == size)))
		{
			switch(swap)
			{
				case 0:
					box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow+1, puzzle.SpaceColumn);
					puzzle.SpaceRow++;
		            break;
		            
		        case 1:
		        	box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow-1, puzzle.SpaceColumn);
		        	puzzle.SpaceRow--;
		            break;
		            
		        case 2:
		        	box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow, puzzle.SpaceColumn+1);
		        	puzzle.SpaceColumn++;
		            break;
		            
		        case 3:
		        	box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow, puzzle.SpaceColumn-1);
		        	puzzle.SpaceColumn--;
		            break;
			}	
		}
	}
	
	return box;
}

int** play(int** box, int size)									// Gets keyboard input from user in order to work on the desired commands
{
	cout<<"\nSteps: "<<puzzle.StepCount<<"\t"<<"Undo: U | Reset: R | Exit: E\n\n";
	
	display(box, size);
	
	if(isCompleted(box, size))
	{
		system("cls");
		cout<<"\n\n";
		display(box, size);
		cout<<"\nNumber of steps taken to complete the puzzle: "<<puzzle.StepCount;
		exit(0);
	}
	
	cout<<"Use arrow keys to provide your input";
	cout<<"\n====================================\n";
	
	static int top = 0;
	
	int key = getch();
	
	if(key == 224)
	{
		switch(getch())
		{
	        case KEY_UP:
	            box = moveUp(box, size, top);
	            top++;
	            play(box, size);
	            
	        case KEY_DOWN:
	            box = moveDown(box, size, top);
	            top++;
	            play(box, size);
	            
	        case KEY_LEFT:
	            box = moveLeft(box, size, top);
	            top++;
	            play(box, size);
	            
	        case KEY_RIGHT:
	            box = moveRight(box, size, top);
	            top++;
	            play(box, size);
        }
	}
	else if(key == 117)
	{
		box = undo(box, top, size);
		top--;
		play(box, size);
	}
	else if(key == 114)
	{
		box = shuffle(size);
		puzzle.StepCount = 0;
		cout<<"\nResetting...";
		usleep(999999);
		system("cls");
		cout<<"\n\n";
		play(box, size);
	}
	else if(101)
	{
		system("cls");
		cout<<"Looking forward to see you again! Good Bye :)";
		usleep(999999);
		exit(0);
	}
	else
	{
		Beep(900,1000);
		cout<<"\nPress a valid arrow key!";
		usleep(999999);
		cout<<"\nWait...";
		usleep(999999);
		system("cls");
		cout<<"\n\n";
		play(box, size);
	}
	
	return box;
}

int display(int** box, int size)										// Display the puzzle to the user
{	
	for(int border=0; border<size; border++)
	{
		cout<<"********";	
	}
	
	cout<<"*";
	
	cout<<"\n";
	
	for(int row=0; row<size; row++)
	{
		for(int column=0; column<size; column++)
		{
			if(box[row][column] == 0)
			{
				cout<<"| ";
				cout<<"\t";
				
				if(column == size-1)
				{
					cout<<"*";
				}
				
				continue;
			}
			
			if(column == 0)
			{
				cout<<"* ";
			}
			else
			{
				cout<<"| ";
			}
			
			cout<<box[row][column];
			
			if(box[row][column]/10 == 0)
			{
				cout<<" ";
			}
			
			cout<<"\t";
			
			if(column == size-1)
			{
				cout<<"*";
			}
		}
		cout<<"\n";
	}
	
	for(int border=0; border<size; border++)
	{
		cout<<"********";	
	}
	
	cout<<"*";
	
	cout<<"\n\n";
	
	return 0;
}

boolean isCompleted(int** box, int size)										// Checks if the puzzle is completed
{
	int element = 1;
	
	for(int row=0; row<size; row++)
	{
		for(int column=0; column<size; column++)
		{
			if(box[row][column] != element%(size*size))
			{
				return false;
			}
			
			element++;
		}
	}
	
	return true;
}

int** moveDown(int** box, int size, int top)								// Helps in moving the piece downward
{
	if(puzzle.SpaceRow-1 < 0)
	{
		Beep(900,1000);
		usleep(999999);
		system("cls");
		cout<<"\n\n";
		play(box, size);
		return box;
	}
	
	box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow-1, puzzle.SpaceColumn);
	puzzle.SpaceRow--;
	
	puzzle.UserStack[top] = 1;
	
	cout<<"Please Wait...";
	usleep(999999);
	system("cls");
	cout<<"\n\n";
	
	puzzle.StepCount++;
	
	return box;
}

int** moveUp(int** box, int size, int top)									// Helps in moving the piece upwards
{
	if(puzzle.SpaceRow+1 == size)
	{
		Beep(900,1000);
		usleep(999999);
		system("cls");
		cout<<"\n\n";
		play(box, size);
		return box;
	}
	
	box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow+1, puzzle.SpaceColumn);
	puzzle.SpaceRow++;
	
	puzzle.UserStack[top] = 0;
	
	cout<<"Please Wait...";
	usleep(999999);
	system("cls");
	cout<<"\n\n";
	
	puzzle.StepCount++;
	
	return box;
}

int** moveRight(int** box, int size, int top)									// Helps in moving the piece rightwards
{
	if(puzzle.SpaceColumn-1 < 0)
	{
		Beep(900,1000);
		usleep(999999);
		system("cls");
		cout<<"\n\n";
		play(box, size);
		return box;
	}
	
	box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow, puzzle.SpaceColumn-1);
	puzzle.SpaceColumn--;
	
	puzzle.UserStack[top] = 2;
	
	cout<<"Please Wait...";
	usleep(999999);
	system("cls");
	cout<<"\n\n";
	
	puzzle.StepCount++;
	
	return box;
}

int** moveLeft(int** box, int size, int top)								// Helps in moving the piece leftward
{
	if(puzzle.SpaceColumn+1 == size)
	{
		Beep(900,1000);
		usleep(999999);
		system("cls");
		cout<<"\n\n";
		play(box, size);
		return box;
	}
	
	box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow, puzzle.SpaceColumn+1);
	puzzle.SpaceColumn++;
	
	puzzle.UserStack[top] = 3;
	
	cout<<"Please Wait...";
	usleep(999999);
	system("cls");
	cout<<"\n\n";
	
	puzzle.StepCount++;
	
	return box;
}

int** move(int** box, int size, int srow, int scol, int vrow, int vcol)						// Used to swap the space and the number
{
	box[vrow][vcol] += box[srow][scol];
	box[srow][scol] = box[vrow][vcol] - box[srow][scol];
	box[vrow][vcol] = box[vrow][vcol] - box[srow][scol];
	
	return box;
}

int** undo(int** box, int top, int size)								// Used to perform undo operation and go back to previous state
{
	if(top == 0)
	{
		Beep(900,1000);
		cout<<"\nCannot undo further!";
		usleep(999999);
		cout<<"\nWait...";
		usleep(999999);
		system("cls");
		cout<<"\n\n";
		return box;
	}
	
	switch(puzzle.UserStack[top-1])
	{
		case 0:
			box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow-1, puzzle.SpaceColumn);
			puzzle.SpaceRow--;
			puzzle.UserStack[top-1] = puzzle.UserStack[top];
			cout<<"Please Wait...";
			usleep(999999);
			system("cls");
			cout<<"\n\n";
			puzzle.StepCount--;
			return box;
	
		case 1:
			box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow+1, puzzle.SpaceColumn);
			puzzle.SpaceRow++;
			puzzle.UserStack[top-1] = puzzle.UserStack[top];
			cout<<"Please Wait...";
			usleep(999999);
			system("cls");
			cout<<"\n\n";
			puzzle.StepCount--;
			return box;
	
		case 2:
			box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow, puzzle.SpaceColumn+1);
			puzzle.SpaceColumn++;
			puzzle.UserStack[top-1] = puzzle.UserStack[top];
			cout<<"Please Wait...";
			usleep(999999);
			system("cls");
			cout<<"\n\n";
			puzzle.StepCount--;
			return box;
			
		case 3:
			box = move(box, size, puzzle.SpaceRow, puzzle.SpaceColumn, puzzle.SpaceRow, puzzle.SpaceColumn-1);
			puzzle.SpaceColumn--;
			puzzle.UserStack[top-1] = puzzle.UserStack[top];
			cout<<"Please Wait...";
			usleep(999999);
			system("cls");
			cout<<"\n\n";
			puzzle.StepCount--;
			return box;
	}
}
