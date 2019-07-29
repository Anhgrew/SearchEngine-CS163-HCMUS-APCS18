#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;
struct Node {
	Node* children[42];//0-9:number,10-35:words,36:maybe :,37:.(for so thap phan), 38:$, 39:%, 40:#, 41:-
	bool isLeaf, isTitle;
	vector<int> order;//place it appears
	string name_file;
};
struct Store {
	string filename;
	vector<int> pos;
	int score;
};
class Engine {
public:
	Node* getNode();
	void addfile(vector<Node*>& root, string namefile, Node *&p);
	string NumberToString(int num);
	void insertWord(Node* &root, string key, int place, bool isTitle);
	void insertStopword(Node* &root, string key);
	Node* searchWord(Node* root, string key, bool title);
	int convert(char key);
	bool accept(char& key);
	bool isNumber(char key);
	bool isWord(char key);
	void DeleteTries(Node* & root);
};


