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
		while (fin.get(c))
		{
			c = tolower(c);
			if (isalnum(static_cast<unsigned char>(c))) {
				word += c;
			}
			if (!isalnum(static_cast<unsigned char>(c))) {
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
void outputfile(vector<Node *> &tree, string key[1000],int p)
{
	bool final = false;
	int count = 1;
	string path = "Group13News0";
	cout << "THE KEYWORDS WAS FOUND IN FILES: " << endl;
	bool mark[100];
	for (int i = 1; i < 26; i++) {
		int k = i;
		mark[i] = true;
		for (int j = 0; j < p; j++)
		{
			if (search(tree[i], key[j]) == false) {
				mark[i] = false;
			}
		}
		if (mark[i] == true && search(tree[i], key[p]) == true &&count<=5) {
			cout << path << k << endl << endl;
			count++;
		}
		if (k < 10) {
			path = "Group13News0";
		}
		else {
			path = "Group13News";
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (mark[i]==true)
		{
			final = true;
		}
	}
	if (final == false) {
		cout << "NOT FOUND THIS KEYWORD...:( " << endl;
	}
}

