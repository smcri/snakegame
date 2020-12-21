#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include<cstdlib>
#include<fstream>


using namespace std;
bool gameOver,gameOver2 = 1;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
char a;
int s = 5;
bool flag = 0,flag2 = 0;
int hscore;


void hwrite()
{
    ofstream fout;
    int i = 0;

    ifstream fin;
    fin.open("abp.dat");
    while(fin>>hscore)
    {
        i++;
    }
    fin.close();
    if(i != 0)
    {
        if(score>hscore)
        {
            hscore = score;
        }
    }
    else
        hscore = score;
    fout.open("abp.dat");
    fout<<hscore;
    fout.close();

}



void Setup()
{
	gameOver = 0;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	if (flag2 == 1)
    {
        nTail = 0;
    }
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width+2; i++)
		cout << "*";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "*";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "o";
			else
			{
				bool print = 0;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << a;
						print = 1;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "*";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "*";
	cout << endl;
	cout << "Score:" << score << endl;
	cout<<"Highscore:"<<hscore<<endl;
	cout<< "Press X to pause the game."<<endl;
	cout<<"Press E to end game."<<endl;
}
void Input()
{
	if (kbhit())
	{
		switch (getch())
		{
		case 'a':
			if(dir != RIGHT)
                dir = LEFT;
			break;
		case 'd':
			if(dir != LEFT)
                dir = RIGHT;
			break;
		case 'w':
			if(dir != DOWN)
                dir = UP;
			break;
		case 's':
			if(dir != UP)
                dir = DOWN;
			break;
		case 'x':
			gameOver = 1;
			break;
        case 'e':
			exit(0);hwrite();
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
	if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = 1;
            flag2 = 1;
        }


	if (x == fruitX && y == fruitY)
	{
		flag = 1;
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void changesleepvalue()
{

    s /= log(score);
}

int main()
{
	ShowConsoleCursor(false);
	cout<<"Choose your body character(Recommended: + or &)-> ";
	cin>>a;
	Setup();
    hwrite();
	int n;
    system("pause");
    while(true)
    {
        while (!gameOver)
        {

            Draw();
            Input();
            Logic();
            if (flag == 1)
            {
                changesleepvalue();
            }
            Sleep(s);
            hwrite();
            flag = 0;
        }



        cout<<"Game Over! Press 5 to continue -> ";
        cin>>n;
        if(n == 5)
        {
                gameOver = 0;
                if(flag2 == 1)
                {
                        Setup();

                }
                flag2 = 0;
        }
        else
            break;
    }
	return 0;
}
