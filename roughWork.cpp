#include <iostream>
#include <windows.h>
using namespace std;
void printEnemy();
void gotoxy(int x, int y);

int enemyTank1X = 15;
int enemyTank1Y = 15;

main()
{
    printEnemy();
}


void printEnemy()
{
    char box = 219;

    char enemyTank1[6] = {'l', 'l', 'l', 'l', 'l', 'l'};
    char enemyTank2[6] = {'l', 'l', 'l', 'l', 'l', 'l'};

    gotoxy(15, 15);

    for (int i = 0; i < 6; i++)
    {
        cout << enemyTank2[i];
    }
    cout << endl;

    gotoxy(15, 16);

    for (int i = 0; i < 6; i++)
    {
        cout << enemyTank2[i];
    }
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}