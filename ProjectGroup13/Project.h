#pragma once
#include <iostream>
#include<vector>
#include <fstream>
#include<string>
#include<sstream>
#include<string.h>
#include<stdio.h>
#include<conio.h>
const int Size = 28;
using namespace std;
#define Project_h_
#ifdef Project_h_
class Node {
public:
	Node *child[Size];
	bool isword;

};
Node *base();
Node *createNode(char key[75]);
	
void insert(Node *&tree, char key[75]);
void input(Node *&tree, Node *& treenext);
void resettree(Node *tree);
bool search(Node *tree, char key[75]);
void search_filemark(Node *&tree, Node *&treenext, char key[75], bool mark[]);
void outputfile(bool mark[]);
#endif // !	Project_h_

