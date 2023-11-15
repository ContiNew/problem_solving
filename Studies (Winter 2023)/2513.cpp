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

	int N, K, S; // 아파트 단지 수, 통학버스의 정원, 학교의 위치
	cin >> N >> K >> S;
	// 학교의 위치를 기준으로 두 집합으로 구별하여 별도로 문제를 푼다

	int ll = 0; int rl = 0; //왼쪽 집합의 길이, 오른쪽 집합의 길이

	for (int i = 0; i < N; i++) {
		int distance, people;
		cin >> distance >> people;
		pair<int, int> tmp = make_pair(distance, people);
		if (distance < S) { // 학교보다 왼쪽이면
			tmp.first = S - tmp.first;// 필요한 정보는 거리뿐이다
			left_stops[ll] = tmp; 
			ll++;
		}
		else { // 학교보다 오른쪽이면
			tmp.first -= S; // 필요한 정보는 거리뿐이다
			right_stops[rl] = tmp; 
			rl++;
		}
	}

	sort(left_stops, left_stops + ll, desc);
	sort(right_stops, right_stops + rl, desc); // 내림차 순으로 정렬한다. 

	int dst_idx = 0; 
	int left_distance = 0; 
	int current_K;
	// 왼쪽에 대해서 연산
	while(dst_idx < ll) {

		int dst_distance = left_stops[dst_idx].first;
		left_distance += dst_distance;

		current_K = K - left_stops[dst_idx].second;
		if (current_K < 0) {//맨 처음 부터 다음에 타야될 사람이 더 많은 경우 다음을 기약한다.
			left_stops[dst_idx].second = -current_K;
			left_distance += dst_distance;
			continue;
		}

		for (int i = dst_idx+1; i < ll; i++) {

			if (current_K == 0) break;
			int nxt_people = left_stops[i].second;

			if (current_K >= nxt_people) { // 공간이 남는 경우에 모두 태운다 
				current_K -= nxt_people;
				dst_idx++;
			}
			else { //남는 공간보다 다음에 타야될 사람이 더 많은 경우 다음을 기약한다.
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

	// 오른쪽에 대해 연산
	while (dst_idx < rl) {

		int dst_distance = right_stops[dst_idx].first;
		right_distance += dst_distance;
		current_K = K - right_stops[dst_idx].second;

		if (current_K < 0) {//맨 처음 부터 다음에 타야될 사람이 더 많은 경우 다음을 기약한다.
			right_stops[dst_idx].second = -current_K;
			right_distance += dst_distance;
			continue;
		}

		for (int i = (dst_idx + 1); i < rl; i++) {

			if (current_K == 0) break;
			int nxt_people = right_stops[i].second;

			if (current_K >= nxt_people) { // 공간이 남는 경우에 모두 태운다 
				current_K -= nxt_people;
				dst_idx++;
			}
			else { //남는 공간보다 다음에 타야될 사람이 더 많은 경우 다음을 기약한다.
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