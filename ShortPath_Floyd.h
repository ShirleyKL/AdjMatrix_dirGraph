#pragma once
//ShortPath_Floyd.h
#ifndef SHORTPATH_FLOYD_H
#define SHORTPATH_FLOYD_H

#include <iostream>
#include "Assistance.h"
#include "AdjMatrix_dirGraph.h"

template<class ElemType,class WeightType>
void ShortPathFloyd(int** path, WeightType** dist, AdjMatrixdirGraph<ElemType, WeightType>& g)
//采用弗洛伊德算法求两点间的最短路径
{
	for (int u = 0; u < g.GetvexNum(); u++)
	{
		for (int v = 0; v < g.GetvexNum(); v++)
		{
			dist[u][v] = g.GetWeight(u, v);
			if (u != v && dist[u][v] < g.GetInfinity())
				path[u][v] = u;
			else
				path[u][v] = -1;     //不存在有向边<u,v>
		}
	}
	for (int k = 0; k < g.GetvexNum(); k++)
	{
		for (int i = 0; i < g.GetvexNum(); i++)
		{
			for (int j = 0; j < g.GetvexNum(); j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
}



template<class ElemType,class WeightType>
void DisplayShortPath_Floyd(const int& v1, const int& v2, AdjMatrixdirGraph<ElemType, WeightType>& g)
//显示两点间的最短路径及其长度
{
	int** path = (int **)new int* [g.GetvexNum()];
	WeightType** dist =(int **) new WeightType* [g.GetvexNum()];
	for (int i = 0; i < g.GetvexNum(); i++)
	{
		path[i] = new int[g.GetvexNum()];
		dist[i] = new WeightType[g.GetvexNum()];
	}
	ShortPathFloyd(path, dist, g);
	LinkStack<int> ls;
	ls.Push(v2);
	for (int i = path[v1][v2]; i != -1; i = path[v1][i])
		ls.Push(i);
	int index;
	ls.Pop(index);
	ElemType e;
	e = g.GetElem(index);
	cout << e;
	for (ls.Pop(index); !ls.IsEmpty(); ls.Pop(index))
	{
		e = g.GetElem(index);
		cout << " -> " << e;
	}
	e = g.GetElem(v2);
	cout << " -> " << e;
	cout << "   最短路径长度为：" << dist[v1][v2] << endl;
}






#endif