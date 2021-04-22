#pragma once
//AdjMatrix_dirGraph.h
#ifndef _ADJMATRIX_DIRGRAPH_H
#define _ADJMATRIX_DIRGRAPH_H

#include <iostream>
#include "Assistance.h"

template<class ElemType>
class AdjMatrixdirGraph
{
protected:
	ElemType* vectexes;
	int** arcs;
	int vexNum, vexMaxNum, ArcNum;
public:
	AdjMatrixdirGraph(int vexnum, ElemType* vec, int vexmax = DEFAULT_SIZE);  
     //以数组vec[]作为顶点，构造含有vexnum个顶点的图，该图的最大顶点个数为vexmax
	AdjMatrixdirGraph(int vexmax = DEFAULT_SIZE);
	 //构造最大顶点个数为vexmax的图
	AdjMatrixdirGraph(AdjMatrixdirGraph<ElemType>& graph);  //复制构造函数
	AdjMatrixdirGraph<ElemType> &operator=(const AdjMatrixdirGraph<ElemType>& graph);  //赋值运算符重载
	~AdjMatrixdirGraph();   //析构函数
	void Clear();   //清空图，即清空所有的顶点即依附于顶点的边
	bool IsEmpty()const;  //判断是否为空图
	int GetIndex(const ElemType& e)const;   //求顶点的序号
	int GetvexNum()const;   //返回顶点的个数
	int GetarcNum()const;    //返回边数

};














#endif


