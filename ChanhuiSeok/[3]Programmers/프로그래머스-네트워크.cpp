#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int visit[200];

void dfs(int Idx, int n, vector<vector<int>>& computers) {
	visit[Idx] = 1; // ó�� ������ �湮

	for (int i = 0; i < n; i++) {
		if (visit[i] != 1 && computers[Idx][i] == 1) { // �̵� ����
			dfs(i, n, computers);
		}
	}

}

int solution(int n, vector<vector<int>> computers) {
	int network = 0;

	for (int i = 0; i < n; i++) {
		if (visit[i] != 1) {
			dfs(i, n, computers);
			network++;
		}
	}
	return network;
}