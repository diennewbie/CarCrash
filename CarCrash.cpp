#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 90

using namespace std;

int enemyX[3];
int enemyY[3];
bool enemyExist[3];
char car[4][4] = {' ','[',']',' ',
                  '[','|','|',']',
                  ' ','|','|',' ',
                  '[','|','|',']'};
int carPos = WIN_WIDTH / 2;
int score = 0;

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hideCursor(bool visible, DWORD size){
    if(size == 0) {
        size = 20;
    }
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = visible;
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursorInfo);
}

void printBorder(){
    for(int i = 0; i < SCREEN_HEIGHT; i++){
        for(int j = 0; j < 15; j++){
            gotoxy(j,i); cout<<"#";
            gotoxy(SCREEN_WIDTH - j,i); cout<<"#";
        }
    }
}

void printEnemy(int index){
    if(enemyExist[index] == true){
        gotoxy(enemyX[index], enemyY[index] + 0); cout<<"@@@@";
        gotoxy(enemyX[index], enemyY[index] + 1); cout<<" @@ ";
        gotoxy(enemyX[index], enemyY[index] + 2); cout<<"@@@@";
        gotoxy(enemyX[index], enemyY[index] + 3); cout<<" @@ ";
    }
}

void eraseEnemy(int index){
    if(enemyExist[index] == true){
        gotoxy(enemyX[index], enemyY[index] + 0); cout<<"    ";
        gotoxy(enemyX[index], enemyY[index] + 1); cout<<"    ";
        gotoxy(enemyX[index], enemyY[index] + 2); cout<<"    ";
        gotoxy(enemyX[index], enemyY[index] + 3); cout<<"    ";
    }
}

void randomEnemy(int index){
    enemyX[index] = 15 + rand() % (35);
    enemyY[index] = 1;
    enemyExist[index] = true;
}

void resetEnemy(int index){
    eraseEnemy(index);
    enemyY[index] = 1;
    randomEnemy(index);
}

void printPlayerCar(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            gotoxy(j + carPos, i + 22);
            cout<<car[i][j];
        }
    }
}

void erasePlayerCar(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            gotoxy(j + carPos, i + 22);
            cout<<" ";
        }
    }
}

int collision(){
    if(enemyY[0] + 4 >= 23){
        if(enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9){
            return 1;
        }
    }
    return 0;
}

void printGameover(){
    system("cls");
    cout<<endl;
    cout<<"/t/t---------GameOver---------/t/t";
    getch();
}

void printScore(){
    gotoxy(WIN_WIDTH + 7,5) ;
    cout<<"Your Score is:"<<score<<endl;
}

void printInstructions(){
    gotoxy(WIN_WIDTH + 7,13);
    cout<<"How to play:";
    gotoxy(WIN_WIDTH + 4,15);
    cout<<"A - Left";
    gotoxy(WIN_WIDTH + 4,16);
    cout<<"D - Right";
}

void play(){
    carPos = WIN_WIDTH / 2;
    score = 0;

    system("cls");
    printBorder();
    printScore();
    printInstructions();
    gotoxy(18,5);
    cout<<"Press any key to play";
    getch();
    gotoxy(18,5);
    cout<<"                     ";
    while(1){
        if(kbhit()){
            char ch = getch();
            if(ch == 'a' || ch == 'A'){
                if(carPos > 16){
                    carPos -= 4;
                }
            }
            if(ch == 'd' || ch == 'D'){
                if(carPos < 60 ){
                    carPos += 4;
                }
            }
            if(ch == 27){
                break;
            }
        }
        printPlayerCar();
        printEnemy(0);
        printEnemy(1);
        if(collision(1)){
            printGameover();
            return;
        }
        Sleep(50);
        erasePlayerCar();
        eraseEnemy(0);
        eraseEnemy(1);
        if(enemyY[0] > SCREEN_HEIGHT - 4){
            resetEnemy(0);
            score++;
            printScore();
        }
        if(enemyY[1] > SCREEN_HEIGHT - 4 ){
            resetEnemy(0);
            score++;
            printScore();
        }
        
    }
    
}

int main()
{
    srand(time(0));
    play();
    system("pause >nul");
    
}
