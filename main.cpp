//  HEADER FILES
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//  DEFINING PIECES
#define WHITE 1
#define BLACK -1
#define EMPTY 0
#define PAWN 1
#define ROOK 2
#define KNIGHT 3
#define BISHOP 4
#define QUEEN 5
#define KING 6

//  DECLARING PROTOTYPES
int printStacky(int len);
int isMovesHashEmpty();
int staleMate();
int pieceMoves();
int selectPosition(int len);
int instructions();
int resetMovesHash();
int king_moves();
int knight_moves();
int queen_moves();
int bishop_moves();
int pawn_moves();
int rook_moves();
void printHash();
void possible_moves();
int mainMenu();
int printBoard();
int initializeBoard();
int swapPieces(struct piece *a, struct piece *b);
int handleCursor(int color);
int loadingScreen();

//  DECLARING GLOBAL VARIABLES
int moved = 0;
int stackPointer = -1;
int mainX;
int mainY;
int moves_hash[8][8]={0};
int whitePieces[6]={PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
int front_color,rear_color;
int cursorX = 0;
int cursorY = 0;

struct piece {
    int type;// LIKE PAWN, ROOK, BISHOP, etc
    int color;
}board[8][8];

struct node{
    int X;
    int Y;
    struct node *next;
}*current, *next;

struct coord {
    int x;
    int y;
}stacky[32], whiteKing, blackKing;

//  MAIN METHOD
int main() {
    initializeBoard();
    //loadingScreen();
    int col = WHITE;
    do {
        if(moved) {
            col *= -1;
        }
        moved = 0;
        possible_moves();
        printBoard();
        printf("\n");
        resetMovesHash();
    }while(handleCursor(col));
    return 0;
}

//  OTHER METHODS
int initializeBoard() {//   INITIALIZES BOARD WITH PIECES ON THEIR DEFAULT POISITION
    int i,j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            board[i][j].type = EMPTY;
            board[i][j].color = 0;
        }
    }
    for(i=0; i<8; i++) {
        board[1][i].type = board[6][i].type = PAWN;
    }
    board[0][0].type = board[0][7].type = board[7][0].type = board[7][7].type = ROOK;
    board[0][1].type = board[0][6].type = board[7][1].type = board[7][6].type = KNIGHT;
    board[0][2].type = board[0][5].type = board[7][2].type = board[7][5].type = BISHOP;
    board[0][3].type = board[7][3].type = QUEEN;
    whiteKing.x = 0;
    whiteKing.y = 4;
    blackKing.x = 7;
    blackKing.y = 4;
    board[0][4].type = board[7][4].type = KING;
    for(i=0; i<8; i++) {
        board[0][i].color = WHITE;
        board[1][i].color = WHITE;
    }
    for(i=0; i<8; i++) {
        board[6][i].color = BLACK;
        board[7][i].color = BLACK;
    }
    front_color = 1;
    rear_color = -1;

    return 1;
}

int printBoard() {//    DISPLAYS THE BOARD IN A SIMPLE WAY
    system("cls");
    //instructions();
    int i, j;
    for(i=0; i<8; i++) {
        printf(" %c", 218);
        for(j=1; j<48; j++) {
            if(j%6==0 && j!=0 && j!=48) {
                printf("%c  %c", 191, 218);
            }else {
                printf("%c", 196);
            }
        }
        printf("%c\n", 191);
        for(j=0; j<8; j++) {
            switch(board[i][j].type) {
                case PAWN:
                    if(i == cursorX && j == cursorY) {
                        printf(" %c%c P %c%c ", 175, 175, 174, 174);
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" %c  P  %c ", 179, 179);
                        else
                            printf(" %c %cP%c %c ", 179, 222, 221, 179);
                    }
                    break;

                case ROOK:
                    if(i == cursorX && j == cursorY) {
                        printf(" %c%c R %c%c ", 175, 175, 174, 174);
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" %c  R  %c ", 179, 179);
                        else
                            printf(" %c %cR%c %c ", 179, 222, 221, 179);
                    }
                    break;

                case BISHOP:
                    if(i == cursorX && j == cursorY) {
                        printf(" %c%c B %c%c ", 175, 175, 174, 174);
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" %c  B  %c ", 179, 179);
                        else
                            printf(" %c %cB%c %c ", 179, 222, 221, 179);;
                    }
                    break;

                case KNIGHT:
                    if(i == cursorX && j == cursorY) {
                        printf(" %c%c N %c%c ", 175, 175, 174, 174);
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" %c  N  %c ", 179, 179);
                        else
                            printf(" %c %cN%c %c ", 179, 222, 221, 179);
                    }
                    break;

                case QUEEN:
                    if(i == cursorX && j == cursorY) {
                        printf(" %c%c Q %c%c ", 175, 175, 174, 174);
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" %c  Q  %c ", 179, 179);
                        else
                            printf(" %c %cQ%c %c ", 179, 222, 221, 179);
                    }
                    break;

                case KING:
                    if(i == cursorX && j == cursorY) {
                        printf(" %c%c K %c%c ", 175, 175, 174, 174);
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" %c  K  %c ", 179, 179);
                        else
                            printf(" %c %cK%c %c ", 179, 222, 221, 179);
                    }
                    break;

                case EMPTY:
                    if(i == cursorX && j == cursorY) {
                        printf(" %c%c   %c%c ", 175, 175, 174, 174);
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" %c     %c ", 179, 179);
                        else
                            printf(" %c  %c  %c ", 179, 219, 179);
                    }
                    break;

            }
        }
        printf("\n");
        printf(" %c", 192);
        for(j=1; j<48; j++) {
            if(j%6==0 && j!=0 && j!=48) {
                printf("%c  %c", 217, 192);
            }else {
                printf("%c", 196);
            }
        }
        printf("%c", 217);
        printf("\n");


    }
    return 1;
}

int swapPieces(struct piece *a, struct piece *b) {//    SWAPS TWO PIECES ON THE BOARD
    *b = *a;
    a->type = EMPTY;
    a->color = 0;
    return 1;
}

int handleCursor(int col) {//  TAKES THE INPUT FROM USER AND MOVES THE CURSOR ACCORDINGLY
    char ch;
    int i, j;
    fflush(stdin);
    ch = getche();
    //resetMovesHash();
    switch(ch) {
        case 'w':
        case 'W':
            for(i=cursorX-1; i>=0; i--) {
                if(board[i][cursorY].color == col) {
                    cursorX = i;
                    break;
                }
            }
            return 1;

        case 'a':
        case 'A':
            for(j=cursorY-1; j>=0; j--) {
                if(board[cursorX][j].color == col) {
                    cursorY = j;
                    break;
                }
            }
            return 1;

        case 's':
        case 'S':
            for(i=cursorX+1; i<8; i++) {
                if(board[i][cursorY].color == col) {
                    cursorX = i;
                    break;
                }
            }
            return 1;

        case 'd':
        case 'D':
            for(j=cursorY+1; j<8; j++) {
                if(board[cursorX][j].color == col) {
                    cursorY = j;
                    break;
                }
            }
            return 1;

        case 'e':
        case 'E':
            exit(0);
            break;

        case '\r':
            possible_moves();
            int len;
            stackPointer = -1;
            int flag;
            mainX = cursorX;
            mainY = cursorY;
            if(board[cursorX][cursorY].type != EMPTY) {
                if(isMovesHashEmpty() == 0) {
                    len = pieceMoves();
                    do
                    {
                        printBoard();
                        flag = selectPosition(len);
                        //printBoard();
                    }while(flag==1);}
            }

    }

    return 1;
}

int loadingScreen() {
    int i;
    printf("Loading\n");
    for(i=0; i<10; i++) {
        printf("%c",219);
        _sleep(500);
    }
    return 0;
}
void possible_moves() {
    switch(board[cursorX][cursorY].type)
        {
        case PAWN:
            pawn_moves();
            break;
        case ROOK:
            rook_moves();
            break;
        case BISHOP:
            bishop_moves();
            break;
        case KNIGHT:
            knight_moves();
            break;
        case KING:
            king_moves();
            break;
        case QUEEN:
            queen_moves();
            break;
        }
}
//TO PRINT THE POSSIBLE MOVES OF ROOK
int rook_moves()
{
    int i,j;
    i=1;
    while(cursorX+i<8)
    {
        if(board[cursorX+i][cursorY].color==board[cursorX][cursorY].color)
        {
            break;
        }
        else if(board[cursorX+i][cursorY].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX+i][cursorY]=1;
            break;
        }
        moves_hash[cursorX+i][cursorY]=1;
        i++;
    }
    i=1;
    while(cursorX-i>=0)
    {
        if(board[cursorX-i][cursorY].color==board[cursorX][cursorY].color)
        {
            break;
        }
        else if(board[cursorX-i][cursorY].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX-i][cursorY]=1;
            break;
        }
        moves_hash[cursorX-i][cursorY]=1;
        i++;
    }
    i=1;
    while(cursorY+i<8)
    {
        if(board[cursorX][cursorY+i].color==board[cursorX][cursorY].color)
        {
            break;
        }
        else if(board[cursorX][cursorY+i].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX][cursorY+i]=1;
            break;
        }
        moves_hash[cursorX][cursorY+i]=1;
        i++;
    }
    i=1;
    while(cursorY-i>=0)
    {
        if(board[cursorX][cursorY-i].color==board[cursorX][cursorY].color)
        {
            break;
        }
        else if(board[cursorX][cursorY-i].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX][cursorY-i]=1;
            break;
        }
        moves_hash[cursorX][cursorY-i]=1;
        i++;
    }

}
//TO PRINT THE POSSIBLE MOVES OF BISHOP
int bishop_moves()
{
    int i,j;
    i=1;
    j=1;
    while(cursorX+i<8&&cursorY+i<8)
    {
        if(board[cursorX+i][cursorY+j].color==board[cursorX][cursorY].color)
            break;
        else if(board[cursorX+i][cursorY+j].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX+i][cursorY+j]=1;
            break;
        }
        moves_hash[cursorX+i][cursorY+j]=1;
        i++;
        j++;
    }
    i=1;
    j=1;
    while(cursorX+i<8&&cursorY-j>=0)
    {
        if(board[cursorX+i][cursorY-j].color==board[cursorX][cursorY].color)
            break;
        else if(board[cursorX+i][cursorY-j].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX+i][cursorY-j]=1;
            break;
        }
        moves_hash[cursorX+i][cursorY-j]=1;
        i++;
        j++;
    }
    i=1;
    j=1;
    while(cursorX-i>=0&&cursorY-j>=0)
    {
        if(board[cursorX-i][cursorY-j].color==board[cursorX][cursorY].color)
            break;
        else if(board[cursorX-i][cursorY-j].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX-i][cursorY-j]=1;
            break;
        }
        moves_hash[cursorX-i][cursorY-j]=1;
        i++;
        j++;
    }
    i=1;
    j=1;
    while(cursorX-i>=0&&cursorY+j<8)
    {
        if(board[cursorX-i][cursorY+j].color==board[cursorX][cursorY].color)
            break;
        else if(board[cursorX-i][cursorY+j].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX-i][cursorY+j]=1;
            break;
        }
        moves_hash[cursorX-i][cursorY+j]=1;
        i++;
        j++;
    }
}
//TO PRINT THE POSSIBLE MOVES OF QUEEN
int queen_moves()
{
    int i,j;
    i=1;
    while(cursorX+i<8)
    {
        if(board[cursorX+i][cursorY].color==board[cursorX][cursorY].color)
        {
            break;
        }
        else if(board[cursorX+i][cursorY].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX+i][cursorY]=1;
            break;
        }
        moves_hash[cursorX+i][cursorY]=1;
        i++;
    }
    i=1;
    while(cursorX-i>=0)
    {
        if(board[cursorX-i][cursorY].color==board[cursorX][cursorY].color)
        {
            break;
        }
        else if(board[cursorX-i][cursorY].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX-i][cursorY]=1;
            break;
        }
        moves_hash[cursorX-i][cursorY]=1;
        i++;
    }
    i=1;
    while(cursorY+i<8)
    {
        if(board[cursorX][cursorY+i].color==board[cursorX][cursorY].color)
        {
            break;
        }
        else if(board[cursorX][cursorY+i].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX][cursorY+i]=1;
            break;
        }
        moves_hash[cursorX][cursorY+i]=1;
        i++;
    }
    i=1;
    while(cursorY-i>=0)
    {
        if(board[cursorX][cursorY-i].color==board[cursorX][cursorY].color)
        {
            break;
        }
        else if(board[cursorX][cursorY-i].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX][cursorY-i]=1;
            break;
        }
        moves_hash[cursorX][cursorY-i]=1;
        i++;
    }
    i=1;
    j=1;
    while(cursorX+i<8&&cursorY+i<8)
    {
        if(board[cursorX+i][cursorY+j].color==board[cursorX][cursorY].color)
            break;
        else if(board[cursorX+i][cursorY+j].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX+i][cursorY+j]=1;
            break;
        }
        moves_hash[cursorX+i][cursorY+j]=1;
        i++;
        j++;
    }
    i=1;
    j=1;
    while(cursorX+i<8&&cursorY-j>=0)
    {
        if(board[cursorX+i][cursorY-j].color==board[cursorX][cursorY].color)
            break;
        else if(board[cursorX+i][cursorY-j].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX+i][cursorY-j]=1;
            break;
        }
        moves_hash[cursorX+i][cursorY-j]=1;
        i++;
        j++;
    }
    i=1;
    j=1;
    while(cursorX-i>=0&&cursorY-j>=0)
    {
        if(board[cursorX-i][cursorY-j].color==board[cursorX][cursorY].color)
            break;
        else if(board[cursorX-i][cursorY-j].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX-i][cursorY-j]=1;
            break;
        }
        moves_hash[cursorX-i][cursorY-j]=1;
        i++;
        j++;
    }
    i=1;
    j=1;
    while(cursorX-i>=0&&cursorY+j<8)
    {
        if(board[cursorX-i][cursorY+j].color==board[cursorX][cursorY].color)
            break;
        else if(board[cursorX-i][cursorY+j].color==-1*board[cursorX][cursorY].color)
        {
            moves_hash[cursorX-i][cursorY+j]=1;
            break;
        }
        moves_hash[cursorX-i][cursorY+j]=1;
        i++;
        j++;
    }
}
//TO PRINT THE POSSIBLE MOVES OF THE KNIGHT
int knight_moves()
{
    int i,j;
    if(cursorX+2<8&&cursorY+1<8)
    {
        if(board[cursorX+2][cursorY+1].color!=board[cursorX][cursorY].color)
            moves_hash[cursorX+2][cursorY+1]=1;

    }
    if(cursorX+2<8&&cursorY-1>=0)
    {
        if(board[cursorX+2][cursorY-1].color!=board[cursorX][cursorY].color)
            moves_hash[cursorX+2][cursorY-1]=1;

    }
    if(cursorX-2>=0&&cursorY+1<8)
    {
        if(board[cursorX-2][cursorY+1].color!=board[cursorX][cursorY].color)
            moves_hash[cursorX-2][cursorY+1]=1;

    }
    if(cursorX-2>=0&&cursorY-1>=0)
    {
        if(board[cursorX-2][cursorY-1].color!=board[cursorX][cursorY].color)
            moves_hash[cursorX-2][cursorY-1]=1;

    }
    if(cursorX+1<8&&cursorY+2<8)
    {
        if(board[cursorX+1][cursorY+2].color!=board[cursorX][cursorY].color)
            moves_hash[cursorX+1][cursorY+2]=1;
    }
    if(cursorX+1<8&&cursorY-2>=0)
    {
        if(board[cursorX+1][cursorY-2].color!=board[cursorX][cursorY].color)
            moves_hash[cursorX+1][cursorY-2]=1;
    }
    if(cursorX-1>=0&&cursorY+2<8)
    {
        if(board[cursorX-1][cursorY+2].color!=board[cursorX][cursorY].color)
            moves_hash[cursorX-1][cursorY+2]=1;
    }
    if(cursorX-1>=0&&cursorY-2>=0)
    {
        if(board[cursorX-1][cursorY-2].color!=board[cursorX][cursorY].color)
            moves_hash[cursorX-1][cursorY-2]=1;
    }
}
//TO PRINT THE POSSIBLE MOVES OF THE KING
int king_moves()
{
    if(cursorX+1<8)
    {
        if(board[cursorX+1][cursorY].color!=board[cursorX][cursorY].color)
        moves_hash[cursorX+1][cursorY]=1;
    }
    if(cursorX-1>=0)
    {
        if(board[cursorX-1][cursorY].color!=board[cursorX][cursorY].color)
        moves_hash[cursorX-1][cursorY]=1;
    }
    if(cursorY+1<8)
    {
        if(board[cursorX][cursorY+1].color!=board[cursorX][cursorY+1].color)
        moves_hash[cursorX][cursorY+1]=1;
    }
    if(cursorY-1<8)
    {
        if(board[cursorX][cursorY-1].color!=board[cursorX][cursorY-1].color)
        moves_hash[cursorX][cursorY-1]=1;
    }
    if(cursorX+1<8&&cursorY+1<8)
    {
        if(board[cursorX+1][cursorY+1].color!=board[cursorX][cursorY].color)
        moves_hash[cursorX+1][cursorY+1]=1;
    }
    if(cursorX+1<8&&cursorY-1>=0)
    {
        if(board[cursorX+1][cursorY-1].color!=board[cursorX][cursorY].color)
        moves_hash[cursorX+1][cursorY-1]=1;
    }
    if(cursorX-1>=0&&cursorY+1<8)
    {
        if(board[cursorX-1][cursorY+1].color!=board[cursorX][cursorY].color)
        moves_hash[cursorX-1][cursorY+1]=1;
    }
    if(cursorX-1>=0&&cursorY-1>=0)
    {
        if(board[cursorX-1][cursorY-1].color!=board[cursorX][cursorY].color)
        moves_hash[cursorX-1][cursorY-1]=1;
    }
}
//TO PRINT THE POSSIBLE MOVES OF THE PAWN
int pawn_moves()
{
    if(board[cursorX][cursorY].color==1&&front_color==1)
    {
        if(board[cursorX+1][cursorY].color==0)
            moves_hash[cursorX+1][cursorY]=1;
        if(board[cursorX+1][cursorY+1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX+1][cursorY+1]=1;
        if(board[cursorX+1][cursorY-1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX+1][cursorY-1]=1;
    }
    else if(board[cursorX][cursorY].color==-1&&front_color==1)
    {
        if(board[cursorX-1][cursorY].color==0)
            moves_hash[cursorX-1][cursorY]=1;
        if(board[cursorX-1][cursorY-1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX-1][cursorY-1]=1;
        if(board[cursorX-1][cursorY+1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX-1][cursorY+1]=1;
    }
    else if(board[cursorX][cursorY].color==-1&&front_color==-1)
    {
        if(board[cursorX+1][cursorY].color==0)
            moves_hash[cursorX+1][cursorY]=1;
        if(board[cursorX+1][cursorY+1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX+1][cursorY+1]=1;
        if(board[cursorX+1][cursorY-1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX+1][cursorY-1]=1;
    }
    else if(board[cursorX][cursorY].color==1&&front_color==-1)
    {
        if(board[cursorX-1][cursorY].color==0)
            moves_hash[cursorX-1][cursorY]=1;
        if(board[cursorX-1][cursorY-1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX-1][cursorY-1]=1;
        if(board[cursorX-1][cursorY+1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX-1][cursorY+1]=1;
    }
}
//TO VERIFY THE POSSIBLE MOVES ARE AT EXPECTED POSITIONS ARE NOT
void printHash()
{
    resetMovesHash();
    int i,j;
    printf("\n");
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%d ",moves_hash[i][j]);
        }
        printf("\n");
    }
}

int resetMovesHash() {// RESETS THE MOVES_HASH ARRAY TO 0
    int i, j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            moves_hash[i][j] = 0;
        }
    }
}

int instructions() {//  DISPLAYS THE INSTRUCTIONS OF GAME
    printf("Use 'w', 'a', 's' and 'd' to move up, left, down and right respectively.");
    printf("\n\n");
    printf("     w                        /\\");
    printf("\n                    =             ");
    printf("\na    s    d             <-    \\/   ->");
    printf("\n\n");
    printf("Press 'e' to exit the game.\n");
    printf("Press 'Enter' to select a piece to move it.\n");
    //printf("Press 'Space' to move a piece.\n\n\n");
}

int selectPosition(int len) {
    char ch;
    printf("'n': next piece\n");
    printf("'p': previous piece\n");
    printf("press 'm' to move or 'r' to return: ");
    ch = getche();
    switch(ch) {
        case 'n':
        case 'N':
            if(stackPointer<len-1) {
                stackPointer++;
                cursorX = stacky[stackPointer].x;
                cursorY = stacky[stackPointer].y;
            }
            return 1;
            break;

        case 'P':
        case 'p':
            if(stackPointer>0) {
                stackPointer--;
                cursorX = stacky[stackPointer].x;
                cursorY = stacky[stackPointer].y;
            }
            return 1;
            break;

        case 'm':
        case 'M':
            if(mainX != cursorX || mainY != cursorY) {
                resetMovesHash();
                piece current = board[mainX][mainY];
                if(current.type == KING) {
                    if(current.color == WHITE) {
                        whiteKing.x = cursorX;
                        whiteKing.y = cursorY;
                    }else if (current.color == BLACK) {
                        blackKing.x = cursorX;
                        blackKing.y = cursorY;
                    }
                }
                swapPieces(&board[mainX][mainY], &board[cursorX][cursorY]);
                moved = 1;
                return 0;
            }
            break;

        case 'r':
        case 'R':
            return 0;
            break;
    }

}

int pieceMoves() {
    int i, j, k = 0;
    //current = (struct node*)malloc(sizeof(struct node));
    //next = current;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            if(moves_hash[i][j]) {
                    stacky[k].x = i;
                    stacky[k].y = j;
                    k++;
            }
        }
    }
    //next->X = 100;
    //printStacky(k);
    return k;
}

int staleMate(int color) {//    TAKES THE COLOR AS INPUT AND RETURNS 1 IF A STALEMATE OCCURED OTHERWISE 0 IS RETURNED
    int i, j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            if(board[i][j].color == color)
            switch(board[i][j].type)
            {
            case PAWN:
                pawn_moves();
                break;
            case ROOK:
                rook_moves();
                break;
            case BISHOP:
                bishop_moves();
                break;
            case KNIGHT:
                knight_moves();
                break;
            case KING:
                king_moves();
                break;
            case QUEEN:
                queen_moves();
                break;
            }
        }
    }
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            if(moves_hash[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int isMovesHashEmpty() {//  RETURNS 1 IF MOVESHASH IF EMPTY, 0 OTHERWISE
    int i, j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            if(moves_hash[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int printStacky(int len) {
    system("cls");
    int i;
    for(i=0; i<len; i++) {
        printf("%d\t%d\n", stacky[i].x, stacky[i].y);
    }
    system("pause");
    system("cls");
}
