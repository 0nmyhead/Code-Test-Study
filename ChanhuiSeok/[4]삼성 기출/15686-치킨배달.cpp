#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

/* ġŲ ��� ���� (next_permutation Ȱ��) */

int arr[51][51];
vector<pair<int, int>> store;
vector<pair<int, int>> house;
vector<int> ind;

int pathLength(int r1, int c1, int r2, int c2) {
	return abs((r1 - r2)) + abs((c1 - c2));
}

int main() {

	int N, M, res_sum_chicken = 1000001;
	cin >> N >> M;
	// N�� ������ ũ�� N X N, M�� ġŲ�� �ִ� M�� ����

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) store.push_back({ i,j });
			if (arr[i][j] == 1) house.push_back({ i,j });
		}
	}
	
	// 1������ ~ M�� �����Ű�� ���� ������ ��� ����� ���� ������ ���Ѵ�
	for (int k = 1; k <= M; k++) {

		int store_size = store.size();
		int house_size = house.size();

		for (int i = 0; i < k; i++)
			ind.push_back(1);
		for (int i = 0; i < store_size - k; i++)
			ind.push_back(0);

		sort(ind.begin(), ind.end());

		int tmp_sum = 0;
		int tmp_sum_chicken = 100001;
		
		// �ּ� 1������ �ִ� M������ ������ ����
		do {
			// ��� ���� ���� ġŲ�Ÿ� ���ϱ�
			for (int j = 0; j < house_size; j++) {
				int temp = 100001;
				// ��� ����� ġŲ���� �ƴ� ���, j��° ���� ġŲ������ �Ÿ� ���ϱ�
				for (int i = 0; i < store_size; i++) {
					// �����Ű�� ���� ġŲ�� ����
					if (ind[i] == 1) {
						temp = min(temp, pathLength(house[j].first, house[j].second,
							store[i].first, store[i].second));
					}
				}
				tmp_sum += temp;
			}
			tmp_sum_chicken = min(tmp_sum_chicken, tmp_sum);
			tmp_sum = 0;

		} while (next_permutation(ind.begin(), ind.end()));

		res_sum_chicken = min(res_sum_chicken, tmp_sum_chicken);
		tmp_sum = 0;
		ind.clear(); // ���ο� ���̽� ���� ����
	}

	cout << res_sum_chicken;

	return 0;
}