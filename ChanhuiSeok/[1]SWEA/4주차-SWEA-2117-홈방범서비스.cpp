#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
int arr[21][21];
int cost[23];
vector <pair<int, int>> v;

int IsInScope(int y, int x, int k) {
	int house = 0;
	// ���� �ִ� ��ǥ�� �߽� ��ǥ���� ���..
	for (int i = 0; i < v.size(); i++) {
		if (abs(y - v[i].first) + abs(x - v[i].second) <= k - 1) {
			house++;
		}
	}
	return house;
}

int main() {

	int N, M, T;
	int MaxHouse = -100;
	int InScopeHouse = -1;

	scanf("%d", &T);

	for (int t = 1; t <= T; t++) {

		scanf("%d %d", &N, &M);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &arr[i][j]);
				if (arr[i][j] == 1)
					v.push_back({ i,j });
			}
		}

		// N�� ���� cost ���
		for (int i = 1; i <= N + 1; i++) {
			cost[i] = (i * i) + (i - 1) * (i - 1);
		}
		
		// ������ �߽��� �� ��ǥ�� (0,0) ���� (N-1,N-1)���� ��� ��������.
		for (int k = 1; k <= N + 1; k++) {

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					InScopeHouse = IsInScope(i, j, k);
					if ((InScopeHouse * M) - cost[k] >= 0
						&& InScopeHouse > MaxHouse) {
						MaxHouse = InScopeHouse;
					}
				}
			}
		}

		printf("#%d %d\n", t, MaxHouse);
		MaxHouse = -100;
		v.clear();
	}
}