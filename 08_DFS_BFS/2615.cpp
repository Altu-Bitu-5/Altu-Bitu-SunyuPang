#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix; //바둑판을 위한 2차원 vector 
const int SIZE = 20, EMPTY = 0; //바둑판의 크기 나타내는 size, 비었을 때를 나타내는 empty 상수로 선언 -> 직관적이게

// 방향에 따른 좌표 증가량
// 맨 왼쪽 위 바둑알을 기준으로 검사하기 때문에 오른쪽+아래쪽으로 향하는 방향만 정의
const vector<int> dx = {-1, 0, 1, 1};   //x축 방향 좌표 증가량
const vector<int> dy = {1, 1, 1, 0};    //y축 방향 좌표 증가량

bool isValid(matrix &board, int x, int y, int color) {  // 범위와 바둑알의 종류가 유효한지 확인
    return (x > 0 && x < SIZE && y > 0 && y < SIZE && board[x][y] == color);    //바둑판을 벗어나지 않는지, 바둑알의 색이 유효한지 확인
}

bool checkWin(matrix &board, int x, int y) {    // 해당 좌표(x, y)부터 연속적으로 5알이 놓이는지 확인
    int color = board[x][y]; // 기준 색
    
    for (int idx = 0; idx < 4; idx++) { // 4 방향에 대해 검사
        int cnt = 1;    // cnt: 같은 방향에 놓인 같은 색 바둑알의 수
        int prev_x = x - dx[idx], prev_y = y - dy[idx]; //이전 방향
        int next_x = x + dx[idx], next_y = y + dy[idx]; //다음 방향
          
        if (isValid(board, prev_x, prev_y, color)) {    // 같은 방향에서 그 이전에도 같은 색 바둑알이 있었다면
            continue;   // 패스(-> 여섯 알 이상 놓이는 경우를 제외하기 위함)
        }
        
        while (isValid(board, next_x, next_y, color) && cnt < 6) {  // 연속적으로 놓인 5알이 같은 색이라면
            next_x += dx[idx];  //바둑알 x축 증가량만큼 이동
            next_y += dy[idx];  //바둑알 y축 증가량만큼 이동
            cnt++;  // cnt(같은 방향에 놓인 같은 색 바둑알의 수) 증가
        }
         
        if (cnt == 5) { // cnt가 5일 때만
            return true;    // true 리턴 (-> 다섯 알보다 적거나 다섯 알보다 많이 놓이는 경우를 제외)            
        }
    }
    return false;   //졌다면 false 리턴
}

int main() {
    // 입력
    matrix board(SIZE, vector<int>(SIZE, 0)); // 바둑판 선언, 초기화
    for (int i = 1; i < SIZE; i++)  //x가 size인 동안
        for (int j = 1; j < SIZE; j++)  //y가 size인 동안
            cin >> board[i][j]; //각 자리의 상태(없음:0, 검은바둑알:1, 흰바둑알:2) 입력

    // 연산 및 출력
    for (int y = 1; y < SIZE; y++) {    //y가 size인 동안
        for (int x = 1; x < SIZE; x++) {    //x가 size인 동안
            if (board[x][y] == EMPTY) { // 빈 칸이면
                continue;   // 패스
            }
            // 해당 좌표(x, y)부터 연속적으로 5알이 놓였다면 정답 출력
            if (checkWin(board, x, y)) {    //이겼디면
                cout << board[x][y] << '\n' //바둑알의 색 출력
                     << x << ' ' << y;  //가장 왼쪽에 있는 바둑알의 가로줄 번호와, 세로줄 번호를 순서대로 출력
                return 0;   //종료
            }
        }
    }
    cout << 0;  //승부가 결정나지 않았다면 0 출력
}