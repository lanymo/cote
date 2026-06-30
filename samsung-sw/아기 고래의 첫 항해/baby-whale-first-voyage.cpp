#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define pii pair<int, int>
#define all(x) x.begin(), x.end()

int N, start_r, start_c, d; // 맵 크기, (r,c) 초기 위치, 초기 방향
int initial_map[51][51]; // 초기 맵
bool visited[51][51]; // 방문 여부 확인
int dist[51][51]; // 현재 위치 기준 거리 (target 선택용)
int d2[51][51];   // target 기준 거리 (마지막 이동 방향 계산용)
vector<pii> path; // 고래 이동 위치를 담을 벡터 

int total_sea = 0;
int cnt = 0;

// 방향 순서 (상 우 하 좌)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// 2단계 이동 우선순서 (좌 하 우 상)
int move_dr[4] = {0, 1, 0, -1}; 
int move_dc[4] = {-1, 0, 1, 0};
int move_dir_map[4] = {3, 2, 1, 0}; // 좌 하 우 상 → 내부 방향 인덱스(상0 우1 하2 좌3)

int main() {
    int in_d;
    cin >> N >> start_r >> start_c >> in_d;

    // 방향 맞추기 (1상 2하 3좌 4우 → 내부 0상 1우 2하 3좌)
    if (in_d == 1) d = 0;
    else if (in_d == 2) d = 2;
    else if (in_d == 3) d = 3;
    else d = 1;

    // 1. 전체 map 정보 받기
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> initial_map[i][j];
            if (initial_map[i][j] == 0) total_sea++;
        }
    }

    int cur_r = start_r;
    int cur_c = start_c;
    path.push_back({cur_r, cur_c});
    cur_r--; cur_c--;
    visited[cur_r][cur_c] = true;
    cnt++;
    
    while (true) {
        bool moved = true;
        while (moved) {
            moved = false;
            int direction[4] = {
                d,            // 직진
                (d + 3) % 4,  // 좌회전
                (d + 1) % 4,  // 우회전
                (d + 2) % 4   // 180도 회전
            };

            for (int i = 0; i < 4; i++){
                int nd = direction[i];
                int nr = cur_r + dr[nd];
                int nc = cur_c + dc[nd];

                if (nr >= 0 && nr < N && nc >= 0 && nc < N
                    && initial_map[nr][nc] == 0 && !visited[nr][nc]){
                    cur_r = nr; cur_c = nc; d = nd;
                    visited[cur_r][cur_c] = true; 
                    path.push_back({cur_r + 1, cur_c + 1});
                    cnt++;
                    moved = true;
                    break;
                } 
            }
        }

        if (cnt == total_sea) break;

        memset(dist, -1, sizeof(dist));
        queue<pii> q;
        q.push({cur_r, cur_c});
        dist[cur_r][cur_c] = 0; 

        int best_r = -1, best_c = -1, best_d = 1e9;
        while(!q.empty()){
            pii cur = q.front(); q.pop();
            for (int i = 0; i < 4; i++){
                int nr = cur.first + dr[i];
                int nc = cur.second + dc[i];
                if (nr >= 0 && nc >= 0 && nr < N && nc < N
                    && initial_map[nr][nc] == 0 && dist[nr][nc] == -1){
                    dist[nr][nc] = dist[cur.first][cur.second] + 1;
                    q.push({nr, nc});
                    if (!visited[nr][nc]){
                        int dd = dist[nr][nc];
                        if (dd < best_d ||
                           (dd == best_d && nr < best_r) ||
                           (dd == best_d && nr == best_r && nc < best_c)){
                            best_d = dd; best_r = nr; best_c = nc;
                        }
                    }
                }
            }
        }

        if (best_r == -1) break; 

        int target_r = best_r, target_c = best_c;

        memset(d2, -1, sizeof(d2));
        queue<pii> q2;
        q2.push({target_r, target_c});
        d2[target_r][target_c] = 0;
        while (!q2.empty()) {
            pii cur = q2.front(); q2.pop();
            for (int i = 0; i < 4; i++) {
                int nr = cur.first + dr[i];
                int nc = cur.second + dc[i];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N
                    && initial_map[nr][nc] == 0 && d2[nr][nc] == -1) {
                    d2[nr][nc] = d2[cur.first][cur.second] + 1;
                    q2.push({nr, nc});
                }
            }
        }

        int sim_r = cur_r, sim_c = cur_c;
        while (sim_r != target_r || sim_c != target_c) {
            int current_dist = d2[sim_r][sim_c];
            for (int i = 0; i < 4; i++) {
                int nr = sim_r + move_dr[i];
                int nc = sim_c + move_dc[i];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N
                    && d2[nr][nc] == current_dist - 1) {
                    d = move_dir_map[i]; 
                    sim_r = nr; sim_c = nc;
                    break;
                }
            }
        }

        cur_r = target_r; cur_c = target_c;
        visited[cur_r][cur_c] = true;
        cnt++;
        path.push_back({cur_r + 1, cur_c + 1});
    }

    for (size_t i = 0; i < path.size(); i++)
        cout << path[i].first << " " << path[i].second << "\n";

    return 0;
}