#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <chrono>
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 38
#define WIN_WIDTH 50

using namespace std;

int score = 0;
int level = 1;
int lives = 1;
bool playAgain = true;
const int MAX_ENEMIES = 3;

struct makeEnemy {
    int X, Y;
    int delayCounter;
    bool active;
};

makeEnemy enemies[MAX_ENEMIES];

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor(bool visible, DWORD size) {
    if (size == 0) size = 20;
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = visible;
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void printBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < 15; j++) {
            gotoxy(j, i); cout << "#";
            gotoxy(SCREEN_WIDTH - j - 1, i); cout << "#";
        }
        gotoxy(21, i); cout << "|";
        gotoxy(28, i); cout << "|";
    }
}

void printEnemy(int x, int y) {
    gotoxy(x, y);     cout << "@@@@";
    gotoxy(x, y + 1); cout << " @@ ";
    gotoxy(x, y + 2); cout << "@@@@";
    gotoxy(x, y + 3); cout << " @@ ";
}

void eraseEnemy(int x, int y) {
    for (int i = 0; i < 4; i++) {
        gotoxy(x, y + i); cout << "    ";
    }
}

void printPlayerCar(int x, int y) {
    gotoxy(x, y);     cout << " || ";
    gotoxy(x, y + 1); cout << "O||O";
    gotoxy(x, y + 2); cout << " || ";
    gotoxy(x, y + 3); cout << "O||O";
}

void erasePlayerCar(int x, int y) {
    for (int i = 0; i < 4; i++) {
        gotoxy(x, y + i); cout << "    ";
    }
}

void printGameOver() {
    system("cls");
    gotoxy(45, 5); cout << " -------------------------- ";
    gotoxy(45, 6); cout << " |        Game Over!      | ";
    gotoxy(45, 7); cout << " --------------------------";
    getch();
    gotoxy(45, 5); cout << " -------------------------------";
    gotoxy(45, 6); cout << " |Press key to play again?(Y/N)|";
    gotoxy(45, 7); cout << " -------------------------------";
    char key = getch();
    if (key == 'N' || key == 'n') playAgain = false;
}

void printScore() {
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Your Score is:" << score;
}

void printLevel() {
    gotoxy(WIN_WIDTH + 7, 1);
    cout << "Level: " << level;
}

void printLives() {
    gotoxy(WIN_WIDTH + 7, 3);
    cout << "Lives: " << lives << "   ";
}

void printWarning() {
    gotoxy(WIN_WIDTH + 10, 18); cout << "WARNING!!!YOU HAVE COLLIDED WITH THE ENEMY!!!";
}

void printInstructions() {
    for (int i = 8; i <= 23; i++) {
        gotoxy(WIN_WIDTH + i, SCREEN_HEIGHT - 6); cout << "-";
    }
    for (int i = SCREEN_HEIGHT - 5; i <= SCREEN_HEIGHT - 1; i++) {
        gotoxy(WIN_WIDTH + 8, i); cout << "|";
        gotoxy(WIN_WIDTH + 23, i); cout << "|";
    }
    for (int i = 8; i <= 23; i++) {
        gotoxy(WIN_WIDTH + i, SCREEN_HEIGHT - 1); cout << "-";
    }
    gotoxy(WIN_WIDTH + 10, SCREEN_HEIGHT - 5); cout << "How to play:";
    gotoxy(WIN_WIDTH + 10, SCREEN_HEIGHT - 3); cout << "A/a - Left";
    gotoxy(WIN_WIDTH + 10, SCREEN_HEIGHT - 2); cout << "D/d - Right";
}

bool checkCollision(int carX, int carY, int enemyX, int enemyY) {
    if (enemyY + 5 > carY) {
        if (enemyX < carX + 4 && enemyX + 4 > carX) return true;
    }
    return false;
}

void play() {
    srand(time(0));
    int carX = 23;
    int carY = SCREEN_HEIGHT - 4;
    score = 0;
    level = 1;
    lives = 1;
    int lastScoreForLevelUp = 0;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].Y = 0;
        enemies[i].X = 16 + 7 * (i % 2);
        enemies[i].delayCounter = i * 5;
        enemies[i].active = false;
    }

    system("cls");
    printBorder();
    gotoxy(WIN_WIDTH + 8, 10); cout << "Press any key to start";
    getch();
    gotoxy(WIN_WIDTH + 8, 10); cout << "                      ";
    printInstructions();
    printScore();
    printLives();
    printLevel();

    while (true) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 27) break;
            erasePlayerCar(carX, carY);
            if (ch == 'a' || ch == 'A') if (carX > 17) carX -= 7;
            if (ch == 'd' || ch == 'D') if (carX < 30) carX += 7;
        }
        printPlayerCar(carX, carY);

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].delayCounter <= 0) {
                enemies[i].active = true;
                printEnemy(enemies[i].X, enemies[i].Y);
            }
        }

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active && checkCollision(carX, carY, enemies[i].X, enemies[i].Y)) {
                lives--;
                printLives();
                if (lives == 0) {
                    printGameOver();
                    return;
                }
                if (lives == 1) {
                    printWarning();
                    gotoxy(WIN_WIDTH + 10, 19); cout << "YOU ONLY HAVE ONE MORE CHANCE!!!";
                }
                printWarning();

                for (int j = 0; j < MAX_ENEMIES; j++) {
                    eraseEnemy(enemies[j].X, enemies[j].Y);
                    enemies[j].Y = 0;
                    enemies[j].delayCounter = j * 5;
                    enemies[j].active = false;
                }
                break;
            }
        }

        Sleep(200);

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) eraseEnemy(enemies[i].X, enemies[i].Y);
        }

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].delayCounter > 0) enemies[i].delayCounter--;
            else if (enemies[i].active) enemies[i].Y += min(6, level + 1);
        }

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active && enemies[i].Y > SCREEN_HEIGHT) {
                enemies[i].Y = 0;
                enemies[i].X = 16 + 7 * (rand() % 3);
                enemies[i].delayCounter = 5 + rand() % 5;
                enemies[i].active = false;
                score++;
                printScore();
                if (score - lastScoreForLevelUp >= 10) {
                    level = min(level + 1, 6);
                    lastScoreForLevelUp = score;
                }
                printLevel();
            }
        }
    }
}

int main() {
    gotoxy(45, 5); cout << "-----------------------------";
    gotoxy(45, 6); cout << "|       Are you ready?      |";
    gotoxy(45, 7); cout << "|                           |";
    gotoxy(45, 8); cout << "|(Press any key to continue)|";
    gotoxy(45, 9); cout << "-----------------------------";
    hideCursor(0, 0);
    srand((unsigned)time(NULL));
    system("pause >nul");
    do {
        play();
    } while (playAgain);
}
