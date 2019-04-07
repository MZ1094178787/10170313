// 最佳工作序列.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

//类Work，包含工作的id，时间，期限和价值
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

//返回剩余工作的个数
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

//递归排序函数
int order(list<Work> works,int value_all,int time_all)
{
	int time_temp;
	int time;
	int temp=0;
	list<Work>::iterator it;
	//挑选出可进行的工作中价值最大并且耗时较短的一个
	for (it=works.begin();it!=works.end();it++)
	{
		list<Work>::iterator ite = works.begin();
		//若it不是第一个工作则令ite为现在工作的前一个
		if (it != works.begin())
		{
			it--;
			ite = it;
			it++;
		}
		//如果该工作已进入结果序列，则退出本次循环
		if (used[(it->ID)-1]== true)
			break;
		value_rest_temp = value_all - (it->value);//得到暂定的剩余价值
		time_temp = (time_all + (it->time));//得到暂定的总工时
		//若不能完成工作则退出本次循环
		if (time_temp > (it->limit))
			break;
		//若进行从工作后的剩余价值减少，则更新剩余价值，暂存此工作的id，更新总工时
		if (value_rest_temp < value_rest)
		{
			value_rest = value_rest_temp;
			temp = it->ID;
			time = time_temp;
		}
		//若进行工作后的剩余价值与进行上一次工作相同，但上一次所需时间更长则暂存此次的id并更新总工时
		if (value_rest_temp == value_rest && ((ite->time) > (it->time)))
		{
			temp = it->ID;
			time = time_temp;
		}
	}
	it = works.begin();
	//若还可以继续找出符合条件的工作则将此工作id存入结果，并标记此工作已计入结果否则退出递归
	if (temp != 0)
	{
		result.push_back(temp);
		for (int i = 0; i != (temp - 1); i++, it++);
		used[(it->ID)-1] = true;
	}
	else
		return 0;
	//若只剩一件工作未计入，将其计入结果，否则进行新的递归
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

