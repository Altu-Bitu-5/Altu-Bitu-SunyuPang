#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX = 10001;

int cnt = 1; //해킹 가능한 컴퓨터 수

void dfs(int v, vector<int> *computer, bool *visited) {
    visited[v] = true;
 
    for (int i = 0; i < computer[v].size(); i++) {
        int next = computer[v][i];
 
        if (!visited[next]) {   //방문하지 않았으면
            visited[next] = true;
            dfs(next, computer, visited);
            cnt++;
        }
    }
}

int getMaxHack(vector<pair<int, int>> v){
    //max_element를 사용해보고 싶었는데 pair일 때 사용하는 법 모르겠음
    int maxHack = v[0].second;
    for (int i = 1; i < v.size(); i++) {
        if (v[i].second > maxHack) {
            maxHack = v[i].second;
        }
    }

    return maxHack;
}

int main() {
    int n, m;
    vector<int> computer[MAX];
    bool visited[MAX];
    vector<pair<int, int>> v; //컴퓨터 번호, 해킹 가능한 컴퓨터 #

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        computer[b].push_back(a);
    }
 
    for (int i = 1; i <= n; i++) {
        dfs(i, computer, visited);

        //visited 초기화
        for (int i = 0; i <= n; i++) {
            visited[i] = false;
        }
        //i번째 컴퓨터의 해킹 가능한 수 저장 
        v.push_back(make_pair(i, cnt));
        //cnt 초기화
        cnt = 1;
    }
 
    int maxHack = getMaxHack(v);    //해킹 가능한 최대 컴퓨터 수
 
    //maxHack인 컴퓨터 번호 출력
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second == maxHack) {
            cout << v[i].first << " ";
        }
    }

    return 0; 
}