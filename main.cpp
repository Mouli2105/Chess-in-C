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
#define horizontal_line 196
#define vertical_line 179
#define top_right_corner 191
#define top_left_corner 218
#define bottom_right_corner 217
#define bottom_left_corner 192
#define plus 197

//  DECLARING PROTOTYPES
void printPiece(int i, int j, char piece);
void printBoard2();
int getpos(int i,int j);
int aboutUs();
int instructions();
int startGame();
int welcome();
int mainMenu();
int check();
int printStacky(int len);
int isMovesHashEmpty();
int staleMate();
int pieceMoves();
int selectPosition(int len);
int controls();
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
int swapPieces(struct piece *a, struct piece *b, int newX, int newY);
int handleCursor(int color);
int loadingScreen(char c, int time);
int setCursor();
int setHashCheckMate();
void resetCheckHash();

//  DECLARING GLOBAL VARIABLES
int count_v=0;
int started = 0;
int moved = 0;
int stackPointer = -1;
int mainX;
int mainY;
int moves_hash[8][8]={0};
int checkmate_hash[8][8]={0};
int front_color,rear_color;
int cursorX = 0;
int cursorY = 0;
int col = WHITE;
int check_flag;
int ifCheck = 0;
int tempcursorX;
int tempcursorY;

struct piece {
    int type;
    int color;
}board[8][8], checkingPiece;

struct coord {
    int x;
    int y;
}positionStack[32], whiteKing, blackKing;

//  MAIN METHOD
//int main() {
//    if(started == 0) {
//        welcome();
//    }
//    system("color 0a");
//    int a;
//    int endGame = 0;
//    do {
//        a = mainMenu();
//        switch(a) {
//            case 1:
//                endGame = startGame();
//                break;
//
//            case 2:
//                instructions();
//                break;
//
//            case 3:
//                controls();
//                break;
//
//            case 4:
//                aboutUs();
//                break;
//
//            case 5:
//                system("cls");
//                printf("\n\n\n\n\t\t\t\t\tThank you!\n\n\n\n\t\t\t\t\t");
//                system("pause");
//                exit(0);
//                break;
//
//        }
//    }while(a!=1 && a!=5 && endGame==0);
//    started = 1;
//    if(endGame) {
//        main();
//    }
//    return 0;
//}

int main() {
    startGame();
    return 0;
}

int setHashCheckMate() {
    int i,j;
    check_flag = 1;
    tempcursorX = cursorX;
    tempcursorY = cursorY;
    for(cursorX=0; cursorX<8; cursorX++) {
        for(cursorY=0; cursorY<8; cursorY++) {
            if(board[cursorX][cursorY].color == col){
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

                    default:
                        break;
                }
                if(check()) {
                    printf("\n\t\t\tCHECK");
                    system("pause");
                    checkingPiece = board[cursorX][cursorY];
                    resetCheckHash();
                    break;
                }else{
                    resetCheckHash();
                }
                resetMovesHash();
            }
        }
    }
    cursorX = tempcursorX;
    cursorY = tempcursorY;
    check_flag = 0;
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
    whiteKing.y = 4;//  USE THESE
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
    int i, j,pos;
    printf("\t\t ----------[c]--controls-----------------[e]--exit to main menu-----------\n\n");
    for(i=0; i<8; i++) {
        printf("\t\t");
        printf(" %c", 218);
        for(j=1; j<48; j++) {
            if(j%6==0 && j!=0 && j!=48) {
                printf("%c  %c", 191, 218);
            }else {
                printf("%c", 196);
            }
        }
        printf("%c\n", 191);
        printf("\t\t");
        for(j=0; j<8; j++) {
            pos=getpos(i,j);
            switch(board[i][j].type) {
                case PAWN:
                    if(i == cursorX && j == cursorY) {
                        if(board[i][j].color == -1) {
                            printf(" %c%c[P]%c%c ", 175, 175, 174, 174);
                        }else {
                            printf(" %c%c P %c%c ", 175, 175, 174, 174);
                        }
                    }else {
                        if(moves_hash[i][j]!=1){
                            if(board[i][j].color == -1) {
                                printf(" %c [P] %c ", 179, 179);
                            }else {
                                printf(" %c  P  %c ", 179, 179);
                            }
                        }else {
                            if(board[i][j].color == -1) {
                                printf(" %c%c[P]%c%c ", 179, 222, 221, 179);
                            }else {
                                printf(" %c %cP%c %c ", 179, 222, 221, 179);
                            }
                        }
                    }
                    break;

                case ROOK:
                    if(i == cursorX && j == cursorY) {
                        if(board[i][j].color == -1) {
                            printf(" %c%c[R]%c%c ", 175, 175, 174, 174);
                        }else {
                            printf(" %c%c R %c%c ", 175, 175, 174, 174);
                        }
                    }else {
                        if(moves_hash[i][j]!=1){
                            if(board[i][j].color == -1) {
                                printf(" %c [R] %c ", 179, 179);
                            }else {
                             printf(" %c  R  %c ", 179, 179);
                            }
                        }else {
                            if(board[i][j].color == -1) {
                                printf(" %c%c[R]%c%c ", 179, 222, 221, 179);
                            }else {
                                printf(" %c %cR%c %c ", 179, 222, 221, 179);
                            }
                        }
                    }
                    break;

                case BISHOP:
                    if(i == cursorX && j == cursorY) {
                        if(board[i][j].color == -1) {
                            printf(" %c%c[B]%c%c ", 175, 175, 174, 174);
                        }else {
                            printf(" %c%c B %c%c ", 175, 175, 174, 174);
                        }
                    }else {
                        if(moves_hash[i][j]!=1){
                            if(board[i][j].color == -1) {
                                printf(" %c [B] %c ", 179, 179);
                            }else {
                                printf(" %c  B  %c ", 179, 179);
                            }
                        }else {
                            if(board[i][j].color == -1) {
                                printf(" %c%c[B]%c%c ", 179, 222, 221, 179);
                            }else {
                                printf(" %c %cB%c %c ", 179, 222, 221, 179);
                            }
                        }
                    }
                    break;

                case KNIGHT:
                    if(i == cursorX && j == cursorY) {
                        if(board[i][j].color == -1) {
                            printf(" %c%c[N]%c%c ", 175, 175, 174, 174);
                        }else {
                            printf(" %c%c N %c%c ", 175, 175, 174, 174);
                        }
                    }else {
                        if(moves_hash[i][j]!=1){
                            if(board[i][j].color == -1) {
                                printf(" %c [N] %c ", 179, 179);
                            }else {
                                printf(" %c  N  %c ", 179, 179);
                            }
                        }else {
                            if(board[i][j].color == -1) {
                                printf(" %c%c[N]%c%c ", 179, 222, 221, 179);
                            }else {
                                printf(" %c %cN%c %c ", 179, 222, 221, 179);
                            }
                        }
                    }
                    break;

                case QUEEN:
                    if(i == cursorX && j == cursorY) {
                        if(board[i][j].color == -1) {
                            printf(" %c%c[Q]%c%c ", 175, 175, 174, 174);
                        }else {
                            printf(" %c%c Q %c%c ", 175, 175, 174, 174);
                        }
                    }else {
                        if(moves_hash[i][j]!=1){
                            if(board[i][j].color == -1) {
                                printf(" %c [Q] %c ", 179, 179);
                            }else {
                                printf(" %c  Q  %c ", 179, 179);
                            }
                        }
                        else{
                            if(board[i][j].color == -1) {
                                printf(" %c%c[Q]%c%c ", 179, 222, 221, 179);
                            }else {
                                printf(" %c %cQ%c %c ", 179, 222, 221, 179);
                            }
                        }
                    }
                    break;

                case KING:
                    if(i == cursorX && j == cursorY) {
                        if(board[i][j].color == -1) {
                            printf(" %c%c[K]%c%c ", 175, 175, 174, 174);
                        }else {
                            printf(" %c%c K %c%c ", 175, 175, 174, 174);
                        }
                    }else {
                        if(moves_hash[i][j]!=1){
                            if(board[i][j].color == -1) {
                                printf(" %c [K] %c ", 179, 179);
                            }else {
                                printf(" %c  K  %c ", 179, 179);
                            }
                        }
                        else{
                            if(board[i][j].color == -1) {
                                printf(" %c%c[K]%c%c ", 179, 222, 221, 179);
                            }else {
                                printf(" %c %cK%c %c ", 179, 222, 221, 179);
                            }
                        }
                    }
                    break;

                case EMPTY:
                    if(i == cursorX && j == cursorY) {
                        printf(" %c%c   %c%c ", 175, 175, 174, 174);
                    }else {
                        if(moves_hash[i][j]!=1){
                            printf(" %c     %c ", 179, 179);
                        }else {
                            printf(" %c  %c  %c ", 179, 219, 179);
                        }
                    }
                    break;
            }
        }
        printf("\n");
        printf("\t\t");
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

int getpos(int i,int j){
    return ((i+1)/8)+((j+1)%8);
}

int swapPieces(struct piece *a, struct piece *b, int newX, int newY) {//    SWAPS TWO PIECES ON THE BOARD
    if(a->type == KING){
        if(a->color == WHITE){
            whiteKing.x = newX;
            whiteKing.y = newY;
        }else if(a->color == BLACK) {
            blackKing.x = newX;
            blackKing.y = newY;
        }
    }
    *b = *a;
    a->type = EMPTY;
    a->color = 0;
    resetMovesHash();
    return 1;
}

int handleCursor(int col) {//  TAKES THE INPUT FROM USER AND MOVES THE CURSOR ACCORDINGLY
    char ch;
    int i, j;
    fflush(stdin);
    ch = getche();
    switch(ch) {
        case 'w':
        case 'W':
            _beep(250, 100);
            for(int i=cursorX-1; i>=0; i--) {
                if(board[i][cursorY].color == col || board[i][cursorY].color == 0) {
                    cursorX = i;
                    break;
                }
            }
            return 1;

        case 'a':
        case 'A':
            _beep(300, 100);
            for(int i=cursorY-1; i>=0; i--) {
                if(board[cursorX][i].color == col || board[cursorX][i].color == 0) {
                    cursorY = i;
                    break;
                }
            }
            return 1;

        case 's':
        case 'S':
            _beep(350, 100);
            for(int i=cursorX+1; i<=7; i++) {
                if(board[i][cursorY].color == col || board[i][cursorY].color == 0) {
                    cursorX = i;
                    break;
                }
            }
            return 1;

        case 'd':
        case 'D':
            _beep(400, 100);
            for(int i=cursorY+1; i<=7; i++) {
                if(board[cursorX][i].color == col || board[cursorX][i].color == 0) {
                    cursorY = i;
                    break;
                }
            }
            return 1;

        case 'e':
        case 'E':
            cursorX = 0;
            cursorY = 0;
            return 0;
            break;

        case 'c':
        case 'C':
            controls();
            return 1;

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
                    do {
                        printBoard2();
                        flag = selectPosition(len);
                    }while(flag==1);
                }
            }

    }
    return 1;
}

int loadingScreen(char c, int time) {   //  DISPLAYS THE LOADING SCREEN
    int i;
    printf("\n\n\n\n\t\t\t\t\t\tLoading");
    for(i=0; i<8; i++) {
        printf("%c",c);
        _sleep(time);
    }
    return 0;
}

void possible_moves() { //  FIND THE POSSIBLE MOVES OF CURRENT PIECE
    switch(board[cursorX][cursorY].type) {
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

int rook_moves() {//    TO PRINT THE POSSIBLE MOVES OF ROOK
    int i, j;
    i = 1;
    while(cursorX+i<8) {
        if(board[cursorX+i][cursorY].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX+i][cursorY].color==-1*board[cursorX][cursorY].color)
        {
            if(check_flag) {
                checkmate_hash[cursorX+i][cursorY] = 1;
            }else {
                moves_hash[cursorX+i][cursorY] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX+i][cursorY] = 1;
        }else {
            moves_hash[cursorX+i][cursorY] = 1;
        }
        i++;
    }
    i = 1;
    while(cursorX-i>=0) {
        if(board[cursorX-i][cursorY].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX-i][cursorY].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-i][cursorY] = 1;
            }else {
                moves_hash[cursorX-i][cursorY] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX-i][cursorY] = 1;
        }else {
            moves_hash[cursorX-i][cursorY] = 1;
        }
        i++;
    }
    i = 1;
    while(cursorY+i<8) {
        if(board[cursorX][cursorY+i].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX][cursorY+i].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX][cursorY+i] = 1;
            }else {
                moves_hash[cursorX][cursorY+i] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX][cursorY+i] = 1;
        }else {
            moves_hash[cursorX][cursorY+i] = 1;
        }
        i++;
    }
    i = 1;
    while(cursorY-i>=0) {
        if(board[cursorX][cursorY-i].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX][cursorY-i].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX][cursorY-i] = 1;
            }else {
                moves_hash[cursorX][cursorY-i] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX][cursorY-i] = 1;
        }else {
            moves_hash[cursorX][cursorY-i] = 1;
        }
        i++;
    }
}

int bishop_moves() {    //TO PRINT THE POSSIBLE MOVES OF BISHOP
    int i, j;
    i = 1;
    j = 1;
    while(cursorX+i<8&&cursorY+i<8) {
        if(board[cursorX+i][cursorY+j].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX+i][cursorY+j].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+i][cursorY+j]=1;
            }else {
                moves_hash[cursorX+i][cursorY+j]=1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX+i][cursorY+j]=1;
        }else {
            moves_hash[cursorX+i][cursorY+j]=1;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while(cursorX+i<8&&cursorY-j>=0) {
        if(board[cursorX+i][cursorY-j].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX+i][cursorY-j].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+i][cursorY-j]=1;
            }else {
                moves_hash[cursorX+i][cursorY-j]=1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX+i][cursorY-j]=1;
        }else {
            moves_hash[cursorX+i][cursorY-j]=1;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while(cursorX-i>=0&&cursorY-j>=0) {
        if(board[cursorX-i][cursorY-j].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX-i][cursorY-j].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-i][cursorY-j]=1;
            }else {
                moves_hash[cursorX-i][cursorY-j]=1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX-i][cursorY-j]=1;
        }else {
            moves_hash[cursorX-i][cursorY-j]=1;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while(cursorX-i>=0&&cursorY+j<8) {
        if(board[cursorX-i][cursorY+j].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX-i][cursorY+j].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-i][cursorY+j]=1;
            }else {
                moves_hash[cursorX-i][cursorY+j]=1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX-i][cursorY+j]=1;
        }else {
            moves_hash[cursorX-i][cursorY+j]=1;
        }
        i++;
        j++;
    }
}

int queen_moves() { //TO PRINT THE POSSIBLE MOVES OF QUEEN
    int i, j;
    i = 1;
    while(cursorX+i<8) {
        if(board[cursorX+i][cursorY].color==board[cursorX][cursorY].color){
            break;
        }else if(board[cursorX+i][cursorY].color==-1*board[cursorX][cursorY].color) {
            if(check_flag)  {
                checkmate_hash[cursorX+i][cursorY] = 1;
            }else {
                moves_hash[cursorX+i][cursorY] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX+i][cursorY] = 1;
        }else {
            moves_hash[cursorX+i][cursorY] = 1;
        }
        i++;
    }
    i = 1;
    while(cursorX-i>=0) {
        if(board[cursorX-i][cursorY].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX-i][cursorY].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-i][cursorY] = 1;
            }else {
                moves_hash[cursorX-i][cursorY] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX-i][cursorY] = 1;
        }else {
            moves_hash[cursorX-i][cursorY] = 1;
        }
        i++;
    }
    i = 1;
    while(cursorY+i<8) {
        if(board[cursorX][cursorY+i].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX][cursorY+i].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX][cursorY+i] = 1;
            }else {
                moves_hash[cursorX][cursorY+i] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX][cursorY+i] = 1;
        }else {
            moves_hash[cursorX][cursorY+i] = 1;
        }
        i++;
    }
    i = 1;
    while(cursorY-i>=0) {
        if(board[cursorX][cursorY-i].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX][cursorY-i].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX][cursorY-i] = 1;
            }else {
                moves_hash[cursorX][cursorY-i] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX][cursorY-i] = 1;
        }else {
            moves_hash[cursorX][cursorY-i] = 1;
        }
        i++;
    }
    j = 1;
    while(cursorX+i<8&&cursorY+i<8) {
        if(board[cursorX+i][cursorY+j].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX+i][cursorY+j].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+i][cursorY+j]=1;
            }else {
                moves_hash[cursorX+i][cursorY+j]=1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX+i][cursorY+j]=1;
        }else {
            moves_hash[cursorX+i][cursorY+j]=1;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while(cursorX+i<8&&cursorY-j>=0) {
        if(board[cursorX+i][cursorY-j].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX+i][cursorY-j].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+i][cursorY-j] = 1;
            }else {
                moves_hash[cursorX+i][cursorY-j] = 1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX+i][cursorY-j] = 1;
        }else {
            moves_hash[cursorX+i][cursorY-j] = 1;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while(cursorX-i>=0&&cursorY-j>=0) {
        if(board[cursorX-i][cursorY-j].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX-i][cursorY-j].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-i][cursorY-j]=1;
            }else {
                moves_hash[cursorX-i][cursorY-j]=1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX-i][cursorY-j]=1;
        }else {
            moves_hash[cursorX-i][cursorY-j]=1;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while(cursorX-i>=0&&cursorY+j<8) {
        if(board[cursorX-i][cursorY+j].color==board[cursorX][cursorY].color) {
            break;
        }else if(board[cursorX-i][cursorY+j].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-i][cursorY+j]=1;
            }else {
                moves_hash[cursorX-i][cursorY+j]=1;
            }
            break;
        }
        if(check_flag) {
            checkmate_hash[cursorX-i][cursorY+j]=1;
        }else {
            moves_hash[cursorX-i][cursorY+j]=1;
        }
        i++;
        j++;
    }
}

int knight_moves() {    //TO PRINT THE POSSIBLE MOVES OF THE KNIGHT
    int i, j;
    if(cursorX+2<8&&cursorY+1<8) {
        if(board[cursorX+2][cursorY+1].color!=board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+2][cursorY+1]=1;
            }else {
                moves_hash[cursorX+2][cursorY+1]=1;
			}
        }
    }
    if(cursorX+2<8&&cursorY-1>=0) {
        if(board[cursorX+2][cursorY-1].color!=board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+2][cursorY-1]=1;
            }else {
                moves_hash[cursorX+2][cursorY-1]=1;
			}
        }
    }
    if(cursorX-2>=0&&cursorY+1<8) {
        if(board[cursorX-2][cursorY+1].color!=board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-2][cursorY+1]=1;
			}else {
                moves_hash[cursorX-2][cursorY+1]=1;
			}
        }
    }
    if(cursorX-2>=0&&cursorY-1>=0) {
        if(board[cursorX-2][cursorY-1].color!=board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-2][cursorY-1]=1;
            }else {
                moves_hash[cursorX-2][cursorY-1]=1;
			}
        }
    }
    if(cursorX+1<8&&cursorY+2<8) {
        if(board[cursorX+1][cursorY+2].color!=board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY+2]=1;
			}else {
                moves_hash[cursorX+1][cursorY+2]=1;
			}
        }

    }
    if(cursorX+1<8&&cursorY-2>=0) {
        if(board[cursorX+1][cursorY-2].color!=board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY-2]=1;
			}else {
                moves_hash[cursorX+1][cursorY-2]=1;
			}
        }
    }
    if(cursorX-1>=0&&cursorY+2<8) {
        if(board[cursorX-1][cursorY+2].color!=board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-1][cursorY+2]=1;
			}else {
                moves_hash[cursorX-1][cursorY+2]=1;
			}
        }
    }
    if(cursorX-1>=0&&cursorY-2>=0) {
        if(board[cursorX-1][cursorY-2].color!=board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-1][cursorY-2]=1;
			}else {
                moves_hash[cursorX-1][cursorY-2]=1;
			}
        }
    }
}

int king_moves() {  //TO PRINT THE POSSIBLE MOVES OF THE KING
    if(cursorX+1<8) {
		if(board[cursorX+1][cursorY].color!=board[cursorX][cursorY].color) {
			if(check_flag) {
				checkmate_hash[cursorX+1][cursorY] = 1;
			}else {
            moves_hash[cursorX+1][cursorY] = 1;
			}
		}
    }
    if(cursorX-1>=0){
        if(board[cursorX-1][cursorY].color!=board[cursorX][cursorY].color) {
			if(check_flag) {
				checkmate_hash[cursorX-1][cursorY] = 1;
			}else {
				moves_hash[cursorX-1][cursorY] = 1;
			}
        }
    }
    if(cursorY+1<8) {
        if(board[cursorX][cursorY+1].color!=board[cursorX][cursorY+1].color) {
			if(check_flag) {
				checkmate_hash[cursorX][cursorY+1]=1;
			}else {
				moves_hash[cursorX][cursorY+1] = 1;
			}
        }
    }
    if(cursorY-1<8) {
        if(board[cursorX][cursorY-1].color!=board[cursorX][cursorY-1].color) {
			if(check_flag) {
				checkmate_hash[cursorX][cursorY-1] = 1;
			}else {
				moves_hash[cursorX][cursorY-1]=1;
			}
        }
    }
    if(cursorX+1<8&&cursorY+1<8) {
        if(board[cursorX+1][cursorY+1].color!=board[cursorX][cursorY].color) {
			if(check_flag) {
				checkmate_hash[cursorX+1][cursorY+1];
			}else {
				moves_hash[cursorX+1][cursorY+1]=1;
			}
        }
    }
    if(cursorX+1<8&&cursorY-1>=0) {
        if(board[cursorX+1][cursorY-1].color!=board[cursorX][cursorY].color) {
			if(check_flag) {
				checkmate_hash[cursorX+1][cursorY-1];
			}else {
				moves_hash[cursorX+1][cursorY-1]=1;
			}
        }
    }
    if(cursorX-1>=0&&cursorY+1<8) {
        if(board[cursorX-1][cursorY+1].color!=board[cursorX][cursorY].color) {
			if(check_flag) {
				checkmate_hash[cursorX-1][cursorY+1];
			}else {
				moves_hash[cursorX-1][cursorY+1]=1;
			}
        }
    }
    if(cursorX-1>=0&&cursorY-1>=0) {
        if(board[cursorX-1][cursorY-1].color!=board[cursorX][cursorY].color) {
			if(check_flag) {
				checkmate_hash[cursorX-1][cursorY-1];
			}else {
				moves_hash[cursorX-1][cursorY-1]=1;
			}
        }
    }
}

int pawn_moves() {  //TO PRINT THE POSSIBLE MOVES OF THE PAWN
    if(board[cursorX][cursorY].color==1&&front_color==1) {
        if(board[cursorX+1][cursorY].color==0) {
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY]=1;
			}else {
                moves_hash[cursorX+1][cursorY]=1;
			}
        }else if(board[cursorX+1][cursorY+1].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY+1]=1;
			}else {
                moves_hash[cursorX+1][cursorY+1]=1;
			}
        }else if(board[cursorX+1][cursorY-1].color==-1*board[cursorX][cursorY].color){
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY-1]=1;
			}else {
                moves_hash[cursorX+1][cursorY-1]=1;
			}
        }
        if(cursorX == 1) {
            if(board[cursorX+2][cursorY].color == EMPTY) {
				if(check_flag) {
					checkmate_hash[cursorX+2][cursorY] = 1;
				}else {
					moves_hash[cursorX+2][cursorY] = 1;
				}
            }
        }
    }else if(board[cursorX][cursorY].color==-1&&front_color==1) {
        if(board[cursorX-1][cursorY].color==0) {
			if(check_flag) {
                checkmate_hash[cursorX-1][cursorY]=1;
			}else {
                moves_hash[cursorX-1][cursorY]=1;
			}
        }
        if(board[cursorX-1][cursorY-1].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-1][cursorY-1]=1;
			}else {
                moves_hash[cursorX-1][cursorY-1]=1;
			}
        }
        if(board[cursorX-1][cursorY+1].color==-1*board[cursorX][cursorY].color) {
            if(check_flag) {
                checkmate_hash[cursorX-1][cursorY+1]=1;
			}else {
                moves_hash[cursorX-1][cursorY+1]=1;
			}
        }
    }
    if(cursorX == 6) {
        if(board[cursorX-2][cursorY].color == EMPTY) {
            if(check_flag) {
                checkmate_hash[cursorX-2][cursorY] = 1;
            }else {
                moves_hash[cursorX-2][cursorY] = 1;
			}
        }
    }
}

void printHash() {  //TO VERIFY THE POSSIBLE MOVES ARE AT EXPECTED POSITIONS ARE NOT
    resetMovesHash();
    int i, j;
    printf("\n");
    for(i=0; i<8; i++) {
        for(j=0;j<8;j++) {
            printf("%d ",moves_hash[i][j]);
        }
        printf("\n");
    }
}

int resetMovesHash() {  // RESETS THE MOVES_HASH ARRAY TO 0
    int i, j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            moves_hash[i][j] = 0;
        }
    }
}

int controls() {    //  DISPLAYS THE INSTRUCTIONS OF GAME
    system("cls");
    printf("\n\n\t\t\t\t\t\tW       :       UP\n");
    printf("\n\n\t\t\t\t\t\tA       :       LEFT\n");
    printf("\n\n\t\t\t\t\t\tS       :       DOWN\n");
    printf("\n\n\t\t\t\t\t\tD       :       RIGHT\n");
    printf("\n\n\t\t\t\t\t\tENTER   :       SELECT PIECE\n");
    printf("\n");
    printf("\n\n\t\t\t\t\t\tE       :       EXIT\n");
    printf("\n\n\n\n\t\t");
    system("pause");
    system("cls");
}

int selectPosition(int len) {   // HELPS THE USER TO DECICE TO PICK LOCATION, MOVE PIECE OR RETURN BACK
    char ch;
    int beepsound;
    printf("N: NEXT POSITION\n");
    printf("P: PREVIOUS POSITION\n");
    printf("M: MOVE PIECE\n");
    printf("R: RETURN\n\n");
    printf("ENTER:  ");
    ch = getche();
    switch(ch) {
        case 'n':
        case 'N':
            if(stackPointer<len-1) {
                stackPointer++;
                cursorX = positionStack[stackPointer].x;
                cursorY = positionStack[stackPointer].y;
            }
            return 1;
            break;

        case 'P':
        case 'p':
            if(stackPointer>0) {
                stackPointer--;
                cursorX = positionStack[stackPointer].x;
                cursorY = positionStack[stackPointer].y;
            }
            return 1;
            break;

        case 'm':
        case 'M':
            if(mainX != cursorX || mainY != cursorY) {
                resetMovesHash();
                piece current = board[mainX][mainY];
                swapPieces(&board[mainX][mainY], &board[cursorX][cursorY],cursorX,cursorY);
                setHashCheckMate();
                //system("pause");
                moved++;
                setCursor();
                if(moved%2==0) {
                    col = WHITE;
				}else {
                    col = BLACK;
                }
            }
            return 0;
            break;

        case 'r':
        case 'R':
            return 0;
            break;
    }
}

void resetCheckHash() {
    int i,j;
    for(i=0; i<8; i++) {
        for(j=0 ; j<8; j++) {
            checkmate_hash[i][j] = 0;
        }
    }
}

int check() {   // RETURNS 1 IF ITS A CHECK, 0 OTHERWISE
    int i, j;
    if( col == WHITE) {
        if(checkmate_hash[blackKing.x][blackKing.y]) {
            return 1;
        }
    }else if( col == BLACK) {
        if(checkmate_hash[whiteKing.x][whiteKing.y]) {
            return 1;
        }
    }
    return 0;
}

int setCursor() {
    int i,j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            if(board[i][j].color == -1*col) {
                cursorX = i;
                cursorY = j;
                return 1;
            }
        }
    }
    return 1;
}

int pieceMoves() {  //  INITIALISES A STACK WITH ALL POSSIBLE MOVES FOR TRAVERSAL
    int i, j, k = 0;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            if(moves_hash[i][j]) {
                    positionStack[k].x = i;
                    positionStack[k].y = j;
                    k++;
            }
        }
    }
    return k;
}

int staleMate(int color) {//    TAKES THE COLOR AS INPUT AND RETURNS 1 IF A STALEMATE OCCURED OTHERWISE 0 IS RETURNED
    int i, j;
    for(i=0; i<8; i++) {
        for(j=0; j<8; j++) {
            if(board[i][j].color == color) {
				switch(board[i][j].type) {
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

int welcome() {
    printf("\n\n\n\n\t\t\t\t\t\tWelcome to ChessC !!\n");
    loadingScreen('.', 300);
}

int mainMenu() {
    char ch;
    do {
        system("cls");
        printf("\n\n\n\n\t\t\t\t\t\tMAIN MENU");
        printf("\n\n\t\t\t\t\t\t1. TWO PLAYER MODE");
        printf("\n\n\t\t\t\t\t\t2. HOW TO PLAY CHESS?");
        printf("\n\n\t\t\t\t\t\t3. CONTROLS");
        printf("\n\n\t\t\t\t\t\t4. ABOUT US");
        printf("\n\n\t\t\t\t\t\t5. EXIT GAME");
        printf("\n\n\n\n\n\t\t\t\t\t\tENTER: ");
        ch = getche();
    }while(ch!='1' && ch!='2' && ch!='3' && ch!= '4' && ch!='5');
    system("cls");
    return(ch-48);
}

int startGame() {
    initializeBoard();
    system("color 0e");
    do {
        possible_moves();
        printBoard2();
        resetMovesHash();
    }while(handleCursor(col));
    return 1;
}

int instructions() {
    printf("\n\n\n\n\t\t\t\t\tThe player controlling the white pieces is named 'White'; the player controlling the black pieces is named 'Black'. White moves first, then players alternate moves. Making a move is required; it is not legal to skip a move, even when having to move is detrimental. Play continues until a king is checkmated, a player resigns, or a draw is declared, as explained below. In addition, if the game is being played under a time control players who exceed their time limit lose the game. The official chess rules do not include a procedure for determining who plays White. Instead, this decision is left open to tournament-specific rules (e.g. a Swiss system tournament or Round-robin tournament) or, in the case of non-competitive play, mutual agreement, in which case some kind of random choice is often employed. A common method is for one player to conceal a piece (usually a pawn) of each color in either hand; the other player chooses a hand to open, and receives the color of the piece that is revealed.");
    printf("\n");
    system("pause");
    system("cls");
    return 1;
}

int aboutUs() {
    printf("\n\n\n\n\t\t\t\t\tSunny");
    printf("\n\n\n\n\t\t\t\t\tSreekara Mouli. T");
    printf("\n");
    printf("\n\n\n\n\t\t\tYou can find the source code to this project at: https://github.com/MouliTadinada/Chess-in-C\n\n\n");
    system("pause");
    system("cls");
    return 1;
}

void printBoard2() {
    system("cls");
    int i, j, k, pos;
    printf("\t\t\t ----------[c]--controls-----------------[e]--exit to main menu-----------\n");
    for(i=0; i<8; i++) {
        printf("\t\t\t");
        if(i!=0) {
            for(k=0; k<8; k++) {
                printf("%c     ", vertical_line);
            }
            printf("%c\n", vertical_line);
            printf("\t\t\t");
        }
        for(k=0; k<8; k++) {
            printf("%c%c%c%c%c%c", plus, horizontal_line, horizontal_line, horizontal_line, horizontal_line, horizontal_line);
        }
        printf("%c\n",  plus);
        printf("\t\t\t");
        for(k=0; k<8; k++) {
            printf("%c     ", vertical_line);
        }
        printf("%c\n", vertical_line);
        printf("\t\t\t");
        for(j=0; j<8; j++) {
            pos=getpos(i,j);
            switch(board[i][j].type) {
                case PAWN:
                    printPiece(i, j, 'P');
                    break;

                case ROOK:
                    printPiece(i, j, 'R');
                    break;

                case BISHOP:
                    printPiece(i, j, 'B');
                    break;

                case KNIGHT:
                    printPiece(i, j, 'N');
                    break;

                case QUEEN:
                    printPiece(i, j, 'Q');
                    break;

                case KING:
                    printPiece(i, j, 'K');
                    break;

                case EMPTY:
                    printPiece(i, j, ' ');
                    break;
            }
        }
        printf("%c\n", vertical_line);
        if(i==7) {
            printf("\t\t\t");
            for(k=0; k<8; k++) {
                printf("%c     ", vertical_line);
            }
            printf("%c\n", vertical_line);
            printf("\t\t\t");
            for(k=0; k<8; k++) {
                printf("%c%c%c%c%c%c", plus, horizontal_line, horizontal_line, horizontal_line, horizontal_line, horizontal_line);
            }
            printf("%c\n", plus);
        }
    }
}

void printPiece(int i, int j, char piece) {
    if(i == cursorX && j == cursorY) {
        if(board[i][j].color == -1) {
            printf("%c%c[%c]%c", 179, 175, piece, 174);
        }else {
            printf("%c%c %c %c", 179, 175, piece, 174);
        }
    }else {
        if(moves_hash[i][j]!=1){
            if(board[i][j].color == -1) {
                printf("%c [%c] ", 179, piece);
            }else {
                printf("%c  %c  ", 179, piece);
            }
        }
        else{
            if(board[i][j].color == -1) {
                printf("%c%c[%c]%c", 179, 222, piece, 221);
            }else {
                printf("%c %c%c%c ", 179, 222, piece, 221);
            }
        }
    }
}
