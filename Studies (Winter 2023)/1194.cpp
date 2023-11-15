#include <iostream>
#include <queue>

using namespace std;

char maze[51][51];
int visited[51][51][(1 << 6)]; // 키의 상태에 따라 방문 여부를 변화를 준다.

int N, M; // 세로크기, 가로크기
pair<int, int> startVertex; // 시작하는 정점의 위치
pair<int, int> directions[] = { {1,0},{-1,0},{0,1},{0,-1} };// 방향을 나타낸다.

struct save_point {
	int x, y, dist, key;
	save_point(int x, int y, int dist, int key) {
		this->x = x; 
		this->y = y;
		this->dist = dist;
		this->key = key;
	}
}; // BFS 순회중 현재 순회중인 정점의 정보와, 이때까지 누적된 거리, 가지고 있는 열쇠 현황을 저장

bool is_bound(int x, int y) {
	if (x > 0 && x <= M && y > 0 && y <= N) {
		return true;
	}
	else return false;
} // 해당 좌표가 그래프 범위 안에 있는지를 확인하는 함수

int main() {
	cin >> N >> M;
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= M; i++) {
			cin >> maze[i][j];
			if (maze[i][j] == '0') {
				startVertex.first = i; startVertex.second = j;
			}
		}
	} // 미로 정보 입력
	queue<save_point> q; // 탐색중인 위치,현재 정점까지의 거리, 현재 가지고 있는 열쇠 상태 
	q.push(save_point(startVertex.first, startVertex.second, 0,0)); // 시작 위치를 큐에 삽입
	visited[startVertex.first][startVertex.second][0] = true; 

	while (!q.empty()) {
		save_point now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int x = now.x;
			int y = now.y;
			int dist = now.dist;
			int key = now.key; // 탐색중인 정점 데이터를 가져온다 

			x += directions[d].first; 
			y += directions[d].second;

			if (!is_bound(x, y)|| maze[x][y] == '#') {
				continue;
			}// 이동한 후, 이동한 정점이 미로의 범위 안에 있는지 확인한다. 또는 해당하는 좌표가 벽인지 확인

			if (visited[x][y][key])continue; // 해당 정점이 이미 방문된 정점인지를 확인 
			
			if (maze[x][y] == '.'|| maze[x][y] == '0') { // 1. 평범하게 통과가능한 구역을 지나가는 경우
				visited[x][y][key] = true;
				q.push(save_point(x, y ,dist + 1,key));
			}
			else if (maze[x][y] >= 'a' && maze[x][y] <= 'f') { //2. 열쇠를 줍게 되는 경우 
				key |= (1 << maze[x][y] - 'a'); // 키를 보유하게 되므로 보유현황을 갱신한다.
				visited[x][y][key] = true;
				q.push(save_point(x, y, dist + 1, key));
			}
			else if (maze[x][y] >= 'A' && maze[x][y] <= 'F') { // 3. 문을 만나게 되는경우
				int tmp_key = key;
				if (tmp_key &= 1 << (maze[x][y] - 'A')) { // 해당하는 열쇠가 있는지를 확인한다. 
					visited[x][y][key] = true;
					q.push(save_point(x, y, dist + 1, key));
				}
			}
			else if (maze[x][y] == '1') { // 4. 출구를 만나게 되는 경우
				visited[x][y][key] = true;
				cout << dist + 1 << "\n";
				return 0;
			}
		}
	}
	cout << -1 << "\n";
	return 0;
}