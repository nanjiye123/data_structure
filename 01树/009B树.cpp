#include <iostream>
using namespace std;

const int t = 2;//B树的最小度数为2

//关键字范围是[t-1,2t-1]
//子树范围是[t,2t]
//每个叶子节点有相同的深度，即树的高度h
typedef struct BTreenode
{
	int keynum;//结点中关键字的个数
	int key[2*t-1];//关键字本身
	struct BTreenode *son[2*t];//子树的指针向量
	bool is_leaf;
}BTreenode;

//*******函数声明**************
BTreenode *btree_node_new();
BTreenode *btree_create();
void BTreeSplit(BTreenode *parent, BTreenode *child, int childPosition);
void BTreeInsertNonfull(BTreenode *node, int input);
BTreenode *btree_insert(BTreenode *root, int input);
void BTreelevelDisplay(BTreenode *root);
void btree_merge_child(BTreenode *root, int pos, BTreenode *child1, BTreenode *child2);
int btree_search_predecessor(BTreenode *root);
int btree_search_successor(BTreenode *root);
void btree_delete_nonone(BTreenode *root, int input);
BTreenode *btree_delete(BTreenode *root, int input);
//****************************


BTreenode *btree_node_new()
{
	BTreenode *node = (BTreenode *)malloc(sizeof(BTreenode));
	if(node == NULL)
	{
		cout<<"申请空间出错！"<<endl;
		return NULL;
	}
	for(int i=0; i<2*t-1; ++i)//初始化key
	{
		node->key[i] = 0;
	}
	for(int i=0; i<2*t; ++i)//初始化子树
	{
		node->son[i] = NULL;
	}
	node->keynum = 0;
	node->is_leaf = true;//默认为叶子
	return node;
}

BTreenode *btree_create()
{
	BTreenode *node = btree_node_new();
	if(node == NULL)
	{
		cout<<"申请根节点空间出错"<<endl;
		return NULL;
	}
	return node;
}
                          //node              原root
void BTreeSplit(BTreenode *parent, BTreenode *child, int childPosition)
{//分裂存储关键字的个数达到最大的节点
 //新创建的节点作为父亲节点，之前的节点分裂成两个儿子节点
	BTreenode *new_child = btree_node_new();//为新分裂的结点分配空间
	new_child->is_leaf = child->is_leaf;//与被分裂点同级
	new_child->keynum = t - 1;//设置节点关键字数
	
	for(int i=0; i<new_child->keynum; ++i)
	{//将原root后半部分的key复制给新节点
		new_child->key[i] = child->key[i+t];
	}

	if(child->is_leaf == false)
	{//如果原root不是叶子，需要把指针拷过去，指针比节点多1
		for(int i=0; i<t; ++i)
		{
			new_child->son[i] = child->son[i+t];
		}
	}

	child->keynum = t - 1;//已经拷走了t-1个，还剩t-1个关键字
	//共2t-2个关键字，中间的关键字需要插入到新的根节点


	//移动新根节点的孩子，准备插入new_child
	for(int i=parent->keynum; i>childPosition; --i)
	{
		parent->son[i+1] = parent->son[i];
	}
	//原root的中间节点需要插入到parent即新根节点的childPosition处
	parent->son[childPosition + 1] = new_child;

	for(int i=parent->keynum-1; i>=childPosition; --i)
	{
		parent->key[i+1] = child->key[i];
	}
	parent->key[childPosition] = child->key[t-1];

	parent->keynum += 1;//加1是需要插入的原root的中间节点
}

//执行该操作时，node->keynum < 2t-1
void BTreeInsertNonfull(BTreenode *node, int input)
{
	if(node->is_leaf == true)//如果要插入到的节点是叶子节点
	{
		int pos = node->keynum;
		while(pos>=1 && input<node->key[pos-1])
		{//向右移动原关键字，直到找到可以插入input的位置
			node->key[pos] = node->key[pos-1];
			pos--;
		}

		node->key[pos] = input;//插入元素
		node->keynum += 1;
	}
	else//如果要插入到的节点不是叶子节点
	{//沿着查找路径下降
		int pos = node->keynum;
		while(pos>=1 && input<node->key[pos-1])
		{//直到找到可以插入input的位置
			pos--;
		}

		if(node->son[pos]->keynum == 2*t-1)//如果路径中有满节点
		{
			BTreeSplit(node, node->son[pos], pos);//分裂
			if(input > node->key[pos])
			{
				pos++;
			}
		}
		BTreeInsertNonfull(node->son[pos], input);
	}
}

//插入节点，起始步骤
BTreenode *btree_insert(BTreenode *root, int input)
{
	if(root == NULL)
	{
		cout<<"root error"<<endl;
		return NULL;
	}
	if(root->keynum == 2*t-1)//根节点的关键字已满，分裂生成新的根节点
	{//如果根是满的，是唯一使得树增高的情形
		BTreenode *node = btree_node_new();
		if(node == NULL) return NULL;
		node->is_leaf = false;
		node->son[0] = root;
		BTreeSplit(node, root, 0);//分裂B树的结点
		BTreeInsertNonfull(node, input);//插入关键字
		return node;
	}
	else//根未满的一般情况
	{
		BTreeInsertNonfull(root, input);
		return root;
	}
}

//广度优先显示树
void BTreelevelDisplay(BTreenode *root)
{
	BTreenode *queue[200] = {};//树中不能超过200个节点
	int front = 0, rear = 0;

	queue[rear++] = root;

	while(front < rear)
	{
		BTreenode *node = queue[front++];

		cout<<"[";
		for(int i=0; i<node->keynum; ++i)
		{
			cout<<node->key[i];
			if(i != node->keynum-1) cout<<' ';
		}
		cout<<"] ";

		for(int i=0; i<=node->keynum; ++i)
		{
			if(node->son[i] != NULL)
			{
				queue[rear++] = node->son[i];
			}
		}
	}
	cout<<endl;
}

//将child1，root的key，child2合并到child1节点，释放child2节点
//child1和child2节点的keynum都为t-1
void btree_merge_child(BTreenode *root, int pos, BTreenode *child1, BTreenode *child2)
{
	child1->keynum = 2*t-1;
	//将child2的节点拷贝到child1的后半部分
	for(int i=t; i<2*t-1; ++i)
	{
		child1->key[i] = child2->key[i-t];
	}
	//root的key拷贝到child1的中间节点
	child1->key[t-1] = root->key[pos];

	//如果child2是非叶子节点，需要拷贝指针
	if(child2->is_leaf == false)
	{
		for(int i=t; i<2*t; ++i)
		{
			child1->son[i] = child2->son[i-t];
		}
	}

	//更新root的key和son
	for(int i=pos+1; i<root->keynum; ++i)
	{
		root->key[i-1] = root->key[i];
		root->son[i] = root->son[i+1];
	}
	root->keynum -= 1;//更新root的keynum
	free(child2);//释放child2
}

//查找以root为根（多层）的最右节点，返回最右节点关键字即最大关键字
int btree_search_predecessor(BTreenode *root)
{
	BTreenode *tmp = root;
	while(tmp->is_leaf == false)
	{
		tmp = tmp->son[tmp->keynum];
	}
	return tmp->key[tmp->keynum-1];
}

//查找以root为根（多层）的最左节点，返回最左节点关键字即最小关键字
int btree_search_successor(BTreenode *root)
{
	BTreenode *tmp = root;
	while(tmp->is_leaf == false)
	{
		tmp = tmp->son[0];
	}
	return tmp->key[0];
}

//root的关键字降到mid，left最大关键字升到root
void btree_shift_to_right_child(BTreenode *root, int pos, BTreenode *left, BTreenode *mid)
{
	mid->keynum += 1;
	for(int i=mid->keynum-1; i>0; --i)
	{//将mid中的关键字逐个向后移动一个位置
		mid->key[i] = mid->key[i-1];
	}
	mid->key[0] = root->key[pos];
	root->key[pos] = left->key[left->keynum-1];

	if(mid->is_leaf == false)
	{//如果mid不是叶子，则还需要逐个向后移动mid的分支son一个位置
		for(int i=mid->keynum; i>0; --i)
		{
			mid->son[i] = mid->son[i-1];
		}
		mid->son[0] = left->son[left->keynum-1];
	}

	left->keynum -= 1;
}

//root的关键字降到mid，right最小关键字升到root
void btree_shift_to_left_child(BTreenode *root, int pos, BTreenode *mid, BTreenode *right)
{
	mid->keynum += 1;
	mid->key[mid->keynum-1] = root->key[pos];//root的关键字降到mid末尾
	root->key[pos] = right->key[0];//right最小关键字升到root

	for(int i=1; i<right->keynum; ++i)
	{//向左逐个移动right关键字
		right->key[i-1] = right->key[i];
	}
	if(right->is_leaf == false)
	{//如果right不是叶子
		mid->son[mid->keynum] = right->son[0];//移动right的第一个分支son到mid的最后分支
		for(int i=1; i<=right->keynum; ++i)
		{//向左逐个移动right的分支son
			right->son[i-1] = right->son[i];
		}
	}
	right->keynum -= 1;
}

//root至少有t个关键字（最少为t-1），可以保证删除后不会回溯
void btree_delete_nonone(BTreenode *root, int input)
{
	if(root->is_leaf == true)//如果input在叶子节点，直接删除
	{
		int pos = 0;
		while(pos < root->keynum && input > root->key[pos])
		{//查找到input的位置
			++pos;
		}

		if(root->key[pos] == input)//找到了input的位置
		{
			for(int j=pos+1; j<2*t-1; ++j)//从root删除input
			{
				root->key[j-1] = root->key[j];
			}
			root->keynum -= 1;
		}
		else//未找到input的位置
		{
			cout<<"no found input!"<<endl;
		}
	}//end if 如果input在叶子节点
	else//input在节点或节点分支上
	{
		int pos = 0;
		BTreenode *left=NULL, *right=NULL;
		while(pos < root->keynum && input > root->key[pos])
		{//查找到input的位置
			++pos;
		}
		if(pos < root->keynum && input == root->key[pos])//在节点找到了input的位置
		{
			left = root->son[pos];//左分支
			right = root->son[pos+1];//右分支
			if(left->keynum > t-1)//*****情况1*****
			{//如果左分支关键字多于t-1，则找到左分支（多层）的最右节点prev，替换input
			 //并在左分支中递归删除prev
				int prev = btree_search_predecessor(left);
				root->key[pos] = prev;
				btree_delete_nonone(left, prev);
			}
			else if(right->keynum > t-1)//*****情况2*****
			{//如果右分支关键字多于t-1，则找到右分支（多层）的最左节点next，替换input
			 //并在右分支中递归删除next
				int next = btree_search_successor(right);
				root->key[pos] = next;
				btree_delete_nonone(right, next);
			}
			else//*****情况3*****
			{//两个分支节点数都为t-1，则将input、right合并至left
			 //并在合并的left中递归删除input
				btree_merge_child(root, pos, left, right);
				btree_delete(left, input);
			}

		}//end if 在节点找到了input的位置
		else//在节点没找到，一定在分支的子节点中
		{
			BTreenode               *mid = root->son[pos];//input一定在这个分支
			if(pos < root->keynum)  right = root->son[pos+1];
			if(pos > 0)             left = root->son[pos-1];

			if(mid->keynum == t-1)//如果input所在分支的节点最少，不能删除
			{
				if(pos>0 && left->keynum > t-1)
				{//左相邻分支的关键字个数大于t-1
				 //则将root的某个关键字降到son[pos]中，将son[pos-1]的最大关键字升到root中
					btree_shift_to_right_child(root, pos-1, left, mid);
				}
				else if(pos < root->keynum && right->keynum > t-1)
				{//右相邻分支的关键字个数大于t-1
				 //则将root的某个关键字降到son[pos]中，将son[pos+1]的最小关键字升到root中
					btree_shift_to_left_child(root, pos, mid, right);
				}
				else if(pos > 0)
				{//若son[pos-1]和son[pos+1]都有最少的t-1个关键字
				 //方法一：将root[pos-1],son[pos-1],son[pos]合并到son[pos-1]
					btree_merge_child(root, pos-1, left, mid);
					mid = left;//?????
				}
				else
				{//若son[pos-1]和son[pos+1]都有最少的t-1个关键字
				 //方法二：将root[pos],son[pos],son[pos+1]合并到son[pos]
					btree_merge_child(root, pos, mid, right);
				}
				btree_delete_nonone(mid, input);//合并完成后，删除input
			}
			else
			{
				btree_delete_nonone(mid, input);
			}
		}//end else 在节点没找到，一定在分支的子节点中
	}//end else 如果input在节点或节点分支上
	
}


//删除入口
BTreenode *btree_delete(BTreenode *root, int input)
{
	//keynum=1意味着根只有两个子女
	if(root->keynum == 1)
	{
		BTreenode *child1 = root->son[0];
		BTreenode *child2 = root->son[1];
		if(child1!=NULL && child2!=NULL && child1->keynum==t-1 && child2->keynum==t-1)
		{//这两个子女的关键字个数都是t-1（即最小），合并根与两个子女
		 //这是唯一能降低树高的情形
			btree_merge_child(root, 0, child1, child2);
			free(root);
			btree_delete_nonone(child1, input);
			return child1;
		}
		else
		{//根只有两个子女，但不合并
			btree_delete_nonone(root, input);
			return root;
		}
	}
	else
	{//其他普通情况
		btree_delete_nonone(root, input);
		return root;
	}
}

int main()//B树
{
	BTreenode *root = btree_create();//创建B树的根结点

	int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20};
	for(int i=0; i<sizeof(arr)/sizeof(arr[0]); ++i)
	{
		root = btree_insert(root, arr[i]);//插入元素
		BTreelevelDisplay(root);
	}

	int todel[] = {15, 18, 23, 30, 31, 52, 50, 48, 47, 45, 20, 12, 10};
	for(int i=0; i<sizeof(todel)/sizeof(todel[0]); ++i)
	{
		cout<<"delete "<<todel[i]<<endl;
		root = btree_delete(root, todel[i]);
		BTreelevelDisplay(root);
	}

	return 0;
}

