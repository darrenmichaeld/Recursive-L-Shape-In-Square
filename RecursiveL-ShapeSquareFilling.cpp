#include <iostream>
using namespace std;

// Constants in global scope
const int MAX_WIDTH = 8;
const int LOCATEQUADRANT_NOT_IMPLEMENTED = 0;

int locateQuadrant(int width, int x, int y)
{
	if(x<width/2 && y <width/2)
		{
			return 1;
		}
	else if(x >= width/2 && y < width/2)
		{
			return 2;
		}
	else if(x >= width/2 && y >= width/2)
		{
			return 3;
		}
	else if(x < width/2 && y >= width/2)
		{
			return 4;
		}
	return LOCATEQUADRANT_NOT_IMPLEMENTED;
}

void visualizePuzzleByText(int width, char puzzleMap[][MAX_WIDTH])
{

	cout << "  ";
	for (int x = 0; x < width; x++)
		cout << x << " ";
	cout << endl;

	for (int y = 0; y < width; y++)
	{
		cout << y << ":";
		for (int x = 0; x < width; x++)
			cout << puzzleMap[x][y] << " ";
		cout << endl;
	}
}

void initializePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < width; y++)
			puzzleMap[x][y] = ' ';
}

void normalizePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
char alphabet[21] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
char mapchanged[width][width];
for(int i = 0; i < width; i++)
{
    for (int j = 0; j < width; j++)
    {
        mapchanged[i][j]= 'n';
    }
}
    char alphabetcorrected[21];
	int nextalphabet = 0;
	char now;
	for(int j = 0; j < width; j++)
	{
		for(int i = 0; i < width; i++)
		{
			if(puzzleMap[i][j]!= ' ' && mapchanged[i][j]=='n')
			{
				now = puzzleMap[i][j];
				puzzleMap[i][j] = alphabet[nextalphabet];
                mapchanged[i][j]= 'y';
              
				if(i-1>=0)   //left
				{
					if(puzzleMap[i-1][j] == now && mapchanged[i-1][j]=='n')
					{
						puzzleMap[i-1][j] = alphabet[nextalphabet];
                        mapchanged[i-1][j]= 'y';
					}
				}
				if(i+1<width) // right
				{
					if(puzzleMap[i+1][j] == now && mapchanged[i+1][j]=='n')
					{
						puzzleMap[i+1][j] = alphabet[nextalphabet];
                        mapchanged[i+1][j]= 'y';
					}
				}
				if(j-1>=0) // up
				{
					if(puzzleMap[i][j-1] == now && mapchanged[i][j-1]=='n')
					{
						puzzleMap[i][j-1] = alphabet[nextalphabet];
                        mapchanged[i][j-1]= 'y';
					}
				}
				if(j+1<width) // down
				{
					if(puzzleMap[i][j+1] == now && mapchanged[i][j+1]=='n')
					{
						puzzleMap[i][j+1] = alphabet[nextalphabet];
                        mapchanged[i][j+1]= 'y';
					}
				}
                if(j-1>=0 && i-1>=0) // top left
                {
                    if(puzzleMap[i-1][j-1] == now && mapchanged[i-1][j-1]=='n')
					{
						puzzleMap[i-1][j-1] = alphabet[nextalphabet];
                        mapchanged[i-1][j-1]= 'y';
					}
                }
                if(i+1<width && j-1>=0) // top right
                {
                    if(puzzleMap[i+1][j-1] == now && mapchanged[i+1][j-1]=='n')
					{
						puzzleMap[i+1][j-1] = alphabet[nextalphabet];
                        mapchanged[i+1][j-1]= 'y';
					}
                }
                if(i+1<width && j+1<width) // bottom right
                {
                    if(puzzleMap[i+1][j+1] == now && mapchanged[i+1][j+1]=='n')
					{
						puzzleMap[i+1][j+1] = alphabet[nextalphabet];
                        mapchanged[i+1][j+1]= 'y';
					}
                }
                if(i-1>=0 && j+1<width) // bottom left
                {
                    if(puzzleMap[i-1][j+1] == now && mapchanged[i-1][j+1]=='n')
					{
						puzzleMap[i-1][j+1] = alphabet[nextalphabet];
                        mapchanged[i-1][j+1]= 'y';
					}
                }
				nextalphabet += 1;
			}
		}
	}
	return;
}

void fillPuzzleRecursive(int width, char puzzleMap[][MAX_WIDTH], int tx,
						 int ty, int x, int y, char &nextChar)
{
	if (width == 2)
	{
		if(locateQuadrant(width, x-tx, y-ty) == 1)
		{
			puzzleMap[x+1][y] = nextChar;
			puzzleMap[x][y+1] = nextChar;
			puzzleMap[x+1][y+1] = nextChar;
		}
		else if(locateQuadrant(width, x-tx, y-ty) == 2)
		{
			puzzleMap[x-1][y] = nextChar;
			puzzleMap[x-1][y+1] = nextChar;
			puzzleMap[x][y+1] = nextChar;
		}
		else if(locateQuadrant(width, x-tx, y-ty) == 3)
		{
			puzzleMap[x-1][y-1] = nextChar;
			puzzleMap[x][y-1] = nextChar;
			puzzleMap[x-1][y] = nextChar;
		}
		else if(locateQuadrant(width, x-tx, y-ty) == 4)
		{
			puzzleMap[x][y-1] = nextChar;
			puzzleMap[x+1][y] = nextChar;
			puzzleMap[x+1][y-1] = nextChar;
		}

	}
	else if (width>2)
	{
		if (locateQuadrant(width, x-tx, y-ty) == 1)
		{
			int mid = width/2;
			puzzleMap[tx+mid][ty+mid-1] = nextChar;
			puzzleMap[tx+mid][ty+mid] = nextChar;
			puzzleMap[tx+mid-1][ty+mid] = nextChar;

			int nextwid = width/2;
			fillPuzzleRecursive(nextwid,puzzleMap, tx+nextwid,ty,tx+mid,ty+mid-1,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx+nextwid,ty+nextwid,tx+mid,ty+mid,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx,ty+nextwid,tx+mid-1,ty+mid,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx,ty,x,y,nextChar+=1);
		}
		else if(locateQuadrant(width, x-tx, y-ty) == 2)
		{
			int mid = width/2;
			puzzleMap[tx+mid-1][ty+mid-1] = nextChar;
			puzzleMap[tx+mid][ty+mid] = nextChar;
			puzzleMap[tx+mid-1][ty+mid] = nextChar;

			int nextwid = width/2;
			fillPuzzleRecursive(nextwid,puzzleMap, tx,ty,tx+mid-1,ty+mid-1,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx+nextwid,ty+nextwid,tx+mid,ty+mid,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx,ty+nextwid,tx+mid-1,ty+mid,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx+nextwid,ty,x,y,nextChar+=1);
		}
		else if(locateQuadrant(width, x-tx, y-ty) == 3)
		{
			int mid = width/2;
			puzzleMap[tx+mid-1][ty+mid-1] = nextChar;
			puzzleMap[tx+mid][ty+mid-1] = nextChar;
			puzzleMap[tx+mid-1][ty+mid] = nextChar;

			int nextwid = width/2;
			fillPuzzleRecursive(nextwid,puzzleMap, tx,ty,tx+mid-1,ty+mid-1,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx+nextwid,ty,tx+mid,ty+mid-1,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx,ty+nextwid,tx+mid-1,ty+mid,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx+nextwid,ty+nextwid,x,y,nextChar+=1);
		}
		else if(locateQuadrant(width, x-tx, y-ty) == 4)
		{
			int mid = width/2;
			puzzleMap[tx+mid-1][ty+mid-1] = nextChar;
			puzzleMap[tx+mid][ty+mid-1] = nextChar;
			puzzleMap[tx+mid][ty+mid] = nextChar;

			int nextwid = width/2;
			fillPuzzleRecursive(nextwid,puzzleMap, tx,ty,tx+mid-1,ty+mid-1,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx+nextwid,ty+nextwid,tx+mid,ty+mid,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx+nextwid,ty,tx+mid,ty+mid-1,nextChar+=1);
			fillPuzzleRecursive(nextwid,puzzleMap, tx,ty+nextwid,x,y,nextChar+=1);
		}
	}
	return;
}

void checkInput(int &width, int &emptyXPos, int &emptyYPos)
{
	int test1 = 0;
	do
	{
		cout << "Enter the width/height of the puzzle (2, 4, 8): ";
		cin >> width;
		if(width == 2|| width == 4|| width ==8)
		{
			test1 += 1;
		}
		cout << endl;
	}while(test1 == 0);
	

	int test2 = 0;
	do
	{
		cout << "Enter the x-coordinate of the empty cell (0-" << width - 1 << "): ";
		cin >> emptyXPos;
		if(emptyXPos < width && emptyXPos >= 0)
		{
			test2 += 1;
		}
		cout << endl;
	}while(test2==0);
	

	int test3 = 0;
	do
	{
		cout << "Enter the y-coordinate of the empty cell (0-" << width - 1 << "): ";
		cin >> emptyYPos;
		if(emptyYPos < width && emptyYPos >= 0)
		{
			test3 += 1;
		}
		cout << endl;
	}while(test3 ==0);
	
	return;
}

int main()
{

	int width = 0;
	int emptyXPos = 0;
	int emptyYPos = 0;

	checkInput(width, emptyXPos, emptyYPos);

	// initialized with empty spaces..
	char puzzleMap[MAX_WIDTH][MAX_WIDTH];

	// initialize
	initializePuzzleMap(width, puzzleMap);

	int modeOfOperation = 0;
	do
	{
		cout
			<< "0: Exit directly (for testing checkInput function), 1: Output Quadrant of the empty cell,"
			<< endl
			<< "2: Output without normalization (for student's debug only), 3: Output with normalization"
			<< endl;
		cout << "Enter the output mode: ";
		cin >> modeOfOperation;
		cout << endl;
	} while (modeOfOperation < 0 || modeOfOperation > 3);

	if (modeOfOperation == 0)
	{
		return 0;
	}
	if (modeOfOperation == 1)
	{
		int quad = locateQuadrant(width, emptyXPos, emptyYPos);
		cout << "Quadrant for the empty cell: " << quad << endl;
		return 0;
	}
	char nextChar = 'A';

	fillPuzzleRecursive(width, puzzleMap, 0, 0, emptyXPos, emptyYPos, nextChar);

	int quad = locateQuadrant(width, emptyXPos, emptyYPos);
	cout << "Quadrant for the empty cell: " << quad << endl;
	if (modeOfOperation == 2)
	{
		visualizePuzzleByText(width, puzzleMap);
	}
	else
	{
		normalizePuzzleMap(width, puzzleMap);
		visualizePuzzleByText(width, puzzleMap);
	}
	return 0;
}
