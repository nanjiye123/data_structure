#include <iostream>
using namespace std;

//根据前序中序找后序
void InPre2Post(const char *str_pre, const char *str_in, int length, char *str_post, int &pos)
{              //          前序遍历            中序遍历   中序遍历长度   所求后序遍历   后序位置
	if(length <= 0)//如果中序遍历串长度为0
	{
		return;
	}
	if(1 == length)//如果中序遍历串长度为1
	{
		str_post[pos] = *str_pre;
		pos++;
		return;
	}

	char root = *str_pre;
	int nRoot = 0;//中序里root的位置
	for(; nRoot<length; nRoot++)
	{//在中序找root的位置，得到nRoot
		if(str_in[nRoot] == root)
		{
			break;
		}
	}

	InPre2Post(str_pre+1, str_in, nRoot, str_post, pos);//root的左边
	InPre2Post(str_pre+nRoot+1, str_in+nRoot+1, length-(nRoot+1), str_post, pos);//root的右边
	str_post[pos] = root;
	pos++;
}

int main()//根据前序中序找后序，根据中序后序找前序
{
	char str_pre[] = "GDAFEMHZ";//前序遍历
	char str_in[]  = "ADEFGHMZ";//中序遍历
	int length = sizeof(str_in) / sizeof(char);
	char *str_post = (char*)malloc(length);
	int pos = 0;
	InPre2Post(str_pre, str_in, length-1, str_post, pos);
	str_post[length-1] = '\0';
	cout<< str_post <<endl;
	free(str_post);
	return 0;
}
