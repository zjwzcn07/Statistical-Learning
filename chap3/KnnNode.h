#ifndef KNNNODE_H
#define KNNNODE_H

#include "my_funtion.h"

class KnnNode
{
public:
	KnnNode();
	~KnnNode();

	void ShowNode();
	
	vector<double> value;
	KnnNode *left_child, *right_child,*parent;
private:

};




#endif