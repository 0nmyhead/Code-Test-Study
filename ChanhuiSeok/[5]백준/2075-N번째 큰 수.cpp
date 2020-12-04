#include <iostream>
#include <string>
#include <queue>

using namespace std;

int N;
priority_queue<int, vector<int>, greater<>> pq;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;

	/* ť�� N���� ���� �Ѵ�. */
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int temp; cin >> temp;
			
			if (pq.size() < N) 
				pq.push(temp);
			
			else if (pq.size() == N) {
				int top = pq.top();
				// ť���� ���� ���� ���� ����.
				if (temp > top) {
					pq.pop(); pq.push(temp);
				}
			}
		}
	}
	cout << pq.top();
	return 0;
}