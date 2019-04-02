// 最佳工作序列.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

class Work
{
public:
	Work(int I,int t,int l,int v)
	{
		ID = I;
		time = t;
		limit = l;
		value = v;
	}

	int ID;
	int time;
	int limit;
	int value;
};

list <Work> works;
list <int> result;
bool used[4] = { false };
int value_rest;
int value_rest_temp;

int num_true(bool uesd[4])
{
	int i;
	int j = 0;
	for (i = 0; i < 4; i++)
	{
		if (used[i] == false)
			j++;
	}
	return j;
}

int order(list<Work> works,int value_all,int time_all)
{
	int time_temp;
	int time;
	int temp=0;
	list<Work>::iterator it;
	for (it=works.begin();it!=works.end();it++)
	{
		list<Work>::iterator ite = works.begin();
		if (it != works.begin())
		{
			it--;
			ite = it;
			it++;
		}
		if (used[(it->ID)-1]== true)
			break;
		value_rest_temp = value_all - (it->value);
		time_temp = (time_all + (it->time));
		if (time_temp > (it->limit))
			break;
		if (value_rest_temp < value_rest)
		{
			value_rest = value_rest_temp;
			temp = it->ID;
			time = time_temp;
		}
		if (value_rest_temp == value_rest && ((ite->time) > (it->time)))
		{
			temp = it->ID;
			time = time_temp;
		}
	}
	it = works.begin();
	if (temp != 0)
	{
		result.push_back(temp);
		for (int i = 0; i != (temp - 1); i++, it++);
		used[(it->ID)-1] = true;
	}
	else
		return 0;
	int num = num_true(used);
	if (num == 1)
	{
		for (int i=0;i<4;i++)
		{
			if (used[i] == false)
				result.push_back(i + 1);
		}
		return 0;
	}
	else
		order(works, value_rest, time);
}

int main()
{
	Work w1(1, 4, 10, 2);
	Work w2(2, 3, 8, 3);
	Work w3(3, 2, 4, 3);
	Work w4(4, 1, 2, 6);
	works.push_back(w1);
	works.push_back(w2);
	works.push_back(w3);
	works.push_back(w4);
	int value_all; 
	value_all= w1.value + w2.value + w3.value + w4.value;
	value_rest = value_all;
	order(works,value_all,0);
	list<int>::iterator it;
	for (it = result.begin(); it != result.end(); it++)
		cout << *it<<" ";
    return 0;
}

