#include <iostream>
#include <queue>
#include <algorithm>

#define MAX_PASS 30000

using namespace std;

pair<int, int> left_stops[MAX_PASS];
pair<int, int> right_stops[MAX_PASS];

bool desc(pair<int, int> a, pair<int, int> b) {
	return a > b;
}

int main() {

	int N, K, S; // ����Ʈ ���� ��, ���й����� ����, �б��� ��ġ
	cin >> N >> K >> S;
	// �б��� ��ġ�� �������� �� �������� �����Ͽ� ������ ������ Ǭ��

	int ll = 0; int rl = 0; //���� ������ ����, ������ ������ ����

	for (int i = 0; i < N; i++) {
		int distance, people;
		cin >> distance >> people;
		pair<int, int> tmp = make_pair(distance, people);
		if (distance < S) { // �б����� �����̸�
			tmp.first = S - tmp.first;// �ʿ��� ������ �Ÿ����̴�
			left_stops[ll] = tmp; 
			ll++;
		}
		else { // �б����� �������̸�
			tmp.first -= S; // �ʿ��� ������ �Ÿ����̴�
			right_stops[rl] = tmp; 
			rl++;
		}
	}

	sort(left_stops, left_stops + ll, desc);
	sort(right_stops, right_stops + rl, desc); // ������ ������ �����Ѵ�. 

	int dst_idx = 0; 
	int left_distance = 0; 
	int current_K;
	// ���ʿ� ���ؼ� ����
	while(dst_idx < ll) {

		int dst_distance = left_stops[dst_idx].first;
		left_distance += dst_distance;

		current_K = K - left_stops[dst_idx].second;
		if (current_K < 0) {//�� ó�� ���� ������ Ÿ�ߵ� ����� �� ���� ��� ������ ����Ѵ�.
			left_stops[dst_idx].second = -current_K;
			left_distance += dst_distance;
			continue;
		}

		for (int i = dst_idx+1; i < ll; i++) {

			if (current_K == 0) break;
			int nxt_people = left_stops[i].second;

			if (current_K >= nxt_people) { // ������ ���� ��쿡 ��� �¿�� 
				current_K -= nxt_people;
				dst_idx++;
			}
			else { //���� �������� ������ Ÿ�ߵ� ����� �� ���� ��� ������ ����Ѵ�.
				left_stops[i].second -= current_K;
				current_K = 0;
			}
		}
		left_distance += dst_distance;
		dst_idx++;
	}

	dst_idx = 0;
	current_K = K;
	int right_distance = 0;

	// �����ʿ� ���� ����
	while (dst_idx < rl) {

		int dst_distance = right_stops[dst_idx].first;
		right_distance += dst_distance;
		current_K = K - right_stops[dst_idx].second;

		if (current_K < 0) {//�� ó�� ���� ������ Ÿ�ߵ� ����� �� ���� ��� ������ ����Ѵ�.
			right_stops[dst_idx].second = -current_K;
			right_distance += dst_distance;
			continue;
		}

		for (int i = (dst_idx + 1); i < rl; i++) {

			if (current_K == 0) break;
			int nxt_people = right_stops[i].second;

			if (current_K >= nxt_people) { // ������ ���� ��쿡 ��� �¿�� 
				current_K -= nxt_people;
				dst_idx++;
			}
			else { //���� �������� ������ Ÿ�ߵ� ����� �� ���� ��� ������ ����Ѵ�.
				// current_K < nxt_people
				right_stops[i].second -= current_K;
				break;
			}

		}

		right_distance += dst_distance;
		dst_idx++;
	}

	cout << right_distance + left_distance << endl;
	return 0;
}