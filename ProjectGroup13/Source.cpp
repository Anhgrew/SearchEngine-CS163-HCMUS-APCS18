#include"Project.h"
int main() {
	ifstream fin;
	bool mark[100];
	Node *tree = baseNode();
	treearr treeafter1;
	char keyword[75];
	cout << "Enter key words: " << endl;
	cin.getline(keyword, 75);
	for (int i = 0; i < strlen(keyword); i++)
	{
		keyword[i] = towlower(keyword[i]);
	}
	inputfile(tree, treeafter1);
	outputfile(tree,treeafter1,keyword);
	system("pause");
	return 0;
}