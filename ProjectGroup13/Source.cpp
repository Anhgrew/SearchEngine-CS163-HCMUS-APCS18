#include"Project.h"
int main() {
	ifstream fin;
	vector<Node *>tree;
	string keyword;
	inputfile(tree);
	cout << "Enter key words: " << endl;
	getline(cin,keyword);
	char c;
	string bunchof_key[1000];
	string newkeyword = "";
		string wq = "'";
		int j = 0;
		for (int i = 0; i <= keyword.length(); i++)
		{
			c = tolower(keyword[i]);
			if (isalnum(static_cast<unsigned char>(c))) {
				newkeyword += c;
			}
			else if(!isalnum(static_cast<unsigned char>(c))){
				bunchof_key[j] = newkeyword;
				j++;
				newkeyword = "";
			}
		}
		outputfile(tree, bunchof_key,j);
	system("pause");
	return 0;
}