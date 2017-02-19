#include "KnnNode.h"

KnnNode::KnnNode()
{
	parent=left_child = right_child = NULL;
	value.clear();
}

KnnNode::~KnnNode()
{
}

void KnnNode::ShowNode()
{
	for (auto x : value)
		cout << x << " ";
	cout << endl;
}