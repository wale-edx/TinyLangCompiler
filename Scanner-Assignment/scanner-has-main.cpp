#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

bool isSpace(char s) { 
	return (s == ' ' || s == '\t' || s == '\n'); 
}

bool isSymbol(char c) { 
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '(' || c == ')' || c == ';' || c == ':='); 
}


enum states { start, comment, numbers, id, assignment, stop};

string RES_WORDS[] = { "read","write","if","then","else","end","repeat","until" };

states state = start; 

void getToken(string l)
{
	string mytoken;
	state = start;
	bool flag = 0;
	int i = 0;
	while (state != stop) {
		switch (state) {
		case start:
			if (isSpace(l[i])) {
				i++;
				if (i == l.length()) state = stop;
				else state = start;
			}
			else if (isdigit(l[i])) {
				state = numbers;
			}
			else if (isalpha(l[i])) {
				state = id;
			}
			else if (l[i] == ':') {
				state = assignment;
			}
			else if (l[i] == '{') {
				i++;
				state = comment;
			}
			else if (isSymbol(l[i])) {
				switch (l[i]) {
				case '+': cout << l[i] << "\t >>  plus symbol" << endl; break;
				case '-': cout << l[i] << "\t >>  minus symbol" << endl; break;
				case '*': cout << l[i] << "\t >>  multiply symbol" << endl; break;
				case '/': cout << l[i] << "\t >>  divide symbol" << endl; break;
				case '=': cout << l[i] << "\t >>  equal symbol" << endl; break;
				case '<': cout << l[i] << "\t >>  less than symbol" << endl; break;
				case '(': cout << l[i] << "\t >>  left bracket symbol" << endl; break;
				case ')': cout << l[i] << "\t >>  right bracket symbol" << endl; break;
				case ';': cout << l[i] << "\t >>  semicolon symbol" << endl; break;
				default: cout << l[i]  << "\t >>  special symbol"; break;
				}
				i++;
				if (i == l.length()) state = stop;
				else state = start;
			}
			else state = stop;
			break;

		case comment:
			if (state == comment) {
				while (l[i] != '}') {
					i++;
				}
				i++;
				if (i == l.length()) state = stop;
				else state = start;
			}
			break;

		case numbers:
			while (isdigit(l[i])) {
				mytoken += l[i];
				i++;
			}
			cout << mytoken << "\t >>  digit" << endl;
			mytoken = "";
			if (i == l.length()) state = stop;
			else state = start;
			break;

		case id:
			while (isalpha(l[i])) {
				mytoken += l[i];
				i++;
			}
			for (int i = 0; i < 8; i++)
			{
				if (RES_WORDS[i] == mytoken) flag = 1;
			}
			if (flag) cout << mytoken << "\t >>  reserved word" << endl;
			else cout <<mytoken <<"\t >>  identifier" << endl;
			mytoken = "";
			flag = 0;
			if (i == l.length()) state = stop;
			else state = start;
			break;

		case assignment:
			if (l[i] == ':') {
				i += 2;
				cout << ":=" << "\t >>  assignment" << endl;
				state = start;
			}
			else {
				if (i == l.length()) state = stop;
				else state = start;
			}
			break;
		case stop:
			break;
		}
	}
}


int main() {
	
	ifstream f;
	string line;
	
	f.open("test_code.txt");
	while (!f.eof()) {
		getline(f, line);
		getToken(line);
		cout << endl;
	}
	
	system("pause");
	return 0;
}
