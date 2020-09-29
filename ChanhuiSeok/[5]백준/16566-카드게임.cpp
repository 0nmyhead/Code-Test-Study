#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

int N, M, K;
int arr[10001];
vector<int> cards;
bool visit[4000001];

int main() {

	int t_card;
	scanf("%d %d %d", &N, &M, &K);

	cards.reserve(10001);

	for (int i = 0; i < M; i++) {
		int input;
		scanf("%d", &input);
		cards.push_back(input);
	}

	sort(cards.begin(), cards.end());

	int tmp;
	for (int i = 0; i < K; i++) {		
		scanf("%d", &tmp);
		int idx = upper_bound(cards.begin(), cards.end(), tmp) - cards.begin();

		// ���õ� �� ���� ���
		if (visit[cards[idx]] == false) {
			printf("%d\n", cards[idx]);
			visit[cards[idx]] = true;
		}
		// ���õ� �� ���� ���, ���õ��� ���� ���� ó������ ���� ������ �ݺ�
		else {
			int i;
			for (i=idx + 1; i<M ; i++) {
				if (visit[cards[i]] == false) 
					break;			
			}
			printf("%d\n", cards[i]);
			visit[cards[i]] = true;
		}
	}

	return 0;
}