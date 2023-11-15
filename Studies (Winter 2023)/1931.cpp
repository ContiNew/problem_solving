#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct timepair { // ȸ�� �ð��� ��Ÿ���� ��ü
	int start;
	int end;
	timepair(int s, int e) {
		start = s; end = e;
	}
};

bool endcmp(timepair* a, timepair* b) { // sort�ϴ� ����, ���� ������ �ð��븦 �տ� �����
	if (a->end == b->end) return (a->start < b->start); // ���� �ð��� ������ �� ���� �����ϴ� ȸ�Ǹ� �켱���Ѵ�.(�߰��� ��ĭ �ּ�ȭ)
	else return(a->end < b->end);
}

/*
�������� ������ �ƴ� ������ ������ ����:
���� ������ ȸ�Ǹ� �������� sorting�� vector�� �����ϸ�, �� ���� ȸ�ǽð� ��ü�� �ִ��� ����
������ ��ü�� �ڵ��� ���Եǰ�, ���� Ž���� �ϸ鼭 �� ��, ��������� �� ���� ȸ�� Ƚ����
������ ���ɼ��� �����.
*/

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	vector<timepair*> v; // ȸ�ǽð��� �����ϴ� ����
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int start, end;
		cin >> start >> end;
		v.push_back(new timepair(start, end)); //�켱 ȸ�ǽð� ��ü�� ���Ϳ� �����Ѵ�.
	}

	sort(v.begin(), v.end(), endcmp); // ȸ�ǽð��� ���� �������� sort

	timepair* target = v[0];// �� ù��° ���Ҹ� �������� �����Ѵ�.
	int count = 1;
	for (int i = 1; i < N; i++) {
		if (target->end <= v[i]->start) { //���� ��Ұ� target ȸ�� �ð��� ������ ũ�ų�, ������ üũ�Ѵ�. 
			count++;
			target = v[i];
		}
	}
	cout << count;

	return 0;
}