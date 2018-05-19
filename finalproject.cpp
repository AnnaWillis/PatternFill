// This program will fill a shape with patterns. Oh, and it doesn't need any points as inputs. Don't deduct points for this, please!
// I just thought it would be cool if the program could do this all by itself without any "help" from the user.

// Here is a sample input that I tried to make into an OSC10 symbol... but I sort of failed.
	//	*************************************************R
	//	*.........**........**........**..**..********..*R
	//	*..*****..**...*******...*******..**..*......*..*R
	//	*..*...*..**...*.....******...**..**..*......*..*R
	//	*..*...*..**...*..........*...**..**..*......*..*R
	//	*..*****..**...*******....*...**..**..*......*..*R
	//	*.........**........*******...**..**..********..*R
	//	*************************************************S

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

char selectPattern(char a[], int limit) // This function takes an array of already used patterns(so as to not use any of those again) and uses random numbers to return a pattern to fill the shape with.
{
	char pattern;
	
	char symbols[] = {'@','$','^','#','!','&','?','<','>','~','+','=','%'};
	char numbers[] = {'0','1','2','3','4','5','6','7','8','9'};
	char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	
	int selector1 = rand()%3+1;
	int selector2;
	
	if (selector1 == 1)
	{
		selector2 = rand()%sizeof(symbols)+0;
		pattern = symbols[selector2];
	}
	
	else if (selector1 == 2)
	{
		selector2 = rand()%sizeof(numbers)+0;
		pattern = numbers[selector2];
	}
	
	else if (selector1 == 3)
	{
		selector2 = rand()%sizeof(letters)+0;
		pattern = letters[selector2];
	}
	
	else
	{
		cout << "\nAn error has occurred. (Error 1)\n";
		pattern = 'E';
		return pattern;
	}
	
	for (int i = 0; i < limit; i++)
	{
		if (pattern == a[i]) // If the pattern is in the array of already-used patterns...
		{
			selectPattern(a, limit); // ...then redo the function.
		}
		
		else if (a[i] == 'E')
		{
			a[i] = pattern;
		}
	}
	
	return pattern;
}

//Fills a region containing a point with a pattern by recursivity. 
void fillshape(char a[100][100], int columnlimit, int rowlimit, char pattern, int x, int y)
{
	//cout << endl << rowlimit; 
	// cout << endl << x << ", " << y;
	if (x < 0 || x > columnlimit || y < 0 || y > rowlimit || a[y][x] != '.')
	{
		return;
	}
	
	a[y][x] = pattern; // 5
	fillshape(a, columnlimit, rowlimit, pattern, x + 1, y); // 6
	fillshape(a, columnlimit, rowlimit, pattern, x, y - 1);	// 2
	fillshape(a, columnlimit, rowlimit, pattern, x, y + 1); // 8
	fillshape(a, columnlimit, rowlimit, pattern, x - 1, y); // 4
	
	// 1 2 3
	// 4 5 6
	// 7 8 9
	
	// case 1: (x - 1, y - 1)
	// case 2: (x, y - 1)
	// case 3: (x + 1, y - 1)
	// case 4: (x - 1, y)
	// case 5: (x, y)
	// case 6: (x + 1, y)
	// case 7: (x - 1, y + 1)
	// case 8: (x, y + 1)
	// case 9: (x + 1, y + 1)
	
	//These four if statements make sure that patterns can't go through diagonal strings of asterisks, which would ruin the shape!
	if (x + 1 > columnlimit || y + 1 > rowlimit || !(a[y][x+1] == '*' && a[y+1][x] == '*'))
	{
		fillshape(a, columnlimit, rowlimit, pattern, x + 1, y + 1); // 9
	}
	if (x + 1 > columnlimit || y - 1 < 0 || !(a[y][x+1] == '*' && a[y-1][x] == '*'))
	{
		fillshape(a, columnlimit, rowlimit, pattern, x + 1, y - 1); // 3
	}
	if (x - 1 < 0 || y + 1 > rowlimit || !(a[y][x-1] == '*' && a[y+1][x] == '*'))
	{
		fillshape(a, columnlimit, rowlimit, pattern, x - 1, y + 1);	// 7
	}
	if (x - 1 < 0 || y - 1 < 0 || !(a[y][x-1] == '*' && a[y-1][x] == '*'))
	{
		fillshape(a, columnlimit, rowlimit, pattern, x - 1, y - 1); // 1
	}
}

int main()
{
	srand(time(0));
	
	cout << "Hello! This program will fill nearly any CLOSED shapes you input with patterns! (Hopefully. Unless it doesn't work for whatever reason.)\n\n";
	cout << "Instructions for inputting shapes: ";
	cout << "\n1. Simply put a period for every empty part of your creation.";
	cout << "\n2. Input asterisks for the border of the shape.";
	cout << "\n3. When you're done with every line besides the last one, enter a capital R and press enter. Why R, you ask? It's a long story.";
	cout << "\n4. When you're done with the entire shape, enter a capital S and press enter. Why S, you'll have to guess for yourself, because it's an extremely obscure reference that I don't really want to share.";
	cout << "\n5. All the lines have to be the same length, otherwise I will track you down just to yell at you.";
	cout << "\n\nPretty simple, right? Please note that I will be absolutely furious with you if you place any stray asterisks that don't belong anywhere. So don't, okay? Make the computer's life easier. And mine.";
	cout << "\n\nInput shape:\n";
	
	char a[100][100]; // It wouldn't let me leave the [][] blank because this array's multidimensional.
	// I am assuming that no one will make their shape any bigger than this, though.
	
	char PlaceHolder;
	int limit = 100;
	int i = 0;
	int characterCount = 0;
	
	while (i < 101)
	{
		cin >> PlaceHolder; // This PlaceHolder is used because I don't want to put any R or S characters into the array. I just want the asterisks and spaces.
		if (PlaceHolder == 'R')
		{
			limit = characterCount - 1;
			i++;
			characterCount = 0;
		}
		else if (PlaceHolder == 'S')
		{
			i++;
			break;
		}
		else
		{
			a[i][characterCount++] = PlaceHolder;
		}
	}
	cout << "\n\nYour input: \n\n";
	for (int d = 0; d < i; d++)
	{
		for (int b = 0; b <= limit; b++)
		{
			if (a[d][b] == '.' || a[d][b] == 'L')
			{
				cout << " ";
			}
			else
			{
				cout << a[d][b];
			}
		}
		cout << endl;
	}
	
	int rowlimit = i - 1; // I need this so that I can easily cout the finished array later.
	int y = 0;
	int x = 0;
	
	for (y = 0; y <= rowlimit; y++)
	{
		for (x = 0; x <= limit; x++)
		{
			if (a[y][x] == '.')
			{
				a[y][x] = 'L';
			}
			
			else if (a[y][x] == '*')
			{
				break;
			}
		}
	}
	
	for (y = 0; y <= rowlimit; y++)
	{
		for (x = limit; x >= 0; x--)
		{
			if (a[y][x] == '.')
			{
				a[y][x] = 'L';
			}
			
			else if (a[y][x] == '*')
			{
				break;
			}
		}
	}
	
	//Those two groups of two for loops were to place Ls outside the shape (one did from the left side, the other from the right) so that the computer knows not to put patterns there.
	
	int PUL = 16; 
	
	char patternsUsed[PUL]; // A nice single-dimension array. It keeps track of the patterns already used so that the computer doesn't do two of the same pattern in a shape.
	
	for (int p = 0; p < PUL; p++)
	{
		patternsUsed[p] = 'E';
	}
	
	char pattern = selectPattern(patternsUsed, PUL);

	for (int q = 1; q <= rowlimit; q++)
	{
		for (int r = 1; r <= limit; r++)
		{
			fillshape(a,limit,rowlimit,pattern,r,q);
			pattern = selectPattern(patternsUsed, PUL);
		}
	}
	
	cout << "\n\nFinished shape: \n\n";
	
	for (y = 0; y <= rowlimit; y++)
	{
		for (x = 0; x <= limit; x++)
		{
			if (a[y][x] == 'L' || a[y][x] == '.')
			{
				cout << " ";
			}
			
			else
			{
				cout << a[y][x];
			}	
		}
		cout << "\n";
	}
	
	return 0;
}
