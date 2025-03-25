#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 90

using namespace std;

int score = 0;
bool playAgain = true;
struct makeEnemy{
	int X;
	int Y;
	
};

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

void printEnemy(int x ,int y){
    gotoxy(x, y + 0); cout<<"@@@@";
    gotoxy(x, y + 1); cout<<" @@ ";
    gotoxy(x, y + 2); cout<<"@@@@";
    gotoxy(x, y + 3); cout<<" @@ ";
}

void eraseEnemy(int x, int y){
    gotoxy(x, y + 0); cout<<"    ";
    gotoxy(x, y + 1); cout<<"    ";
    gotoxy(x, y + 2); cout<<"    ";
    gotoxy(x, y + 3); cout<<"    ";
}


void printPlayerCar(int x, int y){
    gotoxy(x, y);     cout << " || ";
    gotoxy(x, y + 1); cout << "O||O";
    gotoxy(x, y + 2); cout << " || ";
    gotoxy(x, y + 3); cout << "O||O";
}

void erasePlayerCar(int x, int y){
	gotoxy(x, y);     cout << "    ";
    gotoxy(x, y + 1); cout << "    ";
    gotoxy(x, y + 2); cout << "    ";
    gotoxy(x, y + 3); cout << "    ";
}

void printGameOver(){
    system("cls");
    gotoxy(45,5); cout<<" -------------------------- "; 
	gotoxy(45,6); cout<<" |        Game Over!      | "; 
	gotoxy(45,7); cout<<" --------------------------";
    getch();
    gotoxy(45,5); cout<<" -------------------------------"; 
	gotoxy(45,6); cout<<" |Press key to play again?(Y/N)|"; 
	gotoxy(45,7); cout<<" -------------------------------";
	char key = getch();
	if(key == 'N' || key == 'n') playAgain = false;
}


void printScore(){
    gotoxy(WIN_WIDTH + 7,5) ;
    cout<<"Your Score is:"<<score<<endl;
}

void printInstructions(){
    gotoxy(WIN_WIDTH + 7,13);
    cout<<"How to play:";
    gotoxy(WIN_WIDTH + 6, 15);
    cout<<"W/w - Up";
    gotoxy(WIN_WIDTH + 6, 16);
    cout<<"A/a - Left";
    gotoxy(WIN_WIDTH + 6, 17);
    cout<<"S/s - Down";
    gotoxy(WIN_WIDTH + 6, 18);
    cout<<"D/d - Right";
}

bool checkCollision(int carX, int carY, int enemyX, int enemyY) {
    if (enemyY + 5 > carY) {
        if (enemyX < carX + 4 && enemyX + 4 > carX) {
            return true;
        }
    }
    return false;
}


void play(){
	srand(time(0));
	makeEnemy enemy1,enemy2;
	
	enemy1.X = 15 + rand() % 28;
	enemy2.X = 45 + rand() % 28;
	enemy1.Y = 0;
	enemy2.Y = 0;
    int carX = SCREEN_WIDTH / 2;
    int carY = SCREEN_HEIGHT - 4;
    score = 0;
    system("cls");
    printBorder();
    printScore();
    printInstructions();
	gotoxy(34, 5);cout<<"Press any key to start";
	getch();
	gotoxy(34, 5);cout<<"                      ";
	while(true){
		if(kbhit()){
			char ch = getch();
			if(ch == 27) break;
			erasePlayerCar(carX, carY);
			if( ch=='a' || ch=='A') {
				if(carX > 17) carX -= 4;
				
			}
			if( ch=='d' || ch=='D'){
				if(carX < 69) carX += 4;
			}
			if( ch=='w' || ch=='W'){
				if(carY > 0) carY -= 2;
			}
			if( ch=='s' || ch=='S'){
				if(carY < SCREEN_HEIGHT - 4) carY += 2;
			}
		}
		printPlayerCar(carX, carY);
    	printEnemy(enemy1.X, enemy1.Y);
    	printEnemy(enemy2.X, enemy2.Y);
    	if(checkCollision(carX,carY,enemy1.X,enemy1.Y) || checkCollision(carX,carY,enemy2.X,enemy2.Y)) {
    		printGameOver();
    		break;
		}
    	Sleep(100);
    	
    	eraseEnemy(enemy1.X, enemy1.Y);
    	eraseEnemy(enemy2.X, enemy2.Y);
    	
    	if(score >= 0){
    		enemy1.Y+=1 + rand() % 2;
    		enemy2.Y+=1 + rand() % 2;
		} 
    	if(enemy1.Y > SCREEN_HEIGHT - 4){
    		enemy1.Y = 0;
    		enemy1.X = 15 + rand() % 28;
    		score++;
    		printScore();
		}
		if(enemy2.Y > SCREEN_HEIGHT - 4){
    		enemy2.Y = 0;
    		enemy2.X = 45 + rand() % 28;
    		score++;
    		printScore();
		}
		
	}
	
}


int main()
{
	gotoxy(45,5); cout<<"--------------------------"; 
	gotoxy(45,6); cout<<"|     Are you ready?     |"; 
	gotoxy(45,7); cout<<"--------------------------";
    hideCursor(0,0);
    srand( (unsigned)time(NULL)); 
    system("pause >nul");
    do{
    	play();
	} while(playAgain);
	
}
