#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <functional>
#include <cstring>

using namespace std;

int output[1001];
int hex2dec(string hex)
{
	int len = hex.size();
	int base = 1, ret = 0;
	for (int i = len - 1; i >= 0; i--) {
		if (hex[i] >= '0' && hex[i] <= '9') ret += (hex[i] - 48) * base;
		else if (hex[i] >= 'A' && hex[i] <= 'F') ret += (hex[i] - 55) * base;
		base *= 16; // ���� �ڸ� �Ѿ��
	}
	return ret;
}

int main() {
	string input;
	int N, T, K, rotate_cnt;

	cin >> T;
	set<int, greater<int>> data; // �����Ͱ� ������������ ���� ��
	set<int, greater<int>>::iterator iter;

	for (int t = 0; t < T; t++) {
		cin >> N >> K; // ������ ���� N(4�� ���, 8~28)�� ũ�� ���� K
		cin >> input;
		rotate_cnt = N / 4;
		int hexToDec = 0;

		//rotate Ƚ����ŭ ���ƺ���.
		for (int k = 0; k < rotate_cnt; k++) {
			string changed_temp;
			char last_str = input[input.size() - 1];

			for (int j = 0; j < N; j = j + rotate_cnt) {
				string temp = input.substr(j, rotate_cnt);
				hexToDec = hex2dec(temp);
				data.insert(hexToDec);
			}
			// �� ȸ�� �� ������ 16���� 10���� ��ȯ �Ϸ�, ���� �ð� �������� ȸ����Ű��
			input.pop_back();
			changed_temp = last_str + input;
			input = changed_temp;
		}

		// ��� �� ���� ���� set�� �����Ͱ� ����Ǿ� �ִ�. set�� �����͸� ���ʴ�� �迭�� �־� ����.
		int idx = 0;
		for (iter = data.begin(); iter != data.end(); iter++)
			output[idx++] = *iter;
		cout << "#" << t + 1 << " " << output[K - 1] << '\n';
		data.clear();
	}
}