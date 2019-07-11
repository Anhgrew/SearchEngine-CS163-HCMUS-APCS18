#include "Project.h"
Node * baseNode()
	{
		Node* p = new Node;
		p->endword = false;
		return p;
	}


void insert(Node*& tree, char key[75])
{
	if (tree == nullptr) {
		tree = baseNode();
	}
	Node* temp = tree;
	for (int i = 0; i < strlen(key); i++) {
		if (temp->map.find(key[i]) == temp->map.end())
			temp->map[key[i]] = baseNode();

		temp = temp->map[key[i]];
	}
	temp->endword = true;
}

/*void input(Node *&tree, Node *&treenext)
{
	ifstream fin;
	ostringstream convert;
	char word[75];
	string path = "Group13News0";
	fin.open("Group13News01.txt", ios::in);
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
			path = "Group13News0";
		}
		else {
			path = "Group13News";
		}
		fin.close();
	}
}
	*/
bool search(Node *tree, char key[75])
	{
		if (tree == nullptr)
			return false;

		Node* temp = tree;
		for (int i = 0; i < strlen(key); i++) {
			temp = temp->map[key[i]];
			if (temp == nullptr) {
				return false;
			}
		}
		return temp->endword;
}
void inputfile(Node *& tree, treearr & treenext)
{
	ifstream fin;
	ostringstream convert;
	char word[75];
	string path = "Group13News0";
	fin.open("Group13News01.txt", ios::in);
	int i = 0;
	while (!fin.eof())
	{
		fin.getline(word, 75, ' ');
		insert(tree, word);
	}
	fin.close();

	Node *treeafter_1 = baseNode();	// van de cay moi duoc tao.... dcm hay la tim cach doi ten de tao ra 
	//100 cay khac nhau nhu kieu doi ten tap tin de nhap file vay, doc code di thang lol.
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
			insert(treeafter_1, word);
		}
		treenext.arraytree.push_back(treeafter_1); // them cay vao mang cay nhung cay cu hinh nhu chua duoc xoa nen no luu vo cay cu roi them vao chuoi cay 2 cay lam 1->search sai.
	if (k < 10) {						  
			path = "Group13News0";
		}
		else {
			path = "Group13News";
		}
		fin.close();  
	}
}				
void outputfile(Node *tree, treearr &treenext,char key[75])
{
	int count = 1;
	string path = "Group13News0";
	cout << "The key words was found in file: " << endl;
	if (search(tree,key) == true) {
		cout << path << "1"<< ".txt" << endl << endl;
	}
	else {
		count = 0;
	}
	for (int i = 2; i < 4; i++) {
		int k = i;
		if (search(treenext.arraytree.at(i),key)==true && count <= 4) {
			cout << path << i << ".txt" << endl << endl;
			count++;
		}
		if (k < 10) {
			path = "Group13News0";
		}
		else {
			path = "Group13News";
		}
	}
}

