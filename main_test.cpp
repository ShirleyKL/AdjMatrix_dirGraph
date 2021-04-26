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
			cout << "文件打开失败!" << endl;
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
			cout << "该有向图的邻接矩阵为：" << endl;
			if (g.IsEmpty()) cout << "该图为空!" << endl;
			else g.Display();
			int c = 1;
			while (c != 0)
			{
				cout << endl << "1. 图清空.";
				cout << endl << "2. 显示图.";
				cout << endl << "3. 取指定顶点的值.";
				cout << endl << "4. 设置指定顶点的值.";
				cout << endl << "5. 删除顶点.";
				cout << endl << "6. 插入顶点.";
				cout << endl << "7. 删除边.";
				cout << endl << "8. 插入边.";
				cout << endl << "9. 深度优先遍历图.";
				cout << endl << "10. 广度优先遍历图.";
				cout << endl << "11. 求顶点出度和入度.";
				cout << endl << "选择功能(1~10): ";
				cin >> c;
				switch (c)
				{
				case 1:
					g.Clear();
					break;
				case 2:
					if (g.IsEmpty())
						cout << "该图为空!" << endl;
					else
						g.Display();
					break;
				case 3:
					cout << endl << "输入顶点的序号(图的顶点序号从0开始): ";
					cin >> v1;
					e1 = g.GetElem(v1);
					cout << "序号为" << v1 << "的顶点为" << e1;
					break;
				case 4:
					cout << endl << "输入顶点的序号(图的顶点序号从0开始): ";
					cin >> v1;
					cout << endl << "输入" << v1 << "号顶点的值:";
					cin >> e1;
					g.SetElem(v1, e1);
					break;
				case 5:
					cout << endl << "输入被删除顶点的值:";
					cin >> e1;
					g.DeleteVerx(e1);
					break;
				case 6:
					cout << endl << "输入插入顶点的值:";
					cin >> e1;
					g.InsertVerx(e1);
					break;
				case 7:
					cout << endl << "输入被删除弧的弧尾和弧头:";
					cin >> e1 >> e2;
					v1 = g.GetIndex(e1);
					v2 = g.GetIndex(e2);
					g.DeleteArc(v1, v2);
					break;
				case 8:
					cout << endl << "输入插入弧的弧尾和弧头值:";
					cin >> e1 >> e2;
					cout << endl << "输入弧的权值:";
					cin >> weight;
					v1 = g.GetIndex(e1);
					v2 = g.GetIndex(e2);
					g.InsertArc(v1, v2,weight);
					break;
				case 9:
					cout << endl << "深度优先遍历图:" << endl;
					g.DFSTranverse(Write);
					break;
				case 10:
					cout << endl << "广度优先遍历图:" << endl;
					g.BFSTranverse(Write);
					break;
				case 11:
					cout << endl << "请输入需要求的顶点值:";
					cin >> e1;
					cout << "顶点" << e1 << "的入度为:" << g.GetInNum(e1);
					cout << "   出度为:" << g.GetOutNum(e1);
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