#include<stdio.h>
#include<stdlib.h>

//  DEFINING PIECES
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

//  DECLARING GLOBAL VARIABLES
int whitePieces[6]={PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
struct node {
    int data;
    struct node *next;
};
struct pos {
    int x;
    int y;
};
struct piece {
    int type;// LIKE PAWN, ROOK, BISHOP, etc
    pos currentPos;
    int color;
    int *possibleMoves;
}board[8][8];//         ***MAY HAVE TO CHANGE THIS***

//  MAIN METHOD
int main() {
    initializeBoard();
    printBoard();
    return 0;
}

//  OTHER METHODS
int initializeBoard() {//   INITIALIZES BOARD WITH PIECES ON THEIR DEFAULT POISITION
    int i,j;
    for(i=0; i<8; i++) {
        board[1][i].type = board[6][i].type = PAWN;
    }
    board[0][0].type = board[0][7].type = board[7][0].type = board[7][7].type = ROOK;
    board[0][1].type = board[0][6].type = board[7][1].type = board[7][6].type = KNIGHT;
    board[0][2].type = board[0][5].type = board[7][2].type = board[7][5].type = BISHOP;
    board[0][3].type = board[7][3].type = QUEEN;
    board[0][4].type = board[7][4].type = KING;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            board[i][j].currentPos.x = i;
            board[i][j].currentPos.x = i;//         ***MAY HAVE TO CHANGE THIS***
        }
    }
    return 1;
}

int printBoard() {//    DISPLAYS THE BOARD IN A SIMPLE WAY
    int i, j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            switch(board[i][j].type) {
                case PAWN:
                    printf(" P ");
                    break;

                case ROOK:
                    printf(" R ");
                    break;

                case BISHOP:
                    printf(" B ");
                    break;

                case KNIGHT:
                    printf(" K ");
                    break;

                case QUEEN:
                    printf(" Q ");
                    break;

                case KING:
                    printf("[K]");
                    break;

                default:
                    printf("   ");
                    break;

            }
        }
        printf("\n");
    }
    return 1;
}
