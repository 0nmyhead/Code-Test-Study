#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;
// ��α׿� �������ؼ� ������ ���� ������ �� ����.
// ����� ���� �������� priority_queue�� ���� ����Ѵٰ� �Ѵ�.

#define pii pair<int, int>

vector<pair<int, int>> input;

int n, d;

struct comp {
	bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
		/* priority_queue�� comp�� ���� ��, �Ϲ����� sort���� comp�Լ� ���Ƕ���
		���ݴ�� ���� �ȴ�. ���������� �Ʒ�ó�� �ۼ��ߴ�. */
		if (a.second == b.second) {
			return a.first > b.first;
		}
		return a.second > b.second;
	}
};

priority_queue<pii, vector<pii>, comp> inputQ;
priority_queue<int, vector<int>, greater<int>> pq;

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.second != b.second) {
		return a.second < b.second;
	}
	else if (a.second == b.second) {
		return a.first < b.first;
	}
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		int h, o;
		cin >> h >> o;
		if (h > o)inputQ.push({ o,h });
		else inputQ.push({ h,o });
	}
	cin >> d;

	int maxSize = 0;

	// n����ŭ ���캻��.
	while (!inputQ.empty()) {
		int iR = inputQ.top().second;
		int iL = inputQ.top().first;
		inputQ.pop();

		// iR-iL ����� d���� ������ �ϴ� ������ �ĺ��ϱ� �� ���� ������ �ִ´�.
		if (iR - iL <= d) {
			pq.push(iL);
		}

		while (!pq.empty()) {
			// ������ ���� ������ �ĺ����� �ִ� pq ���� �ϳ��� �̾Ƽ�
			// ���� ���캸�� �ִ� n��° ��ǲ�� ������ �������� �Ÿ��� ����ϰ�
			// �� �Ÿ��� d �����̸� ������ �ٸ� ��ǲ�� ��� ����
			// d ���� ū �Ÿ��̸� ������ ���� ������ �ĺ����� �װ��� ��������.
			int tmp = pq.top();
			if (iR - tmp <= d) break;
			else 
				pq.pop();		
		}
		maxSize = max(maxSize, (int)pq.size());
	}

	cout << maxSize;

	return 0;
}