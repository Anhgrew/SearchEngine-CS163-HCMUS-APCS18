#include"Project.h"
int main() {
	ifstream fin;
	bool mark[100];
	vector<Node *>treenext;
	Node *tree = baseNode();
	char keyword[75];
	cout << "Enter key words: " << endl;
	cin.getline(keyword, 75);
	for (int i = 0; i < strlen(keyword); i++)
	{
		keyword[i] = towlower(keyword[i]);
	}
	inputfile(tree, treenext);
	outputfile(tree,treenext,keyword);
	system("pause");
	return 0;
}