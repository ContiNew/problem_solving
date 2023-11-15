#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;


struct city {
	int x, y, type;
	city(int x, int y, int type) {
		this->x = x;
		this->y = y;
		this->type = type;
	}
	city(){
		x = y = type = 0;
	}
};

int min_time[1000][1000];
city cities[1000];

int main() {
	int N, M, T; // ������ ��, �־��� ���� ��, �ڷ���Ʈ�� �ɸ��� �ð�
	cin >> N >> T;
	
	for (int i = 0; i < N; i++) {
		int s, x, y;
		cin >> s >> x >> y;
		city c(x,y,s);
		cities[i] = c;
	} // �������� ������ �Է� ��, �ε��� �̿��ؼ� �ؽ�
	
	for(int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) min_time[i][j] = 0;
			else {
				int xlen = abs((cities[i].x - cities[j].x));
				int ylen = abs((cities[i].y - cities[j].y));
				int len = xlen + ylen;
				min_time[i][j] = len;
			}
		}
	} // �׷��� �ʱ�ȭ

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (cities[i].type == 1 && cities[j].type == 1) {
					min_time[i][j] = min({ min_time[i][j], min_time[i][k] + min_time[k][j], T });
				}
				else {
					min_time[i][j] = min(min_time[i][j], min_time[i][k] + min_time[k][j]);
				}
			}
		}
	} // �÷��̵� �ͼ�

	cin >> M;
	
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		--a; --b; // �ε����� 0���� �־��� ������ �����Ѵ�.

		cout << min_time[a][b] << "\n";
	}
	
	return 0; 
}