#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

int cal[3];

int solution(string dartResult) {
	string oper[3][3];
	int size = dartResult.size();

	string tmpNum = "";
	// ���� �����
	int k = -1, idx = 0;
	int j = 0;
	bool flag = false;

	// ���ڿ� ��ɾ� �����
	while (idx <= size - 1) {
		// ������ ��� k ����
		if (dartResult[idx] >= '0' && dartResult[idx] <= '9' && !flag) {
			j = 0;
			k++;
			tmpNum += dartResult[idx];
			oper[k][j++] = tmpNum;
			idx++;
			flag = true;
		}
		else if (dartResult[idx] >= '0' && dartResult[idx] <= '9' && flag) {
			tmpNum += dartResult[idx];
			oper[k][j-1] = tmpNum;
			idx++;
			flag = false;
		}
		// ���ڰ� �ƴ� ���
		else {
			tmpNum = dartResult[idx];
			oper[k][j++] = tmpNum;
			idx++;
			tmpNum = "";
			flag = false;
		}
	}

	// �迭�� ��� ��ɾ��� ����ϱ�
	cal[0] = stoi(oper[0][0]);
	cal[1] = stoi(oper[1][0]);
	cal[2] = stoi(oper[2][0]);

	for (int row = 0; row < 3; row++) {
		//int num = cal[row];
		for (int col = 1; col < 3; col++) {
			if (oper[row][col] != "") {

				if (oper[row][col] == "D") 
					cal[row] = pow(cal[row], 2);			
				else if (oper[row][col] == "T") 
					cal[row] = pow(cal[row], 3);
				else if (oper[row][col] == "*") {
					// �� �ڽ� 2��
					cal[row] = cal[row] * 2;
					// �� ������ 2��
					if (row != 0) 
						cal[row - 1] = cal[row - 1] * 2;
				}
				else if (oper[row][col] == "#") {
					// �� �ڽ��� ���� ���̳ʽ�
					cal[row] = cal[row] * -1;
				}
			}
		}
	}

	return cal[0]+cal[1]+cal[2];
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int res = solution("1S*2T*3S");
	cout << res;

	return 0;
}