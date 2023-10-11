#include <iostream>
#include <queue>
using namespace std;
const int MAX = 50;
int map[MAX][MAX];
bool visited[MAX][MAX];
queue<pair<int,int>> land;

int w,h;
int dx[] = {1,1,0,-1,-1,-1,0,1};
int dy[] = {0,1,1,1,0,-1,-1,-1};

bool isRange(int nx, int ny){
    return (nx>=0 && nx<w && ny>=0 && ny<h);
}

void bfs(){
    while(!land.empty()){
        int y = land.front().first;
        int x = land.front().second;

        land.pop();

        for(int i=0; i<8; i++){
            int ny = y + dy[i];
            int nx = x + dx[i];

            if(!isRange(nx, ny)){
                continue;
            }

            if(map[ny][nx] == 1 && !visited[ny][nx]){
                visited[ny][nx] = true;
                land.push(make_pair(ny,nx));
            }
        }
    }
}

int main(){
    while(true){
        cin >> w >> h;

        if(!w && !h){
            break;
        }

        for(int i=0; i<h; i++){
            for(int j=0; j<w ;j++){
                cin >> map[i][j];
                visited[i][j] = false;  //방문 여부 초기화
            }
        }

        int cnt = 0;
        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++){
                if(!visited[i][j] && map[i][j] == 1){
                    visited[i][j] = true;
                    land.push(make_pair(i,j));
                    bfs();
                    cnt++;
                }
            }
        }

        cout << cnt << "\n";
    }
}