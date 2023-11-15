#include <iostream>
#include <vector>
#include <queue>

#define GREEN 0
#define RED 1
#define NOT_EXIST -1

using namespace std;

int tomatoes[100][100][100]; // ���� ���� ����
queue<vector<int>> current_breadth;
int directions[6][3]
= { {1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1} };

int main() {

	ios::sync_with_stdio(0); cin.tie(0);

	int m, n, h;
	cin >> m >> n >> h;
	int max_amount = m * n * h; // ���ھȿ� �� ��ü �丶���
	int ghost_tomatoes = 0; // ����ִ� �丶���� ��
	int checked_tomatoes = 0; // üũ�� �丶���� ��

	for (int k = 0; k < h; k++) { //���̿� ���ؼ�
		for (int j = 0; j < n; j++) { // ���ο� ���ؼ�
			for (int i = 0; i < m; i++) { // ���ο� ���ؼ� 
				int tmp;
				cin >> tmp;
				tomatoes[k][j][i] = tmp; // �丶�並 �Է¹޴´� 
				if (tmp == RED) { // ���� �丶���� ��� ��ġ�� üũ�Ѵ�.
					vector<int> loc = { i,j,k }; //vector�� �̿��� ��ġ��ǥ�� ����ش�. ������ �Ķ���ʹ� �� �丶�䰡 �ͱ����� ����ѽð�.
					current_breadth.push(loc); // �̸� ť�� ����ִ´�
				}
				else if (tmp == NOT_EXIST) ghost_tomatoes++; // �������� �ʴ� �丶��� ���� ���ش�.
			}
		}
	}

	while (!current_breadth.empty()) {
		vector<int> cur = current_breadth.front(); // ��ġ������ �ҷ�����
		checked_tomatoes++;  // �丶�並 üũ�����Ƿ� �����Ѵ�. 
		for (int i = 0; i < 6; i++) { // ������ ��� ���⿡ ���ؼ� BFS ��ȸ�� �����Ѵ�. 
			int x = cur[0] + directions[i][0];
			int y = cur[1] + directions[i][1];
			int z = cur[2] + directions[i][2];

			if (x < 0 || x >= m) continue;
			if (y < 0 || y >= n) continue;
			if (z < 0 || z >= h) continue; // ������ �Ѿ�� ��� �ƹ��͵� ���� �ʴ´�. 

			int status = tomatoes[z][y][x];
			if (status >= RED || status == NOT_EXIST) continue; // ���°� �̹� �湮�ϰų� �������� �ʴ°�쵵 �ƹ��͵� ���� �ʴ´�. 

			tomatoes[z][y][x] = 1 + tomatoes[cur[2]][cur[1]][cur[0]]; // �� ��쿡�� ��ȸ�ϸ鼭 �� ���� ���̿� �ִ� �丶�信 ����ġ�� �����ش�
			vector<int> loc = {x,y,z}; // �� �丶���� ��ġ�� ���ؼ� �����ϰ�
			current_breadth.push(loc); // �̸� ť�� ����־��ش�. 
		}
		current_breadth.pop(); // ��� ���⿡ ���� ��ȸ�� �������� ��ġ������ ť���� ���ش�.
	}

	int ans = 0;
	for (int k = 0; k < h; k++) { //���̿� ���ؼ�
		for (int j = 0; j < n; j++) { // ���ο� ���ؼ�
			for (int i = 0; i < m; i++) { // ���ο� ���ؼ� 
				if (tomatoes[k][j][i] == 0) {
					cout << "-1\n";
					return 0;
				}
				else {
					ans = max(ans, tomatoes[k][j][i]); // ���� �������� Ž���� �丶���� ����ġ ���� ���ϰ��� �ߴ� �����̴�
				}
			}
		}
	}
	cout << ans - 1 << "\n"; // 0���϶� ���� �丶���� ���°� 1�̹Ƿ� ���ش�

	return 0;
}