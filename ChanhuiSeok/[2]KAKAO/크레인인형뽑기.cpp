#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
	int answer = 0;
	stack<int> stk;
	int crashCount = 0;

	for (int i = 0; i < moves.size(); i++) {

		// N*N �ǿ��� �� ������ �ľ��� ����.
		for (int j = 0; j < board.size(); j++) {
			// j��° ��, movse[i]��° ��
			// �� �� �־�����, �������� �̵��Ѵ�.
			if (board[j][moves[i] - 1] != 0) {

				/* ���ÿ��� ������ �� ���� */
				if (!stk.empty() && stk.top() == board[j][moves[i] - 1]) {
					stk.pop();
					crashCount += 2; // 2�� ����					
				}
				else {
					stk.push(board[j][moves[i] - 1]);
				}
				board[j][moves[i] - 1] = 0;
				break;
			}
		}
	}

	return crashCount;
}