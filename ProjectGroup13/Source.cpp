#include"Project.h"
int main() {
	ifstream fin;
	bool mark[100];
	Node *tree = base();
	Node *tree1 = base();
	char keyword[75];
	cout << "Enter key words: " << endl;
	cin.getline(keyword, 75);
	for (int i = 0; i < strlen(keyword); i++)
	{
		keyword[i] = towlower(keyword[i]);
	}
	search_filemark(tree, tree1, keyword, mark);
	outputfile(mark);
	system("pause");
	return 0;
}