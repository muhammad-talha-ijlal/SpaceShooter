#include <iostream>
#include <windows.h>
#include <time.h>
#include<fstream>
using namespace std;


bool gameRun = true;
int lives = 3;
int px, py; // spaceship coordiantes
int controlAestroids = 0;
int controlSpeedAesteroids = 0;
int controlAliens = 0;
int controlSpeedAliens = 0;
int aliensBulletSpeed = 0;
int shipHealth = 100;
int score;
int level = 1;
int bulletCount = 1;
int color;
string reason;

int bulletsX[100], bulletsY[100];
int aesteroidsX[100], aesteroidsY[100];
int aliensX[100], aliensY[100];
int alienBulletsX[100], alienBulletsY[100];
char backupSpace[][70] = {
    {"#####################################################################"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"#####################################################################"}};
char space[][70] = {
    {"#####################################################################"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|       >                                                           |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"|                                                                   |"},
    {"#####################################################################"}};

void load();
void store();
void gotoxy(int y, int x);
void display();
void restoreSpace();
bool findShipPos();
void generateBullet();
void moveBullets();
void decreaseLives();
void health(int value);
void moveShip(int dir);
int random();
int quickRandom();
void generateAesteroids();
void generateAliens();
void moveAliens();
void generateAlienBullets();
void moveAlienBullets();
int countALienShips();
void gotoxy(int y, int x)
{
    COORD c;
    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void display()
{
    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 70; col++)
        {
            cout << space[row][col];
        }
        cout << "\n";
    }
}
void restoreSpace()
{
    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 70; col++)
        {
            space[row][col] = backupSpace[row][col];
        }
        gotoxy(0,0);
        display();
    }
}
bool findShipPos()
{
    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 70; col++)
        {
            if (space[row][col] == '>')
            {
                px = row;
                py = col;
                return true;
            }
        }
    }
    return false;
}

void generateBullet()
{
    space[px][py + 1] = '-';
}
void moveBullets()
{
    int count = 0;
    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 70; col++)
        {
            if (space[row][col] == '-')
            {
                bulletsX[count] = row;
                bulletsY[count] = col;
                count++;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (space[bulletsX[i]][bulletsY[i] + 1] == '.')
        {
            space[bulletsX[i]][bulletsY[i] + 1] = ' ';
        }
        else if (space[bulletsX[i]][bulletsY[i] + 1] == '<')
        {
            space[bulletsX[i]][bulletsY[i] + 1] = ' ';
            gotoxy(bulletsX[i], bulletsY[i] + 1);
            cout << ' ';
            score++;
            Beep(10000, 100);
        }
        else if (space[bulletsX[i]][bulletsY[i] + 1] != '|' && space[bulletsX[i]][bulletsY[i] + 1] != 'O')
        {
            space[bulletsX[i]][bulletsY[i] + 1] = '-';
            gotoxy(bulletsX[i], bulletsY[i] + 1);
            cout << '-';
        }
        space[bulletsX[i]][bulletsY[i]] = ' ';
        gotoxy(bulletsX[i], bulletsY[i]);
        cout << ' ';
    }
}
void decreaseLives()
{

    lives--;
    if (lives == 0)
    {
        reason = "Lives exhausted... You failed.";
        Beep(700, 1500);
        gameRun = false;
    }
    else
    {
        Sleep(1000);
        shipHealth = 100;
        Beep(10000, 750);
        restoreSpace();
    }
}
void health(int value)
{
    shipHealth = shipHealth + value;
    if (shipHealth <= 100 && shipHealth > 0)
    {
        Beep(10, 400);
    }
    if (shipHealth > 100)
    {
        int extra = shipHealth - 100;
        shipHealth = shipHealth - extra;
    }
    if (shipHealth <= 0)
    {
        decreaseLives();
    }
}
void moveShip(int dir)
{
    if (dir == 1)
    {
        if (space[px + 1][py] == 'O')
        {
            space[px + 1][py] = '>';
            gotoxy(px + 1, py);
            cout << '>';
            health(-50);
        }
        else if (space[px + 1][py] == '.')
        {
            space[px + 1][py] = '>';
            gotoxy(px + 1, py);
            cout << '>';
            health(-25);
        }
        else if (space[px + 1][py] == '<')
        {
            space[px + 1][py] = '>';
            gotoxy(px + 1, py);
            cout << '>';
            health(-50);
        }
        else if (space[px + 1][py] != '#')
        {
            space[px + 1][py] = '>';
            gotoxy(px + 1, py);
            cout << '>';
        }
        space[px][py] = ' ';
        gotoxy(px, py);
        cout << ' ';
    }
    if (dir == 2)
    {
        if (space[px - 1][py] == 'O')
        {
            space[px - 1][py] = '>';
            gotoxy(px - 1, py);
            cout << '>';
            health(-50);
        }
        else if (space[px - 1][py] == '.')
        {
            space[px - 1][py] = '>';
            gotoxy(px - 1, py);
            cout << '>';
            health(-25);
        }
        if (space[px - 1][py] != '#')
        {

            space[px - 1][py] = '>';
            gotoxy(px - 1, py);
            cout << '>';
        }
        space[px][py] = ' ';
        gotoxy(px, py);
        cout << ' ';
    }
    if (dir == 3)
    {
        if (space[px][py - 1] == 'O')
        {
            space[px][py - 1] = '>';
            gotoxy(px, py - 1);
            cout << '>';
            health(-50);
        }
        if (space[px][py - 1] == '.')
        {
            space[px][py - 1] = '>';
            gotoxy(px, py - 1);
            cout << '>';
            health(-25);
        }
        if (space[px][py - 1] != '|')
        {
            space[px][py - 1] = '>';
            gotoxy(px, py - 1);
            cout << '>';
        }
        space[px][py] = ' ';
        gotoxy(px, py);
        cout << ' ';
    }
    if (dir == 4)
    {
        if (space[px][py + 1] == 'O')
        {
            space[px][py + 1] = '>';
            gotoxy(px, py + 1);
            cout << '>';
            health(-50);
        }
        if (space[px][py + 1] == '.')
        {
            space[px][py + 1] = '>';
            gotoxy(px, py + 1);
            cout << '>';
            health(-25);
        }
        if (space[px][py + 1] != '|')
        {
            space[px][py + 1] = '>';
            gotoxy(px, py + 1);
            cout << '>';
        }
        space[px][py] = ' ';
        gotoxy(px, py);
        cout << ' ';
    }
}

int random()
{
    srand(time(0));
    return 1 + (rand() % 12);
}
int quickRandom()
{
    return (rand());
}

void generateAesteroids()
{
    int c = 50 - 2*level;
    if (controlAestroids == c)
    {
        int ox = random();
        int oy = 65;

        space[ox][oy] = 'O';
        gotoxy(ox, oy);
        cout << 'O';
        controlAestroids = 0;
    }
    controlAestroids++;
}
void moveAesteriods()
{
    int c = 10 - level;
    if (controlSpeedAesteroids == c)
    {
        int count = 0;
        for (int row = 0; row < 15; row++)
        {
            for (int col = 0; col < 70; col++)
            {
                if (space[row][col] == 'O')
                {
                    aesteroidsX[count] = row;
                    aesteroidsY[count] = col;
                    count++;
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            if (space[aesteroidsX[i]][aesteroidsY[i] - 1] != '|')
            {
                int ran = quickRandom();
                if (ran % 2 == 0)
                {
                    if (space[aesteroidsX[i] + 1][aesteroidsY[i]] != '#')
                    {
                        if (space[aesteroidsX[i] + 1][aesteroidsY[i] - 1] == '>')
                        {
                            health(-50);
                        }
                        space[aesteroidsX[i] + 1][aesteroidsY[i] - 1] = 'O';
                        gotoxy(aesteroidsX[i] + 1, aesteroidsY[i] - 1);
                        cout << 'O';
                    }
                }
                else
                {
                    if (space[aesteroidsX[i] - 1][aesteroidsY[i]] != '#')
                    {
                        if (space[aesteroidsX[i] - 1][aesteroidsY[i] - 1] == '>')
                        {
                            health(-50);
                        }
                        space[aesteroidsX[i] - 1][aesteroidsY[i] - 1] = 'O';
                        gotoxy(aesteroidsX[i] - 1, aesteroidsY[i] - 1);
                        cout << 'O';
                    }
                }
            }
            space[aesteroidsX[i]][aesteroidsY[i]] = ' ';
            gotoxy(aesteroidsX[i], aesteroidsY[i]);
            cout << ' ';
        }
        controlSpeedAesteroids = 0;
    }
    controlSpeedAesteroids++;
}

void generateAliens()
{
    int c = 25 - 2*level;
    if (controlAliens == c)
    {
        int ax = random();
        int ay = 65;

        space[ax][ay] = '<';
        gotoxy(ax, ay);
        cout << "<";
        controlAliens = 0;
    }
    controlAliens++;
}

void moveAliens()
{
    int c = 10 - level;
    if (controlSpeedAliens == c)
    {
        int count = 0;
        for (int row = 0; row < 15; row++)
        {
            for (int col = 0; col < 70; col++)
            {
                if (space[row][col] == '<')
                {
                    aliensX[count] = row;
                    aliensY[count] = col;
                    count++;
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            if (space[aliensX[i]][aliensY[i] - 1] == '|')
            {
                gameRun = false;
                reason = "Enemy Sneaked out. Earth is invaded. You failed, our aviour...";
            }
            else if (space[aliensX[i]][aliensY[i] - 1] != '|' && space[aliensX[i]][aliensY[i] - 1] != 'O')
            {
                bool found = false;
                for (int j = py; j < 70; j++)
                {
                    if (space[px][j] == '<')
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    if (aliensX[i] > px)
                    {
                        space[aliensX[i] - 1][aliensY[i] - 1] = '<';
                        gotoxy(aliensX[i] - 1, aliensY[i] - 1);
                        cout << '<';
                    }
                    else if (aliensX[i] < px)
                    {
                        space[aliensX[i] + 1][aliensY[i] - 1] = '<';
                        gotoxy(aliensX[i] + 1, aliensY[i] - 1);
                        cout << '<';
                    }
                }
                else if (found == true)
                {
                    space[aliensX[i]][aliensY[i] - 1] = '<';
                    gotoxy(aliensX[i], aliensY[i] - 1);
                    cout << '<';
                }
            }
            space[aliensX[i]][aliensY[i]] = ' ';
            gotoxy(aliensX[i], aliensY[i]);
            cout << ' ';
        }
        controlSpeedAliens = 0;
    }
    controlSpeedAliens++;
}

void generateAlienBullets()
{
    int count = 0;
    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 70; col++)
        {
            if (space[row][col] == '<')
            {
                aliensX[count] = row;
                aliensY[count] = col;
                count++;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (aliensX[i] == px)
        {
            space[aliensX[i]][aliensY[i] - 2] = '.';
            gotoxy(aliensX[i], aliensY[i] - 2);
            cout << '.';
        }
    }
}
void moveAlienBullets()
{
    int c = 10 - level;
    if (aliensBulletSpeed == c)
    {
        int count = 0;
        for (int row = 0; row < 15; row++)
        {
            for (int col = 0; col < 70; col++)
            {
                if (space[row][col] == '.')
                {
                    alienBulletsX[count] = row;
                    alienBulletsY[count] = col;
                    count++;
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            if (space[alienBulletsX[i]][alienBulletsY[i] - 1] == '>')
            {
                space[px][py] = ' ';
                space[alienBulletsX[i]][alienBulletsY[i]] = '>';
                gotoxy(alienBulletsX[i], alienBulletsY[i]);
                cout << '>';
                health(-25);
                findShipPos();
                continue;
            }
            if (space[alienBulletsX[i]][alienBulletsY[i] - 1] == '<')
            {
                space[alienBulletsX[i]][alienBulletsY[i] - 1] = ' ';
                gotoxy(alienBulletsX[i], alienBulletsY[i]);
                cout << ' ';
            }
            else if (space[alienBulletsX[i]][alienBulletsY[i] - 1] != '|' && space[alienBulletsX[i]][alienBulletsY[i] - 1] != 'O')
            {
                space[alienBulletsX[i]][alienBulletsY[i] - 1] = '.';
                gotoxy(alienBulletsX[i], alienBulletsY[i] - 1);
                cout << '.';
            }
            space[alienBulletsX[i]][alienBulletsY[i]] = ' ';
            gotoxy(alienBulletsX[i], alienBulletsY[i]);
            cout << ' ';
        }
        aliensBulletSpeed = 0;
    }
    aliensBulletSpeed++;
}
int countALienShips()
{
    int count = 0;
    for (int row = 0; row < 15; row++)
    {
        for (int col = 0; col < 70; col++)
        {
            if (space[row][col] == '<')
            {
                count++;
            }
        }
    }
    return count;
}
void load()
{
    fstream file;
    string line;

    file.open("space.txt", ios::in);
    getline(file,line);
    score = stoi(line);
    getline(file,line);
    lives = stoi(line);
    getline(file, line);
    level = stoi(line);
    getline(file, line);
    bulletCount = stoi(line);
    file.close();
}
void store()
{
    fstream file;
    file.open("space.txt" , ios::out);
    file << score << endl;
    file << lives << endl;
    file << level << endl;
    file << bulletCount << endl;

    file.close();
}
main()
{
    
    cout << "Menu>>" << endl;
    cout << "1_Start New game."<< endl;
    cout << "2_Load Game." << endl;
    cout << "3_Exit" << endl;
    int op = 0;
    cin >> op;
    if(op == 2)
    {
        load();
    }

    if(op == 3)
    {
        reason = "Exit";
        gameRun = false;
    }
    gotoxy(0, 0);
    display();
    while (gameRun)
    {
        findShipPos();
        gotoxy(16, 0);
        cout << "Health: " << shipHealth << "\tLives: " << lives << "\tScore: " << score << "\tLevel: " << level << "\tEconomy :" << bulletCount/(score+1);
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
            bulletCount++;
        }
        moveBullets();

        if (GetAsyncKeyState(VK_DOWN))
        {
            moveShip(1);
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveShip(2);
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveShip(3);
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveShip(4);
        }
        findShipPos();

        generateAesteroids();
        moveAesteriods();

        generateAliens();
        moveAliens();

        generateAlienBullets();
        moveAlienBullets();

        int oldLevel = level;
        level = score / 10;
        if (level != oldLevel)
        {
            color = random();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        }

        if (level == 10)
        {
            gameRun = false;
            reason = "You won... Enemies finished saviour...";
        }
        Sleep(3);
        store();
        if(bulletCount/(score+1) > 40)
        {
            reason = "Economy Exceeded 40.";
            break;
        }
    }
    system("cls");
    cout << "Score: " << score << "\tLevel: " << level << endl;
    cout << reason << endl<< endl;
    system("pause");
}