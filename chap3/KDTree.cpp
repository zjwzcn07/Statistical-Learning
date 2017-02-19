#include "KDTree.h"

KDTree::KDTree(int _N)
{
	N = _N;
	root = NULL;
}

KDTree::KDTree()
{
}

KDTree::~KDTree()
{
}

void KDTree::PrintSegment(vector<vector<double>>&segment)
{
	for (auto row : segment)
	{
		for (auto element : row)
		{
			cout << element << " ";
		}
		cout << endl;
	}
}

void KDTree::PrintNode(KnnNode *nowNode)
{
	if (nowNode != NULL)
	{
		nowNode->ShowNode();
		if (nowNode->left_child != NULL)
			PrintNode(nowNode->left_child);
		if (nowNode->right_child != NULL)
			PrintNode(nowNode->right_child);
	}
}


KnnNode *KDTree::Create(vector<vector<double>> &segment, int depth)
{
	//比较向量第j维数的大小,以此排序
	sort(segment.begin(), segment.end(), [capture = make_pair(N, depth)](const vector<double>&a, const vector<double>&b) {
		int j = capture.second%capture.first;
		return a[j] < b[j];
	});
	//PrintSegment(segment);
	int sz = segment.size();
	int mid = sz / 2;
	KnnNode *newNode = new KnnNode;
	newNode->value = segment[mid];
	if (depth == 0)
	{
		root = newNode;
	}
	vector<vector<double>>left_segment, right_segment;
	left_segment.clear();
	right_segment.clear();
	for (int i = 0;i != mid;++i)
		left_segment.push_back(segment[i]);
	for (int i = mid + 1;i != sz;++i)
		right_segment.push_back(segment[i]);
	if (mid)
	{
		newNode->left_child = Create(left_segment, depth + 1);
		newNode->left_child->parent = newNode;
	}
	if (sz - mid - 1)
	{
		newNode->right_child = Create(right_segment, depth + 1);
		newNode->right_child->parent = newNode;
	}
	return newNode;
}

//最邻近搜索,lp是距离选择,lp=2是欧式距离
void KDTree::NearestSearch(int depth, KnnNode *now_node, vector<KnnNode*>&path, const vector<double>&target, KnnNode &now_goal, double &now_distance, bool back, int lp)
{
	//若此节点为叶子，则更新当前最近点，设置回溯值back = 1
	if (now_node->left_child == NULL && now_node->right_child == NULL)
	{
		double dis = LpDistance(now_node->value, target, lp);
		if (dis < now_distance)
		{
			now_goal = *now_node;
			now_distance = dis;
		}
		path.push_back(now_node);
		back = 1;
	}
	//若不是回溯，则检查目标点是否小于当前点当前维度，是的话则向左递归，否则向右递归
	if (!back)
	{
		path.push_back(now_node);
		//当前维度
		int k = depth%N;
		if(now_node->left_child==NULL)
			NearestSearch(depth + 1, now_node->right_child, path, target, now_goal, now_distance, back, lp);
		else if(now_node->right_child==NULL)
			NearestSearch(depth + 1, now_node->left_child, path, target, now_goal, now_distance, back, lp);
		else if (target[k] < now_node->value[k])
		{
			NearestSearch(depth + 1, now_node->left_child,path,target, now_goal, now_distance, back, lp);
		}
		else
		{
			NearestSearch(depth + 1, now_node->right_child, path, target, now_goal, now_distance, back, lp);
		}
	}
	//回溯检查当前节点，若当前界定啊更优则更新
	else {
		if (path.size() == 0)
			return;
		KnnNode *next_node = path.back();
		path.pop_back();
		double dis = LpDistance(next_node->value, target, lp);
		if (dis < now_distance)
		{
			now_goal = *next_node;
			now_distance = dis;
		}
		KnnNode *par = next_node->parent;
		//若兄弟节点更优则对兄弟节点递归搜索
		if (par->left_child != NULL && par->left_child != next_node)
		{
			double other_dis = LpDistance(par->left_child->value, target, lp);
			if (other_dis < now_distance)
			{
				now_goal = *par->left_child;
				now_distance = other_dis;
				back = 0;
				NearestSearch(depth, par->left_child, path, target, now_goal, now_distance, back, lp);
			}
		}
		else if (par->right_child != NULL && par->right_child != next_node)
		{
			double other_dis = LpDistance(par->right_child->value, target, lp);
			if (other_dis < now_distance)
			{
				now_goal = *par->right_child;
				now_distance = other_dis;
				back = 0;
				NearestSearch(depth, par->right_child, path, target, now_goal, now_distance, back, lp);
			}
		}
		else {
			NearestSearch(depth - 1, par, path, target, now_goal, now_distance, back, lp);
		}
		if (path.size() == 0)
			return;
	}
}
