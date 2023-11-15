#include <iostream>
#include <queue>

using namespace std;

char maze[51][51];
int visited[51][51][(1 << 6)]; // Ű�� ���¿� ���� �湮 ���θ� ��ȭ�� �ش�.

int N, M; // ����ũ��, ����ũ��
pair<int, int> startVertex; // �����ϴ� ������ ��ġ
pair<int, int> directions[] = { {1,0},{-1,0},{0,1},{0,-1} };// ������ ��Ÿ����.

struct save_point {
	int x, y, dist, key;
	save_point(int x, int y, int dist, int key) {
		this->x = x; 
		this->y = y;
		this->dist = dist;
		this->key = key;
	}
}; // BFS ��ȸ�� ���� ��ȸ���� ������ ������, �̶����� ������ �Ÿ�, ������ �ִ� ���� ��Ȳ�� ����

bool is_bound(int x, int y) {
	if (x > 0 && x <= M && y > 0 && y <= N) {
		return true;
	}
	else return false;
} // �ش� ��ǥ�� �׷��� ���� �ȿ� �ִ����� Ȯ���ϴ� �Լ�

int main() {
	cin >> N >> M;
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= M; i++) {
			cin >> maze[i][j];
			if (maze[i][j] == '0') {
				startVertex.first = i; startVertex.second = j;
			}
		}
	} // �̷� ���� �Է�
	queue<save_point> q; // Ž������ ��ġ,���� ���������� �Ÿ�, ���� ������ �ִ� ���� ���� 
	q.push(save_point(startVertex.first, startVertex.second, 0,0)); // ���� ��ġ�� ť�� ����
	visited[startVertex.first][startVertex.second][0] = true; 

	while (!q.empty()) {
		save_point now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int x = now.x;
			int y = now.y;
			int dist = now.dist;
			int key = now.key; // Ž������ ���� �����͸� �����´� 

			x += directions[d].first; 
			y += directions[d].second;

			if (!is_bound(x, y)|| maze[x][y] == '#') {
				continue;
			}// �̵��� ��, �̵��� ������ �̷��� ���� �ȿ� �ִ��� Ȯ���Ѵ�. �Ǵ� �ش��ϴ� ��ǥ�� ������ Ȯ��

			if (visited[x][y][key])continue; // �ش� ������ �̹� �湮�� ���������� Ȯ�� 
			
			if (maze[x][y] == '.'|| maze[x][y] == '0') { // 1. ����ϰ� ��������� ������ �������� ���
				visited[x][y][key] = true;
				q.push(save_point(x, y ,dist + 1,key));
			}
			else if (maze[x][y] >= 'a' && maze[x][y] <= 'f') { //2. ���踦 �ݰ� �Ǵ� ��� 
				key |= (1 << maze[x][y] - 'a'); // Ű�� �����ϰ� �ǹǷ� ������Ȳ�� �����Ѵ�.
				visited[x][y][key] = true;
				q.push(save_point(x, y, dist + 1, key));
			}
			else if (maze[x][y] >= 'A' && maze[x][y] <= 'F') { // 3. ���� ������ �Ǵ°��
				int tmp_key = key;
				if (tmp_key &= 1 << (maze[x][y] - 'A')) { // �ش��ϴ� ���谡 �ִ����� Ȯ���Ѵ�. 
					visited[x][y][key] = true;
					q.push(save_point(x, y, dist + 1, key));
				}
			}
			else if (maze[x][y] == '1') { // 4. �ⱸ�� ������ �Ǵ� ���
				visited[x][y][key] = true;
				cout << dist + 1 << "\n";
				return 0;
			}
		}
	}
	cout << -1 << "\n";
	return 0;
}