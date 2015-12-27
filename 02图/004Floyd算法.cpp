//Floyd算法
//数据结构与算法分析C语言描述
//所有顶点对之间的最短路径
#include <iostream>
using namespace std;
typedef char NodeType;//顶点的数据类型
typedef int AdjType;//边权重的数据类型
#define MAX_VEX 100
#define MAX     100000

NodeType inputNodeValue[] = {'a','b','c','d','e'};
const int NodeNum = 5;

typedef struct Graph
{
	NodeType node[MAX_VEX];//顶点
	AdjType  arcs[MAX_VEX][MAX_VEX];//带权重的邻接矩阵
	                                //不改变，仅表示顶点的连接情况
}Graph;

typedef struct Path
{
	AdjType adj[MAX_VEX][MAX_VEX];//存放每对顶点间的最短路径长度
	int prevex[MAX_VEX][MAX_VEX];//元素值为i到j路径中j的前驱顶点的下标值
}Path;


Graph* init(Graph *G)
{//初始化顶点值和邻接矩阵
	G = (Graph*)malloc(sizeof(Graph));
	for(int i=0; i<NodeNum; i++)
	{
		for(int j=0; j<NodeNum; j++)
		{
			G->arcs[i][j] = (i==j ? 0 : MAX);//初始化带权重的邻接矩阵
			                                 //对角线为0，无连接为MAX
		}//endfor
	}//endfor
	G->arcs[0][1] = 1;//初始化有连接的点
	G->arcs[0][3] = 3;
	G->arcs[0][4] = 10;
	G->arcs[1][2] = 5;
	G->arcs[2][4] = 1;
	G->arcs[3][2] = 2;
	G->arcs[3][4] = 6;

	for(int i=0; i<NodeNum; i++)
	{
		G->node[i] = inputNodeValue[i];//初始化顶点值
	}
	return G;
}

Path* floyd(Graph *G, Path *path)
{
	path = (Path*)malloc(sizeof(Path));
	//生成前驱序号矩阵prevex
	for(int i=0; i<NodeNum; i++)
	{
		for(int j=0; j<NodeNum; j++)
		{
			if(i!=j && G->arcs[i][j]<MAX)
			{
				path->prevex[i][j] = i;//生成前驱序号矩阵prevex
			}
			else
			{
				path->prevex[i][j] = -1;//生成前驱序号矩阵prevex
			}
			path->adj[i][j] = G->arcs[i][j];//拷贝最短路径长度矩阵
		}//endfor(j)
	}//endfor(i)

	for(int k=0; k<NodeNum; k++)//遍历所有顶点
	{
		for(int i=0; i<NodeNum; i++)//遍历整个图
		{
			for(int j=0; j<NodeNum; j++)//遍历整个图
			{
				if(path->adj[i][j] > path->adj[i][k]+path->adj[k][j])
				{
					//如果i-j-k的权重小于i-j，替换权重
					path->adj[i][j] = path->adj[i][k]+path->adj[k][j];
					//替换j的前驱
					path->prevex[i][j] = path->prevex[k][j];
				}
			}//endfor(j)
		}//endfor(i)
	}//endfor(k)
	return path;
}

void print(Graph *G, Path *path)
{
	for(int i=0; i<NodeNum; i++)//遍历整个图
	{
		for(int j=0; j<NodeNum; j++)//遍历整个图
		{
			if(i==j || path->adj[i][j]>=MAX)continue;
			int k = 0;//存储路径的辅助变量
			int pre = path->prevex[i][j];
			int tmp[MAX_VEX] = {0};//存储i到j路径中，除了ij外的所有顶点
			while(pre!=i && pre!=j)
			{//从j循环查找路径i到j中的所有顶点，直到源头i
				tmp[k++] = pre;
				pre = path->prevex[i][pre];
			}

			cout << G->node[i] << "->";
			while(k>0)
			{
				cout << G->node[tmp[--k]] << "->";
			}
			cout << G->node[j] << ", 长度为" << path->adj[i][j] << endl;
		}//endfor(j)
	}//endfor(i)
}

int main()//Floyd算法
{//使用有向图、邻接矩阵
	Graph *G = NULL;
	Path  *path = NULL;
	G = init(G);//生成带权的邻接矩阵
	path = floyd(G, path);
	print(G, path);
	return 0;
}
