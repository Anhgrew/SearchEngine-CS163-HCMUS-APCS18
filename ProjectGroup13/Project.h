#pragma once
#include <iostream>
#include<vector>
#include <fstream>
#include<string>
#include<sstream>
#include<string.h>
const int Size = 28;
using namespace std;
#define Project_h_
#ifdef Project_h_
class Node {
	Node *child[Size];
	bool isword;
	Node() {
		Node *p = new Node;
		isword = false;
		for (int i = 0; i < Size; i++)
		{
			p->child[i] = NULL;
		}
	}
	void insert(Node *&tree, char key[75]);
	void input(ifstream &fin, Node *&tree, Node *& treenext);
	void resettree(Node *tree);
	bool search(Node *tree, char key[75]);
};

#endif // !	Project_h_

