#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
int D, W, K;
int arr[14][21];
int copies[14][21];

//vector< vector<int>> arr(14);
//vector< vector<int>> copies(14);
vector < vector<int> > permuList;
vector <int> permu;

void solve(int subResult, int array[][21], vector<int>& cont) {
	for (int n = 0; n < W; n++) { // ��
		for (int m = 0; m < D - (K - 1); m++) { // �� - (K-1)��ŭ
			subResult = 0;
			for (int p = 0; p < K - 1; p++) {

				if (array[m + p][n] == array[m + p + 1][n])
					subResult += 1;
				else
					subResult = 0;
			}
			if (subResult == K - 1) {
				cont.push_back(1);
				break;
			}
		}
		if (subResult < K - 1) {
			cont.push_back(0);
		}
		subResult = 0;
	}
}

void make_permutation(int n, int cnt) {
	// n�� �ڸ����� �ǹ���. ��, 0�� 1 ������ n�ڸ� �ߺ������� ����� �д�.

	if (cnt == n) {
		//permu[idx].push_back();
		permuList.push_back(permu);
		return;
	}

	for (int i = 0; i < 2; i++) {
		permu.push_back(i);
		make_permutation(n, cnt + 1);
		permu.pop_back();
	}
}

int main() {

	int T;
	int indK, subResult = 0;
	int passFlag = 0;
	vector<int> cont;

	scanf("%d", &T);

	for (int t = 1; t <= T; t++) {

		// D�� ��ȣ�ʸ� �β�(���� ����), W�� ����ũ��(���� ����), K�� �հݱ���(���ӵ� ���� ���� ����)
		scanf("%d %d %d", &D, &W, &K);

		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%d", &arr[i][j]);
				copies[i][j] = arr[i][j];
			}
		}

		solve(0, arr, cont);

		if (find(cont.begin(), cont.end(), 0) == cont.end()) {
			printf("#%d 0\n", t);
			continue; // ���� �׽�Ʈ ���̽��� �̵�
		}

		else {
			// ���� �Լ� �� ��ǰ ó�� �ڵ� ����
			vector<int> n;
			vector<int> ind;
			cont.clear();
			passFlag = 0;

			for (int i = 0; i < D; i++) 
				n.push_back(i);
			
			for (indK = 1; indK <= K; indK++) {
				ind.clear();
				passFlag = 0;

				for (int i = 0; i < indK; i++)
					ind.push_back(1);
				for (int i = 0; i < n.size() - indK; i++)
					ind.push_back(0);
				sort(ind.begin(), ind.end());

				// 0 �Ǵ� 1�� ������ �ߺ������� ����� ���´�.

				permuList.clear();
				make_permutation(indK, 0);

					do {
						for (int p = 0; p < permuList.size(); p++) {

							int q = 0;
							// ���� �ٲ� ��鿡 ���Ͽ�
							for (int k = 0; k < ind.size(); k++) {
								if (ind[k] == 1) {
									// k��° ���� ������ permuList�� ������ ����	
									for (int m = 0; m < W; m++) {
										copies[k][m] = permuList[p][q];
									}
									q += 1;
								}
							}

							solve(0, copies, cont);

							if (find(cont.begin(), cont.end(), 0) == cont.end()) {
								printf("#%d %d\n", t, indK);
								passFlag = 1;
								break;
							}

							else {
								// ����
								//copy(arr.begin(), arr.end(), copies.begin());
								for (int i = 0; i < D; i++) {
									for (int j = 0; j < W; j++) {
										copies[i][j] = arr[i][j];
									}
								}

								cont.clear();
								continue;
							}

							/*
							// �����ϴ� ���� ������ŭ�� ����
							for (int k = 0; k < ind.size(); k++) {
								if (ind[k] == 1) {
									// k��° ���� ������ ��� j������ �ٲ۴�.
									for (int m = 0; m < W; m++)
										copies[k][m] = j;
								}
							}

							solve(0, copies, cont);

							if (find(cont.begin(), cont.end(), 0) == cont.end()) {
								printf("#%d %d\n", t, indK);
								passFlag = 1;
								break;
							}

							else {
								// ����
								copy(arr.begin(), arr.end(), copies.begin());
								cont.clear();
								continue;
							}*/
							//}
						}


					if (passFlag) {
						ind.clear();
						cont.clear();
						break;
					}

				} while (next_permutation(ind.begin(), ind.end()));


				if (passFlag) {
					break;
				}
			}


		}

	}

}
