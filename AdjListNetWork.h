#pragma once
//AdjListNetWork.h
#ifndef ADJLISTNETWORK_H
#define ADJLISTNETWORK_H

#include <iostream>
#include "AdjMatrix_dirGraph.h"
#include "Assistance.h"
#include "LinkStack.h"
#include "LinkQueue.h"

template<class ElemType,class WeightType>
Status CriticalPath(AdjMatrixdirGraph<ElemType, WeightType>& g)
{
	int* InDegree = new int[g.GetvexNum()];   //顶点入度数组
	WeightType* ve = new WeightType [g.GetvexNum()];  //事件最早发生时刻数组
	WeightType* vl = new WeightType[g.GetvexNum()];       //事件最迟发生时刻数组
	LinkQueue<int> q;             //用于存储入度为0的顶点
	LinkStack<int> s;             //用于实现逆拓扑排序序列的栈
	int u, v, count = 0;
	WeightType ee, el;
	ElemType e1, e2;
	for (v = 0; v < g.GetvexNum(); v++)
	{
		ve[v] = 0;
	}
	StateInDegree(g, InDegree);     //统计顶点的入度
	for (v = 0; v < g.GetvexNum(); v++)
	{
		if (InDegree[v] == 0)
			q.EnQueue(v);
	}
	while (!q.IsEmpty())
	{
		q.DelQueue(u);
		s.Push(u);
		count++;
		for (v = g.FirstVerx(u); v != -1; v = g.NextVerx(u, v))
		{
			if (--InDegree[v] == 0)
				q.EnQueue(v);
			if (ve[u] + g.GetWeight(u, v) > ve[v])
				ve[v] = ve[u] + g.GetWeight(u, v);
		}
	}
	delete[] InDegree;
	if (count < g.GetvexNum())
	{
		delete[]ve;
		delete[]vl;
		return FAIL;
	}
	s.Top(u);        //取出栈顶
	for (v = 0; v < g.GetvexNum(); v++)     
	{
		vl[v] = ve[u];
	}
	while (!s.IsEmpty())
	{
		s.Pop(u);
		for (v = g.FirstVerx(u); v != -1; v = g.NextVerx(u, v))
		{
			if (vl[v] - g.GetWeight(u, v) < vl[u])
				vl[u] = vl[v] - g.GetWeight(u, v);
		}
	}
	int num = 0;
	for (u = 0; u < g.GetvexNum(); u++)
	{
		for (v = g.FirstVerx(u); v != -1; v = g.NextVerx(u, v))
		{
			ee = ve[u];
			el = vl[v] - g.GetWeight(u, v);
			if (ee == el)
			{
				num++;
				e1 = g.GetElem(u);
				e2 = g.GetElem(v);
				cout << "<" << e1 << "," << e2 << "> ";
			}
		}
	}
	if (num == 0) cout << "该图无关键路径" << endl;
	delete[]ve;
	delete[]vl;
	return SUCCESS;
}


template<class ElemType,class WeightType>
void StateInDegree(AdjMatrixdirGraph<ElemType, WeightType>& g, int* InDgree)
{
	int num = g.GetvexNum();
	ElemType e;
	for (int i = 0; i < num; i++)
	{
		e = g.GetElem(i);
		InDgree[i] = g.GetInNum(e);
	}
}




#endif