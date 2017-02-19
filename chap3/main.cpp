
#include "my_funtion.h"

#include "KDTree.h"



int main()
{
	vector<vector<double>> myVec;
	Mat data = (Mat_<double>(2, 6) << 2, 5, 9, 4, 8, 7,
									  3, 4, 6, 7, 1, 2);
	for (int i = 0;i != 6;++i)
	{
		vector<double>row;
		row.clear();
		for (int j = 0;j < 2;j++)
		{
			row.push_back(data.at<double>(j, i));
		}
		myVec.push_back(row);
	}
	KDTree myTree(6);
	myTree.Create(myVec,0);
	myTree.PrintNode(myTree.root);
	vector<double>goal{ 7.5,5 };
	vector<KnnNode*>path;
	KnnNode ans;
	double dis = 1000;
	myTree.NearestSearch(0, myTree.root, path, goal, ans, dis, 0, 2);
	cout << "Nearest Point" << endl;
	ans.ShowNode();
	system("pause");
	waitKey();
	return 0;
}