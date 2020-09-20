#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <cstring>

using namespace std;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int board[52][52];
int visit[52][52];
int m_board[52][52];
int cp_board[52][52];

int R, C, T;

vector<pair<int, int>> purifier;

void purify() {

	memset(m_board, 0, sizeof(m_board));

	// ���� �迭 �����
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cp_board[i][j] = board[i][j];
		}
	}

	// ù ��° ����û����� �ݽð����
	int fy = purifier[0].first;
	int fx = purifier[0].second;

	// ����û���Ⱑ ��ġ�� ��, ���� ������ ĭ���� ���ʴ�� ��ȯ ����
	int ty = fy, tx = fx;

	// ����û���� ǥ��
	m_board[fy][fx] = -1;

	/* ------------> ���� */
	for (int i = tx + 1; i <= C - 1; i++) 
		m_board[ty][i + 1] = cp_board[ty][i];
	
	/* |�� ���� */
	for (int i = ty; i >= 2; i--) 
		m_board[i - 1][C] = cp_board[i][C];
	
	/* <------------ ���� */
	for (int i = C; i >= 2; i--) 
		m_board[1][i - 1] = cp_board[1][i];
	
	/* |�Ʒ� ���� */
	for (int i = 1; i < fy - 1; i++) 
		m_board[i + 1][1] = cp_board[i][1];
	
	// �̵� �� �� ������ ĭ�� ����ϱ�
	// 2����� ~ fy-1 �����, fx+1������ ~ C - 1������
	for (int i = 2; i <= fy - 1; i++) {
		for (int j = fx+1; j <= C - 1; j++) {
			m_board[i][j] = board[i][j];
		}
	}

	// �� ��° ����û����� �ð����
	int sy = purifier[1].first;
	int sx = purifier[1].second;

	// ����û���Ⱑ ��ġ�� ��, ���� ������ ĭ���� ���ʴ�� �ð� ���� ��ȯ ����
	ty = sy, tx = sx;

	// ����û���� ǥ��
	m_board[sy][sx] = -1;
	
	/* ----------> ���� */
	for (int i = tx + 1; i <= C - 1; i++) 
		m_board[ty][i + 1] = cp_board[ty][i];
	
	/* | �Ʒ� ���� */
	for (int i = sy; i <= R - 1; i++) 
		m_board[i + 1][C] = cp_board[i][C];	

	/* <------- ���� */
	for (int i = C; i >= 2; i--) 
		m_board[R][i - 1] = cp_board[R][i];

	/* | �� ���� */
	for (int i = R; i > sy + 1; i--) 
		m_board[i - 1][1] = cp_board[i][1];
	

	// �̵� �� �� ������ ĭ�� ����ϱ�
	// sy + 1����� ~ R-1 �����, sx+1������ ~ C - 1������
	for (int i = sy+1; i <= R - 1; i++) {
		for (int j = sx + 1; j <= C - 1; j++) {
			m_board[i][j] = board[i][j];
		}
	}
	
	// ����, ���ο� �̼����� ĭ�� �ٽ� visit ǥ��
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			// �̼������� ��� Ȯ�� ������� ���� ǥ��
			if (m_board[i][j] != 0 && m_board[i][j] != -1) {
				visit[i][j] = m_board[i][j];
			}
		}
	}
	
	// board�� ����
	for (int i = 1; i <= R; i++) 
		for (int j = 1; j <= C; j++) 
			board[i][j] = m_board[i][j];
			
}

void diffusion() {

	// 1�� ����, [1]�̼������� Ȯ�� ���� [2]����û���Ⱑ �۵��Ѵ�.
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {

			// Ȯ�� ����� ���
			if (visit[i][j] != 0) {
				int cnt = 0; // �� ĭ�̳� Ȯ���ߴ��� ����
				int val = visit[i][j] / 5;
				for (int k = 0; k < 4; k++) {
					int ty = i + dy[k];
					int tx = j + dx[k];

					// ������ ĭ�� ��쿡��
					if (ty > 0 && tx > 0 && ty <= R && tx <= C
						&& board[ty][tx] != -1) {
						cnt += 1;
						board[ty][tx] = board[ty][tx] + val;
					}
				}
				board[i][j] = board[i][j] - (val * cnt);
			}
		}
	}

	// ���� �ð����� ���ο� �̼����� ĭ�� ���� �ϴ� �ʱ�ȭ
	memset(visit, 0, sizeof(visit));

}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C >> T;

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> board[i][j];
			// �̼������� ��� Ȯ�� ������� ���� ǥ��
			if (board[i][j] != 0 && board[i][j] != -1) {
				visit[i][j] = board[i][j];
			}
			// ����û������ ��� ��ǥ�� ����
			else if (board[i][j] == -1)
				purifier.push_back({ i,j });
		}
	}

	while (T > 0) {
		/* Ȯ�� */
		diffusion();

		/* û�� */
		purify();

		T--;
	}

	int res = 0;

	// �����ִ� �̼����� �� ���ϱ�
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (board[i][j] != -1 && board[i][j] != 0) {
				res += board[i][j];
			}
		}
	}

	cout << res;

	return 0;
}