#pragma once
//AdjMatrix_dirGraph.h
#ifndef _ADJMATRIX_DIRGRAPH_H
#define _ADJMATRIX_DIRGRAPH_H

#include <iostream>
#include "Assistance.h"

template<class ElemType,class WeightType>
class AdjMatrixdirGraph   //有向图的邻接矩阵
{
protected:
	ElemType* vectexes;
	int** arcs;
	int vexNum, vexMaxNum, ArcNum;
	WeightType Infinity;
	mutable Status* tag;
public:
	AdjMatrixdirGraph(int vexnum, ElemType* vec, int vexmax = DEFAULT_SIZE,WeightType infinity=DEFAULT_INFINITY);  
     //以数组vec[]作为顶点，构造含有vexnum个顶点的图，该图的最大顶点个数为vexmax
	AdjMatrixdirGraph(int vexmax = DEFAULT_SIZE,WeightType infinity=DEFAULT_INFINITY);
	 //构造最大顶点个数为vexmax的图
	AdjMatrixdirGraph(const AdjMatrixdirGraph<ElemType,WeightType>& graph);  //复制构造函数
	AdjMatrixdirGraph<ElemType,WeightType> &operator=(const AdjMatrixdirGraph<ElemType,WeightType>& graph);  //赋值运算符重载
	~AdjMatrixdirGraph();   //析构函数
	void Clear();   //清空图，即清空所有的顶点即依附于顶点的边
	bool IsEmpty()const;  //判断是否为空图
	int GetIndex(const ElemType& e)const;   //求顶点的序号
	int GetvexNum()const;   //返回顶点的个数
	int GetarcNum()const;    //返回边数
	void InsertVerx(ElemType& e);   //在图中插入一个顶点
	void InsertArc(int& v1, int& v2, WeightType& weight);   //在图中插入一条边
	void DeleteArc(const int& v1, const int& v2);     //在图中删除一条边
	void DeleteVerx(ElemType& e);    //在图中删除一个顶点及依附于它的边
	int FirstVerx(const int& v)const;   //在图中取顶点v的第一个邻接顶点
	int NextVerx(const int& v1, const int& v2)const;          //在图中取顶点v1的在v2后的下一个顶点
	void Tranverse()const;    //遍历图
	Status SetElem(ElemType& e);   //设置顶点的元素值
	ElemType& GetElem(const int& v)const;  //求顶点的元素值
	Status GetTag(const int& v)const;     //求顶点的标志
	Status SetTag(const int& v, Status& state);    //设置顶点的标志
	void Display();  //显示有向图的邻接矩阵
	WeightType& GetInfinity()const;    
};


template<class ElemType,class WeightType>
AdjMatrixdirGraph<ElemType, WeightType>::AdjMatrixdirGraph(int vexnum, ElemType* vec, int vexmax, WeightType infinity)
   //以数组vec[]作为顶点，构造含有vexnum个顶点的图，该图的最大顶点个数为vexmax
{
	if (vexmax < 0)
		throw Error("允许的顶点的最大数目不能为负!");
	if (vexnum > vexmax)
		throw Error("顶点数目不能大于允许的顶点最大数目!");
	vexNum = vexnum;
	vexMaxNum = vexmax;
	Infinity = infinity;
	ArcNum = 0;
	vectexes = new ElemType[vexMaxNum];
	arcs = (int **)new int* [vexMaxNum];
	tag = new Status[vexMaxNum];
	for (int i = 0; i < vexMaxNum; i++)
	{
		arcs[i] = new int [vexMaxNum];
		tag[i] = UNVISITED;
	}
	for (int i = 0; i < vexNum; i++)
		vectexes[i] = vec[i];
}


template<class ElemType,class WeightType>
AdjMatrixdirGraph<ElemType, WeightType>::AdjMatrixdirGraph(int vexmax, WeightType infinity)
    //构造最大顶点个数为vexmax的图
{
	if (vexmax < 0)
		throw Error("允许的顶点最大数目不能为负!");   //抛出异常
	vexNum = 0;
	vexMaxNum = vexmax;
	Infinity = infinity;
	ArcNum = 0;
	arcs =(int **) new int* [vexMaxNum];
	for (int i = 0; i < vexMaxNum; i++)
		arcs[i] = new int[vexMaxNum];
	tag = new Status[vexMaxNum];
	vectexes = new ElemType[vexMaxNum];
}


template<class ElemType,class WeightType>
AdjMatrixdirGraph<ElemType, WeightType>::AdjMatrixdirGraph(const AdjMatrixdirGraph<ElemType,WeightType>& graph)
//复制构造函数
{
	vexMaxNum = graph.vexMaxNum;
	Infinity = graph.Infinity;
	ArcNum = graph.ArcNum;
	vexNum = graph.vexNum;
	tag = new Status[vexMaxNum];
	arcs =(int **) new int* [vexMaxNum];
	vectexes = new ElemType[vexMaxNum];
	for (int i = 0; i < vexMaxNum; i++)
	{
		tag[i] = UNVISITED;
		arcs[i] = new int[vexMaxNum];
	}
	if (vexNum > 0)
	{
		vectexes = new ElemType[vexNum];
		for (int i = 0; i < vexNum; i++)
		{
			vectexes[i] = graph.vectexes[i];
			for (int j = 0; j < vexNum; j++)
			{
				arcs[i][j] = graph.arcs[i][j];
			}
		}
	}
}


template<class ElemType,class WeightType>
AdjMatrixdirGraph<ElemType, WeightType>& AdjMatrixdirGraph<ElemType, WeightType>::operator=(const AdjMatrixdirGraph<ElemType, WeightType>& graph)
//赋值运算符重载
{
	if (*this != graph)
	{
		vexMaxNum = graph.vexMaxNum;
		ArcNum = graph.ArcNum;
		vexNum = graph.vexNum;
		arcs =(int **) new int* [vexMaxNum];
		tag = new Status[vexMaxNum];
		vectexes = new ElemType[vexMaxNum];
		Infinity = graph.Infinity;
		for (int i = 0; i < vexMaxNum; i++)
		{
			arcs[i] = new int[vexMaxNum];
			tag[i] = UNVISITED;
		}
		if (vexNum > 0)
		{
			for (int i = 0; i < vexNum; i++)
			{
				vectexes[i] = graph.vectexes[i];
				for (int j = 0; j < vexNum; j++)
				{
					arcs[i][j] = graph.arcs[i][j];
				}
			}
		}
	}
	return *this;
}

template<class ElemType,class WeightType>
AdjMatrixdirGraph<ElemType, WeightType>::~AdjMatrixdirGraph()
//析构函数
{
	delete[] vectexes;
	delete[] tag;
	for (int i = 0; i < vexMaxNum; i++)
		delete[] arcs[i];
	delete[] arcs;
}


template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::Clear()
//清空图，清空图中所有的顶点及依附于顶点的边
{
	vexNum = 0;
	ArcNum = 0;
}

template<class ElemType,class WeightType>
bool AdjMatrixdirGraph<ElemType, WeightType>::IsEmpty()const
//判断是否为空图
{
	return vexNum == 0;
}

template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::GetIndex(const ElemType& e)const
//返回指定元素值的序号,没有找到该元素则返回-1
{
	for (int i = 0; i < vexNum; i++)
	{
		if (vectexes[i] == e)
			break;
		else
			continue;
	}
	if (i < vexNum) return i;
	else return -1;
}


template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::GetvexNum()const
//返回顶点个数
{
	return vexNum;
}

template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::GetarcNum()const
//返回边数
{
	return ArcNum;
}

template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::InsertVerx(ElemType& e)
//在图中插入顶点e
{
	if (vexNum == vexMaxNum)
		throw Error("图中顶点数不能超过最大顶点数!");
	vectexes[vexNum] = e;
	for (int i = 0; i < vexNum; i++)
	{
		arcs[i][vexNum] = Infinity;
		arcs[vexNum][i] = Infinity;
	}
	arcs[vexNum][vexNum] = 0;
	tag[vexNum] = UNVISITED;
	vexNum++;
}

template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::InsertArc(int& v1, int& v2, WeightType& weight)
//在图中插入一条从顶点v1到顶点v2的一条有向边，权值为weight
{
	if (v1<0 || v1>vexNum)
		throw Error("v1不合法!");
	if (v2<0 || v2>vexNum)
		throw Error("v2不合法!");
	if (v1 == v2)
		throw Error("v1不能等于v2!");
	arcs[v1][v2] = weight;
	ArcNum++;
}







#endif


