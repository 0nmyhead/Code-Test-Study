#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

long long N, M;
vector<long long> time;

// ǥ�� �׷��� Ȯ���� ����, Ư�� �ð����� ž���� ����� ����
// �Ʒ��� ���� ���� �� �ִ�.
long long calcul(long long times) {
	long long result = 0;
	for (int i = 0; i < M; i++) {
		result += times / time[i];
	}
	return result;
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		long long tmp; cin >> tmp;
		time.push_back(tmp);
	}

	// ��̵� ������ ���̰��� ���� �� ���ٸ� �׳� �ٷ� ���
	if (N <= M) {
		cout << N;
		return 0;
	}

	long long mid;
	long long people = M; // ���̱ⱸ�� ��� �¿�� ����

	long long left = 0;

	// ���̱ⱸ�� 1���ۿ� ����, ����� �ִ� �� ��ŭ �ְ�, ���̱ⱸ ����ð���
	// �ִ� 30��¥���� ��� ���� ���� �ɸ��� �ð�
	long long right = 2000000000LL * 30LL;

	long long findTime = 0; // ������ ������� ���� ���� �ð�

	while (left <= right) {
		mid = (left + right) / 2;
		long long times = calcul(mid);

		// ã���� �ϴ� �ͺ��� Ŭ ��� right ���� ������
		// +M �� ������, 0�п��� ó���� ��� ���̱ⱸ�� �л����� �� ž���ϹǷ�
		if (times + M >= N) {
			right = mid - 1;
			findTime = mid;
		}
		else {
			left = mid + 1;
		}
	}

	// findTime-1 �б��� ������ �ο� ���ϱ�
	for (int i = 0; i < M; i++) {
		people += (findTime - 1) / time[i];
	}

	// 1�� �� �ο� +1 ����� N���� �� ������ �־��.
	long long answer = 0;
	for (int k = 0; k < M; k++) {
		long long tmp = findTime % time[k];	
		// ������ ������ ���
		if (tmp == 0) {
			people++;
			answer = k;
		}
		if (people >= N) break;
	}
	cout << answer + 1;

	return 0;
}