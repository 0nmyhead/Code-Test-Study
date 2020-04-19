#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

/* vector�� ����ϸ� �Ϲ� array�� ����� ������ Ž�� �� ���꿡��
	�ӵ��� �� �����ٰ� �Ѵ�

	���߿� array �Ἥ �ð� �����غ���!!!
*/

using namespace std;

int N, K, T, M;
int arr[101][101];

bool isMetChemical(int y, int x) {
	if (y == 0 || y >= N - 1 || x == 0 || x >= N - 1)
		return true;
	else
		return false;
}

void MetFunc(int dir, int idx, vector<vector<int>> &v) {
	if (dir == 1) {
		v[idx][2] = v[idx][2] / 2;
		v[idx][3] = 2;
	}
	else if (dir == 2) {
		v[idx][2] = v[idx][2] / 2;
		v[idx][3] = 1;
	}
	
	else if (dir == 3) {
		v[idx][2] = v[idx][2] / 2;
		v[idx][3] = 4;
	}
	
	else if (dir == 4) {
		v[idx][2] = v[idx][2] / 2;
		v[idx][3] = 3;
	}
}


int main() {

	// N�� ���� �� ���� ����, // K�� �� ������ ����, // M�ð����� ���� �ݸ� ����
	int sero, garo, nums, dir;
	bool isMet;
	int SameSum = 0, maxX, maxY;
	int resultSum = 0, idx = 0;

	vector <vector<int>> v;

	scanf("%d", &T);

	for (int t = 1; t <= T; t++) {

		scanf("%d %d %d", &N, &M, &K);
		v.resize(K);
		v.reserve(K);

		// dir ���� 1,2,3,4 ���� ��,��,��,��
		// ������ ��� ������ �޾ƿ���
		for (int i = 0; i < K; i++) {
			scanf("%d %d %d %d", &sero, &garo, &nums, &dir);
			v[i].reserve(4);
			v[i].push_back(sero);
			v[i].push_back(garo);
			v[i].push_back(nums);
			v[i].push_back(dir);
		}
		
		// �ùķ��̼� ���� (M�ð�����)
		for (int t = 1; t <= M; t++) {

			// ��� ���� �����͵鿡 ���Ͽ� ����
			for (int idx = 0; idx < v.size(); idx++) {

				/* �ϴ� �̵����� �ϰ������� �� ���� */
				if (v[idx][3] == 1)  // ��
					v[idx][0] = v[idx][0] - 1;
				
				else if (v[idx][3] == 2)  // ��
					v[idx][0] = v[idx][0] + 1;
				
				else if (v[idx][3] == 3)  // ��
					v[idx][1] = v[idx][1] - 1;
				
				else if (v[idx][3] == 4)  // ��
					v[idx][1] = v[idx][1] + 1;
				////////////////////////////////
			}

			// �̵��� ���� �����鿡 ���Ͽ� sorting //
			sort(v.begin(), v.end());

			idx = 0;
			while (idx <= v.size() - 1) {
				SameSum = 0; // �ʱ�ȭ

				// CASE 1. ��ǰ�� �����°�? // ��ǰ�� ��������, �𿩼� ��ġ�� ���� ���� �������� �ʴ´�.
				isMet = isMetChemical(v[idx][0], v[idx][1]);
				if (isMet) {
					MetFunc(v[idx][3], idx, v);

					// �̻��� ���� 0�� �Ǹ� �� ���� ����
					if (v[idx][2] == 0) {
						v.erase(v.begin() + idx);
					}
					else
						idx++;
				}
				// CASE 2. ��ǰ�� ������ �ʾ�����,
				// ���� ���� ��ǥ�� ������ ���� ���, �� �����Ͱ� ���� �ʿ䰡 �����Ƿ� ���������� ������ �ش�.
				else if (!isMet && idx == v.size() - 1) {
					idx++;
				}
				// CASE 3. ��ǰ�� ������ �ʾҰ�, ���� ���Ϳ� �ڱ�� ���� ��ǥ ������ ���� ���
				// �׳� �̵��� �� �����Ƿ� �������θ� �Ѿ��.
				else if (!isMet &&
					(v[idx][0] != v[idx + 1][0] || v[idx][1] != v[idx + 1][1])) {
					idx++;
				}
				// CASE 4. ��ǰ�� ������ �ʾҰ�, ���� ���Ϳ� �ڱ�� ���� ��ǥ ������ ���� ���
				else if (!isMet &&
					(v[idx][0] == v[idx + 1][0] && v[idx][1] == v[idx + 1][1])) {

					while (1) {
						if (idx == v.size() - 1) { // �̹� �������̸� 						
							v[idx][2] += SameSum;
							idx++;
							break;
						}

						else if (v[idx][0] == v[idx + 1][0] && v[idx][1] == v[idx + 1][1]) {
							// �̻��� ���� ���� ���Ѵ�.
							// �׸��� ������ ��ǥ�� ������ �̻��� ���� �� ���� ���̾����� �� ���ʹ� �����Ѵ�.
							SameSum = SameSum + v[idx][2];
							v.erase(v.begin() + idx);
						}

						else {
							// ���� ��ǥ�� ������ ������ �� ���� ū �����̹Ƿ�,
							// �������� �ʰ� �ո� ���� �� ������.
							SameSum += v[idx][2];
							v[idx][2] = SameSum;
							idx++;
							break;
						}
					}
				}
			}
		}


		// ��� �̻������� �� ���ϱ�
		for (int i = 0; i < v.size(); i++) 
			resultSum += v[i][2];
		
		printf("#%d %d\n",t,resultSum);

		// ���ο� �׽�Ʈ���̽��� ���� �ʱ�ȭ
		resultSum = 0;
		v.clear();
	}


}