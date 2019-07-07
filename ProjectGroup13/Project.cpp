#include "Project.h"

Node * base()
{
	Node *p = new Node;
	p->isword = false;
	for (int i = 0; i < Size; i++)
	{
		p->child[i] = NULL;
	}
	return p;
}


void insert(Node *& tree, char key[75])
{
	for (int i = 0; i < strlen(key); i++)
	{
		key[i] = tolower(key[i]);
	}
	Node *p = tree;
	for (int i = 0; i < strlen(key); i++)
	{
		int index = key[i] - 'a';
		if (!p->child[index]) {
			p->child[index] = base();
		}
		p = p->child[index];
	}
	p->isword = true;
}

void input(Node *&tree, Node *&treenext)
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
void resettree(Node * tree)
{
	if (tree == nullptr)return;
	for (int i = 0; i < Size; i++) {
		if (tree->child[i]) {
			delete tree->child[i];
		}
	}
	for (int i = 0; i < Size; i++)
	{
		if (tree->child[i]) {
			resettree(tree->child[i]);
		}
	}
	delete tree;
}

bool search(Node *tree, char key[75])
{
	Node* p = tree;
	if (p == NULL) return false;
	for (int i = 0; i < strlen(key); i++) {
		int index = key[i] - 'a';
		if (!p->child[index]) {
			return false;
		}
		p = p->child[index];
	}

	return (p != NULL && p->isword);
}

void search_filemark(Node *& tree, Node *& treenext, char key[75], bool mark[])
{
	ifstream fin;
	ostringstream convert;
	char word[75];
	string path = "Group13News0";
	fin.open("Group13News01.txt", ios::in);
	if (fin.fail()) {
		cout << "NOT FOUND" << endl;
	}
	while (!fin.eof())
	{
		fin.getline(word, 75, ' ');
		insert(tree, word);
	}
	int i = 1;
	if (search(tree, key) == true) {
		mark[1] = true;
	}
	else
	{
		mark[1] = false;
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
		if (search(tree, key) == true) {
			mark[i] = true;
		}
		else
		{
			mark[i] = false;
		}
		//resettree(treenext);//???? reset deo duoc
		fin.close();
	}

}
void outputfile(bool mark[])
{
	int count = 1;
	string path = "Group13News0";
	cout << "The key words was found in file: " << endl;
	if (mark[count] == true) {
		cout << path << "1"<< ".txt" << endl << endl;
	}
	for (int i = 2; i < 12; i++) {
		int k = i;
		if (mark[i] == true && count <= 4) {

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

