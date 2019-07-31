#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<sstream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;
struct Node {
	Node* children[42];	//0-9:number,10-35:words,36:maybe :,37:.(for so thap phan), 38:$, 39:%, 40:#, 41:-
	bool isLeaf, isTitle;
	vector<int> order;	//place it appears
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
	void InputListFile(vector<Node*>&root);
	void InputFile(Node*& root, ifstream& file);
	void InsertStopword(Node*& root);
	void InputSen(Node*& root, string sen, int& start, bool title);
	bool searchRoot(Node* root, string query, Node* stopword, vector<int>& pos, int& score);
	int convert(char key);
	bool accept(char& key);
	bool isNumber(char key);
	bool isWord(char key);
	void DeleteTries(Node* & root);
	void exact(vector<int>& v1, vector<int>& v2, int cnt, vector<int>& out1, vector<int>& out2);
	string SenFilter(string sen);
	void OutputResult(string filename, vector<int> pos);
	void Init(vector<Node*>&root, Node* &stopword);
	void searchIncomplete(Node* root, string key, vector<int>& res);
	void findIncomplete(Node* root, vector<int>& res);
	void findNumber(Node* root, string number, double lowbound, double upbound, vector<int>& pos);
	bool getRange(string tmp, double& lowbound, double& upbound);
	bool checkOperator(string query);
	vector<int> corporator(vector<int>& v1, vector<int>& v2);
	void destructor(vector<Node*>&root, Node* &stopword);
	vector<string> getSyno(string key);
	bool searchSyno(Node* root, string key, vector<int>& res, vector<string>& syno);
	bool isstopword(Node *& root, string &stopword);
	void removing_stopword(string &key, Node *& stopword);
};
bool CompareByScore(const Store&a, const Store&b);
int WordinSen(string sen);
void History(vector<string>& res, string query);
void clearHistory();