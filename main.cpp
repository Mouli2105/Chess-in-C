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
int handleCursor();
int loadingScreen();

//  DECLARING GLOBAL VARIABLES
int moves_hash[8][8]={0};
int whitePieces[6]={PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
int front_color,rear_color;
int cursorX = 0;
int cursorY = 0;

struct piece {
    int type;// LIKE PAWN, ROOK, BISHOP, etc
    int color;
}board[8][8];

//  MAIN METHOD
int main() {
    initializeBoard();
    do {
        printBoard();
    }while(handleCursor());
    possible_moves();
    printBoard();
    printHash();
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
    board[0][4].type = board[7][4].type = KING;
    for(i=0; i<8; i++)
        board[0][i].color = WHITE;
    for(i=0; i<8; i++)
        board[1][i].color = WHITE;
    for(i=0; i<8; i++)
        board[7][i].color = BLACK;
    for(i=0; i<8; i++)
        board[6][i].color = BLACK;
    front_color = 1;
    rear_color = -1;

    return 1;
}

int printBoard() {//    DISPLAYS THE BOARD IN A SIMPLE WAY
    system("cls");
    printf("--[w]---[a]---[s]---[d]---[e]---\n\n\n");
    int i, j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            switch(board[i][j].type) {
                case PAWN:
                    if(i == cursorX && j == cursorY) {
                        if(moves_hash[i][j]!=1)
                            printf("[P] ");
                        else
                            printf("[P]*");
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" P  ");
                        else
                            printf(" P* ");
                    }
                    break;

                case ROOK:
                    if(i == cursorX && j == cursorY) {
                        if(moves_hash[i][j]!=1)
                            printf("[R] ");
                        else
                            printf("[R]*");
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" R  ");
                        else
                            printf(" R* ");
                    }
                    break;

                case BISHOP:
                    if(i == cursorX && j == cursorY) {
                        printf("[B] ");
                    }else {
                        printf(" B  ");
                    }
                    break;

                case KNIGHT:
                    if(i == cursorX && j == cursorY) {
                        printf("[N] ");
                    }else {
                        printf(" N  ");
                    }
                    break;

                case QUEEN:
                    if(i == cursorX && j == cursorY) {
                        printf("[N] ");
                    }else {
                        printf(" N  ");
                    }
                    break;

                case KING:
                    if(i == cursorX && j == cursorY) {
                        printf("[K] ");
                    }else {
                        printf(" K  ");
                    }
                    break;

                case EMPTY:
                    if(i == cursorX && j == cursorY) {
                        if(moves_hash[i][j]!=1)
                            printf("[-] ");
                        else
                            printf("[-]*");
                    }else {
                        if(moves_hash[i][j]!=1)
                            printf(" -  ");
                        else
                            printf(" -* ");
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
            return 1;

        case 'a':
        case 'A':
            if(cursorY > 0) {
                cursorY--;
            }
            return 1;

        case 's':
        case 'S':
            if(cursorX < 7) {
                cursorX++;
            }
            return 1;

        case 'd':
        case 'D':
            if(cursorY < 7) {
                cursorY++;
            }
            return 1;

        case 'e':
        case 'E':
            exit(0);
            break;
        case ' ':
            system("pause");
            break;
        case '\r':
            return 0;
    }
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
void possible_moves()
{
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
    if(front_color==1&&cursorX<8)
    {
        if(board[cursorX+1][cursorY].color==0)
            moves_hash[cursorX+1][cursorY]=1;
        if(board[cursorX+1][cursorY+1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX+1][cursorY+1]=1;
        if(board[cursorX+1][cursorY-1].color==-1*board[cursorX][cursorY].color)
            moves_hash[cursorX+1][cursorY-1]=1;
    }
}
//TO VERIFY THE POSSIBLE MOVES ARE AT EXPECTED POSITIONS ARE NOT
void printHash()
{
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
