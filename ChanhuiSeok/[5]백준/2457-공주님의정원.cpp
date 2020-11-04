#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;

vector<pair<int, int>> flower;

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) {
		int m1, d1, m2, d2;
		cin >> m1 >> d1 >> m2 >> d2;
		flower.push_back(make_pair(m1 * 100 + d1, m2 * 100 + d2));
	}

	sort(flower.begin(), flower.end());

	int startTime = 301, endTime = 1130;
	int time = startTime;
	bool flag = true;
	int idx = -1, result = 0, tmpTime = 0;

	while (time <= endTime) {
		if (idx >= (int)flower.size()) break;

		flag = false;
		idx += 1;

		// time�� �����ϰ�, ���̰� ���� �� �� ����
		for (int k = idx; k < flower.size(); k++) {
			// ���� ��¥��, ���� ���� ������ ���� �� ���� ���
			if (time < flower[k].first) break;

			// �� ���� �ű��
			if (time >= flower[k].first && tmpTime < flower[k].second) {
				tmpTime = flower[k].second;
				flag = true;
				idx = k;
			}
		}

		// ������ �� �ִ� ���� �־��� ���
		if (flag) {
			time = tmpTime; // ���� ��¥�� �� ���� ������ ��¥�� ����
			result++;
		}
		// ������ �� �ִ� ���� ������ ��� �� ���̿� �� ��¥�� �ִ�.
		else {
			cout << 0;
			return 0;
		}
	}

	cout << result;
	return 0;
}
