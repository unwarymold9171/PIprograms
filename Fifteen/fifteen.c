#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Constants
#define DIM_MIN 3
#define DIM_MAX 9

//Types
typedef char* string;
typedef int bool;
#define true 1
#define false 0


//Board
int board[DIM_MAX][DIM_MAX];

//Dimensions
int d;

//Methods
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
int GetInt(void);

int main(int argc, string argv[]) {
	 // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }
	
	// ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
	
	// open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();
	
	// accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("You Win!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

		if(tile == -1){
			return -1;
		}

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void) {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void) {
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void) {
    int spaceNumbers = d * d - 1;
    int i, j;
    
    for(i = 0; i < d; i++){
        for(j = 0; j < d; j++){
            if(spaceNumbers == 2 && d % 2 == 0){
                board[i][j] = 1;
            } else if(spaceNumbers == 1 && d % 2 == 0){
                board[i][j] = 2;
            } else {
                board[i][j] = spaceNumbers;
            }
            spaceNumbers--;
        }
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void) {
    int i, j;
    
    for(i = 0; i < d; i++){
        for(j = 0; j < d; j++){
            if(board[i][j]){
                if(board[i][j] > 9)
                    printf(" %d", board[i][j]);
                else
                    printf("  %d", board[i][j]);
            } else
                printf("  _");
            
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile) {
    int i, j;
    int pos1, pos2;
    int posBlank1, posBlank2;
    bool moves = false;
    
    for(i = 0; i < d; i++){
        for(j = 0; j < d; j++){
            if(tile == board[i][j]){
                pos1 = i;
                pos2 = j;
            } else if(board[i][j] == 0){
                posBlank1 = i;
                posBlank2 = j;
            }
        }
    }
    
    if(pos1 + 1 == posBlank1 && pos2 == posBlank2){
        moves = true;
    } else if(pos1 - 1 == posBlank1 && pos2 == posBlank2){
        moves = true;
    } else if(pos1 == posBlank1 && pos2 + 1 == posBlank2){
        moves = true;
    } else if(pos1 == posBlank1 && pos2 - 1 == posBlank2){
        moves = true;
    }
    
    if(moves){
        board[posBlank1][posBlank2] = board[pos1][pos2];
        board[pos1][pos2] = 0;
    }
    return moves;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void) {
    int i, j;
    bool win = false;
    int temp = 1;
    
    for(i = 0; i < d; i++){
        for(j = 0; j < d; j++){
            if(board[i][j] == temp && board[i][j] != 0){
                temp++;
            } else if(board[i][j] == 0 && temp == d * d){
                win = true;
            } else {
                break;
            }
        }
    }
    
    return win;
}

int GetInt() {
	char str[10];
	int resault = 0;
	
	scanf("%s", str);
	
	int i = 0;
	for(i = 0; i < 10; i++) {
		if(!(str[i] >= '0' && str[i] <= '9')) {
			if(i == 0) {
				resault = -1;
			}
			break;
		}
		
		if(i > 0) {
			resault *= 10;
		}
		
		resault = (char)str[i] - 48;
		
	}

	return resault;
}
