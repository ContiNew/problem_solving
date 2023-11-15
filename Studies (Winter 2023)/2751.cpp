#include <iostream>
#include <queue>

using namespace std;


queue<string> bucket[10];//��� ��Ŷ
queue<string> minus_bucket[10];// ���� ��Ŷ
int N;
string arr[1000001];

string make_same_digits(string s, int digit) {
	string res = "";
	if (s.length() == digit) return s;
	else {
		int diff = digit - s.length();
		if (s.front() == '-') {
			for (int i = 0; i < diff; i++) {
				res.push_back('-');
			}
		}
		else {
			for (int i = 0; i < diff; i++) {
				res.push_back('0');
			}
		}
		res.append(s);
		return res;
	}
}

string convert(string _s) {
	string s = _s;
	while (s.front() == '-') {
		if (s[1] != '-')break; // �� �ڰ� - ��ȣ�� �ƴϸ�
		s.erase(s.begin());
	}
	while (s.front()== '0') {
		if (s.length()==1 && s[0] == '0')break;
		s.erase(s.begin());
	}
	return s;
}

void radix_sort(string* arr, int digit, int size) {	
	for (int i = 0; i < size; i++) {
		arr[i] = make_same_digits(arr[i], digit);
	} // digit�� �����ش�. 

	int cur_digit = digit - 1;
	while (cur_digit > -1) {
		for (int i = 0; i < size; i++) {
			if (arr[i].front() == '-') {
				int num = arr[i][cur_digit] - '0';
				if (arr[i][cur_digit] == '-') num = 0;
				minus_bucket[num].push(arr[i]); // �����϶��� ������ ��Ŷ����
			}
			else {
				int num = arr[i][cur_digit] - '0';
				bucket[num].push(arr[i]); // ����϶��� ����� ��Ŷ���� 
			}
		}
		int idx = 0;
		for (int i = 9; i > -1 ; i--) {
			while (!minus_bucket[i].empty()) { // ������ �������� ����
				arr[idx] = minus_bucket[i].front();
				minus_bucket[i].pop();
				idx++;
			}
		} // ������ �켱���� �����Ƿ� ���� �����Ѵ�.
		for (int i = 0; i < 10; i++) {
			while (!bucket[i].empty()) { // ����� ������
				arr[idx] = bucket[i].front();
				bucket[i].pop();
				idx++;
			}
		}
		--cur_digit;
	}
}


int main() {
	int size = 0;
	int maxdigits = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		string tmp;
		cin >> tmp;
		if (maxdigits < tmp.length()) {
			maxdigits = tmp.length();
		}
		arr[i] = tmp;
		size++;
	}
	radix_sort(arr, maxdigits, size);
	for (int i = 0; i < N; i++) {
		string res = convert(arr[i]);
		cout << res << "\n";
	}
	return 0;
}