#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <string>
#include <map>
#include <cstring>

using namespace std;

#define pii pair<int,int>

int parent[100001];
int sizes[100001];

vector<pair<long long, pii>> node;

int find(int a) {
	if (parent[a] == a) return a;
	return parent[a] = find(parent[a]);
}

void unite(int a, int b) {
	a = find(a);
	b = find(b);

	parent[b] = a;
	sizes[a] += sizes[b];
}

bool cmp(const pair<int, pii>& a, const pair<int, pii>& b) {
	return a.first > b.first;
}

int N, M;

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		long long x, y, w;
		cin >> x >> y >> w;
		node.push_back({ w, { x,y } }); // x-y ���� ����ġ w
	}

	// �θ� �迭 �� ũ�� �ʱ�ȭ
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		sizes[i] = 1;
	}

	// u-v �� �� �� ������, �׷����� �ּ� �������� ����鼭
	// ��� u-v�� �� �� �ִ��� �ľ��Ѵ�.

	// ����ġ �������� ����
	sort(node.begin(), node.end(), cmp);

	// 1������ n�� ���������� ����ġ �� ����
	long long sum_all = 0;
	for (int i = 0; i < node.size(); i++) {
		sum_all += node[i].first;
	}

	// ������ �Ѱ��� �����ϸ鼭 ���
	// ���õ� ������ ����ġ�� ������ ���´�.
	long long result = 0;
	long long selected = 0;
	for (int k = 0; k < node.size(); k++) {

		long long a = node[k].second.first;
		long long b = node[k].second.second;
		long long w = node[k].first;

		// a�� b �������ϱ�
		// ��, a�� b�� �ٸ� �����̾��� ��쿡��
		if (find(a) != find(b)) {
			// �� ����ϱ�
			// ��ġ�� �� (a ���� ������) * (b ���� ������) * (����ġ ���� - �̹� ���õ� ����ġ ��) ���
			long long a_size = sizes[parent[a]];
			long long b_size = sizes[parent[b]];
			result += (((a_size * b_size) % 1000000000) * (sum_all - selected)) % 1000000000;

			unite(a, b);
		}
		selected += w;
	}

	cout << result % 1000000000;

	return 0;
}