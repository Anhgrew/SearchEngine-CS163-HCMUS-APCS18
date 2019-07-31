#include"Project.h"
#include"console.h"
#include<conio.h>
using namespace std;
int main() {//Khanh
	
	resizeConsole(1700,820);
	Engine search;
	vector<Node*> root;
	Node* stopword = search.getNode();
	Node *addafile = search.getNode();
	TextColor(15);
	search.Init(root, stopword);
	cout << endl;
	system("pause");
	system("cls");
	TextColor(14);
	ifstream fin;
	fin.open("New Text Document.txt", ios::in);
	while (!fin.eof())
	{

		char a;
		fin.get(a);
		cout << a;
	}
	system("color 245");
	fin.close();
	TextColor(10);
	VeKhungCH(0, 0, 210, 57, true);
	system("pause");
	system("cls");
	clock_t begin, end1, end2;
	while (1) {
		int NumOfRes = 0;
		cout << "0. Exit" << endl;
		cout << "1. Input query from keyboard" << endl;
		cout << "2. Clear history" << endl;
		cout << "3. Add a new file" << endl;
		cout << "4. View file data" << endl;
		cout << "OPTION:   ";
		int choice; 
		cin >> choice;
		system("cls");
		cin.ignore();
		if (!choice) break;
		if (choice == 4)
		{
		
			ifstream fin;
			string namefile;
			cout << "Enter the file name that you wanna view data: " << endl;
			getline(cin, namefile);
			string tmp;
			system("cls");
			fin.open(namefile, ios::in);
			if (!fin.is_open())
			{
				cout << "WRONG FILE NAME OR FILE IS NOT EXISTING IN THE PROJECT!!!" << endl;
				continue;
			}
			else {
				cout << namefile << endl;
				while (!fin.eof()) {
					getline(fin, tmp, '.');
					cout << tmp;
				}
			}
		}
		if (choice == 3) {
			string namefile;
			cout << "Enter a new file name: " << endl;
			cin >> namefile;
			cin.ignore();
			search.addfile(root, namefile, addafile);
			Sleep(500);
			system("cls");
			continue;
		}
		if (choice == 2) {
			clearHistory();
			cout << "History has been cleared..............." << endl << endl;
			Sleep(500);
			system("cls");
			continue;
		}
		string query;
		cout << "Query:";
		getline(cin, query);
		search.removing_stopword(query, stopword);
		if (query.length()==0)
		{
			break;
		}
		cout << "0. Search" << endl;
		cout << "1. Show history suggestion" << endl;
		cout << "OPTION:   ";
		cin >> choice;
		cin.ignore();
		system("cls");
		if (choice) {
			vector<string> res;
			History(res, query);
			cin >> choice; 
			cin.ignore();
			if (choice > res.size() - 1) {
				cout << "Invalid" << endl;
				choice = 0;
			}
			query = res[choice];
		}
		else {
			ofstream output;
			output.open("history.txt", ios::app);
			output << query << endl;
			output.close();
		}
		begin = clock();
		vector<string> syno;
		if (query[0] == '~') syno = search.getSyno(query.substr(1));
		bool check = search.checkOperator(query);
		vector<Store> prior, result;
		for (int i = 0; i < 100; ++i) {	//size+1 file dk add
			Store File;
			File.score = 0;
			if (query[0] == '~') {
				if (search.searchSyno(root[i], query.substr(1), File.pos, syno)) {
					++NumOfRes;
					File.filename = root[i]->name_file;
					prior.push_back(File);
				}
				continue;
			}
			if (check) {
				string exact = '"' + query + '"';
				if (search.searchRoot(root[i], exact, stopword, File.pos, File.score)) {
					++NumOfRes;
					File.filename = root[i]->name_file;
					prior.push_back(File);
					continue;
				}
			}
			bool res = search.searchRoot(root[i], query, stopword, File.pos, File.score);
			if (res) {
				++NumOfRes;
				File.filename = root[i]->name_file;
				result.push_back(File);
			}
		}

		end1 = clock();
		sort(prior.begin(), prior.end(), CompareByScore);
		sort(result.begin(), result.end(), CompareByScore);
		int count = 0;
		TextColor(15);
		for (int i = 0; i < prior.size(); ++i) {
			cout << prior[i].filename << endl << endl << endl;
			search.OutputResult(prior[i].filename, prior[i].pos);
			cout << "Score:" << prior[i].score << endl << endl;
			count++;
			cout << "--------------------------------------------------------------------------------------------------------------------\n";
			if (count == 5)break;
		}
		int count1 = 0;
		cout << "====================================================================================================================\n";
		for (int i = 0; i < result.size(); ++i) {
			cout << result[i].filename << endl << endl << endl;
			search.OutputResult(result[i].filename, result[i].pos);
			cout << "Score:" << result[i].score << endl << endl;
			count1++;
			if (count1 == 5)break;
			cout << "--------------------------------------------------------------------------------------------------------------------\n";
		}
		end2 = clock();
		cout << "Total result(s): " << NumOfRes << endl;
		cout << "Search time: " << (float)(end1 - begin) / CLOCKS_PER_SEC << "s" << endl;
		cout << "Output time: " << (float)(end2 - begin) / CLOCKS_PER_SEC << "s" << endl << endl;
	}
	TextColor(10);
	cout << "Destructor is running..." << endl;
	search.destructor(root, stopword);
	system("pause");
	return 0;
}