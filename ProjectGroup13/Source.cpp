#include"Project.h"
int main() {
	ifstream fin;
	vector<Node *>tree;
	string keyword;
	cout << "Enter key words: " << endl;
	getline(cin,keyword);
	transform(keyword.begin(), keyword.end(), keyword.begin(), tolower);
	inputfile(tree);
	outputfile(tree,keyword);
	system("pause");
	return 0;
}