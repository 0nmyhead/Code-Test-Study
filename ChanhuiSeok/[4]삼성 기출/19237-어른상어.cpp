#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <map>
#include <stack>
#include <string>

#define pii pair<int,int>
#define POINT 5

int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };

using namespace std;

int board[400][400];
vector<int> pxy[21];

void draw_curve(int sy, int sx, int sDir, int gen) {

	// ���� ��ǥ (sy, sx) ���� gen �������
	for (int i = 0; i <= gen; i++) {
		// 0������ ���
		if (i == 0) 
			pxy[0].push_back(sDir); // ���Ϳ� �ֱ�				
		else {		
			// �� ���� ������ �״�� �ְ�
			for (int k = 0; k < pxy[i - 1].size(); k++)
				pxy[i].push_back(pxy[i - 1][k]);

			// �ڿ� �� ������ ������ �Ųٷ� �� �� +1�� �Ͽ� ���ʴ�� �ִ´�.
			for (int k = pxy[i - 1].size() - 1; k >= 0; k--) 
				pxy[i].push_back((pxy[i - 1][k] + 1) % 4);		
		}
	}

}


int main(){

	int N;
	cin >> N;

	vector<vector<int>> dragon;
	dragon.resize(N);

	for (int i = 0; i < N; i++) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		// x, y�� �巡�� Ŀ�� ������, d�� ���� ����, g�� ����

		dragon[i].push_back(x); dragon[i].push_back(y);
		dragon[i].push_back(d); dragon[i].push_back(g);
	}
	// �巡�� Ŀ�� �Է� �Ϸ�

	// ���� ��ġ�� (100, 100) �� ������ �ǵ��� �����.
	// dragon[0] ���� ���ʴ�� �����ǿ� �׸��� �׷� ����.

	for (int i = 0; i < N; i++) {
		int y = dragon[i][1];
		int x = dragon[i][0];
		int dir = dragon[i][2];
		int gen = dragon[i][3];

		draw_curve(y, x, dir, gen);

		// ���� �� ���븶�� ������ ���� ������� ��鿡 ǥ���Ѵ�.
		int sY, sX, eY, eX;
		sY = y; sX = x;
		for (int k = 0; k <= gen; k++) {

			// k����
			for (int j = pxy[k].size() / 2; j < pxy[k].size(); j++) {
				// ���� ������ ǥ��
				//if(sY >= 0 && sY <=100 && sX >= 0 && sX <= 100)
					board[sY][sX] = POINT;

				eY = sY + dy[pxy[k][j]];
				eX = sX + dx[pxy[k][j]];
				// �� ������ ǥ��
				//if (eY >= 0 && eY <= 100 && eX >= 0 && eX <= 100)
					board[eY][eX] = POINT;

				// ���� �� ������ ���������� �ǹǷ�
				sY = eY; sX = eX;
			}

		}

		for (int k = 0; k <= gen; k++) {
			pxy[k].clear();
		}
	
	}
	

	int ans = 0;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (board[i][j] == POINT &&
				board[i][j + 1] == POINT &&
				board[i + 1][j] == POINT &&
				board[i + 1][j + 1] == POINT) {
				ans += 1;
			}
		}
	}

	return 0;
}