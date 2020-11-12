#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

unordered_map<string, int> maps;
string arr[27];

vector<int> solution(string msg) {
	vector<int> answer;

	string target;
	string copymsg = msg;
	string tmp = msg;
	int idx = 1;
	int endIdx = 27;
	int index = 0;

	while (!tmp.empty()) {
		// �������� ���� �Է°� ��ġ�ϴ� ���� �� ���ڿ� w ã��
		while (idx <= tmp.length()) {
			// ���� ���ڿ��� 1, 2, 3,... ���� ��� ã�ƺ���
			target = tmp.substr(0, idx);
			if (maps.count(target)) {
				index = maps[target];
				idx++;
				continue;
			}
			// �������� ã�� �� ���� ���
			else {
				// ���� �� ���ڿ��� ���� ��ȣ ����
				break;
			}
		}

		// ���� �� ���ڿ��� ���� ��ȣ�� index�� ����Ǿ� ����
		answer.push_back(index);

		// �Է¿��� w ����
		tmp = tmp.substr(idx - 1);

		// �Է¿��� ó������ ���� ���ڰ� ���� ������ ������ ����
		maps.insert({ target, endIdx++ });

		// idx �ʱ�ȭ
		idx = 1;
	}

	return answer;
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	// maps �ʱ�ȭ
	for (int i = 1; i <= 26; i++) {
		arr[i] = 'A' + i - 1;
		maps[arr[i]] = i;
	}

	vector<int> answer = solution("ABABABABABABABAB");

	return 0;
}