#include "Project.h"

void Node::insert(Node *& tree, char key[75])
{
	struct Node *p = tree;

	for (int i = 0; i <strlen(key); i++)
	{
		int index = key[i] - 'a';
		if (!p->child[index])
			p->child[index] = new Node();

		p = p->child[index];
	} 
	p->isword = true;
}

void Node::input(ifstream &fin, Node *&tree, Node *&treenext)
{	   
	ostringstream convert;
	char word[75];
	string path = "Group01News0";
	fin.open("Group01News01.txt", ios::in);
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
			path = "Group01News0";
		}
		else {
			path = "Group01News";
		}
		fin.close();
	}
	
}

void Node::resettree(Node * tree)
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

bool Node::search(Node *tree, char key[75])
{
	
		 Node* p = tree;

		for (int i = 0; i < strlen(key); i++) {
			int index = key[i] - 'a';
			if (!p->child[index])
				return false;

			p = p->child[index];
		}

		return (p != NULL && p->isword);
}

