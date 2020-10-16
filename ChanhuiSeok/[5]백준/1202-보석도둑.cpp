#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <deque>
#include <queue>

#define pii pair<long long, long long>

using namespace std;

int N, K;

multiset<long long> bag;
priority_queue<pii, vector<pii>> pq; // max-heap

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		long long m, v;
		cin >> m >> v;
		pq.push({ v,m });
	}
	for (int i = 0; i < K; i++) {
		long long c;
		cin >> c;
		bag.insert(c);
	}

	long long sum = 0;

	while (!pq.empty()) {
		int top_value = pq.top().first;
		int top_weight = pq.top().second;
		pq.pop();

		// ���� ���Կ� ���ų� ū ������ ó������ ������ �ε��� ã��
		multiset<long long>::iterator iter = bag.lower_bound(top_weight);
		if (iter == bag.end()) continue;

		bag.erase(iter);
		sum += top_value;
	}

	cout << sum;

	return 0;
}