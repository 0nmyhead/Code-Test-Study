#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <hash_map>

using namespace std;

int main() {

	long long k;
	long long bit = 0;
	vector<long long> room_number;
	vector<long long> answer;
	long long Idx;
	hash_map<long long, long long> room;

	k = 10;
	room_number.push_back(1);
	room_number.push_back(3);
	room_number.push_back(4);
	room_number.push_back(1);
	room_number.push_back(3);
	room_number.push_back(1);

	/* ��Ʈ����ŷ Ǯ�̹� -> ���ڰ� ũ�� �ð��ʰ�... */
	/*
	for (int i = 0; i < room_number.size(); i++) {
		Idx = room_number[i];

		// �湮���� �ʾ�����
		if ((bit & (1 << Idx)) == 0) {
			result.push_back(room_number[i]);
			bit = bit | (1 << Idx); // �湮 ǥ��
		}

		// �湮������, �̰ͺ��� ���ڰ� ũ�鼭 ���� ���� ���� ��ȣ�� �ִ´�.
		else {
			while (1) {
				if ((bit & (1 << Idx)) == 0) { // �湮���� �ʾ�����
					result.push_back(Idx);
					bit = bit | (1 << Idx); // �湮 ǥ��
					break;
				}
				else
					Idx++;
			}
		}
	}
	*/

	for (int i = 0; i < room_number.size(); i++) {
		Idx = room_number[i];
		if (room.find(Idx) == room.end()) {
			room.insert({ Idx, 1 });
			answer.push_back(Idx);
		}
		else {
			while (1) {
				Idx += 1;
				if (room.find(Idx) == room.end()) {
					room.insert({ Idx, 1 });
					answer.push_back(Idx);
					break;
				}
			}
		}
	}
	
}