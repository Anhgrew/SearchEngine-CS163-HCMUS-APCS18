#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;
struct Node {
	Node* children[42];
	bool isLeaf, isTitle;
	vector<int> order;
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
	void InputListFile(vector<Node*>&root);
	void InputFile(Node*& root, ifstream& file);
	void InsertStopword(Node*& root);
	void InputSen(Node*& root, string sen, int& start, bool title);
	bool searchRoot(Node* root, string query, Node* stopword, vector<int>& pos, int& score);
	void Init(vector<Node*>&root, Node* &stopword);
	bool isstopword(Node *& root, string &stopword);
	void removing_stopword(string &key, Node *& stopword);
	bool checkOperator(string query);
	string SenFilter(string sen);
	void OutputResult(string filename, vector<int> pos);
};
void loading(int x, int y);
void VeKhungCH(int x, int y, int width, int height, bool draw);
void resizeConsole(int width, int height);


