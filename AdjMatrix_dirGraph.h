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
     //������vec[]��Ϊ���㣬���캬��vexnum�������ͼ����ͼ����󶥵����Ϊvexmax
	AdjMatrixdirGraph(int vexmax = DEFAULT_SIZE);
	 //������󶥵����Ϊvexmax��ͼ
	AdjMatrixdirGraph(AdjMatrixdirGraph<ElemType>& graph);  //���ƹ��캯��
	AdjMatrixdirGraph<ElemType> &operator=(const AdjMatrixdirGraph<ElemType>& graph);  //��ֵ���������
	~AdjMatrixdirGraph();   //��������
	void Clear();   //���ͼ����������еĶ��㼴�����ڶ���ı�
	bool IsEmpty()const;  //�ж��Ƿ�Ϊ��ͼ
	int GetIndex(const ElemType& e)const;   //�󶥵�����
	int GetvexNum()const;   //���ض���ĸ���
	int GetarcNum()const;    //���ر���

};














#endif


