#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <stack>
#include <string>

using namespace std;

int arr[21][21];
int visit[21];
int N;

int minV = 987654321;

vector<int> teamA, teamB;

// ���� ���� ���� ���� �Լ�
void dfs(int idx, int cnt) {

	// ������ ��� ������ ��
	if (cnt == N / 2) {
		for (int i = 1; i <= N; i++) {
			if (visit[i] == 1)
				teamA.push_back(i);
			else {
				teamB.push_back(i);
			}
		}
		// teamA, teamB�� ���� ��
		// �� ���鿡�� ���� �� �ִ� ��� ���� ���Ѵ�.
		int a_sum = 0;
		int b_sum = 0;

		for (int i = 0; i < teamA.size(); i++) {
			for (int j = i + 1; j < teamA.size(); j++) {
				int t1 = teamA[i];
				int t2 = teamA[j];

				a_sum += arr[t1][t2];
				a_sum += arr[t2][t1];
			}
		}

		for (int i = 0; i < teamB.size(); i++) {
			for (int j = i + 1; j < teamB.size(); j++) {
				int t1 = teamB[i];
				int t2 = teamB[j];

				b_sum += arr[t1][t2];
				b_sum += arr[t2][t1];
			}
		}

		int res = abs(a_sum - b_sum);
		minV = min(minV, res);
		return;
	}

	for (int i = idx; i <= N; i++) {	
		if (visit[i] == 1) continue;	
		visit[i] = 1;

		dfs(i, cnt + 1);
		visit[i] -= 1;	
		teamA.clear(); teamB.clear();
	}

}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> N;

	for (int i = 1; i <= N; i++) {
		for(int j = 1; j<=N; j++)
			cin >> arr[i][j];
	}

	// �������� �����...
	// 4���̸� 1,2,3,4 �� �� ������ ������
	// 6���̸� 1,2,3,4,5,6 �� �� ������ ������...
	

	dfs(1, 0);
	
	cout << minV;

	return 0;
}