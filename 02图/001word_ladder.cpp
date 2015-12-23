/*单词变换问题word ladder
给定字典和一个起点单词和一个终点单词，每次只能变换一个字母，
问从起点单词是否可以到达终点单词？最短多少步？
如：
start="hit"
end  ="cog"
dict =[hot,dot,dog,lot,log]
hit -> hot -> dot -> dog -> cog
*/
/*
思路：路径内的单词在词典里，但起点和终点的单词没有要求
搜索路径可以用图
*/
#include <iostream>
#include <string>
using namespace std;

int CalLength(const string& start, const string& end, const set<string>& dict)
{
	queue<string> q;
	q.push(start);
	

	return ;
}

int main()
{
	set<string> dict;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("lot");
	dict.insert("log");
	string start = "hit";
	string end   = "cog";
	cout << CalLength(start, end, dict);//计算最短长度数
	return 0;	
}




