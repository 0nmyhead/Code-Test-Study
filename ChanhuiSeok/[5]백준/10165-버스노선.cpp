#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>

#define ll long long
#define pii pair<int,int>

using namespace std;

ll N, M;
typedef struct bus {
	int num, a, b;
}Bus;

vector<Bus> route1, route2;
bool compare(const Bus& f, const Bus& s) {
	if (f.a != s.a) return f.a < s.a;
	else return f.b > s.b;
}

bool able[500001];
int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	cin >> M;

	ll minA = 1e12, maxB = -1;

	for (int i = 1; i <= M; i++) {
		ll a, b; cin >> a >> b;
		Bus bus;
		bus.num = i; bus.a = a; bus.b = b;

		if (a - b <= 0) {
			route1.push_back(bus);
		}
		else {
			minA = min(minA, a);
			maxB = max(maxB, b);
			route1.push_back(bus);

			bus.b = b + N;
			route2.push_back(bus);
		}
		able[i] = true;
	}

	sort(route1.begin(), route1.end(), compare);
	sort(route2.begin(), route2.end(), compare);

	int right = 0;
	for (int i = 0; i < route1.size(); i++) {
		// 0�� ��ġ�� �뼱�� �ǳʶڴ�.
		if (route1[i].a > route1[i].b)
			continue;

		// 0�� ��ġ�� �ʴ� �Ϲ����� �뼱�� ��������
		// 0�� ��ġ�� �뼱�� ���������� �ڿ� ������,
		// �ݵ�� 0�� ��ġ�� �뼱 �ȿ� ���Եȴ�.

		// Ȥ��, 0�� ��ġ�� �ʴ� �Ϲ����� �뼱�� ��������
		// 0�� ��ġ�� �뼱�� ���������� �տ� ������,
		// �ݵ�� 0�� ��ġ�� �뼱 �ȿ� ���Եȴ�.
		if (minA <= route1[i].a) able[route1[i].num] = false;
		if (maxB >= route1[i].b) able[route1[i].num] = false;

		// �Ϲ����� ���
		if (route1[i].b <= right) {
			able[route1[i].num] = false; // ���ԵǾ����� ����
		}
		else {
			right = route1[i].b;
		}
	}

	// 0�� ��ġ�� �뼱�鳢���� ��
	// �� �뼱���� ������ N�� ���ؼ� ���� ����.
	right = 0;
	for (int i = 0; i < route2.size(); i++) {
		// �Ϲ����� ���� ���
		if (route2[i].b <= right) {
			able[route2[i].num] = false; // ���ԵǾ����� ����
		}
		else {
			right = route2[i].b;
		}
	}

	for (int i = 1; i <= M; i++) {
		if (able[i] == true) {
			cout << i << ' ';
		}
	}

	return 0;
}