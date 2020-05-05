#define pb push_back

#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;
	int min_answer = 999999999;

	vector<int> li_origin; // ������ ��� �������� �ϳ��� ��ġ�� ����
	vector<int> li_reverse; // ������ ��� �������� �ϳ��� ��ġ�� ����
	vector<int> ind; // permutation ��� ���� ����
	set<int> visit;

	sort(dist.begin(), dist.end());

	for (int i = 0; i < weak.size(); i++) {

		for (int p = i; p < weak.size(); p++) {
			li_origin.pb(weak[p]);
		}
		for (int p = 0; p < i; p++) {
			li_reverse.pb(weak[p] + n);
		}
		li_origin.insert(li_origin.end(), li_reverse.begin(), li_reverse.end());
		// {1,5,6,10} -> {5,6,10,13} -> ...

		for (int j = 1; j <= dist.size(); j++) {

			// ������ �ƴ϶� ������ �������.
			// dist �迭�� permutation�� ����
			// ���� ����� ģ������ �̾Ƴ��� ���� 1, 0 ind ���͸� �����.
			for (int k = 0; k < j; k++)  // j ��ŭ�� ����
				ind.pb(1);
			for (int m = 0; m < dist.size() - j; m++)
				ind.pb(0);
			sort(ind.begin(), ind.end());

			do {
				vector<int> vec;
				for (int i = 0; i < ind.size(); i++) {
					if (ind[i] == 1) {
						vec.push_back(dist[i]);
					}
				}
				sort(vec.begin(), vec.end());
				// vec���� ���� ��� dist{3,5,7} �̸� {3, 5} �� �� �ִ�.
				// ���� �� vec�� ������ �ٽ� ������ �����.
				do {

					int endIdx = 0;
					bool iterFlag = false;
					bool possibleFlag = false; // ���� �Ϸ��� ���

					for (int i = 0; i < vec.size(); i++) {
						// �����ϱ�
						for (int j = endIdx; j < weak.size(); j++) {
							for (int k = j; k < weak.size(); k++) {

								if (k == j && li_origin[k] <= vec[i]) {
									visit.insert(li_origin[k]);
									possibleFlag = true;
								}

								else if (li_origin[k] - li_origin[j] <= vec[i]) {
									// ���� ����
									if (k + 1 <= weak.size() - 1) {
										visit.insert(li_origin[k]);
										visit.insert(li_origin[j]);
										endIdx = k + 1;
									}
									else {
										visit.insert(li_origin[k]);
										visit.insert(li_origin[j]);
										endIdx = weak.size();
									}
									possibleFlag = true;
								}
								else {
									// ���� �Ұ� �� �� ���캼 �ʿ䰡 ����
									iterFlag = true;
									break;
								}
							}
							if (iterFlag)
								break;
						}

						if (possibleFlag)
							answer += 1;
					}

					if (visit.size() == weak.size()) {
						min_answer = min(min_answer, answer);
					}

					visit.clear();
					answer = 0;

				} while (next_permutation(vec.begin(), vec.end()));
				vec.clear();
			} while (next_permutation(ind.begin(), ind.end()));
			ind.clear();
		}

		li_origin.clear();
		li_reverse.clear();
	}

	if (min_answer != 999999999)
		return min_answer;
	else
		return -1;
}