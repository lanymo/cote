#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define pii pair<int, int>

const int OFFSET = 3;

int R, C, K; 

pii inform[1001]; // 골렘 입력 정보 
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int grid[75][75];
bool isExit[75][75];
int answer = 0;

/*
r,c가 중심인 골렘의 영역
(r,c) (r-1,c) (r+1,c) (r,c+1) (r,c-1)
출구는 (r,c) 제외 

남쪽 이동: (r+1, c-1) (r+1, c+1) (r+2, c)가 비어있는 경우 이동 가능 

불가 -> 서쪽 회전
서쪽 이동: (r-1, c-1) (r+1, c-1) (r, c-2)
후 남쪽으로 이동 가능한지 (r+c, c-1) (r+1, c+1) (r+2, c)
이동 후 반시계 회전

불가 -> 동쪽 방향으로 회전
동쪽 이동: (r+1, c+1) (r-1, c+1) (r, c+2) 
후 남쪽으로 이동 마찬가지 
이동 후 시계 회전 
*/

bool in_range(int r, int c) { // 이동 가능 여부 확인
    if (c - 1 < 1 || c + 1 > C) return false;
    if (r + 1 > OFFSET + R) return false;
    if (grid[r][c] != 0) return false;
    for (int k = 0; k < 4; k++){
        if (grid[r + dr[k]][c + dc[k]] != 0) return false;
    }
    return true;
}

bool is_outside(int r) { // 이동 멈춘 후 리셋 조건 확인 
    return (r - 1 < OFFSET + 1);
}

void init_grid(){
    memset(grid, 0, sizeof(grid));
    memset(isExit, false, sizeof(isExit));
}

void stamp(int id, int r, int c, int d){
    // 골렘이 멈춘 후 grid에 표시 
    grid[r][c] = id;
    for (int k = 0; k < 4; k++){
        grid[r + dr[k]][c + dc[k]] = id;
    }
    isExit[r + dr[d]][c + dc[d]] = true; 
}

bool visited[75][75];

int bfs(int r, int c){
    // 최대한 남쪽으로 이동
    memset(visited, false, sizeof(visited));

    int maxRow = r + 1;

    queue<pii> q;
    q.push({r,c}); visited[r][c] = true;

    while(!q.empty()){
        pii cur = q.front(); q.pop();
        int curId = grid[cur.first][cur.second];

        for (int i = 0; i < 4; i++){
            int nr = cur.first + dr[i];
            int nc = cur.second + dc[i];

            if (visited[nr][nc] || grid[nr][nc] == 0) continue;
            if (grid[nr][nc] == curId || isExit[cur.first][cur.second]){
                q.push({nr, nc});
                visited[nr][nc] = true;
                maxRow = max(maxRow, nr);
            }
        }

    }

    return maxRow;
}

void drop(int &r, int &c, int &d){
    while (true){
        // 남, 서, 북 방향 가능 확인 + 이동
        if (in_range(r+1, c)){
            r++;
        }else if (in_range(r, c-1) && in_range(r+1, c-1)){
            c--;
            r++;
            d = (d+3) % 4;
        }else if (in_range(r, c+1) && in_range(r+1, c+1)){
            c++;
            r++;
            d = (d+1) % 4;
        }
        else break;
    }
}

int main() {
    cin >> R >> C >> K;

    int c, d;
    // d: 0 1 2 3 (북, 동, 남, 서)

    for (int i = 0; i < K; i++){
        cin >> c >> d;
        inform[i] = {c, d};
    }

    for (int i = 0; i < K; i++){
        pii cur = inform[i];
        int cr = 2;
        int cc = cur.first;
        int cd = cur.second;

        // 골렘 drop 위치 찾기
        drop(cr, cc, cd);

        if (is_outside(cr)){
            init_grid();
            continue;
        }

        stamp(i + 1, cr, cc, cd);
        answer += bfs(cr, cc) - OFFSET;
        
    }

    cout << answer << "\n";

    return 0;
}