#include "Project.h"

Node* Engine::getNode() {
	Node* pNode = NULL;
	pNode = new Node;
	if (pNode) {
		pNode->isLeaf = false;
		pNode->isTitle = false;
		for (int i = 0; i < 42; ++i) pNode->children[i] = NULL;
	}
	return pNode;
}
string Engine::NumberToString(int num) {
	stringstream ss;
	ss << num;
	return ss.str();
}
string FloatToString(float num) {
	stringstream ss;
	ss << num;
	return ss.str();
}
void Engine::insertWord(Node* &root, string key, int place, bool title) {
	Node* p = root;
	int index, length = key.length();
	for (int i = 0; i < length; ++i) {
		index = convert(key[i]);
		if (index == -1) continue;
		if (!p->children[index]) p->children[index] = getNode();
		p = p->children[index];
	}
	p->isLeaf = true;
	p->order.push_back(place);
	if (title) p->isTitle = true;
}
void Engine::addfile(vector<Node*>& root, string namefile, Node*& p)
{
	bool check = true;
	ifstream fin;
	ofstream fout;
	fin.open(namefile);
	if (!fin)
	{
		cout << "NOT FOUND" << endl;
		check = false;
	}
	else {
		fin.close();
		fin.open("___index.txt", ios::in);
		string tmp;
		if (!fin.is_open())
		{
			cout << "WRONG FILE NAME OR FILE IS NOT EXISTING IN THE PROJECT!!!" << endl;
		}
		else {
			while (getline(fin, tmp)) {
				if (tmp == namefile)
				{
					cout << "THIS FILE WAS ADDED PREVIOUSLY" << endl;
					check = false;
				}
			}
		}
	}
	fin.close();
	if (check)
	{
		fout.open("___index.txt", ios::app);
		if (!fout.is_open())
		{
			cout << "CAN'T OPEN THE SYSTEM TO ADD A NEW FILE" << endl;
		}
		else {
			fout << endl;
			fout << namefile;
		}
		fout.close();
		p->name_file = namefile;
		clock_t start1, end1;

		fin.open(namefile, ios::in);
		if (!fin.is_open())
		{
			cout << "WRONG FILE NAME OR FILE IS NOT EXISTING IN THE PROJECT!!!" << endl;
		}
		else {
			start1 = clock();
			InputFile(p, fin);
			cout << "SUCCESSFULLY ADDED FILE !!! " << endl;
			fin.close();
			root.push_back(p);
			end1 = clock();

			cout << "INPUT A NEWFILE TIME: " << (float)(end1 - start1) / CLOCKS_PER_SEC << "s" << endl << endl;
			Sleep(1000);
		}
		fin.close();
	}
}
void Engine::insertStopword(Node* &root, string key) {
	Node* p = root;
	int index, length = key.length();
	for (int i = 0; i < length; ++i) {
		index = convert(key[i]);
		if (index == -1) continue;
		if (!p->children[index]) p->children[index] = getNode();
		p = p->children[index];
	}
	p->isLeaf = true;
}

Node* Engine::searchWord(Node* root, string key, bool title) {
	Node* p = root;
	int index, length = key.length();
	for (int i = 0; i < length; ++i) {
		index = convert(key[i]);
		if (index == -1) continue;
		if (!p->children[index]) return NULL;
		p = p->children[index];
	}
	if (p) {
		if (title && !p->isTitle) return NULL;
		if (p->isLeaf) return p;
	}
	return NULL;
}

int Engine::convert(char key) {
	if (key >= 48 && key <= 57) return (key - '0');
	if (key >= 97 && key <= 122) return (int(key) - 87);
	if (key >= 65 && key <= 90) return (int(key) - 55);
	if (key == ' ') return 36;
	if (key == '.') return 37;
	if (key == '$') return 38;
	if (key == '%') return 39;
	if (key == '#') return 40;
	if (key == '-') return 41;
	return -1;
}
bool Engine::accept(char& key) {
	if (key >= 65 && key <= 90) {
		key = int(key) + 32;
		return true;
	}
	if ((key >= 48 && key <= 57) || (key >= 97 && key <= 122)) return true;
	if (key == '\n') {
		key = ' '; return true;
	}
	if (key == '—') {
		key = '-'; return true;
	}
	if (key == ' ' || key == '$' || key == '%' || key == '#' || key == '-') return true;
	return false;
}
bool Engine::isNumber(char key) {
	if (key >= 48 && key <= 57) return true;
	return false;
}
bool Engine::isWord(char key) {
	if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)) return true;
	return false;
}
void Engine::DeleteTries(Node* & root) {
	if (!root) return;
	for (int i = 0; i < 38; ++i) {
		DeleteTries(root->children[i]);
	}
	delete root;
}
