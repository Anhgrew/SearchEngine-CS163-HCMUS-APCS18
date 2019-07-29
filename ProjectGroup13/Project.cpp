#include "Project.h"
#include "console.h"

//return the new Node
//ASCII, 0:48, 9:57, A:65, Z:90, a:97, z:122

Node* Engine::getNode() {
	Node* pNode = NULL;
	pNode = new Node;
	if (pNode) {
		pNode->isLeaf = false;
		pNode->isTitle = false;
		for (int i = 0; i < 42; ++i) 
			pNode->children[i] = NULL;
	}
	return pNode;
}

// return number to string
string Engine::NumberToString(int num) {
	stringstream ss;
	ss << num;
	return ss.str();
}

// return float number to string
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

void Engine::InsertStopword(Node*& root) {
	ifstream file;
	string get;
	file.open("stopword.txt");
	if (!file.is_open()) return;
	while (!file.eof()) {
		getline(file, get, ' ');
		insertStopword(root, get);
	}
	file.close();
}

void Engine::insertStopword(Node* &root, string key) {
	Node* p = root;
	int index, length = key.length();
	for (int i = 0; i < length; ++i) {
		index = convert(key[i]);
		if (index == -1) continue;
		if (!p->children[index]) 
			p->children[index] = getNode();
		p = p->children[index];
	}
	p->isLeaf = true;
}

void Engine::removing_stopword(string& key, Node*& stopword)
{
	string tmp = " ";
	string result = "";
	stringstream newkey(key);
	string word;
	while (newkey >> word)
	{

		if ((!isstopword(stopword, word)) || (word == "AND" || word == "OR" || word == "intitle:" || word == "+and" || word == "filetype:txt" || word == "~" || word == "*"))
		{
			result += word;
			result += tmp;
		}
	}
	key = result;
}

string Engine::SenFilter(string sen) {
	string res;
	int length = sen.length();
	for (int i = 0; i < length; ++i) {
		if (!accept(sen[i])) {
			if (sen[i] == 39 && sen[i + 1] == 's'&&sen[i + 2] == ' ') ++i;
			else if (i + 1 != length && sen[i] == '.'&&isNumber(sen[i - 1]) && isNumber(sen[i + 1]))
				res.append(sen, i, 1);
		}
		else res.append(sen, i, 1);
	}
	return res;
}
void Engine::InputListFile(vector<Node*>& root) {
	ifstream fin;
	int k = 0;
	vector <string> namefileinput;
	fin.open("___index.txt", ios::in);
	int i = 0;
	string name_offile;
	root.resize(5);
	while (getline(fin, name_offile))
	{
		namefileinput.push_back(name_offile);
		k++;
	}
	fin.close();

	for (int i = 0; i < 5; i++)
	{
		system("cls");
		root[i] = getNode();
		root[i]->name_file = namefileinput[i];
		fin.open(root[i]->name_file, ios::in);
		InputFile(root[i], fin);
		cout << "|________________________________________________________LOADING______________________________________________________|                       " << endl;
		fin.close();
	}



}
void Engine::InputFile(Node*& root, ifstream& file) {
	int start = 0;
	string sen;
	getline(file, sen, '.');

	InputSen(root, sen, start, true);
	while (!file.eof()) {
		getline(file, sen, '.');
		if (sen.length() && isNumber(sen.back())) {
			string next;
			getline(file, next, '.');
			if (next.length() && isNumber(next[0])) {
				sen = sen + '.' + next;
				InputSen(root, sen, start, false);
				continue;
			}
			else {
				InputSen(root, sen, start, false);
				InputSen(root, next, start, false);
				continue;
			}
		}
		InputSen(root, sen, start, false);
	}
}
void Engine::InputSen(Node*& root, string sen, int& start, bool title) {
	sen = SenFilter(sen);
	if (!root) return;
	stringstream ss(sen);
	while (ss >> sen) {
		if (title) insertWord(root, sen, start, true);
		else insertWord(root, sen, start, false);
		++start;
	}
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
void Engine::OutputResult(string filename, vector<int> pos) {
	if (!pos.size()) return;
	ifstream file; file.open(filename);
	if (!file.is_open()) { cout << "Error" << endl; return; }
	string title; getline(file, title);
	cout << title << endl;
	file.clear();
	file.seekg(0, ios::beg);
	int cnt = 0, cur = 0, totalLength = -1;
	while (!file.eof()) {
		string tmp, res;
		getline(file, tmp, '.');
		if (tmp.length() && isNumber(tmp.back())) {
			string next; getline(file, next, '.');
			if (next.length() && isNumber(next[0])) {
				tmp = tmp + '.' + next;
			}
			else tmp = tmp + " " + next;
		}
		tmp = SenFilter(tmp);
		int NumWord = WordinSen(tmp);
		totalLength += NumWord;
		if (pos[cur] > totalLength) {
			cnt += NumWord;
			continue;
		}
		cout << "...";
		stringstream ss(tmp);
		while (ss >> tmp) {
			if (cur < pos.size() && pos[cur] == cnt) {
				++cur;
				for (int i = 0; i < tmp.length(); ++i) if (isWord(tmp[i])) tmp[i] -= 32;
				TextColor(78);
				cout << tmp << " ";
				TextColor(15);
			}
			else cout << tmp << " ";
			++cnt;
		}
		cout << "..." << endl;
		if (cur >= pos.size()) {
			file.close();
			return;
		}
	}
	file.close();
}

bool Engine::searchRoot(Node* root, string query, Node* stopword, vector<int>& pos, int& score) {
	stringstream ss(query);
	string tmp, get;
	while (ss >> tmp) {
		if (tmp[0] == '"') {
			vector<int> res;
			Node* res1 = searchWord(root, tmp, false), *res2;
			if (!res1) return false;
			if (tmp.back() == '"') {
				pos = corporator(pos, res1->order);
				score += res1->order.size();
				continue;
			}
			string tmp2;
			vector<int> tmp = res1->order;
			while (ss >> tmp2) {
				int cnt = 1;
				if (tmp2 == "") return true;
				if (tmp2 == "*") {
					++cnt;
					while (ss >> tmp2) {
						if (tmp2 == "*") ++cnt;
						else break;
					}
				}
				res2 = searchWord(root, tmp2, false);
				if (!res2) return false;
				vector<int> out1, out2;
				exact(tmp, res2->order, cnt, out1, out2);
				if (out1.empty()) return false;
				//res = corporator(res, corporator(out1, out2));
				if (tmp2.back() == '"') {
					score += out1.size();
					break;
				}
				tmp = out2;
			}
			pos = corporator(pos, res);
			continue;
		}
		if (tmp[0] == '-') {
			if (searchWord(root, tmp.substr(1), false)) return false;
			continue;
		}
		get = tmp.substr(0, 8);
		if (get == "intitle:") {
			get = tmp.substr(8);
			Node* title = searchWord(root, get, true);
			if (!title) return false;
			score += title->order.size();
			pos = corporator(pos, title->order);
			while (ss >> get) {
				title = searchWord(root, get, true);
				if (!title) return false;
				score += title->order.size();
				pos = corporator(pos, title->order);
			}
			continue;
		}
		Node* searchRes;
		if (tmp == "OR") {
			ss >> tmp;
			searchRes = searchWord(root, tmp, false);
			if (searchRes) {
				pos = corporator(pos, searchRes->order);
				score += searchRes->order.size();
			}
			continue;
		}
		searchRes = searchWord(root, tmp, false);
		if (tmp[0] == '+') {
			if (!searchRes) return false;
			pos = corporator(pos, searchRes->order);
			score += searchRes->order.size();
		}
		if (searchWord(stopword, tmp, false)) continue;
		if (tmp == "AND" || tmp == "filetype:txt") continue;
		if (tmp.back() == '*') {
			vector<int> res;
			searchIncomplete(root, tmp, res);
			if (res.empty()) return false;
			pos = corporator(pos, res);
			continue;
		}
		if (isNumber(tmp[0]) || tmp[0] == '$') {
			double lowbound, upbound;
			if (getRange(tmp, lowbound, upbound)) {
				string number;  vector<int> res;
				if (tmp[0] == '$') {
					if (!root->children[38]) return false;
					findNumber(root->children[38], number, lowbound, upbound, res);
					if (res.empty()) return false;
				}
				else findNumber(root, number, lowbound, upbound, res);
				if (res.empty()) return false;
				pos = corporator(pos, res);
				continue;
			}
		}
		if (!searchRes) {
			bool check = false;
			while (ss >> tmp) {
				if (tmp == "OR") {
					ss >> tmp;
					searchRes = searchWord(root, tmp, false);
					if (searchRes) {
						pos = corporator(pos, searchRes->order);
						score += searchRes->order.size();
						check = true;
						break;
					}
				}
				else return false;
			}
			if (!check) return false;
		}
		else {
			pos = corporator(pos, searchRes->order);
			score += searchRes->order.size();
		}
	}
	return true;
}
void Engine::Init(vector<Node*>&root, Node* &stopword) {
	clock_t load = clock();
	InputListFile(root);
	InsertStopword(stopword);
	clock_t end = clock();
	TextColor(160);
	cout << "   Loading time: " << (float)(end - load) / CLOCKS_PER_SEC << "s";
	TextColor(14);
}
bool Engine::checkOperator(string query) {
	stringstream ss(query);
	string tmp;
	while (ss >> tmp) {
		string get; get = tmp.substr(0, 8);
		if (get == "intitle:") return false;
		if (tmp == "AND" || tmp == "OR" || tmp[0] == '-' || tmp == "*" || tmp == "filetype:txt" || tmp[0] == '"' || tmp.back() == '*') return false;
		int length = tmp.length();
		for (int i = 0; i <= length - 3; ++i) {
			if (tmp[i] == '.'&&tmp[i + 1] == '.') return false;
		}
	}
	return true;
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
}  bool Engine::isstopword(Node *& root, string &stopword)
{
	if (searchWord(root, stopword, false) != NULL) return true;
	else return false;
}

void loading(int x, int y)
{
	TextColor(10);
	VeKhungCH(x - 18, y - 1, 57, 2, true);
	int i, c, d;
	char a = 177, b = 219;
	gotoXY(x + 8, y);
	cout << "LOADING";
	gotoXY(x + 1, y);
	for (i = 0; i < 55; i++) {
		c = rand() % 40;
		Sleep(c);
		cout << "\r\r";
		cout << "\t\t\t\t";
	}
	for (i = 0; i < 56; i++) {
		cout << b;
		d = rand() % 20;
		Sleep(d);
	}
	system("cls");
}
void VeKhungCH(int x, int y, int width, int height, bool draw) {
	if (draw) {
		gotoXY(x, y);
		cout << char(218);
		gotoXY(x + width, y);
		cout << char(191);
		gotoXY(x, y + height);
		cout << char(192);
		gotoXY(x + width, y + height);
		cout << char(217);
		for (int i = x + 1; i < (x + width); i++) {
			gotoXY(i, y);
			cout << char(196);
		}
		for (int i = x + 1; i < (x + width); i++) {
			gotoXY(i, y + height);
			cout << char(196);
		}
		for (int i = y + 1; i < (y + height); i++) {
			gotoXY(x, i);
			cout << char(179);
		}
		for (int i = y + 1; i < (y + height); i++) {
			gotoXY(x + width, i);
			cout << char(179);
		}
	}
	else {
		gotoXY(x, y);
		cout << " ";
	
		gotoXY(x + width, y);
		cout << " ";
	
		gotoXY(x, y + height);
		cout << " ";
	
		gotoXY(x + width, y + height);
		cout << " ";

	
		for (int i = x + 1; i < (x + width); i++) {
			gotoXY(i, y);
			cout << " ";
		}
	
		for (int i = x + 1; i < (x + width); i++) {
			gotoXY(i, y + height);
			cout << " ";
		}
	
		for (int i = y + 1; i < (y + height); i++) {
			gotoXY(x, i);
			cout << " ";
		}
		for (int i = y + 1; i < (y + height); i++) {
			gotoXY(x + width, i);
			cout << " ";
		}

	}
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
