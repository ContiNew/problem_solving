#include <iostream>
#include <vector>
#include <queue>

#define GREEN 0
#define RED 1
#define NOT_EXIST -1

using namespace std;

int tomatoes[100][100][100]; // 높이 세로 가로
queue<vector<int>> current_breadth;
int directions[6][3] 
= {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

int main() {

	ios::sync_with_stdio(0); cin.tie(0);

	int m, n, h; 
	cin >> m >> n >> h;
	int max_amount = m * n * h; // 상자안에 들어갈 전체 토마토수
	int ghost_tomatoes = 0; // 비어있는 토마토의 수
	int checked_tomatoes = 0; // 체크한 토마토의 수

	for (int k = 0; k < h; k++) { //높이에 대해서
		for (int j = 0; j < n; j++) { // 세로에 대해서
			for (int i = 0; i < m; i++) { // 가로에 대해서 
				int tmp;
				cin >> tmp;
				tomatoes[k][j][i] = tmp; // 토마토를 입력받는다 
				if (tmp == RED) { // 익은 토마토일 경우 위치를 체크한다.
					vector<int> loc = { i,j,k,0 }; //vector를 이용해 위치좌표를 잡아준다. 마지막 파라미터는 이 토마토가 익기위해 경과한시간.
					current_breadth.push(loc); // 이를 큐에 집어넣는다
				}
				else if (tmp == NOT_EXIST) ghost_tomatoes++; // 존재하지 않는 토마토는 따로 세준다.
			}
		}
	}
	
	int day = 0;
	while (!current_breadth.empty()) {
		vector<int> cur = current_breadth.front(); // 위치정보를 불러오고
		if (day < cur[3]) day++; // 날이 지났을 경우 day 데이터를 갱신한다. 
		checked_tomatoes++;  // 토마토를 체크했으므로 갱신한다. 
		for (int i = 0; i < 6; i++) { // 가능한 모든 방향에 대해서 BFS 순회를 진행한다. 
			int x = cur[0] + directions[i][0];
			int y = cur[1] + directions[i][1];
			int z = cur[2] + directions[i][2];
			int d = cur[3]; 

			if (x < 0 || x >= m) continue;
			if (y < 0 || y >= n) continue;
			if (z < 0 || z >= h) continue; // 범위를 넘어서는 경우 아무것도 하지 않는다. 
	
			int status = tomatoes[z][y][x];
			if (status == RED || status == NOT_EXIST) continue; // 상태가 이미 방문하거나 존재하지 않는경우도 아무것도 하지 않는다. 

			tomatoes[z][y][x] = RED; // 그 외의 경우에는 토마토를 익히고 
			vector<int> loc = { x,y,z,++d }; // 그 토마토의 위치에 대해서 저장한뒤, 하루 뒤에 익었으므로 날짜를 갱신한다. 
			current_breadth.push(loc); // 이를 큐에 집어넣어준다. 
		}
		current_breadth.pop(); // 모든 방향에 대한 순회를 마쳤으면 위치정보를 큐에서 빼준다.
	}

	int possible_tomatoes = max_amount - ghost_tomatoes - checked_tomatoes; // 토마토의 총량을 계산한다.
	if (possible_tomatoes > 0) cout << -1 << "\n"; // 총량이 양수인 경우에는 안익은 토마토가 존재하므로  -1을 출력
	else {
		cout << day << "\n"; // 그 외에는 연산완료된 날짜를 출력한다.
	}

	return 0;
}