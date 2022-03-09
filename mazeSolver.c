#include <stdio.h>
#include <stdlib.h>

//Funtion to write all correct moves made,to a file
void writeToFile(int a, int b)
{
      FILE *fptr;
      fptr = fopen("program.txt","a");
      if(fptr == NULL){ 
           printf("Error!");
           exit(1);
        }
      fprintf(fptr,"User moved to the location: %d %d \n",a,b);
      fclose(fptr);    
}

//Function to read all the moves made
void readFromFile()
{
      int ch;
      FILE *fp = fopen("program.txt", "r");
      if (fp == NULL) {
            printf("ERROR!");
            exit(0);
      }
      while ((ch = getc(fp)) != EOF) //Reading File Until end of Character
            putchar(ch);
      fclose(fp);
         
}

// Utility function to check validity of coordinate
int isValid(int rows, int columns, char maze[rows][columns], int x, int y)
{
    if (x >= 0 && x < rows && y >= 0 && y < columns)
        if (maze[x][y] == ' ' || maze[x][y] == 'S' || maze[x][y] == 's' || maze[x][y] == 'E' || maze[x][y] == 'e')
            return 1;
    return 0;
}

// Utility function to display solution maze
void displayMaze(int rows, int columns, char maze[rows][columns], char sol[rows][columns])
{
    printf("+");
    for (int i = 0; i < 2*columns+1; ++i)
        printf("-");
    printf("+\n");
    for (int row = 0; row < rows; ++row)
    {
        printf("| ");
        for (int column = 0; column < columns; ++column)
        {
            if (sol[row][column] == maze[row][column] && maze[row][column] == ' '){
                printf("X ");
                writeToFile(row, column);
            }
            else
                printf("%c ", maze[row][column]);
        }
        printf("|\n");      
    }
    printf("+");
    for (int i = 0; i < 2*columns+1; ++i)
        printf("-");
    printf("+\n");    
}

// Function to solve the given maze
int solveMaze(int rows, int columns, char maze[rows][columns], char sol[rows][columns], int x, int y, int end[2])
{
    // If (x,y) is end return 1
    if (x == end[0] && y == end[1] && maze[x][y] == 'E')
    {
        sol[x][y] = 1;
        return 1;
    }

    // Checking if (x,y) is valid for given maze
    if (isValid(rows, columns, maze, x, y))
    {
        // Check if current coordinate is already part of solution path
        if (sol[x][y] == ' ')
            return 0;
        
        // Marking (x,y) as a part of solution path
        sol[x][y] = ' ';

        // Move down in row
        if (solveMaze(rows, columns, maze, sol, x+1, y, end))   // .  ..  ...  
            return 1; 
        
        // If no solution, move right in column
        if (solveMaze(rows, columns, maze, sol, x, y+1, end))
            return 1;

        // If no solution, move up in column
        if (solveMaze(rows, columns, maze, sol, x-1, y, end))
            return 1;

        // If no solution, move left in column
        if (solveMaze(rows, columns, maze, sol, x, y-1, end))
            return 1;

        // If none of above 4 steps work unmark (x,y) as path of solution
        sol[x][y] = '0';
        return 0;
    }
    return 0;
}

int main()
{
    char maze[][6] = {{'S', '0', '0', '0', '0', ' '},
                      {' ', ' ', ' ', ' ', '0', ' '},
                      {' ', '0', '0', ' ', '0', ' '},
                      {' ', ' ', ' ', ' ', '0', '0'},
                      {' ', '0', '0', ' ', '0', ' '},
                      {' ', ' ', '0', ' ', ' ', 'E'}};

    // Calculating number of rows and columns
    int rows = sizeof(maze) / sizeof(maze[0]);
    int columns = sizeof(maze[0]) / sizeof(maze[0][0]);

    // Making solution array having all elements '0'
    char sol[rows][columns];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            sol[i][j] = '0';

    // Getting start and end Coordinates
    int start[2] = {-1, -1}, end[2] = {-1, -1};
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
        {
            if (maze[i][j] == 'S' || maze[i][j] == 's')
            {
                start[0] = i;
                start[1] = j;
            }
            else if (maze[i][j] == 'E')
            {
                end[0] = i;
                end[1] = j;
            }
            // Checking for invalid character
            else if (maze[i][j] != ' ' && maze[i][j] != '0')
            {
                printf("Invalid Maze: Invalid character \'%c\' at (%d, %d).\n", maze[i][j], i, j);
                return 0;
            }
        }

    // Checking validity of maze
    if (start[0] == -1 || end[0] == -1)
    {
        printf("Invalid Maze: start/end not specified.\n");
        return 0;
    }

    if (!(solveMaze(rows, columns, maze, sol, start[0], start[1], end)))
    {
        printf("Solution doesn\'t exist.\n");
        return 0;
    }
    printf("One of the possible paths:\n");
    displayMaze(rows, columns, maze, sol);
    
    printf("Do you want to see all the moves made? (y/n): ");
      char movesmade;
      scanf(" %c", &movesmade);
      if(movesmade=='y' || movesmade=='Y'){
            readFromFile();
      }
      else 
            printf("End of game. Thank You.");
    return 1;
}