//main_test.cpp
#include "Assistance.h"
#include <iostream>
#include "AdjMatrix_dirGraph.h"
#include <fstream>
using namespace std;

int main()
{
	try
	{
		ifstream file;
		int n,m,v1,v2,weight;
		char e1, e2;
		file.open("test.txt", ios::in);
		if (!file)
			cout << "�ļ���ʧ��!" << endl;
		else
		{
			file >> n;
			char* elems = new char[n];
			for (int i = 0; i < n; i++)
				file >> elems[i];
			file >> m;
			AdjMatrixdirGraph<char, int> g(n, elems);
			for (int j = 0;j < m; j++)
			{
				file >> e1 >> e2 >> weight;
				v1 = g.GetIndex(e1);
				v2 = g.GetIndex(e2);
				g.InsertArc(v1, v2, weight);
			}
			cout << "������ͼ���ڽӾ���Ϊ��" << endl;
			if (g.IsEmpty()) cout << "��ͼΪ��!" << endl;
			else g.Display();
			int c = 1;
			while (c != 0)
			{
				cout << endl << "1. ͼ���.";
				cout << endl << "2. ��ʾͼ.";
				cout << endl << "3. ȡָ�������ֵ.";
				cout << endl << "4. ����ָ�������ֵ.";
				cout << endl << "5. ɾ������.";
				cout << endl << "6. ���붥��.";
				cout << endl << "7. ɾ����.";
				cout << endl << "8. �����.";
				cout << endl << "9. ������ȱ���ͼ.";
				cout << endl << "10. ������ȱ���ͼ.";
				cout << endl << "11. �󶥵���Ⱥ����.";
				cout << endl << "ѡ����(1~10): ";
				cin >> c;
				switch (c)
				{
				case 1:
					g.Clear();
					break;
				case 2:
					if (g.IsEmpty())
						cout << "��ͼΪ��!" << endl;
					else
						g.Display();
					break;
				case 3:
					cout << endl << "���붥������(ͼ�Ķ�����Ŵ�0��ʼ): ";
					cin >> v1;
					e1 = g.GetElem(v1);
					cout << "���Ϊ" << v1 << "�Ķ���Ϊ" << e1;
					break;
				case 4:
					cout << endl << "���붥������(ͼ�Ķ�����Ŵ�0��ʼ): ";
					cin >> v1;
					cout << endl << "����" << v1 << "�Ŷ����ֵ:";
					cin >> e1;
					g.SetElem(v1, e1);
					break;
				case 5:
					cout << endl << "���뱻ɾ�������ֵ:";
					cin >> e1;
					g.DeleteVerx(e1);
					break;
				case 6:
					cout << endl << "������붥���ֵ:";
					cin >> e1;
					g.InsertVerx(e1);
					break;
				case 7:
					cout << endl << "���뱻ɾ�����Ļ�β�ͻ�ͷ:";
					cin >> e1 >> e2;
					v1 = g.GetIndex(e1);
					v2 = g.GetIndex(e2);
					g.DeleteArc(v1, v2);
					break;
				case 8:
					cout << endl << "������뻡�Ļ�β�ͻ�ͷֵ:";
					cin >> e1 >> e2;
					cout << endl << "���뻡��Ȩֵ:";
					cin >> weight;
					v1 = g.GetIndex(e1);
					v2 = g.GetIndex(e2);
					g.InsertArc(v1, v2,weight);
					break;
				case 9:
					cout << endl << "������ȱ���ͼ:" << endl;
					g.DFSTranverse(Write);
					break;
				case 10:
					cout << endl << "������ȱ���ͼ:" << endl;
					g.BFSTranverse(Write);
					break;
				case 11:
					cout << endl << "��������Ҫ��Ķ���ֵ:";
					cin >> e1;
					cout << "����" << e1 << "�����Ϊ:" << g.GetInNum(e1);
					cout << "   ����Ϊ:" << g.GetOutNum(e1);
				}
			}
		}
	}
	catch (Error err)
	{
		err.Show();
	}
	system("PAUSE");
	return 0;
}