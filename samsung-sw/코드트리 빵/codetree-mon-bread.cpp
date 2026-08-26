#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define pii pair<int, int>

int n, m;
int board[20][20]; // 0: 빈 공간, 1: 베캠 위치
bool blocked[20][20]; // 지나갈 수 없는 칸  표기 

struct Person {
    int r, c; // 현재 위치
    int tr, tc; // 목표 편의점 위치
    bool done;
};
Person p[31];


// 1번 단계 우선순위에 따라 설정 
int dr[4] = {-1, 0, 0, 1};
int dc[4] = {0, -1, 1, 0}; 

int dist[20][20];

void bfs(int sr, int sc){ // 편의점에서부터 역순으로 가야
    memset(dist, -1, sizeof(dist));
    queue<pii> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});

    while(!q.empty()){
        pii cur = q.front(); q.pop();
        int r = cur.first;
        int c = cur.second;
        for (int d = 0; d < 4; d++){
            int nr = r + dr[d], nc = c + dc[d];

            if (nr < 1 || nr > n || nc < 1 || nc > n) continue;
            if (blocked[nr][nc] || dist[nr][nc] != -1) continue;

            q.push({nr, nc});
            dist[nr][nc] = dist[r][c] + 1;
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            cin >> board[i][j];
        }
    }

    for (int i = 1; i <= m; i++){
        int tr, tc; cin >> tr >> tc;
        p[i].tr = tr; p[i].tc = tc;
        p[i].r = p[i].c = -1; p[i].done = false;
    }

    for (int t = 1; ; t++){

        // 1번 단계 bfs
        for (int i = 1; i <= m; i++){
            if (p[i].r == -1 || p[i].done) continue;

            int saved_r = p[i].r, saved_c = p[i].c;
            bool saved = blocked[p[i].r][p[i].c];
            blocked[p[i].r][p[i].c] = false;

            bfs(p[i].tr, p[i].tc);
            int cur = dist[p[i].r][p[i].c];

            for (int d = 0; d < 4; d++){
                int nr = p[i].r + dr[d];
                int nc = p[i].c + dc[d];

                if (nr < 1 || nr > n || nc < 1 || nc > n) continue;
                if (dist[nr][nc] == cur - 1){
                    p[i].r = nr; p[i].c = nc;
                    break;
                }
            }

            blocked[saved_r][saved_c] = saved;
        }

        // 2번 단계 - 편의점 도착 확인 + 기록
        for (int i = 1; i <= m; i++){
            if (p[i].r == -1 || p[i].done) continue;
            if (p[i].r == p[i].tr && p[i].c == p[i].tc){
                p[i].done = true;
                blocked[p[i].r][p[i].c] = true;
            }
        }

        bool all_done = true;
        for (int i = 1; i <= m; i++) if (!p[i].done) all_done = false;

        if (all_done) { cout << t << "\n"; break;}

        // 3번 단계 - t번 사람의 베캠 확인 
        if (t <= m){
            // board[i][j] == 1인 것이랑 bfs 확인
            bfs(p[t].tr, p[t].tc);
            int br = -1, bc = -1;
            for (int i = 1; i <= n; i++){
                for (int j = 1; j <= n; j++){
                    if (blocked[i][j]) continue;
                    if (board[i][j] != 1) continue;
                    if (dist[i][j] == -1) continue;
                    if (br == -1 || dist[i][j] < dist[br][bc]) {br = i; bc = j;}
                }
            }
            p[t].r = br; p[t].c = bc;
            blocked[br][bc] = true;
        }
    }


    return 0;
}