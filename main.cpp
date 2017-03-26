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
};

//  MAIN METHOD
int main() {
    int i, j;
    for(i=0; i<6; i++) {
        printf("%4d", whitePieces[i]);
    }
    return 0;
}
