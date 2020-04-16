#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int solution(int N, int number) {
	int answer = 0;
	int powN = 0;
	string cont_n = "";
	vector<vector<int>> NVector;
	NVector.resize(9);

	// ù��° ������ N, NN, NNN, NNNN �� ���� ���ڰ� ����.
	/*
	for (int i = 0; i < 8; i++) {
		powN = powN + (pow(10, i) * N);
		NVector[i+1].push_back(powN);
	}*/
	for (int i = 1; i <= 8; i++) {
		cont_n += to_string(N);
		NVector[i].push_back(stoi(cont_n));
	}


	// 2�����ʹ�, �� 2�� 55�� 2�����ʹ� 5+5, 5*5, 5-5, 5/5�� ���� �Ѵ�.
	// �� ����, 2���� 1���� ��� ���ڿ� 1���� ��� ���ڵ��� ��Ģ���� ���� ����.
	// 3����, 1���� ��� ���ڿ� 2���� ��� ���ڵ��� ��Ģ������ ����,
	// 2���� ��� ���ڿ� 1���� ��� ���ڵ��� ��Ģ���� ���� ����.
	// �̷��� ���� ä��������..

	// ��ü 8���� �࿡ ���Ͽ� ����
	for (int i = 2; i <= 8; i++) {
		// j+k �� ���� i�� ���� ��, ��� ��Ģ������ �����Ѵ�.
		// ��, 5���� 1+4, 2+3, 3+2, 4+1 �࿡ ���� ��Ģ������ �����Ѵ�.
		for (int j = 1; j <= 8; j++) {
			for (int k = 1; k <= 8; k++) {
				if (j + k == i) {

					for (int m = 0; m < NVector[j].size(); m++) {
						for (int p = 0; p < NVector[k].size(); p++) {
							NVector[i].push_back(NVector[j][m] + NVector[k][p]);
							NVector[i].push_back(NVector[j][m] * NVector[k][p]);
							NVector[i].push_back(NVector[j][m] - NVector[k][p]);
							if (NVector[k][p] != 0)
								NVector[i].push_back(NVector[j][m] / NVector[k][p]);
						}
					}

				}
			}
		}

		for (int q = 0; q < NVector[i].size(); q++) {
			if (NVector[i][q] == number)
			{
				int answer = i;
				return answer;
			}
		}
	}

	answer = -1;
	return answer;
}