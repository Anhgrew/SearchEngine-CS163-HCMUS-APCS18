#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include<string>
#include<sstream>
#include<string>
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
Node *baseNode();
void insert(Node*& tree,const string& key);
bool search(Node* tree,const string& key);
void inputfile(vector<Node *> &tree);
void outputfile(vector<Node *> &tree,string key[1000],int p);
#endif // !	Project_h_

