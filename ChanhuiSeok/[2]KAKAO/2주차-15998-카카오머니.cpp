#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long int arr1[300001], arr2[300001];
// �ִ����� �Լ�

long long int gcd(long long int a, long long int b) {
	
	if (b == 0)
		return a;
	else {
		return gcd(b, a % b);
	}
}


int main() {
	
	long long int N;
	vector <pair<long long int, long long int>> v;
	long long int history, bal;
	long long int beforeBal, nowBal;
	long long int testBal = 0;
	long long int M;
	long long int targetBal;

	long long int result = 0;

	int FirstDrawl = 0;
	int FindSuccessFlag = 0;
	int i = 0;
	int M_Sum_cnt = 0;
	int FirstDrawlIdx = 0;

	scanf("%lld", &N);

	/*
	for (int i = 0; i < N; i++) {
		scanf("%lld %lld", &history, &bal);
		v.push_back({ history, bal });
	}
	*/

	for (int i = 1; i <= N; i++) {
		scanf("%lld %lld", &arr1[i], &arr2[i]);
	}

	// ���� ���¿��� �����Ͽ� �����ϴ� �ݾ׵��� �ִ����� ����
	for (int i = 1; i <= N; i++) {
		result = gcd(result, arr2[i] - arr2[i - 1] - arr1[i]);
	}


	for (int i = 1; i <= N; i++) {
		// �ùٸ��� �ܾ׿� �ԱݵǾ� ��ġ�ϴ� ���
		// Ȥ��, �ùٸ��� �ܾ׿��� ��ݵǾ� ��ġ�ϴ� ���
		if (arr2[i] == arr2[i - 1] + arr1[i]) {
			continue;
		}

		//[���� 1]
		//���� ���¿��� ����� �� �ݾ׺��� ���� �ܾ��� ũ�� ���
		if (arr2[i] >= result) {
			printf("-1");
			return 0;
		}

		//[���� 2]
		//���� �������� �ʾҴ� ��Ȳ����, ���� �ܾװ� ��(��)�� �ܾ��� ���� ���� �ܾ��� ���� ������ ���
		if (arr2[i-1] + arr1[i] >= 0 && arr2[i] != arr2[i - 1] + arr1[i]) {
			printf("-1");
			return 0;
		}
	}
	
	if (result != 0)
		printf("%lld", result);
	else if (result == 0)
		printf("%lld", 1);

}

