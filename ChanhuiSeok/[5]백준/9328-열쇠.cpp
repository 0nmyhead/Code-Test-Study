#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <string>
#include <map>
#include <cstring>

using namespace std;

#define pii pair<int, int>

int h, w;
char arr[111][111];
int visit[111][111];

vector<int> answer;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	string tmp;
	cin >> T;

	for (int t = 0; t < T; t++) {
		cin >> h >> w; // ���� h, �ʺ� w

		memset(arr, 0, sizeof(arr));
		for (int i = 1; i <= h; i++) {
			for (int j = 1; j <= w; j++) {
				cin >> arr[i][j];
			}
		}

		map<char, int> maps; // ���� ������ �����ϴ� ��ųʸ�
		// ���ĺ� ��ųʸ� - ���� �������� ������ ��ųʸ� �ʱ�ȭ
		for (int i = 0; i < 26; i++) maps['A' + i] = 0;

		cin >> tmp;
		if (tmp != "0") {
			for (int i = 0; i < tmp.size(); i++) maps[toupper(tmp[i])] = 1;
		}
		// visit �ʱ�ȭ
		memset(visit, false, sizeof(visit));

		map<char, vector<pii>> door; // ���� ��ġ�� �����ϴ� ��ųʸ�
		queue<pii> q;

		int res_cnt = 0;
		q.push({ 0,0 });

		while (!q.empty()) {
			int idy = q.front().first;
			int idx = q.front().second;
			q.pop();

			if (arr[idy][idx] == '$') res_cnt++;

			for (int i = 0; i < 4; i++) {
				int ty = idy + dy[i];
				int tx = idx + dx[i];
				// �湮�� �� ���� ���� ��󳻱�
				if (ty < 0 || tx < 0 || ty > h + 1 || tx > w + 1)
					continue;
				if (visit[ty][tx])
					continue;
				if (arr[ty][tx] == '*')
					continue;

				// ���̾��� ���
				if (isupper(arr[ty][tx])) {
					// ���̾��µ� ���谡 ���� ��� ��ġ�� door�� �����Ѵ�.
					if (maps[arr[ty][tx]] == 0) {
						door[arr[ty][tx]].push_back({ ty,tx });
						continue;
					}
				}

				// ���迴�� ���
				if (islower(arr[ty][tx])) {
					maps[toupper(arr[ty][tx])] = 1; // ���� ���� true
					// ���� ���谡 �� �� �ִ� ���� q�� �ִ´�.
					int dy, dx;
					for (int m = 0; m < door[toupper(arr[ty][tx])].size(); m++) {
						int dy = door[toupper(arr[ty][tx])][m].first;
						int dx = door[toupper(arr[ty][tx])][m].second;
						q.push({ dy,dx });
					}
				}
				// ���谡 �ִ� ���̾��ų� ��ĭ�̰ų� ������ ���
				visit[ty][tx] = true;
				q.push({ ty,tx });
			}
		}

		answer.push_back(res_cnt);
		door.clear();
	}

	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << '\n';

	return 0;
}