//  HEADER FILES
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//  DEFINING PIECES
#define EMPTY 0
#define PAWN 1
#define ROOK 2
#define KNIGHT 3
#define BISHOP 4
#define QUEEN 5
#define KING 6

//  DECLARING PROTOTYPES
int mainMenu();
int printBoard();
int initializeBoard();
int swapPieces(struct piece *a, struct piece *b);
int handleCursor();
int loadingScreen();

//  DECLARING GLOBAL VARIABLES
int whitePieces[6]={PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
int cursorX = 0;
int cursorY = 0;

struct piece {
    int type;// LIKE PAWN, ROOK, BISHOP, etc
    int color;
}board[8][8];

//  MAIN METHOD
int main() {
    initializeBoard();
    loadingScreen();
    do {
        printBoard();
        handleCursor();
    }while(1);
    return 0;
}

//  OTHER METHODS
int initializeBoard() {//   INITIALIZES BOARD WITH PIECES ON THEIR DEFAULT POISITION
    int i,j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            board[i][j].type = EMPTY;
        }
    }
    for(i=0; i<8; i++) {
        board[1][i].type = board[6][i].type = PAWN;
    }
    board[0][0].type = board[0][7].type = board[7][0].type = board[7][7].type = ROOK;
    board[0][1].type = board[0][6].type = board[7][1].type = board[7][6].type = KNIGHT;
    board[0][2].type = board[0][5].type = board[7][2].type = board[7][5].type = BISHOP;
    board[0][3].type = board[7][3].type = QUEEN;
    board[0][4].type = board[7][4].type = KING;

    return 1;
}

int printBoard() {//    DISPLAYS THE BOARD IN A SIMPLE WAY
    system("cls");
    printf("--[w]---[a]---[s]---[d]---[e]---[SPACE]--\n\n\n");
    int i, j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            switch(board[i][j].type) {
                case PAWN:
                    if(i == cursorX && j == cursorY) {
                        printf("[P]");
                    }else {
                        printf(" P ");
                    }
                    break;

                case ROOK:
                    if(i == cursorX && j == cursorY) {
                        printf("[R]");
                    }else {
                        printf(" R ");
                    }
                    break;

                case BISHOP:
                    if(i == cursorX && j == cursorY) {
                        printf("[B]");
                    }else {
                        printf(" B ");
                    }
                    break;

                case KNIGHT:
                    if(i == cursorX && j == cursorY) {
                        printf("[N]");
                    }else {
                        printf(" N ");
                    }
                    break;

                case QUEEN:
                    if(i == cursorX && j == cursorY) {
                        printf("[N]");
                    }else {
                        printf(" N ");
                    }
                    break;

                case KING:
                    if(i == cursorX && j == cursorY) {
                        printf("[K]");
                    }else {
                        printf(" K ");
                    }
                    break;

                case EMPTY:
                    if(i == cursorX && j == cursorY) {
                        printf("[-]");
                    }else {
                        printf(" - ");
                    }
                    break;

            }
        }
        printf("\n");
    }
    return 1;
}

int swapPieces(struct piece *a, struct piece *b) {//    SWAPS TWO PIECES ON THE BOARD
    int temp;
    b = a;
    a->type = EMPTY;
    // a->color = ...
    return 1;
}

int handleCursor() {//  TAKES THE INPUT FROM USER AND MOVES THE CURSOR ACCORDINGLY
    char ch;
    fflush(stdin);
    ch = getche();
    switch(ch) {
        case 'w':
        case 'W':
            if(cursorX > 0) {
                cursorX--;
            }
            break;

        case 'a':
        case 'A':
            if(cursorY > 0) {
                cursorY--;
            }
            break;

        case 's':
        case 'S':
            if(cursorX < 7) {
                cursorX++;
            }
            break;

        case 'd':
        case 'D':
            if(cursorY < 7) {
                cursorY++;
            }
            break;

        case 'e':
        case 'E':
            exit(0);
            break;

        case ' ':
            system("pause");
            break;
    }
}

int loadingScreen() {
    system("cls");
    int i;
    printf("Loading\n");
    for(i=0; i<10; i++) {
        printf("%c",219);
        _sleep(250);
    }
    system("cls");
    return 0;
}
