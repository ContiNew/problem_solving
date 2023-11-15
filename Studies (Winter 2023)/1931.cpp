#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct timepair { // 회의 시간을 나타내는 객체
	int start;
	int end;
	timepair(int s, int e) {
		start = s; end = e;
	}
};

bool endcmp(timepair* a, timepair* b) { // sort하는 기준, 빨리 끝나는 시간대를 앞에 세운다
	if (a->end == b->end) return (a->start < b->start); // 같은 시간에 끝나면 더 빨리 시작하는 회의를 우선시한다.(중간에 빈칸 최소화)
	else return(a->end < b->end);
}

/*
시작점이 기준이 아닌 끝점이 기준인 이유:
빨리 끝나는 회의를 기준으로 sorting한 vector를 생각하면, 그 뒤의 회의시간 객체도 최대한 빨리
끝나는 객체가 뒤따라 오게되고, 따라서 탐색을 하면서 볼 때, 상대적으로 더 많은 회의 횟수를
만족할 가능성이 생긴다.
*/

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	vector<timepair*> v; // 회의시간을 저장하는 백터
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int start, end;
		cin >> start >> end;
		v.push_back(new timepair(start, end)); //우선 회의시간 객체를 벡터에 삽입한다.
	}

	sort(v.begin(), v.end(), endcmp); // 회의시간의 끝을 기준으로 sort

	timepair* target = v[0];// 맨 첫번째 원소를 가져오고 시작한다.
	int count = 1;
	for (int i = 1; i < N; i++) {
		if (target->end <= v[i]->start) { //다음 요소가 target 회의 시간의 끝보다 크거나, 같은지 체크한다. 
			count++;
			target = v[i];
		}
	}
	cout << count;

	return 0;
}