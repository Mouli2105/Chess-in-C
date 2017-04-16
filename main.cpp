//  HEADER FILES
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define _WIN32_WINNT 0x0601
#include<windows.h>

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
int is_king_can_move();
int find_checkedpiece_path();
int checkmate();
int all_moves();
int possible_moves_at_check();
int find_rook_path();
int find_bishop_path();
int find_queen_path();
int find_knight_path();
int find_pawn_path();
int find_king_path();
void printCheckHash();
void printPiece(int i, int j, char piece);
void printBoard2();
int getpos(int i,int j);
int aboutUs();
int instructions();
int startGame();
int mainMenu();
int check();
int welcome();
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
int printBoard();
int initializeBoard();
int swapPieces(struct piece *a, struct piece *b, int newX, int newY);
int handleCursor(int color);
int loadingScreen(int time);
int setCursor();
int setHashCheckMate();
void resetCheckHash();

//  DECLARING GLOBAL VARIABLES
int pawn_flag = 0;
int codX,codY;
int count_v=0;
int started = 0;
int moved = 0;
int stackPointer = -1;
int mainX;
int mainY;
int king_hash[8][8] = {0};
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
int flag = 0;
int cursor_flag = 0;
int black_checked = 0;
int white_checked = 0;

struct piece {
    int type;
    int color;
}board[8][8], checkingPiece;

struct coord {
    int x;
    int y;
}positionStack[32], whiteKing, blackKing,checkedKing,checkingPiece_pos,checkstack[32],king_stack[32];
int checkKingMoves(coord pos);

//  MAIN METHOD
int main() {
    COORD Coord;
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &Coord);
    if(started == 0) {
        welcome();
    }
    system("color 0a");
    int a;
    int endGame = 0;
    do {
        a = mainMenu();
        switch(a) {
            case 1:
                endGame = startGame();
                break;

            case 2:
                instructions();
                break;

            case 3:
                controls();
                break;

            case 4:
                aboutUs();
                break;

            case 5:
                system("cls");
                printf("\n\n\n\n\t\t\t\t\tThank you!\n\n\n\n\t\t\t\t\t");
                system("pause");
                exit(0);
                break;

        }
    }while(a!=1 && a!=5 && endGame==0);
    started = 1;
    if(endGame) {
        main();
    }
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
                        if(flag){
                    if(col == WHITE){
                        printf("\n\t\t\tblack");
                        black_checked = 1;
                    }
                    else{
                        printf("\n\t\t\twhite");
                        white_checked = 1;
                    }
                    printf("CHECK");
                    system("pause");
                    checkingPiece = board[cursorX][cursorY];
                    checkingPiece_pos.x = cursorX;
                    checkingPiece_pos.y = cursorY;
                    resetCheckHash();
                        }
                    cursorX = tempcursorX;
                    cursorY = tempcursorY;
                    check_flag = 0;
                    return 1;
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
    board[0][4].type = board[7][4].type = QUEEN;
    whiteKing.x = 0;
    whiteKing.y = 3;//  USE THESE
    blackKing.x = 7;
    blackKing.y = 3;
    board[0][3].type = board[7][3].type = KING;
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

int loadingScreen(int time) {   //  DISPLAYS THE LOADING SCREEN
    int i;
    printf("\n\n\n\n\t\t\t\t\t\tLoading");
    for(i=0; i<20; i++) {
        printf("%c", '.');
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
		if(board[cursorX+1][cursorY].color!=board[cursorX][cursorY].color&&cursorX+1<8) {
			if(check_flag) {
				checkmate_hash[cursorX+1][cursorY] = 1;
			}else {
            moves_hash[cursorX+1][cursorY] = 1;
			}
		}
        if(board[cursorX-1][cursorY].color!=board[cursorX][cursorY].color&&cursorX-1>=0) {
			if(check_flag) {
				checkmate_hash[cursorX-1][cursorY] = 1;
			}else {
				moves_hash[cursorX-1][cursorY] = 1;
			}
        }
        if(board[cursorX][cursorY+1].color!=board[cursorX][cursorY].color&&cursorY+1<8) {
			if(check_flag) {
				checkmate_hash[cursorX][cursorY+1]=1;
			}else {
				moves_hash[cursorX][cursorY+1] = 1;
			}
        }
        if(board[cursorX][cursorY-1].color!=board[cursorX][cursorY].color&&cursorY-1>=0) {
			if(check_flag) {
				checkmate_hash[cursorX][cursorY-1] = 1;
			}else {
				moves_hash[cursorX][cursorY-1]=1;
			}
        }
        if(board[cursorX+1][cursorY+1].color!=board[cursorX][cursorY].color&&cursorX+1<8&&cursorY+1<8) {
			if(check_flag) {
				checkmate_hash[cursorX+1][cursorY+1];
			}else {
				moves_hash[cursorX+1][cursorY+1]=1;
			}
        }
        if(board[cursorX+1][cursorY-1].color!=board[cursorX][cursorY].color&&cursorX+1<8&&cursorY-1>=0) {
			if(check_flag) {
				checkmate_hash[cursorX+1][cursorY-1];
			}else {
				moves_hash[cursorX+1][cursorY-1]=1;
			}
        }
        if(board[cursorX-1][cursorY+1].color!=board[cursorX][cursorY].color&&cursorX-1>=0&&cursorY+1<8) {
			if(check_flag) {
				checkmate_hash[cursorX-1][cursorY+1];
			}else {
				moves_hash[cursorX-1][cursorY+1]=1;
			}
        }
        if(board[cursorX-1][cursorY-1].color!=board[cursorX][cursorY].color&&cursorX-1>=0&&cursorY-1>=0) {
			if(check_flag) {
				checkmate_hash[cursorX-1][cursorY-1];
			}else {
				moves_hash[cursorX-1][cursorY-1]=1;
			}
        }
}

int pawn_moves() {  //TO PRINT THE POSSIBLE MOVES OF THE PAWN
    if(board[cursorX][cursorY].color==1&&front_color==1) {
        if(board[cursorX+1][cursorY].color==0) {
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY]=1;
                checkmate_hash[cursorX+1][cursorY+1]=1;
                checkmate_hash[cursorX+1][cursorY-1]=1;
			}else {
                moves_hash[cursorX+1][cursorY]=1;
                if(pawn_flag){
                moves_hash[cursorX+1][cursorY+1]=1;
                moves_hash[cursorX+1][cursorY-1]=1;
                }
			}
        }
         if(board[cursorX+1][cursorY+1].color==-1*board[cursorX][cursorY].color&&cursorX+1<8&&cursorY+1<8) {
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY+1]=1;
			}else {
                moves_hash[cursorX+1][cursorY+1]=1;
			}
        }
         if(board[cursorX+1][cursorY-1].color==-1*board[cursorX][cursorY].color&&cursorX+1<8&&cursorY-1>=0){
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY-1]=1;
			}else {
                moves_hash[cursorX+1][cursorY-1]=1;
			}
        }
        if(cursorX == 1) {
            if(board[cursorX+2][cursorY].color == EMPTY && board[cursorX+1][cursorY].color == EMPTY&&cursorX+2<8) {
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
                checkmate_hash[cursorX-1][cursorY-1]=1;
                checkmate_hash[cursorX-1][cursorY+1]=1;
			}else {
                moves_hash[cursorX-1][cursorY]=1;
                if(pawn_flag){
                moves_hash[cursorX+1][cursorY+1]=1;
                moves_hash[cursorX+1][cursorY-1]=1;
                }
			}
        }
        if(board[cursorX-1][cursorY-1].color==-1*board[cursorX][cursorY].color&&cursorX-1>=0&&cursorY-1>=0) {
            if(check_flag) {
                checkmate_hash[cursorX-1][cursorY-1]=1;
			}else {
                moves_hash[cursorX-1][cursorY-1]=1;
			}
        }
        if(board[cursorX-1][cursorY+1].color==-1*board[cursorX][cursorY].color&&cursorX+1>=0&&cursorY+1<8) {
            if(check_flag) {
                checkmate_hash[cursorX-1][cursorY+1]=1;
			}else {
                moves_hash[cursorX-1][cursorY+1]=1;
			}
        }
    }
    if(cursorX == 6) {
        if(board[cursorX-2][cursorY].color == EMPTY&&board[cursorX-1][cursorY].color == EMPTY&&cursorX-2>=0) {
            if(check_flag) {
                checkmate_hash[cursorX-2][cursorY] = 1;
            }else {
                moves_hash[cursorX-2][cursorY] = 1;
			}
        }
    }
}

void printHash() {  //TO VERIFY THE POSSIBLE MOVES ARE AT EXPECTED POSITIONS ARE NOT
    //resetMovesHash();
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

int controls() {    //  DISPLAYS THE CONTROLS OF GAME
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
                black_checked = 0;
                white_checked = 0;
                piece current = board[mainX][mainY];
                swapPieces(&board[mainX][mainY], &board[cursorX][cursorY],cursorX,cursorY);
                flag = 1;
                setHashCheckMate();
                flag = 0;
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
                checkedKing.x = blackKing.x;
                checkedKing.y = blackKing.y;
            return 1;
        }
    }else if( col == BLACK) {
        if(checkmate_hash[whiteKing.x][whiteKing.y]) {
                checkedKing.x = whiteKing.x;
                checkedKing.y = whiteKing.y;
            return 1;
        }
    }
    return 0;
}
void printCheckHash()
{
    int i,j;
    for( i = 0 ; i < 8 ; i++){
        for( j = 0 ; j < 8 ; j++)
        {
            printf("%d ",checkmate_hash[i][j]);
        }
        printf("\n");
    }
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
	printf("\n\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	printf("\n\t\t\t\t\t%c       %c    %c    %c    %c%c%c%c%c%c%c%c%c%c  %c           %c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c%c   %c       %c   %c%c%c%c%c%c%c%c      %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t%c       %c    %c    %c    %c           %c           %c           %c       %c   %c%c     %c%c   %c             %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t%c       %c    %c    %c    %c%c%c%c%c%c%c%c%c%c  %c           %c           %c       %c   %c%c%c   %c%c%c   %c%c%c%c%c%c%c%c      %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t%c        %c  %c %c  %c     %c           %c           %c           %c       %c   %c%c%c%c %c%c%c%c   %c             %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t%c         %c%c   %c%c      %c%c%c%c%c%c%c%c%c%c  %c%c%c%c%c%c%c%c%c%c  %c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c      %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
	printf("\n");
	printf("\n\t\t\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	printf("\n\t\t\t\t\t\t\t\t%c     %c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c%c    %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t\t\t%c          %c          %c        %c    %c", 186, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t\t\t%c          %c          %c        %c    %c", 186, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t\t\t%c          %c          %c        %c    %c", 186, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t\t\t%c          %c          %c        %c    %c", 186, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t\t\t%c          %c          %c%c%c%c%c%c%c%c%c%c    %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
	printf("\n");
	printf("\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	printf("\n\t\t\t\t\t\t%c   %c%c%c%c%c%c%c %c     %c %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c %c%c%c%c%c%c%c    %c%c%c%c%c%c%c %c     %c   %c%c%c%c%c%c%c    %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t%c   %c       %c     %c %c        %c       %c             %c    %c%c    %c   %c          %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t%c   %c       %c     %c %c        %c       %c             %c    %c %c   %c   %c          %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t%c   %c       %c%c%c%c%c%c%c %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c %c%c%c%c%c%c%c       %c    %c  %c  %c   %c          %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t%c   %c       %c     %c %c              %c       %c       %c    %c   %c %c   %c          %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t%c   %c       %c     %c %c              %c       %c       %c    %c    %c%c   %c          %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t%c   %c%c%c%c%c%c%c %c     %c %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c %c%c%c%c%c%c%c    %c%c%c%c%c%c%c %c     %c   %c%c%c%c%c%c%c    %c", 186, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 186);
	printf("\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    loadingScreen(150);
}

int mainMenu() {
    char ch;
    int X = 0, Y = 0;
    do {
        system("cls");
        printf("\n\n\n\n\t\t\t\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
        printf("\n\t\t\t\t\t\t\t\t\t%c  MAIN MENU %c", 186, 186);
        printf("\n\t\t\t\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
        printf("\n\n\n\t\t\t\t\t\t\t\t\t[1] TWO PLAYER MODE");
        printf("\n\n\n\t\t\t\t\t\t\t\t\t[2] HOW TO PLAY CHESS?");
        printf("\n\n\n\t\t\t\t\t\t\t\t\t[3] CONTROLS");
        printf("\n\n\n\t\t\t\t\t\t\t\t\t[4] ABOUT US");
        printf("\n\n\n\t\t\t\t\t\t\t\t\t[5] EXIT GAME");
        printf("\n\n\n\n\n\t\t\t\t\t\tENTER YOUR CHOICE: ");
        ch = getche();
    }while(ch!='1' && ch!='2' && ch!='3' && ch!= '4' && ch!='5');
    system("cls");
    return(ch-48);
}

int startGame() {
    piece temp;
    int tempX,tempY,i;
    initializeBoard();
    system("color 0e");
    do {
            cursor_flag = 1;
            if(black_checked || white_checked){
                    find_checkedpiece_path();
//                    for(i=0;checkstack[i].x!=-1;i++)
//                        printf("%d %d\n",checkstack[i].x,checkstack[i].y);
//                    system("pause");

                    if( checkmate()&&is_king_can_move())
                    {
//                        printf("\nEntered");
//                        system("pause");
                        printf("check mate\ngmae over");
                        break;
                    }
                    else
                    {
                       // find_checkedpiece_path();
                        possible_moves_at_check();
                        printBoard2();
                        cursor_flag = 0;
                    }

        }
        temp = board[cursorX][cursorY];
        tempX = cursorX;
        tempY = cursorY;
        col = -1 * col;
        board[cursorX][cursorY].type = EMPTY;
        board[cursorX][cursorY].color = 0;
        if(setHashCheckMate())
        {
            col = -1 * col;
            cursorY = tempY;
            cursorX = tempX;
           // printf("\n\n\t\t\t\t%d %d",temp.type,temp.color);
            board[tempX][tempY] = temp;
            //system("pause");
            resetMovesHash();
        }
        else
        {
            col = -1 * col;
            cursorX = tempX;
            cursorY = tempY;
            board[tempX][tempY] = temp;
            possible_moves();


        }
        if(cursor_flag){
        board[whiteKing.x][whiteKing.y].type = KING;
        board[whiteKing.x][whiteKing.y].color = WHITE;
        board[blackKing.x][blackKing.y].type = KING;
        board[blackKing.x][blackKing.y].color = BLACK;
        printBoard2();
        }
//        printHash();
//        system("pause");
        resetMovesHash();
        resetCheckHash();
    }while(handleCursor(col));
    return 1;
}
int find_checkedpiece_path(){
    switch(checkingPiece.type)
        {
            case ROOK : find_rook_path();
                        break;
            case BISHOP : find_bishop_path();
                        break;
            case QUEEN : find_queen_path();
                        break;
            case KNIGHT : find_knight_path();
                        break;
            case PAWN : find_pawn_path();
                        break;
            case KING : find_king_path();
                        break;

        }
        return 0;
}
int find_rook_path(){
    int i,j;
    if(checkingPiece_pos.x == checkedKing.x && checkingPiece_pos.y < checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = checkingPiece_pos.x;
            checkstack[j++].y = i;
            i++;
        }while(i < 8 && i != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x == checkedKing.x && checkingPiece_pos.y > checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = checkingPiece_pos.x;
            checkstack[j++].y = i;
            i--;
        }while(i <= 0 && i != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x < checkedKing.x && checkingPiece_pos.y == checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        do
        {
            checkstack[j].y = checkingPiece_pos.y;
            checkstack[j++].x = i;
            i++;
        }while(i < 8 && i != checkedKing.x);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x > checkedKing.x && checkingPiece_pos.y == checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        do
        {
            checkstack[j].y = checkingPiece_pos.y;
            checkstack[j++].x = i;
            i--;
        }while(i >= 0  && i != checkedKing.x);
        checkstack[j].x = -1;
    }
}
int find_bishop_path(){
    int i,j,k;
    if(checkingPiece_pos.x < checkedKing.x && checkingPiece_pos.y < checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        k = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = i;
            checkstack[j++].y = k;
            i++;
            k++;
        }while(i < 8 && k < 8 && i != checkedKing.x && k != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x < checkedKing.x && checkingPiece_pos.y > checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        k = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = i;
            checkstack[j++].y = k;
            i++;
            k--;
        }while(i < 8 && k >= 0 && i != checkedKing.x && k != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x > checkedKing.x && checkingPiece_pos.y > checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        k = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = i;
            checkstack[j++].y = k;
            i--;
            k--;
        }while(i >= 0 && k >= 0 && i != checkedKing.x && k != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x > checkedKing.x && checkingPiece_pos.y < checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        k = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = i;
            checkstack[j++].y = k;
            i--;
            k++;
        }while(i >= 0 && k < 8 && i != checkedKing.x && k != checkedKing.y);
        checkstack[j].x = -1;
    }
}
int find_queen_path(){
   int i,j,k;
    if(checkingPiece_pos.x == checkedKing.x && checkingPiece_pos.y < checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = checkingPiece_pos.x;
            checkstack[j++].y = i;
            i++;
        }while(i < 8 && i != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x == checkedKing.x && checkingPiece_pos.y > checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = checkingPiece_pos.x;
            checkstack[j++].y = i;
            i--;
        }while(i <= 0 && i != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x < checkedKing.x && checkingPiece_pos.y == checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        do
        {
            checkstack[j].y = checkingPiece_pos.y;
            checkstack[j++].x = i;
            i++;
        }while(i < 8 && i != checkedKing.x);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x > checkedKing.x && checkingPiece_pos.y == checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        do
        {
            checkstack[j].y = checkingPiece_pos.y;
            checkstack[j++].x = i;
            i--;
        }while(i >= 0  && i != checkedKing.x);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x < checkedKing.x && checkingPiece_pos.y < checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        k = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = i;
            checkstack[j++].y = k;
            i++;
            k++;
        }while(i < 8 && k < 8 && i != checkedKing.x && k != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x < checkedKing.x && checkingPiece_pos.y > checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        k = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = i;
            checkstack[j++].y = k;
            i++;
            k--;
        }while(i < 8 && k >= 0 && i != checkedKing.x && k != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x > checkedKing.x && checkingPiece_pos.y > checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        k = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = i;
            checkstack[j++].y = k;
            i--;
            k--;
        }while(i >= 0 && k >= 0 && i != checkedKing.x && k != checkedKing.y);
        checkstack[j].x = -1;
    }
    else if(checkingPiece_pos.x > checkedKing.x && checkingPiece_pos.y < checkedKing.y)
    {
        j = 0;
        i = checkingPiece_pos.x;
        k = checkingPiece_pos.y;
        do
        {
            checkstack[j].x = i;
            checkstack[j++].y = k;
            i--;
            k++;
        }while(i >= 0 && k < 8 && i != checkedKing.x && k != checkedKing.y);
        checkstack[j].x = -1;
    }
}
int find_knight_path(){
    int i = 0,j = checkingPiece_pos.x,k = checkingPiece_pos.y;
    if(j+2 == checkedKing.x && k+1 == checkedKing.y)
    {
        checkstack[i].x = j;
        checkstack[i].y = k;
    }
    else if(j+2 == checkedKing.x && k-1 == checkedKing.y)
    {
        checkstack[i].x = j;
        checkstack[i].y = k;
    }
    else if(j-2 == checkedKing.x && k+1 == checkedKing.y)
    {
        checkstack[i].x = j;
        checkstack[i].y = k;
    }
    else if(j-2 == checkedKing.x && k-1 == checkedKing.y)
    {
        checkstack[i].x = j;
        checkstack[i].y = k;
    }
    else if(j+1 == checkedKing.x && k+2 == checkedKing.y)
    {
        checkstack[i].x = j;
        checkstack[i].y = k;
    }
    else if(j-1 == checkedKing.x && k+2 == checkedKing.y)
    {
        checkstack[i].x = j;
        checkstack[i].y = k;
    }
    else if(j+1 == checkedKing.x && k-2 == checkedKing.y)
    {
        checkstack[i].x = j;
        checkstack[i].y = k;
    }
    else if(j-1 == checkedKing.x && k-2 == checkedKing.y)
    {
        checkstack[i].x = j;
        checkstack[i].y = k;
    }
    checkstack[i+1].x = -1;
   // printf("    in knight  %d  %d",checkstack[0].x,checkstack[0].y);
    //system("pause");
    return 1;
}
int find_pawn_path(){
    int i,j,k=0;
    i = checkedKing.x;
    j = checkedKing.y;
    if(board[checkedKing.x][checkedKing.y].color == WHITE){
    if(i+1 == checkingPiece_pos.x && j+1 == checkingPiece_pos.y){
        checkstack[k].x = i-1;
        checkstack[k].y = j-1;
    }
    if(i+1 == checkingPiece_pos.x && j-1 == checkingPiece_pos.y){
        checkstack[k].x = i-1;
        checkstack[k].y = j+1;
    }
    }
    if(board[checkedKing.x][checkedKing.y].color == BLACK){
    if(i-1 == checkingPiece_pos.x && j-1 == checkingPiece_pos.y){
        checkstack[k].x = i-1;
        checkstack[k].y = j-1;
    }
    if(i-1 == checkingPiece_pos.x && j+1 == checkingPiece_pos.y){
        checkstack[k].x = i-1;
        checkstack[k].y = j+1;
    }
    }
    checkstack[k+1].x = -1;
   // printf("  %d %d ",checkstack[0].x,checkstack[0].y);
    //system("pause");
}
int find_king_path(){}
int checkmate() {
    int i,j,FLAG = 0,color;
    piece temp;
    codX = cursorX;
    codY = cursorY;
    resetMovesHash();
   // cursorX = codX;
    //cursorY = codY;
    all_moves();
   // cursorX = tempcursorX;
   // cursorY = tempcursorY;
   cursorX = codX;
    cursorY = codY;
    for( i = 0 ; checkstack[i].x>=0 ;i++)
    {
            if(moves_hash[checkstack[i].x][checkstack[i].y]){
             return 0;
                }
               // printHash()
    }
    return 1;
}
int all_moves(){
    tempcursorX = cursorX;
    tempcursorY = cursorY;
    pawn_flag = 1;
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

                    case QUEEN:
                        queen_moves();
                        break;
                    default:
                        break;
                }
            }
        }
    }
    pawn_flag = 0;

}
int possible_moves_at_check(){
    int i;
    resetMovesHash();
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

            for( i = 0 ; checkstack[i].x >= 0 ; i++)
            {
             //   printf("  %d %d",checkstack[i].x,checkstack[i].y);
              //  system("pause");
                if(moves_hash[checkstack[i].x][checkstack[i].y])
                {
                        return 1;
                }

            }
            resetMovesHash();
            return 1;
}
int instructions() {//  DISPLAYS THE INSTRUCTION OF THE GAME
    FILE *fp;
    char ch;
    fp = fopen("instructions.txt", "r");
    if(fp == NULL) {
        printf("Unable to open the file!");
    }else {
        while((ch=fgetc(fp)) != EOF) {
            printf("%c", ch);
        }
    }
    fclose(fp);
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
    printf("\t\t\t\t\t\t ----------[c]--controls-----------------[e]--exit to main menu-----------\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t     A     B     C     D     E     F     G     H   \n");
    for(i=0; i<8; i++) {
        printf("\t\t\t\t\t\t\t  ");
        if(i!=0) {
            for(k=0; k<8; k++) {
                printf("%c     ", vertical_line);
            }
            printf("%c\n", vertical_line);
            printf("\t\t\t\t\t\t\t  ");
        }
        for(k=0; k<8; k++) {
            printf("%c%c%c%c%c%c", plus, horizontal_line, horizontal_line, horizontal_line, horizontal_line, horizontal_line);
        }
        printf("%c\n",  plus);
        printf("\t\t\t\t\t\t\t  ");
        for(k=0; k<8; k++) {
            printf("%c     ", vertical_line);
        }
        printf("%c\n", vertical_line);
        printf("\t\t\t\t\t\t  ");
        for(j=0; j<8; j++) {
            if(j==0) {
                printf("\t");
            }
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
            printf("\t\t\t\t\t\t\t  ");
            for(k=0; k<8; k++) {
                printf("%c     ", vertical_line);
            }
            printf("%c\n", vertical_line);
            printf("\t\t\t\t\t\t\t  ");
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
            if(j==0) {
                printf("%d %c%c[%c]%c", i+1, 179, 175, piece, 174);
            }else {
                printf("%c%c[%c]%c", 179, 175, piece, 174);
            }
        }else {
            if(j==0) {
                printf("%d %c%c %c %c", i+1, 179, 175, piece, 174);
            }else {
                printf("%c%c %c %c", 179, 175, piece, 174);
            }
        }
    }else {
        if(moves_hash[i][j]!=1){
            if(board[i][j].color == -1) {
                if(j==0) {
                    printf("%d %c [%c] ", i+1, 179, piece);
                }else {
                    printf("%c [%c] ", 179, piece);
                }
            }else {
                if(j==0) {
                    printf("%d %c  %c  ", i+1, 179, piece);
                }else {
                    printf("%c  %c  ", 179, piece);
                }
            }
        }
        else{
            if(board[i][j].color == -1) {
                if(j==0) {
                    printf("%d %c%c[%c]%c", i, 179, 222, piece, 221);
                }else {
                    printf("%c%c[%c]%c", 179, 222, piece, 221);
                }
            }else {
                if(j==0) {
                    printf("%d %c %c%c%c ", i, 179, 222, piece, 221);
                }else {
                    printf("%c %c%c%c ", 179, 222, piece, 221);
                }
            }
        }
    }
}
int is_king_can_move()
{
    int i,temp_color;
    piece temp;
    checkKingMoves(checkedKing);
    resetMovesHash();
    temp_color = board[checkedKing.x][checkedKing.y].color;
    board[checkedKing.x][checkedKing.y].color = 0;
    board[checkedKing.x][checkedKing.y].type = EMPTY;
    for(i=0;king_stack[i].x>=0;i++){
    temp = board[king_stack[i].x][king_stack[i].y];
    board[king_stack[i].x][king_stack[i].y].type = EMPTY;
    board[king_stack[i].x][king_stack[i].y].color = 0;
    col = -1 * col;
    all_moves();
    cursorX = codX;
    cursorY = codY;
    col = -1 * col;
    //printHash();
    //system("pause");
    if(moves_hash[king_stack[i].x][king_stack[i].y] == 0)
    {
        board[checkedKing.x][checkedKing.y].color = temp_color;
        board[checkedKing.x][checkedKing.y].color = KING;
        return 0;
    }
    board[king_stack[i].x][king_stack[i].y] = temp;
    }
        board[checkedKing.x][checkedKing.y].color = temp_color;
        board[checkedKing.x][checkedKing.y].color = KING;
    return 1;
}

int checkKingMoves(coord pos){
    int i = 0;
    if((board[pos.x][pos.y].color == -1*board[pos.x+1][pos.y].color || board[pos.x+1][pos.y].color == EMPTY) && pos.x!=7){
         //   printf("*1");
        king_stack[i].x = pos.x+1;
        king_stack[i].y = pos.y;
        i++;
    }
    if((board[pos.x][pos.y].color == -1*board[pos.x-1][pos.y].color || board[pos.x-1][pos.y].color == EMPTY) && pos.x!=0){
       // printf("*2");
        king_stack[i].x = pos.x-1;
        king_stack[i].y = pos.y;
        i++;
    }
    if((board[pos.x][pos.y].color == -1*board[pos.x][pos.y+1].color || board[pos.x][pos.y+1].color == EMPTY) && pos.y!=7){
       // printf("*3");
        king_stack[i].x = pos.x;
        king_stack[i].y = pos.y+1;
        i++;
    }
    if((board[pos.x][pos.y].color == -1*board[pos.x][pos.y-1].color || board[pos.x][pos.y-1].color == EMPTY) && pos.y!=0){
       // printf("*4");
        king_stack[i].x = pos.x;
        king_stack[i].y = pos.y-1;
        i++;
    }
    if((board[pos.x][pos.y].color == -1*board[pos.x+1][pos.y+1].color || board[pos.x+1][pos.y+1].color == EMPTY) && pos.x!=7 && pos.y!=7){
       // printf("*5");
        king_stack[i].x = pos.x+1;
        king_stack[i].y = pos.y+1;
        i++;
    }
    if((board[pos.x][pos.y].color == -1*board[pos.x+1][pos.y-1].color || board[pos.x+1][pos.y-1].color == EMPTY) && pos.x!=7 && pos.y!=0){
       // printf("*6");
        king_stack[i].x = pos.x+1;
        king_stack[i].y = pos.y-1;
        i++;
    }
    if((board[pos.x][pos.y].color == -1*board[pos.x-1][pos.y+1].color || board[pos.x-1][pos.y+1].color == EMPTY) && pos.x!=0 && pos.y!=7){
        //printf("*7");
        king_stack[i].x = pos.x-1;
        king_stack[i].y = pos.y+1;
       // printf("       %d %d",king_stack[i].x,king_stack[i].y);
        i++;
    }
    if((board[pos.x][pos.y].color == -1*board[pos.x-1][pos.y-1].color || board[pos.x-1][pos.y-1].color == EMPTY) && pos.x!=0 && pos.y!=0){
       // printf("*8");
        king_stack[i].x = pos.x-1;
        king_stack[i].y = pos.y-1;
        i++;
    }
    king_stack[i].x = -1;
//    for(i=0;king_stack[i].x>=0;i++){
//        printf("   %d  %d ",king_stack[i].x,king_stack[i].y);
//    }
//    system("pause");
}
