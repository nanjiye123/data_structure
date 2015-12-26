//Dijkstra算法
//数据结构与算法分析C语言描述
#include <iostream>
using namespace std;
typedef char NodeType;//顶点的数据类型
typedef int AdjType;//边权重的数据类型
#define MAX_LENGTH 10000

NodeType inputNodeValue[] = {'a','b','c','d','e','f','g'};
const int NodeNum = 7;
const int AdjNum = 12;
int InputEdge[AdjNum][3]={{0,1,2},//边的信息，由两个顶点的序号组成
					      {0,3,1},//第三个数字是权重值
					      {1,3,3},//构成一个带有权重的有向图
					      {1,4,10},
					      {2,0,4},
	                      {2,5,5},
						  {3,2,2},
						  {3,4,2},
						  {3,5,8},
						  {3,6,4},
						  {4,6,6},
						  {6,5,1}};

typedef struct Node//邻接表结点
{
	int adjvex;//结点的序号，即数组下标
	int weight;//边的权值
	Node* next;//下一条边的指针
}Node;

typedef struct HeadNode//图的顶点
{
	 NodeType NodeValue;//顶点的数值
	 bool     isKnown;//起始顶点至该顶点的最短路径是否已知
	 int      inDegree;//入度
	 Node*    link;//指向第一个邻接点的指针
	 int      length;//当前情况下起始顶点至该顶点的最短路径,初始化为无穷大，权重
	 int      parent;//表示最短路径的上一个顶点的序号
}HeadNode;


HeadNode* CreateGraph(HeadNode* G)//初始化图，构建邻接表
{
	G = (HeadNode*)malloc(sizeof(HeadNode)*NodeNum);
	//图的顶点初始化
	for(int i=0; i<NodeNum; i++)
	{
		G[i].NodeValue = inputNodeValue[i];//将顶点值传入
		G[i].inDegree = 0;//入度为0
		G[i].link = NULL;
		G[i].isKnown = false;
		G[i].length = MAX_LENGTH;
		G[i].parent = -1;
	}

	//构建邻接表
	for(int j=0; j<AdjNum; j++)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		node->adjvex = InputEdge[j][1];//赋值边终点的序号
		node->weight = InputEdge[j][2];//赋值权重
		G[node->adjvex].inDegree++;//边终点的入度加1
		//插入到邻接表的第一个位置，即头插法
		node->next = G[InputEdge[j][0]].link;
		G[InputEdge[j][0]].link = node;
	}
	return G;
}

void printGraph(HeadNode* G)//打印邻接表
{
	for(int i=0; i<NodeNum; i++)
	{
		cout << "结点" << G[i].NodeValue;
		cout << "（入度为" << G[i].inDegree << "）";
		Node *node = G[i].link;
		while(node)
		{
			cout << "->" << G[node->adjvex].NodeValue;
			cout << "（权:" << node->weight << "）";
			node = node->next;
		}
		cout<<endl;
	}

}

HeadNode* Dijkstra(HeadNode* G, int startNode)
{
	G[startNode].length = 0;//起始点到其本身的距离为0
	while(true)//如果所有顶点的最短路径都known，则跳出循环
	{
		bool ok = true;
		for(int i=0; i<NodeNum; i++)
		{
			if(!G[i].isKnown)
			{
				ok = false;
				break;
			}
		}//end for
		if(ok) break;//所有顶点都known，退出while循环

		//==================================================
		int tmpMinPos = -1;//路径最短的顶点序号
		AdjType tmpMinAdj = MAX_LENGTH;
		for(int i=0; i<NodeNum; i++)//在未知点中，搜索路径最短的
		{
			if(!G[i].isKnown && tmpMinAdj > G[i].length)
			{
				tmpMinAdj = G[i].length;
				tmpMinPos = i;
			}
		}//此段可以用最小堆来实现
		//===================================================
		cout<<"当前选中的顶点为："<< G[tmpMinPos].NodeValue <<endl;
		G[tmpMinPos].isKnown = true;//更新为known
		
		//将以tmpMinPos为起始点的所有路径length更新
		Node *node = G[tmpMinPos].link;
		while(node)
		{
			AdjType weight = node->weight;
			if(G[tmpMinPos].length+weight < G[node->adjvex].length)
			{//如果当前终止点的权重 大于 当前起始点加weight，即现在的路径比原路径的权重小
				G[node->adjvex].length = G[tmpMinPos].length+weight;
				G[node->adjvex].parent = tmpMinPos;
			}
			node = node->next;
		}//end while(node)
	}//end while(true)
	return G;
}

void printPath(HeadNode *G, int k)
{
	if(G[k].parent != -1)//继续递归，直到搜索到起始点
	{              
		printPath(G, G[k].parent);
		cout<<"->"<<G[k].NodeValue;
	}
	else//parent=-1,意味着其parent是起始点
	{//找到起始点
		cout<< G[k].NodeValue;//打印起始点
	}
}

int main()//Dijkstra算法
{//使用有向图、邻接表、广度优先搜索
	HeadNode *G = NULL;
	G = CreateGraph(G);
	cout<<"初始化图完成。"<<endl<<endl;
	cout<<"========打印邻接表========"<<endl;
	printGraph(G);
	cout<<endl;
	cout<<"======Dijkstra过程======="<<endl;
	G = Dijkstra(G, 0);//设定起始点为a，其下标为0
	cout<<endl;

	cout<<"====打印从起始点开始所有的最短路径===="<<endl;
	for(int k=1; k<NodeNum; k++)
	{
		cout<<"a到"<<G[k].NodeValue<<"的最短路径为";
		printPath(G, k);
		cout<<",权重为"<<G[k].length<<endl;
	}
	return 0;
}
