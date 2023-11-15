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
//vector<int> graph_without_SCC[1250]; //SCC간 간선이 제거된 그래프
vector<int> graphT_without_SCC[1250]; //SCC간 간선이 제거된 전치그래프
bool visited[1250]{ false }; // 첫 DFS에서의 방문여부
bool visitedT[1250]{ false }; // 두번쨰 DFS에서의 방문여부
//bool visited_without_SCC[1250]{ false }; //
bool visitedT_without_SCC[1250]{ false }; // 

long long scores[1250]; // 정점이 가진 점수
int scc_gids[1250]; // 각정점이 소속되어있는 scc그룹은 어디인지 저장하는 배열

stack<int> dfs_order;
int vertexNo = 0; // 사이트 이름에 대해 붙일 번호

int getVertexNo(unordered_map<string, int>& map, string key); // 스트링으로 된 사이트 이름을 정수형으로 바꿔줌
void DFSfirst(int idx, stack<int>& order);
void DFSSecond(int startVertex, int curVertex);
void scoring(int vertexNo);

int main() {
	int N; cin >> N;
	
	for (int i = 0; i < N; i++) {
		int dstVertexNo, srcVertexNo;
		string dst; int edges;
		cin >> dst >> edges;
		dstVertexNo = getVertexNo(map,dst);
		for (int i = 0; i < edges; i++) {
			string src;// 기점 정점
			cin >> src;
			srcVertexNo = getVertexNo(map, src);
			graph[srcVertexNo].push_back(dstVertexNo); 
			graphT[dstVertexNo].push_back(srcVertexNo);
		}
	}
	// 그래프 생성 및 딕셔너리를 이용한 그래프에서의 맵 설정

	int vertices = map.size(); //버텍스들의 총 갯수를 구한다
	for (int i = 0; i < vertices; i++) { // 버텍스들의 기본 점수를 1로 초기화
		scores[i] = 1;
	}

	for (int i = 0; i < vertices; i++) {
		DFSfirst(i, dfs_order); // 모든 버텍스에 대해서 DFS를 돈다
	}

	while (!dfs_order.empty()) {
		int scc_leader = dfs_order.top();
		dfs_order.pop();
		DFSSecond(scc_leader, scc_leader);
	} 
	// 전치그래프에 대해서 한번 더 DFS를 수행해서 scc들을 구분한다. 

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			int dstVertex = graph[i][j];
			if (scc_gids[i] != scc_gids[dstVertex]) { // 같은 scc 그룹 안에 없을 때만
				//graph_without_SCC[i].push_back(dstVertex); // 연결해준다.
				graphT_without_SCC[dstVertex].push_back(i); //그 전치그래프도 같이 만들어준다. 
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
	int targetNo = map[target];

	cout << scores[targetNo];

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
			DFSSecond(startVertex,a);
		}
		scc_gids[curVertex] = startVertex;
	}
}

void scoring(int vertexNo) {
	vector<int> deeperVertice;
	if (!visitedT_without_SCC[vertexNo]) { 
		visitedT_without_SCC[vertexNo] = true;
		for (auto a : graphT_without_SCC[vertexNo]) {
			deeperVertice.push_back(a);// 연결되어있는 버텍스들을 기록한다. 
			scoring(a);
		}
		long long currentScore = 0;
		for (auto a : deeperVertice) { // 연결된 버텍스들의 점수를 수집한다.
			currentScore += scores[a];
		}
		scores[vertexNo] += currentScore; // bottom -up 식으로 기록한다. 
	}
	
}

//void topologic_sort(int vertexNo, stack<int>& order) {
//	if (!visited[vertexNo]) {
//		visited[vertexNo] = true;
//		for (auto a : graph[vertexNo]) {
//			topologic_sort(a, order);
//		}
//		order.push(vertexNo); // 먼저 끝난 순으로 스택에 집어 넣는다
//	}
//}