#pragma once
//ShortPath_Dijkstra.h
#ifndef SHORTPATH_DIJKSTRA_H
#define SHORTPATH_DIJKSTRA_H
#include "Assistance.h"
#include "AdjMatrix_dirGraph.h"
#include <iostream>
#include "LinkStack.h"

template<class ElemType,class WeightType>
void DisplayShortAB_Dij(const int& v1, const int& v2, AdjMatrixdirGraph<ElemType, WeightType>& g)
//��ʾA��B�����·����·������
{
	int* path = new int[g.GetvexNum()];
	WeightType* dist = new WeightType[g.GetvexNum()];
	ShortestPathDij(v1, path, dist, g);
	LinkStack<int> ls;
	ls.Push(v2);
	for (int i = path[v2]; i != -1; i = path[i])
		ls.Push(i);
	int index;
	ls.Pop(index);
	ElemType e;
	e=g.GetElem(index);
	cout << e;
	for (ls.Pop(index); !ls.IsEmpty(); ls.Pop(index))
	{
		e=g.GetElem(index);
		cout << " -> " << e;
	}
	e=g.GetElem(v2);
	cout << " -> " << e;
	cout << "   ���·������Ϊ��" << dist[v2] << endl;
}


template<class ElemType,class WeightType>
void ShortestPathDij(int v0, int* path, WeightType* dist,AdjMatrixdirGraph<ElemType,WeightType>& g)
//ʹ�õϽ�˹�����㷨�ҵ���Դ��v0��������������·��
{
	int v, u;
	WeightType MinVal;
	int num = g.GetvexNum();
	for (v = 0; v < num; v++)
	{
		dist[v] = g.GetWeight(v0, v);
		if (dist[v] == g.GetInfinity() || dist[v] == 0)   //v0��v֮��û��ֱ��·��
			path[v] = -1;
		else
		{
			path[v] = v0;
		}
		g.SetTag(v, UNVISITED);      //��ʼ�����ж����tagΪUNVISITED
	}
	g.SetTag(v0, VISITED);
	for (int i = 1; i < num; i++)      //�ҵ���ǰ�������Сֵ
	{
		MinVal = g.GetInfinity();
		u = v0;
		for (v = 0; v < num; v++)
		{
			if (g.GetTag(v) == UNVISITED && dist[v] < MinVal)
			{
				u = v;
				MinVal = dist[v];
			}
		}
		g.SetTag(u, VISITED);         //��u���뼯��U��
		for (v = g.FirstVerx(u); v != -1; v = g.NextVerx(u, v))
		{
			if (g.GetTag(v) == UNVISITED && dist[v] > MinVal + g.GetWeight(u, v))
			{
				dist[v] = MinVal + g.GetWeight(u, v);
				path[v] = u;
			}
		}
	}
}









#endif
