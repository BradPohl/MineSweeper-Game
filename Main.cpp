// This is a project to create and random minesweeper game with the option to cheat if you're afraid of losing
// You are allowed to choose from 3 seperate difficulties
// Beginner is 9x9 with 10 mines
// Intermediate is 16x16 with 40 mines
// Advanced is 24x24 with 99 mines

#include <iomanip>
#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::setw;

int SIDE; //global variable to set amount of sides
int MINES; //global variable to set amount of mines


/**
 * @brief Choose the difficulty, if inproper entry enter loop until correct entry
 * 
 * @note Changed input to character because when it was integer it caused infite loop when character was entered
 */
void chooseDifficulty(){
    char level;

    cout << "Beginner (9x9 tiles, 10 mines), Enter 1" << endl
         << "Intermediate (16x16 tiles, 40 mines), Enter 2" << endl
         << "Advanced (24x24 tiles, 99 mines), Enter 3" << endl;

    cin >> level;

    if(level == '1'){
        SIDE = 9;
        MINES = 10;
    }
    else if(level == '2'){
        SIDE = 16;
        MINES = 40;
    }
    else if(level == '3'){
        SIDE = 24;
        MINES = 99;
    }
    else{
        while(level != '1' && level != '2' && level != '3'){
            cout << "You did not enter the correct value, please try again" << endl;
            cout << "Beginner (9x9 tiles, 10 mines), Enter 1" << endl
                << "Intermediate (16x16 tiles, 40 mines), Enter 2" << endl
                << "Advanced (24x24 tiles, 99 mines), Enter 3" << endl;

            cin >> level;
        }
    }
}




/**
 * @brief create initial boards
 * 
 * @param realBoard - board with mines
 * @param myBoard - board the user sees to play
 */
void initialize(char realBoard[][25], char myBoard[][25]){
    srand(time(NULL)); // Using random with time so the same layout does not occur

    // Build initial board with no mines
    for(int i = 0; i <= SIDE; i++){
        for(int j = 0; j <= SIDE; j++){
            myBoard[i][j] = realBoard[i][j] = '-';
        }
    }
}


/**
 * @brief place mines on realBoard so it can be checked after entering
 * 
 * @param mines holds coordinates to mines
 * @param realBoard hidden board that holds mines
 */
void placeMines(int mines[][2], char realBoard[][25]){
    bool createMine[25*25];

    memset(createMine, false, sizeof(createMine));  // sets every spot to false

    for(int i = 0; i < MINES;){
        int random = rand() % (SIDE * SIDE);
        int x = random / SIDE;
        int y = random % SIDE;

        // check if mine is there, if not place then turn true
        if(createMine[random] == false){
            mines[i][0] = x; // adds to row
            mines[i][1] = y; // adds to column

            // place mine then flip switch
            realBoard[mines[i][0]][mines[i][1]] = '*';
            createMine[random] = true;
            i++; // only increase after mine was placed
        }
    }
}

/**
 * @brief print board that is contained in parameter
 * 
 * @param board board that is to be printed
 */
void printBoard(char board[][25]){
    cout << "     ";

    for(int i = 1; i <= SIDE; i++){ // Print the top level
        cout << setw(3) << i;
    }
    cout << endl << endl;

    for(int i = 1; i <= SIDE; i++){
        cout << std::left << setw(5) << i;
        for(int j = 1; j <= SIDE; j++){
            cout << setw(3) << board[i][j];
        }
        cout << endl;
    }
}


/**
 * @brief Use this when you want to see the realBoard
 * 
 * @param realBoard board to be printed showing mines
 */
void cheaterFunction(char realBoard[][25]){
    cout << endl << "Avoid the mines" << endl;

    printBoard(realBoard);
}


/**
 * @brief get input
 * 
 * @param x row
 * @param y column
 */
void makeMove(int *x, int *y){
    cout << "Enter your move 'row column': ";
    scanf("%d %d", x, y);
}


/**
 * @brief check if mine is there
 * 
 * @param x row
 * @param y column
 * @param board board containing mines (realBoard)
 * @return true there is a mine
 * @return false there is not a mine
 */
bool isMine(int x, int y, char board[][25]){
    return(board[x][y] == '*');
}



/**
 * @brief replace mine with a valid spot
 * 
 * @param x row
 * @param y column
 * @param board board being used to check for mines 
 */
void replaceMine(int x, int y, char board[][25]){
    for(int i = 0; i < SIDE; i++){
        for(int j = 0; j < SIDE; j++){
            if(board[i][j] != '*'){
                board[i][j] = '*';
                board[x][y] = '-';
            }
        }
    }
}


/**
 * @brief check if entry was valid
 * 
 * @param x row entered
 * @param y column entered
 * @return true entry was valid
 * @return false opposite ^
 */
bool isValid(int x, int y){
    return (x > 0) && (x < SIDE) && (y > 0) && (y < SIDE);
}



/**
 * @brief check surrounding areas of input
 * 
 * @param x row
 * @param y column
 * @param mines mines placement
 * @param realBoard board with mines
 * @return int returns number of spots with no mines
 */
int countAdjacentMines(int x, int y, int mines[][2], char realBoard[][25]){
    int count = 0;

    // check up
    if(isValid(x-1, y) == true){
        if(isMine(x-1, y, realBoard) == true)
            count++;
    }

    // check down
    if(isValid(x+1, y) == true){
        if(isMine(x+1, y, realBoard) == true)
            count++;
    }

    // check left
    if(isValid(x, y-1) == true){
        if(isMine(x, y-1, realBoard) == true)
            count++;
    }

    // check right
    if(isValid(x, y+1) == true){
        if(isMine(x, y+1, realBoard) == true)
            count++;
    }

    // check left up
    if(isValid(x-1, y-1) == true){
        if(isMine(x-1, y-1, realBoard) == true)
            count++;
    }

    // check left down
    if(isValid(x+1, y-1) == true){
        if(isMine(x+1, y-1, realBoard) == true)
            count++;
    }

    // check right up
    if(isValid(x-1, y+1) == true){
        if(isMine(x-1, y+1, realBoard) == true)
            count++;
    }

    //check right down
    if(isValid(x+1, y+1) == true){
        if(isMine(x+1, y+1, realBoard) == true)
            count++;
    }

    return count;
}


/**
 * @brief do your checks and determine if you win or lose
 * 
 * @param myBoard board for player
 * @param realBoard board for cheater (and checks)
 * @param mines mine placement
 * @param x row
 * @param y column
 * @param totalMoves moves made
 * @return true end game
 * @return false continue game
 */
bool playGameUntil(char myBoard[][25], char realBoard[][25], int mines[][2], int x, int y, int *totalMoves){
    //base case, checks if mine is there
    if(myBoard[x][y] != '-')
        return false;

    //opened a mine, time to lose
    if(realBoard[x][y] == '*'){
        myBoard[x][y] = '*';

        for(int i = 0; i < MINES; i++)
            myBoard[mines[i][0]][mines[i][1]] = '*';

        printBoard(myBoard);
        cout << endl << "You lost" << endl;
        return true;
    }
    else{
        int count = countAdjacentMines(x, y, mines, realBoard);
        *totalMoves--;

        myBoard[x][y] = count + '0'; // Place number where user input was

        if(!count){
            // up
            if(isValid(x-1, y) == true){
                if(isMine(x-1, y, realBoard) == false)
                    playGameUntil(myBoard, realBoard, mines, x-1, y, totalMoves);
            }
            // down
            if(isValid(x+1, y) == true){
                if(isMine(x+1, y, realBoard) == false)
                    playGameUntil(myBoard, realBoard, mines, x+1, y, totalMoves);
            }
            // left
            if(isValid(x, y-1) == true){
                if(isMine(x, y-1, realBoard) == false)
                    playGameUntil(myBoard, realBoard, mines, x, y-1, totalMoves);
            }
            // right
            if(isValid(x, y+1) == true){
                if(isMine(x, y+1, realBoard) == false)
                    playGameUntil(myBoard, realBoard, mines, x, y+1, totalMoves);
            }
            // up left
            if(isValid(x-1, y-1) == true){
                if(isMine(x-1, y-1, realBoard) == false)
                    playGameUntil(myBoard, realBoard, mines, x-1, y-1, totalMoves);
            }
            // down left
            if(isValid(x+1, y-1) == true){
                if(isMine(x+1, y-1, realBoard) == false)
                    playGameUntil(myBoard, realBoard, mines, x+1, y-1, totalMoves);
            }
            // up right
            if(isValid(x-1, y+1) == true){
                if(isMine(x-1, y+1, realBoard) == false)
                    playGameUntil(myBoard, realBoard, mines, x-1, y+1, totalMoves);
            }
            // down right
            if(isValid(x+1, y+1) == true){
                if(isMine(x+1, y+1, realBoard) == false)
                    playGameUntil(myBoard, realBoard, mines, x+1, y+1, totalMoves);
            }
        }
        return false;
    }
}


/**
 * @brief play the game
 * 
 */
void playMineSweeper(){
    bool playGame = false;  //Game is not over when you enter

    char realBoard[25][25], myBoard[25][25]; //Create boards with a max size of +1 as advanced

    int totalMoves = SIDE * SIDE - MINES;
    int x, y; //coordinates of mines
    int mines[99][2]; //99 is max mines, 2 is spots for mine coordinates

    initialize(realBoard, myBoard);

    placeMines(mines, realBoard);

    cheaterFunction(realBoard); // Remove front "//" if you are afraid to lose

    int moveCounter = 0;
    while(playGame == false){
        cout << endl << "Current board: " << endl;
        printBoard(myBoard);
        makeMove(&x, &y);

        if(moveCounter == 0){
            if(isMine(x, y, realBoard) == true)
                replaceMine(x, y, realBoard);   //if the first move is a mine, remove it
        }
        moveCounter++;

        playGame = playGameUntil(myBoard, realBoard, mines, x, y, &totalMoves);

        if((playGame == false) && (totalMoves == 0)){
            cout << "You won!" << endl;
            playGame == true;
        }
    }
}


//Driver for the program
int main(){
    chooseDifficulty();

    playMineSweeper();
    return 0;
}