#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int N, M, F;
int board[25][25];
int tw[5][12][12];
bool anom[25][25];

int dr[4] = {0, 0, 1, -1}; // 동 서 남 북
int dc[4] = {1, -1, 0, 0};

int wr, wc; // 시간의 벽 좌상단
int mr, mc; // 타임머신 시작 위치

// face: 0=동 1=서 2=남 3=북 4=윗면 5=바닥
bool visited[6][25][25];
struct State {int face, r, c;};

struct Anom {int r, c, d, v; bool alive;}; // r,c = 현재 뻗어나간 맨 끝
vector<Anom> anoms;

queue<State> q;

void spread(int t){
    for (auto& a : anoms){
        if (!a.alive) continue;
        if (t % a.v != 0) continue;

        int nr = a.r + dr[a.d];
        int nc = a.c + dc[a.d];

        if (nr < 0 || nr >= N || nc < 0 || nc >= N || board[nr][nc] != 0) {
            a.alive = false;
            continue;
        }

        anom[nr][nc] = true;
        a.r = nr;
        a.c = nc;
    }
}

State moveTo(State cur, int d){
    int f = cur.face;
    int nr = cur.r + dr[d];
    int nc = cur.c + dc[d];

    if (f == 5){ // 바닥
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) return {-1, 0, 0};
        return {5, nr, nc};
    }
    else if (f == 4){ // 윗면
        if (nr < 0)  return {3, 0, M-1-nc};   // 북면 (뒤집힘)
        if (nr >= M) return {2, 0, nc};
        if (nc < 0)  return {1, 0, nr};
        if (nc >= M) return {0, 0, M-1-nr};   // 동면 (뒤집힘)
        return {4, nr, nc};
    }
    else {
        if (nr < 0){ // 옆 -> 윗
            if (f == 0) return {4, M-1-nc, M-1};
            if (f == 1) return {4, nc, 0};
            if (f == 2) return {4, M-1, nc};
            return {4, 0, M-1-nc};
        }

        if (nr >= M){ // 옆 -> 바닥
            int br, bc;
            if (f == 0)      { br = wr + (M-1-nc); bc = wc + M; }
            else if (f == 1) { br = wr + nc;       bc = wc - 1; }
            else if (f == 2) { br = wr + M;        bc = wc + nc; }
            else             { br = wr - 1;        bc = wc + (M-1-nc); }
            if (br < 0 || br >= N || bc < 0 || bc >= N) return {-1, 0, 0};
            return {5, br, bc};
        }

        if (nc < 0){ // 시계 방향
            if (f == 0) return {2, nr, M-1};   // 동 -> 남
            if (f == 1) return {3, nr, M-1};   // 서 -> 북
            if (f == 2) return {1, nr, M-1};   // 남 -> 서
            return {0, nr, M-1};               // 북 -> 동
        }

        if (nc >= M){ // 반시계 방향
            if (f == 0) return {3, nr, 0};     // 동 -> 북
            if (f == 1) return {2, nr, 0};     // 서 -> 남
            if (f == 2) return {0, nr, 0};     // 남 -> 동
            return {1, nr, 0};                 // 북 -> 서
        }

        return {f, nr, nc};
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> F;

    wr = wc = -1;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> board[i][j];
            if (board[i][j] == 3 && wr == -1) { wr = i; wc = j; }
        }
    }

    for (int f = 0; f < 5; f++){
        for (int i = 0; i < M; i++){
            for (int j = 0; j < M; j++){
                cin >> tw[f][i][j];
                if (tw[f][i][j] == 2){ mr = i; mc = j; }
            }
        }
    }

    for (int i = 0; i < F; i++){
        int r, c, d, v;
        cin >> r >> c >> d >> v;
        anoms.push_back({r, c, d, v, true});
        anom[r][c] = true;
    }

    q.push({4, mr, mc});
    visited[4][mr][mc] = true;

    int t = 0;

    while (!q.empty()){
        t++;
        spread(t);

        int sz = q.size();

        for (int i = 0; i < sz; i++){
            State cur = q.front(); q.pop();

            for (int d = 0; d < 4; d++){
                State nxt = moveTo(cur, d);
                if (nxt.face == -1) continue;
                if (visited[nxt.face][nxt.r][nxt.c]) continue;

                if (nxt.face == 5){
                    if (board[nxt.r][nxt.c] == 4){
                        cout << t << "\n";
                        return 0;
                    }
                    if (board[nxt.r][nxt.c] != 0) continue;
                    if (anom[nxt.r][nxt.c]) continue;
                }else{
                    if (tw[nxt.face][nxt.r][nxt.c] == 1) continue;
                }

                visited[nxt.face][nxt.r][nxt.c] = true;
                q.push(nxt);
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}