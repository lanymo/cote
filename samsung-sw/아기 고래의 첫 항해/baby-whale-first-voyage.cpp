#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

#define pii pair<int, int>

int N, start_r, start_c, dir; // 초기 입력값
int maps[51][51]; // 바다 정보를 담을 배열
bool visited[51][51]; // 방문 여부 확인 용 배열 
int dist[51][51]; // bfs용 거리 배열 
int dist2[51][51];

// 방향 배열(좌 하 우 상)
int dr[] = {0, 1, 0, -1};
int dc[] = {-1, 0, 1, 0};

#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 3 

vector<pii> paths; // 출력 벡터
int cnt = 1; // 현재 탐색한 칸 수
int sea = 0; // 바다 칸 수 

int main() {
    int in_d; // 들어오는 방향값 설정 (1:상 2: 하 3: 좌 4: 우)
    
    // 1. 입력 받기 + 방향 설정
    cin >> N >> start_r >> start_c >> in_d;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> maps[i][j];
            if (maps[i][j] == 0) sea++;
        }
    }
    
    if (in_d == 1) dir = UP;
    else if (in_d == 2) dir = DOWN;
    else if (in_d == 3) dir = LEFT;
    else dir = RIGHT;

    // 탐험 시작
    int cr = start_r - 1;
    int cc = start_c - 1;
    visited[cr][cc] = true;
    paths.push_back({cr + 1,cc + 1});

    // 반복 탐험
    while(true){
        // 1단계 인접 탐험
        bool moved= true;

        while (moved){
            moved = false;
            int direction[4] = {
                dir, // 직진
                (dir + 1) % 4, // 좌회전
                (dir + 3) % 4, // 우회전
                (dir + 2) % 4 // 180도 회전
            };

            for (int i = 0; i < 4; i++){
                int d = direction[i];
                int nr = cr + dr[d];
                int nc = cc + dc[d];

                if (nr >= 0 && nr < N && nc >= 0 && nc < N && !visited[nr][nc] && maps[nr][nc] == 0){
                    moved = true;
                    cr = nr; cc = nc;
                    visited[cr][cc] = true;
                    dir = d; cnt++;
                    paths.push_back({cr + 1, cc + 1});
                    break;
                }
            }
        }

        // 전체 바다 탐색 여부 확인
        if (cnt == sea) break;

        // 2 단계 가장 가까운 바다로 이동 
        memset(dist, -1, sizeof(dist));

        // 2 - 1. 가까운 칸 찾기 (target 좌표 설정)
        queue<pii> q;
        q.push({cr, cc});
        dist[cr][cc] = 0;
        int target_r = -1, target_c = -1, target_dist = 987654321;

        while(!q.empty()){
            pii cur = q.front(); q.pop();

            if (!visited[cur.first][cur.second] && maps[cur.first][cur.second] == 0) {
                int d = dist[cur.first][cur.second];
                if (d < target_dist) {
                    target_dist = d;
                    target_r = cur.first;
                    target_c = cur.second;
                }else if (d == target_dist){
                    if (cur.first < target_r){
                        target_r = cur.first;
                        target_c = cur.second;
                    }else if (cur.first == target_r && cur.second < target_c){
                        target_c = cur.second;
                    }
                }
            }
            
            for (int i = 0; i < 4; i++){
                int nr = cur.first + dr[i];
                int nc = cur.second + dc[i];

                if (nr < 0 || nr >= N || nc < 0 || nc >= N || dist[nr][nc] != -1 || maps[nr][nc] == 1) continue;

                dist[nr][nc] = dist[cur.first][cur.second] + 1;
                q.push({nr, nc});
            }
        }

        if (target_r == -1) break;

        // 2 -2. target 기준 거리 계산
        memset(dist2, -1, sizeof(dist2));
        queue<pii> q2;
        q2.push({target_r, target_c});
        dist2[target_r][target_c] = 0;

        while(!q2.empty()){
            pii cur = q2.front(); q2.pop();

            for (int i = 0; i < 4; i++){
                int nr = cur.first + dr[i];
                int nc = cur.second + dc[i];

                if (nr < 0 || nr >= N || nc < 0 || nc >= N || dist2[nr][nc] != -1 || maps[nr][nc] == 1) continue;

                dist2[nr][nc] = dist2[cur.first][cur.second] + 1;
                q2.push({nr, nc});
            }
        }
        
        // 경로 시뮬레이션
        while (cr != target_r || cc != target_c){
            int current = dist2[cr][cc];

            for (int i = 0; i < 4; i++){
                int nr = cr + dr[i];
                int nc = cc + dc[i];

                if (nr >= 0 && nr < N && nc >= 0 && nc < N && dist2[nr][nc] == current - 1){
                    cr = nr; cc = nc;
                    dir = i;
                    break;
                }
            }
        }
        
        visited[cr][cc] = true;
        cnt++;
        paths.push_back({cr + 1, cc + 1});
    }

    for (auto p : paths){
        cout << p.first << " " << p.second << "\n";
    }
    
    return 0;
}