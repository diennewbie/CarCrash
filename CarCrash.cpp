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

int collision(){

    return 0;
}


int main()
{
    srand(time(0));
    system("cls");
    printPlayerCar();
}
