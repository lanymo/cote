#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>

int N, M, K; // 포탑 수 N * M, 
int P[15][15]; // 공격력
int T[15][15]; // 마지막으로 공격한 시점
bool aff[15][15]; // 해당 턴에 공격에 관여했는지
int dist[15][15]; // 타켓까지 거리

// 레이저 공격 - 우 하 좌 상 순위대로 
int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};
int dr8[8] = {-1, -1, -1 , 0, 0, 1, 1, 1};
int dc8[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int wr(int r) {return (r % N + N) % N;}
int wc(int c) {return (c % M + M) % M;}

bool weaker(int i, int j, int ar, int ac){
    if (P[i][j] != P[ar][ac]) return P[i][j] < P[ar][ac];
    if (T[i][j] != T[ar][ac]) return T[i][j] > T[ar][ac];
    if ((i+j) != (ar+ac)) return i + j > ar + ac;
    return j > ac;
}

bool stronger(int i, int j, int tr, int tc){
    if (P[i][j] != P[tr][tc]) return P[i][j] > P[tr][tc];
    if (T[i][j] != T[tr][tc]) return T[i][j] < T[tr][tc];
    if ((i+j) != (tr+tc)) return i + j < tr + tc;
    return j < tc;
}

int main() {
    // 입력 처리
    cin >> N >> M >> K;

    // 초기 보드
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> P[i][j]; T[i][j] = 0;
        }
    }

    for (int turn = 1; turn <= K; turn++){
        int alive = 0;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                if (P[i][j] > 0) alive++;
            }
        }

        if (alive <= 1) break;

        // 공격자 선정: 공격력 낮은, 최근 공격한, r+c, c 높은
        int ar = -1, ac = -1; // 공격자 좌표
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                if (P[i][j] <= 0) continue;
                if (ar == -1 || weaker(i, j, ar, ac)) {ar = i; ac = j;}
            }
        }

        P[ar][ac] += N + M;
        T[ar][ac] = turn;

        // 공격 대상 선정
        int tr = -1, tc = -1;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                if (P[i][j] <= 0) continue;
                if (i == ar && j == ac) continue;
                if (tr == -1 || stronger(i, j, tr, tc)) {tr = i; tc = j;}
            }
        }

        // 타겟 기준 BFS
        memset(dist, -1, sizeof(dist));
        memset(aff, false, sizeof(aff));
        queue<pii> q;

        q.push({tr, tc});
        dist[tr][tc] = 0;

        while (!q.empty()){
            auto cur = q.front(); q.pop();
            
            for (int d = 0; d < 4; d++){
                int nr = wr(cur.first + dr[d]);
                int nc = wc(cur.second + dc[d]);

                if (P[nr][nc] <= 0 || dist[nr][nc] != -1) continue;

                q.push({nr,nc});
                dist[nr][nc] = dist[cur.first][cur.second] + 1;
            }
        }

        aff[ar][ac] = true;
        int affect = P[ar][ac];

        if (dist[ar][ac] != -1){ // 공격자 포탑까지 가는 경로 O
            // 레이저 공격
            int r = ar, c = ac;
            while (!(r == tr && c == tc)){
                for (int d = 0; d < 4; d++){
                    int nr = wr(r + dr[d]), nc = wc(c + dc[d]);
                    if (P[nr][nc] <= 0) continue;
                    if (dist[nr][nc] == dist[r][c] - 1) {
                        r = nr; c = nc; break;
                    }
                }

                aff[r][c] = true;
                if (r == tr && c == tc) P[r][c] -= affect;
                else P[r][c] -= (affect / 2);
            }

        }else{
            // 포탄 공격
            aff[tr][tc] = true;
            P[tr][tc] -= affect;

            for (int d = 0; d < 8; d++){
                int nr = wr(tr + dr8[d]), nc = wc(tc + dc8[d]);
                if (nr == ar && nc == ac) continue;
                if (P[nr][nc] <= 0) continue;
                aff[nr][nc] = true;
                P[nr][nc] -= (affect / 2);
            }
        }

        // 부서짐 처리와 경비
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                if (P[i][j] < 0) P[i][j] = 0;
            }
        }
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                if (P[i][j] > 0 && !aff[i][j]) P[i][j]++;
            }
        }

    }

    int ans = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) ans = max(ans, P[i][j]);
    cout << ans << "\n";

    return 0;
}