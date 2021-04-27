#pragma once
//AdjMatrix_dirGraph.h
#ifndef _ADJMATRIX_DIRGRAPH_H
#define _ADJMATRIX_DIRGRAPH_H

#include <iostream>
#include "Assistance.h"
#include "SeqQueue.h"

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
	void DFSTranverse(void (*Visit)(const ElemType &))const;    //������ȱ���ͼ
	void DFS(const int& v, void (*Visit)(const ElemType&))const;    //�Զ���v���������������
	void BFS(const int& v, void (*Visit)(const ElemType&))const;    //�Զ���v���й����������
	void BFSTranverse(void (*Visit)(const ElemType&))const;    //������ȱ���ͼ
	Status SetElem(const int &v,const ElemType& e);   //���ö����Ԫ��ֵ
	ElemType& GetElem(const int& v)const;  //�󶥵��Ԫ��ֵ
	Status &GetTag(const int& v)const;     //�󶥵�ı�־
	void SetTag(const int& v, Status state);    //���ö���ı�־
	void Display();  //��ʾ����ͼ���ڽӾ���
	WeightType& GetInfinity();    
	int GetOutNum(const ElemType& e)const;      //�󶥵�ĳ���
	int GetInNum(const ElemType& e)const;     //�󶥵�����
	WeightType& GetWeight(const int& v1, const int& v2)const;  //�󶥵�v1������v2������ߵ�Ȩֵ
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
	for (int i = 0; i < vexNum; i++)
	{
		for (int j = 0; j < vexNum; j++)
		{
			if (i == j) arcs[i][j] = 0;
			else
				arcs[i][j] = Infinity;
		}
	}
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
	int i;
	for (i = 0; i < vexNum; i++)
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

template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::DeleteArc(const int& v1, const int& v2)
//��ͼ��ɾ��һ����
{
	if (v1<0 || v1>vexNum)
		throw Error("v1���Ϸ�!");
	if (v2<0 || v2>vexNum)
		throw Error("v2���Ϸ�!");
	if (v1 == v2)
		throw Error("v1���ܵ���v2!");
	arcs[v1][v2] = Infinity;
	ArcNum--;
}


template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::DeleteVerx(ElemType& e)
//��ͼ��ɾ��һ�����㼰���������ı�
{
	int index = GetIndex(e);
	if (index == -1)
		throw Error("���㲻����!");
	if (index == vexNum - 1)    //�����ɾ���Ķ���λ�������ĩβ
		vexNum--;
	else
	{
		for (int i = 0; i < vexNum; i++)
		{
			if (arcs[i][index] != Infinity && i != index)
			{
				arcs[i][index] = Infinity;      //ɾ��������e��ͷ�ı�
				ArcNum--;
			}
			if (arcs[index][i] != Infinity && i != index)
			{
				arcs[index][i] = Infinity;     //ɾ��������eΪ��β�ı�
				ArcNum--;
			}
		}
		vectexes[index] = vectexes[vexNum - 1];
		tag[index] = tag[vexNum - 1];
		for (int i = 0; i < vexNum; i++)
		{
			arcs[i][index] = arcs[i][vexNum - 1];
			arcs[index][i] = arcs[vexNum - 1][i];
		}
		vexNum--;
	}
}


template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::FirstVerx(const int& v)const
//��ͼ��ȡ����vΪ��β�ĵ�һ���ڽӶ���
{
	int i;
	for (i = 0; i < vexNum; i++)
	{
		if (arcs[v][i] != Infinity && arcs[v][i] != 0)
			break;
	}
	if (i < vexNum) return i;
	else return -1;        //vû������Ϊ��β���ڽӶ���,����-1
}


template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::NextVerx(const int& v1, const int& v2)const
//��ͼ��ȡ����v1����v2�����һ������
{
	int i;
	for (i = v2+1; i < vexNum; i++)
	{
		if (arcs[v1][i] != Infinity && arcs[v1][i] != 0)
			break;
	}
	if (i < vexNum) return i;
	else return -1;
}

template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::DFS(const int& v, void (*Visit)(const ElemType&))const
//�Զ���v���������������
{
	if (tag[v] == VISITED) return;
	else
	{
		tag[v] = VISITED;
		(*Visit)(vectexes[v]);
		for (int i = FirstVerx(v); i>0&&i<vexNum; i = NextVerx(v, i))
		{
			if (tag[i] == UNVISITED)
				DFS(i, (*Visit));
		}
	}
}



template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::DFSTranverse(void (*Visit)(const ElemType&))const
//������ȱ���ͼ
{
	for (int i = 0; i < vexNum; i++)
		tag[i] = UNVISITED;
	for (int i = 0; i < vexNum; i++)
	{
		if(tag[i]==UNVISITED)
		DFS(i, (*Visit));
	}
}


template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::BFS(const int& v, void (*Visit)(const ElemType&))const
//�Զ���v���й����������
{
	if (tag[v] == VISITED) return;
	else
	{
		tag[v] = VISITED;
		(*Visit)(vectexes[v]);
		SeqQueue<int> que;
		que.EnQueue(v);
		int index;
		while (!que.IsEmpty())
		{
			que.DelQueue(index);
			for (int i = FirstVerx(index); i>0&&i<vexNum; i = NextVerx(index, i))
			{
				if (tag[i] == UNVISITED)
				{
					tag[i] = VISITED;
					(*Visit)(vectexes[i]);
					que.EnQueue(i);
				}
			}
		}
	}
}


template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::BFSTranverse(void (*Visit)(const ElemType&))const
//������ȱ���ͼ
{
	for (int i = 0; i < vexNum; i++)
		tag[i] = UNVISITED;
	for (int i = 0; i < vexNum; i++)
	{
		if (tag[i] == UNVISITED)
		{
			BFS(i, (*Visit));
		}
	}
}


template<class ElemType,class WeightType>
Status AdjMatrixdirGraph<ElemType, WeightType>::SetElem(const int& v, const ElemType& e)
//�޸Ķ���v��Ԫ��ֵ
{
	if (v < 0 || v >= vexNum)
		return FAIL;
	else vectexes[v] = e;
	return SUCCESS;
}


template<class ElemType,class WeightType>
ElemType& AdjMatrixdirGraph<ElemType, WeightType>::GetElem(const int& v)const
//�󶥵�v��Ԫ��ֵ
{
	if (v < 0 || v >= vexNum)
		throw Error("Ԫ���������Ϸ�!");
	return vectexes[v];
}


template<class ElemType,class WeightType>
Status &AdjMatrixdirGraph<ElemType, WeightType>::GetTag(const int& v)const
//��ȡ����v�ı��
{
	if (v < 0 || v >= vexNum)
		throw Error("Ԫ���������Ϸ�!");
	return tag[v];
}

template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::SetTag(const int& v, Status state)
//���ñ�־
{
	if (v < 0 || v >= vexNum)
		throw Error("Ԫ���������Ϸ�!");
	tag[v] = state;
}

template<class ElemType,class WeightType>
void AdjMatrixdirGraph<ElemType, WeightType>::Display()
//��ʾ����ͼ���ڽӾ���
{
	cout << " ";
	for (int i = 0; i < vexNum; i++)
		cout << "\t" << vectexes[i];
	cout << endl;
	for (int i = 0; i < vexNum; i++)
	{
		cout << vectexes[i];
		for (int j = 0; j < vexNum; j++)
		{
			if (arcs[i][j] == Infinity)
				cout << "\t" << "��";
			else
				cout << "\t" << arcs[i][j];
		}
		cout << endl;
	}
}


template<class ElemType,class WeightType>
WeightType& AdjMatrixdirGraph<ElemType, WeightType>::GetInfinity()
{
	return Infinity;
}


template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::GetOutNum(const ElemType& e)const
{
	int v = GetIndex(e),num=0;
	for (int i = 0; i < vexNum; i++)
	{
		if (arcs[v][i] != Infinity && arcs[v][i] != 0)
			num++;
	}
	return num;
}


template<class ElemType,class WeightType>
int AdjMatrixdirGraph<ElemType, WeightType>::GetInNum(const ElemType& e)const
{
	int v = GetIndex(e), num = 0;
	for (int i = 0; i < vexNum; i++)
	{
		if (arcs[i][v] != Infinity && arcs[i][v] != 0)
			num++;
	}
	return num;
}


template<class ElemType,class WeightType>
WeightType& AdjMatrixdirGraph<ElemType, WeightType>::GetWeight(const int& v1, const int& v2)const
//�󶥵�v1������v2������ߵ�Ȩֵ
{
	return arcs[v1][v2];
}




#endif


