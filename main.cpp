////  HEADER FILES
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define _WIN32_WINNT 0x0601
#include<windows.h>

//  DEFINING PIECES
#define BLOCK 219
#define BLOCK1 178
#define BLOCK2 177
#define BLOCK3 176
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
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
int castling();
int pawnChoice();
int thankYou();
void printPiece2(int i, int j);
void gotoxy(int x, int y);
int quit();
int scanPlayers();
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
void printCheckHash();
void printPiece(int i, int j, char piece);
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
int copyArray();
int resetTempArray();
void settings();
void displayMode();
void esc();

//  DECLARING GLOBAL VARIABLES
int DARK_MODE = 1;
int MUTE = -1;
int whiteDeadPointer = -1;
int blackDeadPointer = -1;
int leftRookWhite = 0;
int leftRookBlack = 0;
int rightRookWhite = 0;
int rightRookBlack = 0;
HANDLE console =GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int whiteFlag = 0,blackFlag = 0;
char player1[50];
char player2[50];
int pawn_flag = 0;
int codX,codY;
int count_v=0;
int started = 0;
int moved = 0;
int stackPointer = -1;
int mainX;
int mainY;
int tempArr[8][8]={0};
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
}board[8][8], checkingPiece, blackDead[16], whiteDead[16];

struct coord {
    int x;
    int y;
}positionStack[32], whiteKing, blackKing,checkedKing,checkingPiece_pos,checkstack[32],king_stack[32];
int checkKingMoves(coord pos);

//  MAIN METHOD
int main() {
//    COORD Coord;
//    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &Coord);
    displayMode();
    if(started == 0) {
        welcome();
    }
    int a;
    int endGame = 0;
    do {
        a = mainMenu();
        switch(a) {
            case 1:
                _sleep(100);
                if(scanPlayers()) {
                    loadingScreen(100);
                    endGame = startGame();
                }
                endGame = 1;
                break;

            case 2:
                instructions();
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                break;

            case 3:
                controls();
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                break;

            case 4:
                settings();
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                break;

            case 5:
                aboutUs();
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                break;

            case 6:
                system("cls");
                if(quit()) {
                    thankYou();
                    exit(0);
                }else {
                    a = 6;
                }
                break;

        }
    }while(a!=1 && a!=6 && endGame==0);
    started = 1;
    if(endGame) {
        main();
    }
    return 0;
}

int setHashCheckMate() {  //SETS THE HASH TABLE USED TO CHECK THE CHECKMATE AND CHECK CONDITION
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
                        black_checked = 1;
                        gotoxy(85, 10);
                        printf("CHECK");
                        gotoxy(83, 11);
                        printf("PROCESSING IF ITS A CHECK-MATE");
                    }
                    else{
                        white_checked = 1;
                        gotoxy(5, 10);
                        printf("CHECK");
                        gotoxy(5, 11);
                        printf("PROCESSING IF ITS A CHECK-MATE");
                    }
                    for(int k=0; k<5; k++) {
                        printf(".");
                        _sleep(650);
                    }
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

void printPiece2(int i, int j) {
    char piece;
    switch(board[i][j].type) {
    case KING:
        if(board[i][j].color == WHITE) {
            piece = 'K';
        }else {
            piece = 'k';
        }
        break;
    case QUEEN:
        if(board[i][j].color == WHITE) {
            piece = 'Q';
        }else {
            piece = 'q';
        }
        break;
    case BISHOP:
        if(board[i][j].color == WHITE) {
            piece = 'B';
        }else {
            piece = 'b';
        }
        break;
    case ROOK:
        if(board[i][j].color == WHITE) {
            piece = 'R';
        }else {
            piece = 'r';
        }
        break;
    case KNIGHT:
        if(board[i][j].color == WHITE) {
            piece = 'N';
        }else {
            piece = 'n';
        }
        break;
    case PAWN:
        if(board[i][j].color == WHITE) {
            piece = 'P';
        }else {
            piece = 'p';
        }
        break;
    case EMPTY:
        piece = ' ';
        break;
    }
    if(cursorX==i && cursorY==j) {
        printf("[%c]", piece);
    }else {
        if(moves_hash[i][j]) {
            if(piece==' ') {
                printf(" %c ", 254);
            }else {
                printf("%c%c%c", 222, piece, 221);
            }
        }else {
            printf(" %c ", piece);
        }
    }
}

int printBoard() {//    DISPLAYS THE BOARD IN A SIMPLE WAY
    system("cls");
    gotoxy(45, 25);
    printf("Press 'm' to mute/unmute.");
    if(whiteDeadPointer != -1) {
        for(int k=0; k<=whiteDeadPointer; k++) {
            gotoxy(115 - k*2, 12);
            switch(whiteDead[k].type) {
            case QUEEN:
                printf("Q");
                break;

            case KNIGHT:
                printf("N");
                break;

            case BISHOP:
                printf("B");
                break;

            case ROOK:
                printf("R");
                break;

            case PAWN:
                printf("P");
                break;
            }
        }
    }
    if(blackDeadPointer != -1) {
        for(int k=0; k<=blackDeadPointer; k++) {
            gotoxy(3 + k*2, 12);
            switch(blackDead[k].type) {
            case QUEEN:
                printf("q");
                break;

            case KNIGHT:
                printf("n");
                break;

            case BISHOP:
                printf("b");
                break;

            case ROOK:
                printf("r");
                break;

            case PAWN:
                printf("p");
                break;
            }
        }
    }
    gotoxy(0, 0);
    int i, j;
    int count = 1;
    printf("\n\n\t\t\t\t\t       ");
    printf("%c%c", 218, 196);
    for(int i=0; i<7; i++) {
        printf("%c%c%c%c", 196, 196, 194, 196);
    }
    printf("%c%c%c", 196, 196, 191);
    for(i=0; i<8; i++) {
        printf("\n\t\t\t\t\t       %c", 179);
        for(j=0; j<8; j++) {
            printPiece2(i, j);
            printf("%c", 179);
        }
        if(i<7) {
            printf("\n\t\t\t\t\t       ");
            printf("%c%c", 195, 196);
            for(int k=0; k<7; k++) {
                printf("%c%c%c%c", 196, 196, 197, 196);
            }
            printf("%c%c%c", 196, 196, 180);
        }
    }
    printf("\n\t\t\t\t\t       ");
    printf("%c%c", 192, 196);
    for(int i=0; i<7; i++) {
        printf("%c%c%c%c", 196, 196, 193, 196);
    }
    printf("%c%c%c", 196, 196, 217);

    if(col == WHITE) {
        system("color a0");
        gotoxy(3, 2);
        printf("%s's Move", player1);
        gotoxy(3, 10);
    }else {
        system("color 4f");
        gotoxy(90, 2);
        printf("%s's Move", player2);
        gotoxy(90, 10);
    }
    return 1;
}

int swapPieces(struct piece *a, struct piece *b, int newX, int newY) {//    SWAPS TWO PIECES ON THE BOARD
    if(b->type!=EMPTY) {
        if(a->color == WHITE) {
            blackDead[++blackDeadPointer].type = b->type;
        }else if(a->color == BLACK) {
            whiteDead[++whiteDeadPointer].type = b->type;
        }
    }

    if(a->type == KING){
        if(a->color == WHITE){
            if(whiteKing.y - newY == -2) {
                swapPieces(&board[0][7], &board[0][4], 0, 4);
            }else if(whiteKing.y - newY == 2) {
                swapPieces(&board[0][0], &board[0][2], 0, 2);
            }
            whiteKing.x = newX;
            whiteKing.y = newY;
            whiteFlag = 1;
        }else if(a->color == BLACK) {
            if(blackKing.y - newY == -2) {
                swapPieces(&board[7][7], &board[7][4], 7, 4);
            }else if(blackKing.y - newY == 2) {
                swapPieces(&board[7][0], &board[7][2], 7, 2);
            }
            blackKing.x = newX;
            blackKing.y = newY;
            blackFlag = 1;
        }
    }
    if(a->type == ROOK) {
        if(a->color == WHITE ) {
            if(cursorY == 0 && cursorX == 0) {
                leftRookWhite = 1;
            }else if(cursorX == 0 && cursorY == 7) {
                rightRookWhite = 1;
            }
        }else {
            if(cursorY == 0 && cursorX == 7) {
                leftRookBlack = 1;
            }else if(cursorX == 7 && cursorY == 7) {
                rightRookBlack = 1;
            }
        }
    }
    *b = *a;
    a->type = EMPTY;
    a->color = 0;
    resetMovesHash();
    return 1;
}

int handleCursor(int col) {//  TAKES THE INPUT FROM USER AND MOVES THE CURSOR ACCORDINGLY
    int ch;
    int i, j;
    fflush(stdin);
    ch = _getch();
    if((char)ch == 'm' || (char)ch == 'M') {
        MUTE *= -1;
    }
    if(ch == 27) {
            if(MUTE < 0) {
                    _beep(800, 50);
                }
        if(quit()) {
            cursorX = 0;
            cursorY = 0;
            return 0;
        }else {
            return 1;
        }
    }else if(ch == 13) {
        if(MUTE < 0) {
            _beep(800, 50);
        }
        printf("\n\t\t");
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
                    printBoard();
                    flag = selectPosition(len);
                }while(flag==1);
            }
        }
    }
    if(ch == 224 || ch == 0) {
        ch = _getch();
        switch(ch) {
            case UP_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                for(int i=cursorX-1; i>=0; i--) {
                    if(board[i][cursorY].color == col || board[i][cursorY].color == 0) {
                        cursorX = i;
                        break;
                    }
                }
                return 1;

            case LEFT_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                for(int i=cursorY-1; i>=0; i--) {
                    if(board[cursorX][i].color == col || board[cursorX][i].color == 0) {
                        cursorY = i;
                        break;
                    }
                }
                return 1;

            case DOWN_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                for(int i=cursorX+1; i<=7; i++) {
                    if(board[i][cursorY].color == col || board[i][cursorY].color == 0) {
                        cursorX = i;
                        break;
                    }
                }
                return 1;

            case RIGHT_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                for(int i=cursorY+1; i<=7; i++) {
                    if(board[cursorX][i].color == col || board[cursorX][i].color == 0) {
                        cursorY = i;
                        break;
                    }
                }
                return 1;

//
//        case 'c':
//        case 'C':
//            controls();
//            return 1;
//
//
//            possible_moves();
//            int len;
//            stackPointer = -1;
//            int flag;
//            mainX = cursorX;
//            mainY = cursorY;
//            if(board[cursorX][cursorY].type != EMPTY) {
//                if(isMovesHashEmpty() == 0) {
//                    len = pieceMoves();
//                    do {
//                        printBoard();
//                        flag = selectPosition(len);
//                    }while(flag==1);
//                }
            }
        }

    return 1;
}

int loadingScreen(int time) {   //  DISPLAYS THE LOADING SCREEN
    system("cls");
    gotoxy(50,10);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    gotoxy(50,11);
    printf("%c                      %c", 186, 186);
    gotoxy(50,12);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    for(int i=0; i<22; i++) {
        gotoxy(51+i, 11);
        printf("%c", 219);
        gotoxy(75, 11);
        float percent = ((i+1)/(float)22)*100;
        printf("%.0f%c", percent, '%');
        _sleep(time);
    }
    printf("\n\n");
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
    i = 1;
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
    if(black_checked == 0 && white_checked == 0)
    castling();
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
				checkmate_hash[cursorX+1][cursorY+1] = 1;
			}else {
				moves_hash[cursorX+1][cursorY+1]=1;
			}
        }
        if(board[cursorX+1][cursorY-1].color!=board[cursorX][cursorY].color&&cursorX+1<8&&cursorY-1>=0) {
			if(check_flag) {
				checkmate_hash[cursorX+1][cursorY-1] = 1;
			}else {
				moves_hash[cursorX+1][cursorY-1]=1;
			}
        }
        if(board[cursorX-1][cursorY+1].color!=board[cursorX][cursorY].color&&cursorX-1>=0&&cursorY+1<8) {
			if(check_flag) {
				checkmate_hash[cursorX-1][cursorY+1] = 1;
			}else {
				moves_hash[cursorX-1][cursorY+1]=1;
			}
        }
        if(board[cursorX-1][cursorY-1].color!=board[cursorX][cursorY].color&&cursorX-1>=0&&cursorY-1>=0) {
			if(check_flag) {
				checkmate_hash[cursorX-1][cursorY-1] = 1;
			}else {
				moves_hash[cursorX-1][cursorY-1]=1;
			}
        }
}

int pawn_moves() {  //TO PRINT THE POSSIBLE MOVES OF THE PAWN
    if(board[cursorX][cursorY].color==1&&front_color==WHITE) {
            if(cursorX == 7){
            board[cursorX][cursorY].type = pawnChoice();
        }else{
        if(board[cursorX+1][cursorY].color==0) {
            if(check_flag) {
                checkmate_hash[cursorX+1][cursorY]=1;
                checkmate_hash[cursorX+1][cursorY+1]=1;
                checkmate_hash[cursorX+1][cursorY-1]=1;
			}else {
                moves_hash[cursorX+1][cursorY]=1;
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
        }
        }else if(board[cursorX][cursorY].color==-1&&front_color==1) {
        if(cursorX == 0){
            board[cursorX][cursorY].type = pawnChoice();
        }else
        {
            if(board[cursorX-1][cursorY].color==0) {
			if(check_flag) {
                checkmate_hash[cursorX-1][cursorY]=1;
                checkmate_hash[cursorX-1][cursorY-1]=1;
                checkmate_hash[cursorX-1][cursorY+1]=1;
			}else {
                moves_hash[cursorX-1][cursorY]=1;
                }
			}
        if(board[cursorX-1][cursorY-1].color==-1*board[cursorX][cursorY].color&&cursorX-1>=0&&cursorY-1>=0) {
            if(check_flag) {
                checkmate_hash[cursorX-1][cursorY-1]=1;
			}else {
                moves_hash[cursorX-1][cursorY-1]=1;
			}
        }
        if(board[cursorX-1][cursorY+1].color==-1*board[cursorX][cursorY].color&&cursorX-1>=0&&cursorY+1<8) {
            if(check_flag) {
                checkmate_hash[cursorX-1][cursorY+1]=1;
			}else {
                moves_hash[cursorX-1][cursorY+1]=1;
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

int castling(){
 if(cursorY == 3 && cursorX == 0||cursorX==7){
    if((board[cursorX][cursorY].color == WHITE && whiteFlag==0 )|| (board[cursorX][cursorY].color == BLACK && blackFlag==0)) {
    if(board[cursorX][2].type == EMPTY && board[cursorX][1].type == EMPTY && board[cursorX][0].type == ROOK && board[cursorX][0].color == board[cursorX][cursorY].color) {
        moves_hash[cursorX][cursorY-2] = 1;
        }
    if(board[cursorX][4].type == EMPTY && board[cursorX][5].type == EMPTY && board[cursorX][6].type == EMPTY && board[cursorX][7].type == ROOK && board[cursorX][7].color == board[cursorX][cursorY].color) {
        moves_hash[cursorX][cursorY+2] = 1;
        }
    }
 }
    return 1;
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
    gotoxy(35, 8);
    printf("    UP_ARROW       :     move up");
    gotoxy(35, 10);
    printf("  DOWN_ARROW       :     move down");
    gotoxy(35, 12);
    printf("  LEFT_ARROW       :     move left");
    gotoxy(35, 14);
    printf("  DOWN_ARROW       :     move down");
    gotoxy(35, 16);
    printf("       ENTER       :     select an option");
    gotoxy(35, 18);
    printf("         ESC       :     go back");
    gotoxy(35, 30);
    system("pause");
}

int selectPosition(int len) {   // HELPS THE USER TO DECICE TO PICK LOCATION, MOVE PIECE OR RETURN BACK
    int ch;
    int beepsound;
    if(col == WHITE) {
    gotoxy(3, 7);
    printf("ENTER: select piece");
    gotoxy(3, 8);
    printf("ESC: select different piece/ go back");
    gotoxy(3, 9);
    }else {
    gotoxy(83, 7);
    printf("ENTER: select piece");
    gotoxy(83, 8);
    printf("ESC: select different piece/ go back");
    gotoxy(85, 9);
    }
    ch = _getch();
    if(ch==13) {
            if(MUTE < 0) {
                    _beep(800, 50);
                }
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
    }
    if(ch==224 || ch==0) {
        ch = _getch();
        int found = 0;
        switch(ch) {
        case UP_ARROW:
            if(MUTE < 0) {
                    _beep(800, 50);
                }
            found = 0;
            for(int i=cursorX-1; i>=0; i--) {
                if(moves_hash[i][cursorY]) {
                    cursorX = i;
                    found = 1;
                    break;
                }
            }
            if(!found) {
                for(int i=cursorX-1; i>=0; i--) {
                    if(moves_hash[i][cursorY-1]) {
                        cursorX = i;
                        cursorY--;
                        found = 1;
                        break;
                    }
                }
            }
            if(!found) {
                for(int i=cursorX-1; i>=0; i--) {
                    if(moves_hash[i][cursorY+1]) {
                        cursorX = i;
                        cursorY++;
                        found = 1;
                        break;
                    }
                }
            }
            return 1;
            break;
        case DOWN_ARROW:
            if(MUTE < 0) {
                    _beep(800, 50);
                }
            found = 0;
            for(int i=cursorX+1; i<=7; i++) {
                if(moves_hash[i][cursorY]) {
                    cursorX = i;
                    found = 1;
                    break;
                }
            }
            if(!found) {
                for(int i=cursorX+1; i<=7; i++) {
                    if(moves_hash[i][cursorY-1]) {
                        cursorX = i;
                        cursorY--;
                        found = 1;
                        break;
                    }
                }
            }
            if(!found) {
                for(int i=cursorX+1; i<=7; i++) {
                    if(moves_hash[i][cursorY+1]) {
                        cursorX = i;
                        cursorY++;
                        found = 1;
                        break;
                    }
                }
            }
            return 1;
            break;
        case LEFT_ARROW:
            if(MUTE < 0) {
                    _beep(800, 50);
                }
            found = 0;
            for(int j=cursorY-1; j>=0; j--) {
                if(moves_hash[cursorX][j]) {
                    cursorY = j;
                    found = 1;
                    break;
                }
            }
            if(!found) {
                for(int j=cursorY-1; j>=0; j--) {
                    if(moves_hash[cursorX-1][j]) {
                        cursorY = j;
                        cursorX--;
                        found = 1;
                        break;
                    }
                }
            }
            if(!found) {
                for(int j=cursorY-1; j>=0; j--) {
                    if(moves_hash[cursorX+1][j]) {
                        cursorY = j;
                        cursorX++;
                        found = 1;
                        break;
                    }
                }
            }
            return 1;
            break;
        case RIGHT_ARROW:
            if(MUTE < 0) {
                    _beep(800, 50);
                }
            found = 0;
            for(int j=cursorY+1; j<=7; j++) {
                if(moves_hash[cursorX][j]) {
                    cursorY = j;
                    found = 1;
                    break;
                }
            }
            if(!found) {
                for(int j=cursorY+1; j<=7; j++) {
                    if(moves_hash[cursorX+1][j]) {
                        cursorY = j;
                        cursorX++;
                        found = 1;
                        break;
                    }
                }
            }
            if(!found) {
                for(int j=cursorY+1; j<=7; j++) {
                    if(moves_hash[cursorX-1][j]) {
                        cursorY = j;
                        cursorX--;
                        found = 1;
                        break;
                    }
                }
            }
            return 1;
            break;
        }
    }
}

void resetCheckHash() { // RESETS THE HASH TABLE
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

void printCheckHash(){
    int i,j;
    for( i = 0 ; i < 8 ; i++){
        for( j = 0 ; j < 8 ; j++)
        {
            printf("%d ",checkmate_hash[i][j]);
        }
        printf("\n");
    }
}

int setCursor() {// SETS THE CURSOR TO INITIAL POSITION
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
    system("color 0e");
    char ch;
    for(int i=0; i<4; i++) {
      system("cls");
      switch(i) {
        case 0:
          ch = BLOCK1;
          break;
        case 1:
          ch = BLOCK3;
          break;
        case 2:
          ch = BLOCK1;
          break;
        case 3:
          ch = BLOCK;
          break;
      }
      printf("\n\n\n\n\n\n\n\n\n\n");
      printf("\n\t\t\t\t  %c%c%c%c%c %c   %c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c  %c%c%c%c%c %c   %c  %c%c%c%c%c", ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch);
      printf("\n\t\t\t\t  %c     %c   %c %c     %c     %c        %c   %c%c  %c  %c    ", ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch);
      printf("\n\t\t\t\t  %c     %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c    %c   %c %c %c  %c    ", ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch);
      printf("\n\t\t\t\t  %c     %c   %c %c         %c     %c    %c   %c  %c%c  %c    ", ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch);
      printf("\n\t\t\t\t  %c%c%c%c%c %c   %c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c  %c%c%c%c%c %c   %c  %c%c%c%c%c", ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch);
      printf("\n\n\t\t\t\t  ");
      _sleep(300);
    }
    ch = BLOCK2;
    for(int i=0; i<50-1; i++) {
      _sleep(30);
      printf("%c", ch);
    }
    system("color f0");
}

int mainMenu() {
    int X = 0;
    int ch;
    char *op[6]={"Play Game", "Rules of Chess", "Controls", "Settings", "About Us", "Quit"};
    do {
      system("cls");
      for(int i=0; i<6; i++) {
        gotoxy(40, 5 + i*2);
        if(X==i) {
            printf("%c  %s", 254, op[i]);
        }else {
            printf("   %s", op[i]);
        }
      }
      gotoxy(15, 25);
      printf("Go to the controls if this is the first time you are using this application.");
      gotoxy(40, 20);
      ch = _getch();
      if((char)ch == 'm' || (char)ch == 'M') {
        MUTE *= -1;
      }
      if(ch == 13) {
        if(MUTE < 0) {
                    _beep(800, 50);
                }
        switch(X) {
            case 0:
                gotoxy(43, 5);
                break;
            case 1:
                gotoxy(43, 7);
                break;
            case 2:
                gotoxy(43, 9);
                break;
            case 3:
                gotoxy(43, 11);
                break;
            case 4:
                gotoxy(43, 13);
                break;
            case 5:
                gotoxy(43, 15);
                break;
            case 6:
                gotoxy(43, 17);
                break;
        }
        for(int i=0; i<strlen(op[X]); i++) {
            printf("%c", 219);
            _sleep(25);
        }
        return X+1;
    }
    if(ch == 224 || ch == 0) {
        ch = _getch();
        switch(ch) {
          case UP_ARROW:
            if(MUTE < 0) {
            _beep(700, 50);
            }
            X--;
            if(X<0) {
              X=5;
            }
            break;

          case DOWN_ARROW:
              if(MUTE < 0) {
            _beep(700, 50);
              }
            X++;
            if(X>5) {
                X=0;
            }
            break;
        }
      }
    }while(1);
}

int startGame() {
    piece temp;
    int tempX,tempY,i;
    initializeBoard();
    // CHECK THIS
    leftRookBlack = 0;
    leftRookWhite = 0;
    rightRookBlack = 0;
    rightRookWhite = 0;
    whiteDeadPointer = -1;
    blackDeadPointer = -1;
    resetCheckHash();   //
    resetMovesHash();   //
    col = WHITE;        //
    cursorX = 0;        //
    cursorY = 0;
    moved = 0;        //
    // CHECK THIS
    do {
            printBoard();
            if(black_checked || white_checked){
                    find_checkedpiece_path();
//                    for(i=0;checkstack[i].x!=-1;i++)
//                        printf("%d %d\n",checkstack[i].x,checkstack[i].y);
//                    system("pause");

                    if( checkmate())
                    {
                        if(is_king_can_move()){
//                        printf("\nEntered");
//                        system("pause");
                        //printBoard();
                        system("cls");
                        gotoxy(50, 10);
                        printf("CHECK-MATE");
                        _sleep(3000);
                        system("cls");
                        gotoxy(50, 10);
                        if(col==WHITE) {
                            printf("%s WINS", player2);
                        }else {
                            printf("%s WIN", player1);
                        }
                        _sleep(3000);
                        break;
                        }
                    }
                       // find_checkedpiece_path();
                       if(board[cursorX][cursorY].type == KING){
                        if(is_king_can_move()){
                            resetMovesHash();
                        }
                        else{
                            resetMovesHash();
                            king_moves();
                        }
                       }
                       else
                        possible_moves_at_check();
//                        printHash();
//                        system("pause");


        }
        else{
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
        }
        board[whiteKing.x][whiteKing.y].type = KING;
        board[whiteKing.x][whiteKing.y].color = WHITE;
        board[blackKing.x][blackKing.y].type = KING;
        board[blackKing.x][blackKing.y].color = BLACK;
        printBoard();

//        printHash();
//        system("pause");
        resetMovesHash();
        resetCheckHash();
    }while(handleCursor(col));
    return 1;
}

int find_checkedpiece_path(){ // FINDS THE PATH FROM CHECKEING PIECE TO OPPENENT KING
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

        }
        return 0;
}

int find_rook_path(){// FIND THE ROOK PATH
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

int find_bishop_path(){//FINDS THE BISHOP PATH
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

int find_queen_path(){//FINDS THE QUEEN PATH
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

int find_knight_path(){//FINDS THE KNIGHT PATH
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

int find_pawn_path(){//FINDS THE PAWN PATH
    int i,j,k=0;
    i = checkedKing.x;
    j = checkedKing.y;
    if(board[checkedKing.x][checkedKing.y].color == WHITE){
    if(i+1 == checkingPiece_pos.x && j+1 == checkingPiece_pos.y){
        checkstack[k].x = i+1;
        checkstack[k].y = j+1;
    }
   else if(i+1 == checkingPiece_pos.x && j-1 == checkingPiece_pos.y){
        checkstack[k].x = i+1;
        checkstack[k].y = j-1;
    }
    }
    else if(board[checkedKing.x][checkedKing.y].color == BLACK){
    if(i-1 == checkingPiece_pos.x && j-1 == checkingPiece_pos.y){
        checkstack[k].x = i-1;
        checkstack[k].y = j-1;
    }
    else if(i-1 == checkingPiece_pos.x && j+1 == checkingPiece_pos.y){
        checkstack[k].x = i-1;
        checkstack[k].y = j+1;
    }
    }
    checkstack[k+1].x = -1;
   // printf("  %d %d ",checkstack[0].x,checkstack[0].y);
    //system("pause");
}

int checkmate() {// RETURNS 1 IF CHECKMATE SITUATION ARRIVES
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

int all_moves(){// FIX THE HASH TABLE WITH ALL THE MOVES EXCEPT KING WHICH IS USED IN CHECKMATE METHOD
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

                    case QUEEN:
                        queen_moves();
                        break;
                    default:
                        break;
                }
            }
        }
    }

}

int possible_moves_at_check(){//FINDS THE POSSIBLE MOVES AFTER CHECKING THE OPPONENT KING
    int i, cons = 0 ;
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
                if(moves_hash[checkstack[i].x][checkstack[i].y])
                {
                        tempArr[checkstack[i].x][checkstack[i].y] = 1;
                        cons = 1;
                }

            }
            if(cons)
                copyArray();
            else
                resetMovesHash();
            resetTempArray();
            return 1;
}

int copyArray(){
int i,j;
for(i=0;i<8;i++){
        for(j=0;j<8;j++)
    moves_hash[i][j] = tempArr[i][j];
}
}

resetTempArray(){
int i,j;
for(i=0;i<8;i++){
    for(j=0;j<8;j++)
        tempArr[i][j] = 0;
}
}

int instructions() {//  DISPLAYS THE INSTRUCTION OF THE GAME
    FILE *fp;
    system("cls");
    char ch;
    fp = fopen("instructions.txt", "r");
    if(fp == NULL) {
        gotoxy(50, 10);
        printf("Unable to open the file!");
        gotoxy(50, 25);
        system("pause");
    }else {
        while((ch=fgetc(fp)) != EOF) {
            printf("%c", ch);
        }
        printf("\n");
        system("pause");
    }
    fclose(fp);
    return 1;
}

int aboutUs() {
    system("cls");
    gotoxy(30, 10);
    printf("Hi, we are Sreekara Mouli and Sunny. We are currently doing our");
    gotoxy(30, 12);
    printf("computer science engineering in St Martin's Engineering College.");
    gotoxy(30, 14);
    printf("We collaborated on doing a C program to build a Chess engine and");
    gotoxy(30, 16);
    printf("this is what we have achieved.");
    gotoxy(30, 20);
    printf("Hoped you all like it! :)");
    gotoxy(30, 22);
    printf("Thank You!");
    gotoxy(30, 30);
    printf("You can download this project at");
    gotoxy(30, 32);
    FILE *fp;
    char ch;
    fp = fopen("downloadURL.txt", "r");
    if(fp == NULL) {
        printf("URL temporarily not available !!");
    }else {
        while((ch=fgetc(fp)) != EOF) {
            printf("%c", ch);
        }
        printf("\n");
    }
    fclose(fp);
    gotoxy(35, 35);
    _getch();
    return 1;
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

int is_king_can_move() {// CHECKES WHETHER A CHECKED KING CAN MOVE AFTER CHECKING
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
    board[king_stack[i].x][king_stack[i].y] = temp;
    if(moves_hash[king_stack[i].x][king_stack[i].y] == 0)
    {
        board[checkedKing.x][checkedKing.y].color = temp_color;
        board[checkedKing.x][checkedKing.y].type = KING;
        return 0;
    }
    }
        board[checkedKing.x][checkedKing.y].color = temp_color;
        board[checkedKing.x][checkedKing.y].type = KING;
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

int scanPlayers() {// SCANS THE  PLAYERNAMES
    system("cls");
    int i;
    char ch;
    player1[0]='\0';
    player2[0]='\0';
    for(i=0; i<2; i++) {
        gotoxy(40,10+i*5+1);
        printf("PLAYER %d: ", i+1);
        gotoxy(50,10+i*5);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
        gotoxy(50,11+i*5);
        printf("%c                      %c", 186, 186);
        gotoxy(50,12+i*5);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    }
    gotoxy(51, 11);
    i=0;
    while((ch=_getche())!=13) {
        if(MUTE < 0) {
        _beep(500, 50);
        }
        if(ch==27) {
            return 0;
        }
        player1[i++]=ch;
    }
    player1[i]='\0';
    if(player1[0]=='\0') {
        strcpy(player1, "Player 1");
    }
    gotoxy(51, 16);
    i=0;
    while((ch=_getche())!=13) {
        if(MUTE < 0) {
            _beep(500, 50);
        }
        if(ch==27) {
            return 0;
        }
        player2[i++]=ch;
    }
    player2[i]='\0';
    if(player2[0]=='\0') {
        strcpy(player2, "Player 2");
    }
    return 1;
}

int quit() {
    cursorX = 0;
    cursorY = 0;

    int op;
    int x=1;
    do {
        system("cls");
        gotoxy(45, 10);
        printf("Are you sure you want to exit?");
//        for(int i=0; i<2; i++) {
//            gotoxy(50+10*i,15);
//            printf("%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 187);
//            gotoxy(50+10*i,16);
//            if(x==i) {
//                printf("%c     %c", 175, 174);
//            }else {
//                printf("%c     %c", 186, 186);
//            }
//            gotoxy(50+10*i,17);
//            printf("%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 188);
//        }
        for(int i = 0; i < 2; i++) {
            gotoxy(50+10*i,16);
            if(x==i) {
                printf("%c     %c", 175, 174);
            }else {
                //printf("%c     %c", 186, 186);
            }
        }
        gotoxy(51, 16);
        printf(" YES");
        gotoxy(61, 16);
        printf(" NO");
        gotoxy(75, 10);
        op = _getch();
        if(op == 27) {
                if(MUTE < 0) {
                    _beep(800, 50);
                }
            return 0;
        }else if(op == 13) {
            if(MUTE < 0) {
                    _beep(800, 50);
                }
            if(x==1) {
                return 0;
            }else {
                return 1;
            }
        }else if(op == 224 || op ==0) {
            op = _getch();
            switch(op) {
            case LEFT_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                x--;
                if(x<0) {
                    x=1;
                }
                break;
            case RIGHT_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                x++;
                if(x>1) {
                    x=0;
                }
                break;
            }

        }
    }while(1);
}

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);

}

int thankYou() {
    system("cls");
    system("color 0e");
    gotoxy(25, 5);
	printf("%c%c%c%c%c%c%c %c     %c    %c    %c     %c %c     %c   %c     %c %c%c%c%c%c%c%c %c     %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(25, 6);
	printf("   %c    %c     %c   %c %c   %c%c    %c %c   %c      %c   %c  %c     %c %c     %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(25, 7);
	printf("   %c    %c     %c  %c   %c  %c %c   %c %c %c         %c %c   %c     %c %c     %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(25, 8);
	printf("   %c    %c%c%c%c%c%c%c %c%c%c%c%c%c%c %c  %c  %c %c%c           %c    %c     %c %c     %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(25, 9);
	printf("   %c    %c     %c %c     %c %c   %c %c %c %c          %c    %c     %c %c     %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(25, 10);
	printf("   %c    %c     %c %c     %c %c    %c%c %c   %c        %c    %c     %c %c     %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(25, 11);
	printf("   %c    %c     %c %c     %c %c     %c %c     %c      %c    %c%c%c%c%c%c%c %c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	for(int i=0; i<68; i++) {
        gotoxy(23+i, 13);
        printf("%c", 219);
        gotoxy(91-i, 3);
        printf("%c", 219);
        _sleep(10);
	}
	for(int i=0; i<10; i++) {
        gotoxy(23, 3+i);
        printf("%c", 219);
        gotoxy(91, 13-i);
        printf("%c", 219);
        _sleep(10);
	}
	gotoxy(25, 25);
}

int pawnChoice() {
    int X = 0;
    int ch;
    do {
        system("cls");
        gotoxy(35, 10);
        if(X==0) {
            printf(">> QUEEN");
        }else {
            printf("   QUEEN");
        }
        gotoxy(35, 12);
        if(X==1) {
            printf(">> ROOK");
        }else {
            printf("   ROOK");
        }
        gotoxy(35, 14);
        if(X==2) {
            printf(">> BISHOP");
        }else {
            printf("   BISHOP");
        }
        gotoxy(35, 16);
        if(X==3) {
            printf(">> KNIGHT");
        }else {
            printf("   KNIGHT");
        }
        gotoxy(35, 18);
        ch = _getch();
        if(ch == 13) {
            switch(X) {
            case 0:
                return QUEEN;
                break;

            case 1:
                return ROOK;
                break;

            case 2:
                return BISHOP;
                break;

            case 3:
                return KNIGHT;
                break;
            }
        }else if(ch==224 || ch==0) {
            ch = _getch();
            switch(ch) {
            case UP_ARROW:
                X--;
                if(X<0) {
                    X=3;
                }
                break;

            case DOWN_ARROW:
                X++;
                if(X>3) {
                    X=0;
                }
                break;
            }
        }

    }while(1);
}

void settings() {
    cursorX = 0;
    cursorY = 0;
    int op;
    int x=1;
    int y=0;
    do {
        system("cls");
        esc();
        gotoxy(30, 10);
        printf("Toggle Sound");
        gotoxy(26, 15);
        printf("Toggle Dark Mode");
        for(int i = 0; i < 2; i++) {
            gotoxy(53+10*i,10 + 5 * y);
            if(x==i) {
                printf("%c", 254);
            }
        }
        if(MUTE < 0) {
            gotoxy(54, 9);
            printf("%c%c%c%c%c%c", top_left_corner, horizontal_line, horizontal_line, horizontal_line, horizontal_line, top_right_corner);
            gotoxy(54, 10);
            printf("%c    %c", vertical_line, vertical_line);
            gotoxy(54, 11);
            printf("%c%c%c%c%c%c", bottom_left_corner, horizontal_line, horizontal_line, horizontal_line, horizontal_line, bottom_right_corner);
        } else if( MUTE > 0) {
            gotoxy(64, 9);
            printf("%c%c%c%c%c%c%c", top_left_corner, horizontal_line, horizontal_line, horizontal_line, horizontal_line, horizontal_line, top_right_corner);
            gotoxy(64, 10);
            printf("%c     %c", vertical_line, vertical_line);
            gotoxy(64, 11);
            printf("%c%c%c%c%c%c%c", bottom_left_corner, horizontal_line, horizontal_line, horizontal_line, horizontal_line, horizontal_line, bottom_right_corner);
        }
        if( DARK_MODE < 0) {
            gotoxy(54, 14);
            printf("%c%c%c%c%c%c", top_left_corner, horizontal_line, horizontal_line, horizontal_line, horizontal_line, top_right_corner);
            gotoxy(54, 15);
            printf("%c    %c", vertical_line, vertical_line);
            gotoxy(54, 16);
            printf("%c%c%c%c%c%c", bottom_left_corner, horizontal_line, horizontal_line, horizontal_line, horizontal_line, bottom_right_corner);
        } else if ( DARK_MODE > 0) {
            gotoxy(64, 14);
            printf("%c%c%c%c%c%c%c", top_left_corner, horizontal_line, horizontal_line, horizontal_line, horizontal_line, horizontal_line, top_right_corner);
            gotoxy(64, 15);
            printf("%c     %c", vertical_line, vertical_line);
            gotoxy(64, 16);
            printf("%c%c%c%c%c%c%c", bottom_left_corner, horizontal_line, horizontal_line, horizontal_line, horizontal_line, horizontal_line, bottom_right_corner);
        }
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                gotoxy(55 + 10 * j, 10 + 5 * i);
                if(j == 0) {
                    printf(" ON");
                }
                else {
                    printf(" OFF");
                }
            }
        }
        gotoxy(75, 10);
        op = _getch();
        if(op == 27) {
            if(MUTE < 0) {
                _beep(800, 50);
            }
            return;
        }else if(op == 13) {
            if(MUTE < 0) {
                _beep(800, 50);
            }
            if(y == 0 && x == 0) {
                MUTE = -1;
            } else if( y == 0 && x == 1) {
                MUTE = 1;
            } else if( y == 1 && x == 0) {
                DARK_MODE = -1;

            } else if ( y == 1 && x == 1) {
                DARK_MODE = 1;
            }
            displayMode();
        }else if(op == 224 || op ==0) {
            op = _getch();
            switch(op) {
            case UP_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                y--;
                if(y < 0) {
                    y = 1;
                }
                break;
            case DOWN_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                y++;
                if(y > 1) {
                    y = 0;
                }
                break;
            case LEFT_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                x--;
                if(x<0) {
                    x=1;
                }
                break;
            case RIGHT_ARROW:
                if(MUTE < 0) {
                    _beep(800, 50);
                }
                x++;
                if(x>1) {
                    x=0;
                }
                break;
            }

        }
    }while(1);
}

void displayMode() {
    if(DARK_MODE > 0) {
        system("color f0");
    }
    else {
        system("color 0f");
    }
}

void esc() {
    gotoxy(35, 30);
    printf("Press ESC to go back.");
}
