#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define RED 1
#define BLUE 2
#define YELLOW 3

int N;
int arr[10001];
int maxVal = -1;

// �� ������ ������ �ٲپ� ����, �������� ������ ��ȯ�ϴ� �Լ�
// ���⼭ ���� ���������� ���� ����
int bomber(int cur, int color) {

	int left = cur, right = cur;
	int origin_color = arr[cur];
	int ans = 0; // �������� ���� ��ȯ

	// �ش� ĭ ���� ����
	arr[cur] = color;

	// �ش� ĭ ���� ���� ��, �ش� ĭ �������� ������ ��� ���鼭
	// �� ����� ���� ĭ�� ���� ������ �����̰�

	// �ش� ĭ ���� ���� ��, �ش� ĭ �������� �������� ��� ���鼭
	// �� ����� ���� ĭ�� ���� ������ �����δ�.

	bool flag = true;

	while (left >= 1 && right <= N && flag) {
		// ���� ĭ�� ���� �ľ�
		int cur_color = arr[left];
		int cnt = 0;

		// ���� �����̱�
		while (left >= 1 && arr[left] == cur_color) {
			left -= 1;
			cnt++;
		}

		// ������ �����̱�
		while (right <= N && arr[right] == cur_color) {
			right += 1;
			cnt++;
		}

		// 4�� �̻� �������ٸ�, �ٸ� ĭ�鵵 ���� ������ �������� ���� �ϹǷ�
		// flag ���� true�� �ٲٰ�, ���� ������ ���Ѵ�.
		if (cnt >= 4){ 
			ans += cnt;
			flag = true;
		}
		// 4�� �̻� �������� ���Ѵٸ�, �ٸ� ���� ������ �˾ƺ� �ʿ䰡 ����.
		else {
			flag = false;
		}
	}

	// �ش� ĭ ���� ����
	arr[cur] = origin_color;
	return ans - 1; // �� ó������ �������� �����ϹǷ� ���� 1ȸ �ѹ� �� �������Ƿ� -1�� ��
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}

	// �Է¹��� �͵��� ���� ������ ����
	for (int i = 1; i <= N; i++) {
		maxVal = max(maxVal, bomber(i, RED));
		maxVal = max(maxVal, bomber(i, BLUE));
		maxVal = max(maxVal, bomber(i, YELLOW));
	}

	cout << N - maxVal;
	return 0;
}