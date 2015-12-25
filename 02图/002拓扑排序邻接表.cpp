//用邻接表表示图的拓扑排序
//数据结构与算法分析C语言描述
//对一个有向图进行拓扑排序
#include <iostream>
#include <stack>
using namespace std;
#define MAXVEX 100
typedef int VexType;

int n = 7;//顶点个数
VexType a[]={0,1,2,3,4,5,6};//顶点的数值

typedef struct EdgeList
{
	int adjvex;//邻接结点
	struct EdgeList *next;//指向下一条边的指针
}EdgeList;//邻接表中的边

typedef struct Vexnode
{
	VexType vertex;//顶点的数据
	EdgeList *firstedge;//指向第一个邻接点的指针
}Vexnode;//邻接表中每个顶点的信息

typedef struct AlGraph
{
	int edgenum;//图中边的个数
	int	vexnum;//图中顶点的个数
	Vexnode vexs[MAXVEX];//邻接表，包括顶点数据和指针
}AlGraph;//图


AlGraph* CreatAdjlist(AlGraph* g)
{
	g = (AlGraph*)malloc(sizeof(AlGraph));
	cout<<"输入顶点数据，完成。"<<endl;
	for(int i=0; i<n; i++)
	{
		g->vexs[i].vertex = a[i];//输入顶点信息
		g->vexs[i].firstedge = NULL;//初始化每个链表为空
	}

	cout<<"输入图的边，两个顶点为0，表示输入结束。完成。"<<endl;
	int InputEdge[13][2]={{0,1},//所有边的信息，由两个顶点组成
					      {0,2},//0,0 结束标志
					      {0,3},//对一个有向图进行拓扑排序
					      {1,3},
					      {1,4},
	                      {2,5},
	                      {3,2},
	                      {3,5},
					      {3,6},
	                      {4,3},
					      {4,6},
						  {6,5},
	                      {0,0}};
	int i  = 0;
	int v1 = InputEdge[i][0];
	int v2 = InputEdge[i][1];
	int EdgeNum = 0;//图的边数
	while(v1!=0 || v2!=0)
	{//建立邻接表，依次插入邻接顶点
		EdgeList *p = (EdgeList*)malloc(sizeof(EdgeList));
		//运用头插法，即在顶点和第一个邻接顶点之间插入
		p->adjvex = v2;
		p->next = g->vexs[v1].firstedge;
		g->vexs[v1].firstedge = p;
		EdgeNum++;
		i++;
		v1=InputEdge[i][0];
		v2=InputEdge[i][1];
	}
	g->vexnum = n;//图中顶点数
	g->edgenum = EdgeNum;//图中边的数

	return g;
}

void CountInDegree(AlGraph* g, int* indegree)//取得图中各个顶点的入度
{
	for(int i=0; i<g->vexnum; i++)
	{
		indegree[i] = 0;
	}
	for(int i=0; i<g->vexnum; i++)
	{
		EdgeList* p = g->vexs[i].firstedge;
		while(p)
		{
			indegree[p->adjvex]++;
			p = p->next;
		}
	}
	/*
	for(int i=0; i<g->vexnum; i++)
	{
		cout<<indegree[i]<<endl;
	}*/
}

void TopologicalSort(AlGraph* g)//拓扑排序算法
{
	int indegree[MAXVEX];//保存各个顶点的入度信息
	CountInDegree(g, indegree);//对各顶点求入度
	stack<VexType> s;
	for(int i=0; i<g->vexnum; i++)
	{
		if(0 == indegree[i]) s.push(g->vexs[i].vertex);//将入度为0的点入栈
	}
	int count = 0;
	while(!s.empty())
	{
		VexType v = s.top();  //从栈中读一个入度为0的点
		s.pop();              //该点出栈
		cout<<g->vexs[v].vertex<<" ";//输出该点
		count++;
		EdgeList* p=g->vexs[v].firstedge;
		while(p)
		{
			int k = p->adjvex;//v的邻接点
			if( !(--indegree[g->vexs[k].vertex]) )//对顶点v的所有邻接点入度减1
			{
				s.push(g->vexs[k].vertex);//新产生的入度为0的顶点进栈
			}
			p = p->next;
		}//end while(p)
	}//end while(!s.empty())
	if(count < g->vexnum) //如果打印的序列长度小于顶点个数
		cout<<"图中存在回路"<<endl;
	else
		cout<<"存在拓扑序列"<<endl;
}

//打印邻接表
void printvexs(AlGraph* g)
{
	cout<<"生成的邻接表如下："<<endl;
	for(int i=0; i<g->vexnum; i++)
	{
		cout<<g->vexs[i].vertex<<": ";
		EdgeList* p = g->vexs[i].firstedge;
		while(p)
		{
			cout<<"->"<<p->adjvex;
			p = p->next;
		}
		cout<<endl;
	}
}

int main()//用邻接表表示图的拓扑排序
{//对一个有向图进行拓扑排序
	AlGraph* g;
	g = CreatAdjlist(g);//建立邻接表
	cout<<"图建立成功。"<<endl;
	printvexs(g);//打印邻接表
	TopologicalSort(g);//拓扑排序算法
	return 0;
}
