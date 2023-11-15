#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

unordered_map<string, int> map; // 문자열로 들어오는 사이트 이름을 해당하는 인덱스로 바꾼다. 
vector<int> graph[1250]; // 1차로 DFS를 돌 그래프 
vector<int> graphT[1250]; // 2차로 DFS를 돌 전치그래프
vector<int> graphT_without_SCC[1250]; //SCC간 간선이 제거된 전치그래프
bool visited[1250]{ false }; // 첫 DFS에서의 방문여부
bool visitedT[1250]{ false }; // 두번쨰 DFS에서의 방문여부
bool visitedT_without_SCC[1250]{ false }; // SCC간 간선이 제거된 전치그래프의 방문여부

long long scores[1250]; // 정점이 가진 점수
int scc_gids[1250]; // 각정점이 소속되어있는 scc그룹은 어디인지 저장하는 배열

stack<int> dfs_order;
int vertexNo = 0; // 사이트 이름에 대해 붙일 번호

int getVertexNo(unordered_map<string, int>& map, string key); // 스트링으로 된 사이트 이름을 정수형으로 바꿔줌
void DFSfirst(int idx, stack<int>& order); // 그래프를 DFS함으로써 위상정렬 했을때 순서를 스텍에 저장
void DFSSecond(int startVertex, int curVertex); // 위상정렬했을때의 스택에서 빠져나오는 순서대로 전치그래프를 DFS, SCC를 확인 
void scoring(int vertexNo); // 재귀를 돌면서 top-down 식으로 score들을 기록한다. 

int main() {
	int N; cin >> N;

	for (int i = 0; i < N; i++) {
		int dstVertexNo, srcVertexNo; // 변환될 도착지와 출발지의 정점번호
		string dst; int edges;
		cin >> dst >> edges;
		dstVertexNo = getVertexNo(map, dst); // 스트링을 키값으로 정점번호를 할당하고 저장
		for (int i = 0; i < edges; i++) {
			string src;// 기점 정점
			cin >> src;
			srcVertexNo = getVertexNo(map, src);
			graph[srcVertexNo].push_back(dstVertexNo);
			graphT[dstVertexNo].push_back(srcVertexNo);
		}
	}
	// 그래프와 전치그래프 생성 및

	int vertices = map.size(); //정점들의 총 갯수를 구한다
	for (int i = 0; i < vertices; i++) { // 정점들의 기본 점수를 1로 초기화
		scores[i] = 1;
	}

	for (int i = 0; i < vertices; i++) {
		DFSfirst(i, dfs_order); // 모든 정점에 대해서 DFS를 돈다. 
	}

	while (!dfs_order.empty()) {
		int scc_leader = dfs_order.top(); // 자기자신이 scc인 정점들로 이뤄진 그룹의 리더라고 생각하자
		dfs_order.pop();
		DFSSecond(scc_leader, scc_leader); 
	}
	// 전치그래프에 대해서 한번 더 DFS를 수행해서 scc들을 구분한다. 

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			int dstVertex = graph[i][j];
			if (scc_gids[i] != scc_gids[dstVertex]) { // 같은 scc 그룹 안에 없을 때만
				graphT_without_SCC[dstVertex].push_back(i); //SCC가 없는 전치그래프에 삽입한다.
			}
		}
	}
	// scc가 존재하지 않는 그래프를 만든다. 

	for (int i = 0; i < vertices; i++) {
		scoring(i);
	}
	// 전치 그래프를 순회하면서 그 점수를 기록해나간다. (DP 응용)

	string target; // 점수를 찾고자하는 타겟
	cin >> target;
	int targetNo = map[target]; // 타겟 버택스의 번호

	cout << scores[targetNo]; // 미리 계산해둔 결과를 출력한다. 

	return 0;
}


int getVertexNo(unordered_map<string, int>& map, string key) {
	// 스트링으로 된 사이트 이름을 정수형으로 바꿔줌
	if (map.find(key) == map.end()) {
		map[key] = vertexNo++;
	}
	int res = map[key];
	return res;
}

void DFSfirst(int vertexNo, stack<int>& order) {
	if (!visited[vertexNo]) {
		visited[vertexNo] = true;
		for (auto a : graph[vertexNo]) {
			DFSfirst(a, order);
		}
		order.push(vertexNo); // 먼저 끝난 순으로 스택에 집어 넣는다
	}
}

void DFSSecond(int startVertex, int curVertex) {
	if (!visitedT[curVertex]) {
		visitedT[curVertex] = true;
		for (auto a : graphT[curVertex]) {
			DFSSecond(startVertex, a);
		}
		scc_gids[curVertex] = startVertex; // 전치그래프를 순회 했을때도 연결이 된다면 
	}
}

void scoring(int vertexNo) {
	vector<int> adjVertice; 
	if (!visitedT_without_SCC[vertexNo]) { 
		visitedT_without_SCC[vertexNo] = true;
		for (auto a : graphT_without_SCC[vertexNo]) {
			adjVertice.push_back(a);// 연결되어있는 정점들을 기록한다. 
			scoring(a);
		}
		long long currentScore = 0;
		for (auto a : adjVertice) { // 연결된 정점들의 점수를 수집한다.
			currentScore += scores[a];
		}
		scores[vertexNo] += currentScore; //  scores 배열에 점수를 기록한다.
	}
} // 정점의 점수: 기본점수 + 나랑 연결된 상위 정점들의 점수의 합, 따라서 거꾸로 생각하면 이를 재귀형태로 풀수 있음