#include <iostream>
#include <windows.h>

using namespace std;

char box = 219;

char tank1[6] = {box, box, box, '-', '-', '>'};
char tank2[6] = {'0', ' ', '0', ' ', ' ', ' '};

char enemy1[6] = {' ', ' ', ' ', '-', '-', '-'};
char enemy2[6] = {'<', '=', '=', '(', '0', ')'};
char enemy3[6] = {' ', ' ', ' ', '\\', '@', '/'};
char enemy4[6] = {' ', ' ', ' ', '*', '*', '*'};

string enemyDirection = "Up";
int score = 0;
int enemyHealth = 100;
int tankHealth = 100;

int bulletX[1000];
int bulletY[1000];
bool isBulletActive[1000];
int bulletCount = 0;

int enemyBulletX[1000];
int enemyBulletY[1000];
bool isEnemyBulletActive[1000];
int enemyBulletCount = 0;

int tankX = 5;
int tankY = 5;

int enemyX = 30;
int enemyY = 10;

void printMaze();

void printTank();
void printEnemy();

void eraseEnemy();
void eraseTank();

void moveBullet();
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void makeBulletInactive(int index);
void generateBullet();
void bulletCollisionWithEnemy();

void moveEnemyBullet();
void printEnemyBullet(int x, int y);
void eraseEnemyBullet(int x, int y);
void makeEnemyBulletInactive(int index);
void generateEnemyBullet();
void bulletCollisionWithTank();

void moveTankLeft();
void moveTankRight();
void moveTankUp();
void moveTankDown();

void addScore();
void printScore();
void eraseEnemyHealth();
void eraseTankHealth();

void printEnemyHealth();
void printTankHealth();
void moveEnemy();

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

main()
{
    int timer = 0;
    system("cls");
    printTank();
    printMaze();
    printEnemy();
    while (true)
    {
        if (enemyHealth <= 0)
        {
            eraseEnemy();
            break;
        }
        if (tankHealth <= 0)
        {
            eraseTank();
            break;
        }
        printScore();
        printEnemyHealth();
        printTankHealth();
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveTankLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveTankRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveTankUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            moveTankDown();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
        }

        if (timer == 3 && (enemyHealth > 0))
        {
            moveEnemy();
            timer = 0;
        }
        moveBullet();
        moveEnemyBullet();
        bulletCollisionWithEnemy();
        bulletCollisionWithTank();
        timer++;
        Sleep(90);
    }
}

void printMaze()
{
    for (int i = 2; i <= 60; i++)
    {
        gotoxy(i, 2);
        cout << "#";
    }

    for (int i = 2; i <= 60; i++)
    {
        gotoxy(i, 30);
        cout << "#";
    }

    for (int i = 2; i <= 30; i++)
    {
        gotoxy(2, i);
        cout << "#";
    }

    for (int i = 2; i <= 30; i++)
    {
        gotoxy(60, i);
        cout << "#";
    }
}
void printTank()
{
    gotoxy(tankX, tankY);
    for (int i = 0; i < 6; i++)
    {
        cout << tank1[i];
    }
    gotoxy(tankX, tankY + 1);
    for (int i = 0; i < 6; i++)
    {
        cout << tank2[i];
    }
}

void printEnemy()
{
    gotoxy(enemyX, enemyY);
    for (int i = 0; i < 6; i++)
    {
        cout << enemy1[i];
    }
    gotoxy(enemyX, enemyY + 1);
    for (int i = 0; i < 6; i++)
    {
        cout << enemy2[i];
    }
    gotoxy(enemyX, enemyY + 2);
    for (int i = 0; i < 6; i++)
    {
        cout << enemy3[i];
    }
    gotoxy(enemyX, enemyY + 3);
    for (int i = 0; i < 6; i++)
    {
        cout << enemy4[i];
    }
}

void eraseTank()
{
    gotoxy(tankX, tankY);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
    gotoxy(tankX, tankY + 1);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
}

void eraseEnemy()
{
    gotoxy(enemyX, enemyY);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 1);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 2);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 3);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
}

void moveTankLeft()
{
    char next = getCharAtxy(tankX - 1, tankY);
    if (next == ' ')
    {
        eraseTank();
        tankX--;
        printTank();
    }
}
void moveTankRight()
{
    char next = getCharAtxy(tankX + 6, tankY);
    if (next == ' ')
    {
        eraseTank();
        tankX++;
        printTank();
    }
}
void moveTankUp()
{
    char next = getCharAtxy(tankX, tankY - 1);
    if (next == ' ')
    {
        eraseTank();
        tankY--;
        printTank();
    }
}
void moveTankDown()
{
    char next = getCharAtxy(tankX, tankY + 2);
    if (next == ' ')
    {
        eraseTank();
        tankY++;
        printTank();
    }
}

void moveEnemy()
{
    if (enemyDirection == "Up")
    {
        char next = getCharAtxy(enemyX, enemyY - 1);
        if (next == ' ')
        {
            eraseEnemy();
            enemyY--;
            printEnemy();
            generateEnemyBullet();
        }
        else if (next == '#')
        {
            enemyDirection = "Down";
        }
    }

    if (enemyDirection == "Down")
    {
        char next = getCharAtxy(enemyX, enemyY + 4);
        if (next == ' ')
        {
            eraseEnemy();
            enemyY++;
            printEnemy();
            generateEnemyBullet();
        }
        else if (next == '#')
        {
            enemyDirection = "Up";
        }
    }
}

void generateBullet()
{
    bulletX[bulletCount] = tankX + 7;
    bulletY[bulletCount] = tankY;
    isBulletActive[bulletCount] = true;
    gotoxy(tankX + 7, tankY);
    cout << ".";
    bulletCount++;
}
void printBullet(int x, int y)
{
    gotoxy(x, y);
    cout << ".";
}

void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void makeBulletInactive(int index)
{
    isBulletActive[index] = false;
}

void moveBullet()
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (isBulletActive[i] == true)
        {
            char next = getCharAtxy(bulletX[i] + 1, bulletY[i]);
            if (next != ' ')
            {
                eraseBullet(bulletX[i], bulletY[i]);
                makeBulletInactive(i);
            }
            else
            {
                eraseBullet(bulletX[i], bulletY[i]);
                bulletX[i]++;
                printBullet(bulletX[i], bulletY[i]);
            }
        }
    }
}
void bulletCollisionWithEnemy()
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (isBulletActive[i])
        {
            if (bulletX[i] + 1 == enemyX && (bulletY[i] == enemyY || bulletY[i] == enemyY + 2 || bulletY[i] == enemyY + 3))
            {
                addScore();
                eraseEnemyHealth();
                enemyHealth = enemyHealth - 5;
            }
            if (enemyX - 1 == bulletX[i] && enemyY + 1 == bulletY[i])
            {
                addScore();
                eraseEnemyHealth();
                enemyHealth = enemyHealth - 5;
            }
        }
    }
}

void moveEnemyBullet()
{
    for (int i = 0; i < enemyBulletCount; i++)
    {
        if (isEnemyBulletActive[i] == true)
        {
            char next = getCharAtxy(enemyBulletX[i] - 1, enemyBulletY[i]);
            if (next != ' ')
            {
                eraseEnemyBullet(enemyBulletX[i], enemyBulletY[i]);
                makeEnemyBulletInactive(i);
            }
            else
            {
                eraseEnemyBullet(enemyBulletX[i], enemyBulletY[i]);
                enemyBulletX[i]--;
                printEnemyBullet(enemyBulletX[i], enemyBulletY[i]);
            }
        }
    }
}
void generateEnemyBullet()
{
    enemyBulletX[enemyBulletCount] = enemyX - 7;
    enemyBulletY[enemyBulletCount] = enemyY + 1;
    isEnemyBulletActive[enemyBulletCount] = true;
    gotoxy(enemyBulletX[enemyBulletCount], enemyBulletY[enemyBulletCount]);
    cout << "-";
    enemyBulletCount++;
}
void printEnemyBullet(int x, int y)
{
    gotoxy(x, y);
    cout << "-";
}

void eraseEnemyBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void makeEnemyBulletInactive(int index)
{
    isEnemyBulletActive[index] = false;
}

void bulletCollisionWithTank()
{
    for (int i = 0; i < enemyBulletCount; i++)
    {
        if (isEnemyBulletActive[i])
        {
            if (enemyBulletX[i] - 1 == tankX + 3 && (enemyBulletY[i] == tankY || enemyBulletY[i] == tankY + 1))
            {
                eraseTankHealth();
                tankHealth = tankHealth - 5;
            }
        }
    }
}

void addScore()
{
    score++;
}

void printScore()
{
    gotoxy(75, 8);
    cout << "Score: " << score << " ";
}

void eraseEnemyHealth()
{
    gotoxy(89, 15);
    cout << "                                               ";
}
void printEnemyHealth()
{
    if (enemyHealth >= 0)
    {
        gotoxy(75, 15);
        cout << "Enemy Health: " << enemyHealth;
    }
}

void printTankHealth()
{
    if (tankHealth >= 0)
    {
        gotoxy(75, 10);
        cout << "Tank Health: " << tankHealth;
    }
}

void eraseTankHealth()
{
    gotoxy(88, 10);
    cout << "                  ";
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}