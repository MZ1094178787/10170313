// 跳马问题.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

class Point
{
public:
	Point(int a = 0, int b = 0)
	{
		x = a;
		y = b;
	}

	void Change(int a, int b)
	{
		x += a;
		y += b;
	}

	bool operator ==(Point temp)
	{
		if (x == temp.x&&y == temp.y)
			return true;
		else
			return false;
	}

	Point operator =(Point temp)
	{
		Point pt(temp.x, temp.y);
		return pt;
	}

	int x;
	int y;
};

#define mapsize 3
int num = 0;
bool beg = true;
Point temp1;
list <Point> roads;
int jump[8][2] = { {2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1} };

bool In(Point horse)
{
	if ((horse.x < mapsize&&horse.x>=0) && (horse.y < mapsize&&horse.y>=0))
		return true;
	else
		return false;
}

void PrintRoads(list <Point> roads)
{
	for (list <Point>::iterator it = roads.begin(); it != roads.end(); it++)
	{
		cout << "(" << it->x + 1 << "," << it->y + 1 << ") ";
	}
}

int Jump(Point horse,Point temp,int _x,int _y,int points[][mapsize])
{
	horse.Change(_x, _y);

	if (In(horse) == false)
	{
		horse.Change(-_x, -_y);
		return 1;
	}
	if (beg==false&&horse == temp1)
	{
		horse.Change(-_x, -_y);
		return 1;
	}
	else
		temp1 = horse;
	if (beg == false && horse == temp)
	{
		num++;
		cout << "road:" << num << " ";
		PrintRoads(roads);
		cout << "(" << temp.x + 1 << "," << temp.y + 1 << ")" << endl;
		horse.Change(-_x, -_y);
		return 0;
	}
	if (points[horse.x][horse.y] == 1)
	{
		horse.Change(-_x, -_y);
		return 1;
	}
	else
		points[horse.x][horse.y] = 1;

	beg = false;
	roads.push_back(horse);

	int points1[mapsize][mapsize];
	for (int i = 0; i < 8; i++)
	{
		//int points1[mapsize][mapsize];
		for (int x = 0; x < mapsize; x++)
			for (int y = 0; y < mapsize; y++)
				points1[x][y] = points[x][y];
		Jump(horse, temp, jump[i][0], jump[i][1],points1);
	}

	roads.pop_back();
	horse.Change(-_x, -_y);
	return 0;
}

//输出的棋盘从1开始，程序运行时从0开始数，包括马的坐标
int main()
{
	Point horse(1, 1);
	Point temp = horse;
	temp1 = horse;
	int points[mapsize][mapsize] = { 0 };
	Jump(horse, temp, 0, 0, points);
    return 0;
}

