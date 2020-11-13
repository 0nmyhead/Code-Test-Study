#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define HOSU 0
#define UNABLE 1
#define ABLE 2

#define GREEN 10
#define RED 20
#define FLOWER 1000

#define GREEN_NOW 60
#define RED_NOW 70

int N, M, G, R;
int arr[51][51];
bool visit[51][51];

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

vector<pair<int, int>> candi;
vector<int> ind;
vector<int> color;

int maxFlower = -987654321;

/* ������ �Ѹ� ���� ������ �̿��Ͽ� ��� ����� ���� ����. */
/* �� �ѷ��� ���� G Ȥ�� R�� ���� ����� ���� ������ �̿��Ͽ� ��� ����� ���� ����. */

void simulation() {

	int copyArr[51][51];
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) 
			copyArr[i][j] = arr[i][j];
		
	// G, R ������ ���� ������ �� ĭ�� �Ѹ���
	// ������ �Ѹ� ĭ�� �������� ����
	do { /* �� ���� */
		vector<pair<int, int>> p_land; // ���� �Ѹ� �� ����Ʈ	
		for (int i = 0; i < ind.size(); i++) {
			if (ind[i] == 1) {
				p_land.push_back(candi[i]);
			}
		}

		do { /* ���� ���� ���� */

			int flower = 0;
			queue<pair<int, int>> q;

			// ������ ó���� ����߸� p_land��, color ������� ������ �Ѹ���.
			for (int i = 0; i < p_land.size(); i++) {
				pair<int, int> p = p_land[i];
				arr[p.first][p.second] = color[i];

				visit[p.first][p.second] = true;
				q.push({ p.first, p.second });
			}

			while (1) {
				vector<pair<int, int>> now; // ��� �ѷ��� �ʷϻ� Ȥ�� ������ ������ ��ġ
				bool flag = false;

				// ������� �۶߷� ����.
				while (!q.empty()) {
					int y, x, curColor;
					y = q.front().first;
					x = q.front().second;
					curColor = arr[y][x];

					q.pop();

					for (int i = 0; i < 4; i++) {
						int ty = y + dy[i];
						int tx = x + dx[i];

						// ȣ���� �ƴϰ�, ���� �ƴ� ���� ���� �Ѹ���
						if (ty >= 0 && tx >= 0 && ty < N && tx < M &&
							!visit[ty][tx] && arr[ty][tx] != HOSU && arr[ty][tx] != FLOWER) {

							// ������ �� ����, ��� �ѷ��� �����̸� �ٸ� �����̾��� ���
							// �� ĭ�� ������ �����.
							if ((arr[y][x] == RED && arr[ty][tx] == GREEN_NOW) ||
								(arr[y][x] == GREEN && arr[ty][tx] == RED_NOW)) {
								arr[ty][tx] = FLOWER;
								flower++;
							}
							else { // �ƴ� ���, �׳� ��Ѹ���.
								flag = true;
								arr[ty][tx] = arr[y][x] + 50; // NOW�� �Ѹ���.
								now.push_back({ ty,tx });
							}
						}
					}
				}

				// ���� ������ �� �̻� ������ �۶߷��� ���� ������ ���
				if (!flag) {
					maxFlower = max(maxFlower, flower); // �� ����
					break;
				}

				// now�� �ִ� ĭ���� �����ϰ� ������ ���� ť�� �ִ´�.
				for (int k = 0; k < now.size(); k++) {
					int y = now[k].first;
					int x = now[k].second;
					visit[y][x] = true;

					if (arr[y][x] != FLOWER &&
						(arr[y][x] == GREEN_NOW || arr[y][x] == RED_NOW)) {
						arr[y][x] = arr[y][x] - 50;
						q.push({ y,x });
					}
				}
			}

			// �� �ʱ�ȭ
			for (int i = 0; i < N; i++) 
				for (int j = 0; j < M; j++) {
					arr[i][j] = copyArr[i][j];
					visit[i][j] = false;
				}

		} while (next_permutation(color.begin(), color.end()));
	} while (next_permutation(ind.begin(), ind.end()));
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M >> G >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == ABLE) {
				candi.push_back({ i,j });
			}
		}
	}

	// R+G ������ŭ 1�� �ְ�
	for (int i = 0; i < R + G; i++)
		ind.push_back(1);
	for (int i = 0; i < candi.size() - (R + G); i++)
		ind.push_back(0);
	sort(ind.begin(), ind.end());

	for (int i = 0; i < R; i++)
		color.push_back(RED);
	for (int i = 0; i < G; i++)
		color.push_back(GREEN);
	sort(color.begin(), color.end());

	// ��� ĭ�� ���� ���� �Ѹ��⸦ ������ �� ����

	simulation();
	cout << maxFlower;

	return 0;
}