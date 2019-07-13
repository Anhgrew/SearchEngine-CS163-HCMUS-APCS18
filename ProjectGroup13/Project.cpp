#include "Project.h"
Node * baseNode()
{
	Node* p = new Node;
	p->endword = false;
	return p;
}


void insert(Node*& tree, const string& key)
{
	if (tree == nullptr)
		tree = baseNode();

	Node* temp = tree;
	for (int i = 0; i < key.length(); i++) {
		char x = key[i];
		if (temp->map.find(x) == temp->map.end())
			temp->map[x] = baseNode();

		temp = temp->map[x];
	}
	temp->endword = true;
}

/*void input(Node *&tree, Node *&treenext)
{
	ifstream fin;
	ostringstream convert;
	char word[75];
	string path = "Group13News0";
	fin.open("Group13News01.txt", ios::in);
	fin.seekg(3, fin.beg);
	int i = 0;
	while (!fin.eof())
	{
		fin.getline(word, 75, ' ');
		insert(tree, word);
	}
	fin.close();
	for (int i = 2; i < 12; i++) {
		int k = i;
		convert.str("");
		convert << i;
		path.append(convert.str());
		path.append(".txt");
		fin.open(path, ios::in);
		while (!fin.eof())
		{
			fin.getline(word, 75, ' ');
			insert(treenext, word);
		}
		if (k < 10) {
			path = "Group13News0";
		}
		else {
			path = "Group13News";
		}
		fin.close();
	}
}
	*/
bool search(Node *tree, const string& key)
{
	if (tree == nullptr)
		return false;

	Node* temp = tree;
	for (int i = 0; i < key.length(); i++) {
		temp = temp->map[key[i]];

		if (temp == nullptr)
			return false;
	}

	return temp->endword;
}
void inputfile(vector<Node *>& tree)
{
	ifstream fin;
	ostringstream convert;
	string word;
	string path = "Group13News0";
	tree.resize(26);
	for (int i = 1; i < 26; i++)
	{
		tree[i] = baseNode();
	}
	for (int i = 1; i < 26; i++) {
		int k = i;
		convert.str("");
		convert << i;
		path.append(convert.str());
		path.append(".txt");
		fin.open(path, ios::in);
		char c;
		string wq = "'";
		while (fin.get(c))
		{
			c = tolower(c);
			if ((c >= '0' &&c <= '9') || (c >= 'a'&&c <= 'z')) {
				word += c;
			}
			if (c == ' ' || c == wq[0]||c=='\n' || c==EOF) {
				//cout << word << endl;	buon thi bo ra coi chay chu choi....  van ko doc dk chu dau va cuoi.
				insert(tree[i], word);
				word = "";
			}	
		}
		fin.close();
		if (k < 10) {
			path = "Group13News0";
		}
		else {
			path = "Group13News";
		}
	}
}
void outputfile(vector<Node *> &tree, const string& key)
{
	int count = 1;
	string path = "Group13News0";
	cout << "The key words was found in file: " << endl;
	for (int i = 1; i < 26; i++) {
		int k = i;
		if (search(tree[i], key) == true && count <= 5) {
			cout << path << i << ".txt" << endl << endl;
			count++;
		}
		if (k < 10) {
			path = "Group13News0";
		}
		else {
			path = "Group13News";
		}
	}
}

