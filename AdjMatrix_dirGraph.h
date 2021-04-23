#pragma once
//AdjMatrix_dirGraph.h
#ifndef _ADJMATRIX_DIRGRAPH_H
#define _ADJMATRIX_DIRGRAPH_H

#include <iostream>
#include "Assistance.h"

template<class ElemType,class WeightType>
class AdjMatrixdirGraph   //����ͼ���ڽӾ���
{
protected:
	ElemType* vectexes;
	int** arcs;
	int vexNum, vexMaxNum, ArcNum;
	WeightType Infinity;
	mutable Status* tag;
public:
	AdjMatrixdirGraph(int vexnum, ElemType* vec, int vexmax = DEFAULT_SIZE,WeightType infinity=DEFAULT_INFINITY);  
     //������vec[]��Ϊ���㣬���캬��vexnum�������ͼ����ͼ����󶥵����Ϊvexmax
	AdjMatrixdirGraph(int vexmax = DEFAULT_SIZE,WeightType infinity=DEFAULT_INFINITY);
	 //������󶥵����Ϊvexmax��ͼ
	AdjMatrixdirGraph(const AdjMatrixdirGraph<ElemType,WeightType>& graph);  //���ƹ��캯��
	AdjMatrixdirGraph<ElemType,WeightType> &operator=(const AdjMatrixdirGraph<ElemType,WeightType>& graph);  //��ֵ���������
	~AdjMatrixdirGraph();   //��������
	void Clear();   //���ͼ����������еĶ��㼴�����ڶ���ı�
	bool IsEmpty()const;  //�ж��Ƿ�Ϊ��ͼ
	int GetIndex(const ElemType& e)const;   //�󶥵�����
	int GetvexNum()const;   //���ض���ĸ���
	int GetarcNum()const;    //���ر���
	void InsertVerx(ElemType& e);   //��ͼ�в���һ������
	void InsertArc(int& v1, int& v2, WeightType& weight);   //��ͼ�в���һ����
	void DeleteArc(const int& v1, const int& v2);     //��ͼ��ɾ��һ����
	void DeleteVerx(ElemType& e);    //��ͼ��ɾ��һ�����㼰���������ı�
	int FirstVerx(const int& v)const;   //��ͼ��ȡ����v�ĵ�һ���ڽӶ���
	int NextVerx(const int& v1, const int& v2)const;          //��ͼ��ȡ����v1����v2�����һ������
	void Tranverse()const;    //����ͼ
	Status SetElem(ElemType& e);   //���ö����Ԫ��ֵ
	ElemType& GetElem(const int& v)const;  //�󶥵��Ԫ��ֵ
	Status GetTag(const int& v)const;     //�󶥵�ı�־
	Status SetTag(const int& v, Status& state);    //���ö���ı�־
	void Display();  //��ʾ����ͼ���ڽӾ���
	WeightType& GetInfinity()const;    
};


template<class ElemType,class WeightType>
AdjMatrixdirGraph<ElemType, WeightType>::AdjMatrixdirGraph(int vexnum, ElemType* vec, int vexmax, WeightType infinity)
   //������vec[]��Ϊ���㣬���캬��vexnum�������ͼ����ͼ����󶥵����Ϊvexmax
{
	if (vexmax < 0)
		throw Error("����Ķ���������Ŀ����Ϊ��!");
	if (vexnum > vexmax)
		throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");
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
    //������󶥵����Ϊvexmax��ͼ
{
	if (vexmax < 0)
		throw Error("����Ķ��������Ŀ����Ϊ��!");   //�׳��쳣
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
//���ƹ��캯��
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
//��ֵ���������
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
//��������
{
	delete[] vectexes;
	delete[] tag;
	for (int i = 0; i < vexMaxNum; i++)
		delete[] arcs[i];
	delete[] arcs;
}


template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::Clear()
//���ͼ�����ͼ�����еĶ��㼰�����ڶ���ı�
{
	vexNum = 0;
	ArcNum = 0;
}

template<class ElemType,class WeightType>
bool AdjMatrixdirGraph<ElemType, WeightType>::IsEmpty()const
//�ж��Ƿ�Ϊ��ͼ
{
	return vexNum == 0;
}

template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::GetIndex(const ElemType& e)const
//����ָ��Ԫ��ֵ�����,û���ҵ���Ԫ���򷵻�-1
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
//���ض������
{
	return vexNum;
}

template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::GetarcNum()const
//���ر���
{
	return ArcNum;
}

template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::InsertVerx(ElemType& e)
//��ͼ�в��붥��e
{
	if (vexNum == vexMaxNum)
		throw Error("ͼ�ж��������ܳ�����󶥵���!");
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
//��ͼ�в���һ���Ӷ���v1������v2��һ������ߣ�ȨֵΪweight
{
	if (v1<0 || v1>vexNum)
		throw Error("v1���Ϸ�!");
	if (v2<0 || v2>vexNum)
		throw Error("v2���Ϸ�!");
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");
	arcs[v1][v2] = weight;
	ArcNum++;
}







#endif


