#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include <unordered_map> 
const int Size = 28;
using namespace std;
#define Project_h_
#ifdef Project_h_
using namespace std;
struct Node {
	bool endword;
	unordered_map<char, Node*> map;
};
struct treearr {
	vector<Node*> arraytree;
};
Node *baseNode();
void insert(Node*& tree, char key[75]);
bool search(Node* tree, char key[75]);
void inputfile(Node *&tree,treearr &treenext);
void outputfile(Node *tree, treearr &treenext, char key[75]);
#endif // !	Project_h_

