#include <string>
#include <vector>
#include <map>
typedef long long ll;
using namespace std;

map<long long, long long> room;

ll getEmpty(ll num) {
	// ���� ��������� num�� �״�� ��ȯ
	if (room[num] == 0) return num;
	return room[num] = getEmpty(room[num]);
}


vector<long long> solution(long long k, vector<long long> room_number) {
	vector<long long> answer;

	for (ll num = 0; num < room_number.size(); num++) {
		ll empty = getEmpty(room_number[num]);
		answer.push_back(empty);
		room[empty] = empty + 1;
	}

	return answer;
}