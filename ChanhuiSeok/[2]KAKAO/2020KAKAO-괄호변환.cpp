
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;
typedef pair<string, string> ps;

string tempStr = "";

ps split(string p) { // �������� ���ڿ��� �и��ϴ� �Լ�

	ps partial;
	string tempStr = "";
	int splitIdx = 0;
	stack <char> s;

	for (int i = 0; i < p.length(); i++) {
		if (!s.empty() && s.top() == '(' && p[i] == ')') {
			s.pop();
			tempStr += p[i];
			splitIdx = i;
		}
		else if (!s.empty() && s.top() == ')' && p[i] == '(') {
			s.pop();
			tempStr += p[i];
			splitIdx = i;
		}
		else if (p[i] == '(' || p[i] == ')') {
			s.push(p[i]);
			tempStr += p[i];
		}
		if (s.empty()) break;
	}

	partial.first = tempStr;
	partial.second = p.substr(splitIdx + 1);
	return partial;
}

bool isCorrect(string p) { // �ùٸ� ��ȣ���� �Ǵ��ϱ�

	bool flag = false;
	stack <char> s;

	if (p[0] != '(')
		return false;
	for (int i = 0; i < p.length(); i++) {
		if (p[i] == '(') s.push(p[i]);

		else if (!s.empty() && s.top() == '(' && p[i] == ')')
			s.pop();
	}
	if (s.empty())
		flag = true;
	return flag;
}


string recursion(string p) {

	ps originStr; // u, v�� ���ԵǴ� pair

	if (p == "")
		return p;

	originStr = split(p); // ���⿡ ���°� �ùٸ� ���ڿ��� �ƴ϶� ��, p ���ڿ� �и�

	if (isCorrect(originStr.first)) { // 3. u�� �ùٸ� ���ڿ��̶��
		return originStr.first + recursion(originStr.second); // 3-1. v�� ���� �ٽ� ���� �� u�� �̾� ���δ�.
	}

	else if (!isCorrect(originStr.first)) { // 4. u�� �ùٸ� ���ڿ��� �ƴ϶��
		string result = "";
		string temp = "";
		temp += "("; // 4-1. �� ���ڿ��� ( �� ���Դϴ�.
		temp += recursion(originStr.second); // 4-2. v�� ���� �ٽ� ������ ��� ���ڿ��� �̾� ���Դϴ�.
		temp += ")"; // 4-3. )�� �ٽ� ���Դϴ�.

		// u�� ù ��° ���ڿ� ������ ���ڸ� ������ ��
		// ���� ���ڿ��� ��ȣ ������ ������, temp �� �ڿ� ���Դϴ�.
		result = originStr.first.substr(1, originStr.first.size() - 2);
		for (int i = 0; i < result.length(); i++) {
			if (result[i] == '(')
				result[i] = ')';
			else if (result[i] == ')')
				result[i] = '(';
		}
		temp += result;

		return temp;
	}

}

string solution(string p) {
	string result;
	bool flag;
	flag = isCorrect(p);

	if (flag) return p;
	result = recursion(p);
	return result;

}