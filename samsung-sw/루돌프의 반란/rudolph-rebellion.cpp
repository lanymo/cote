#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, P, C, D; // 게임판 크기, 게임 턴 수, 산타 수, 루돌프 힘, 산타 힘
int board[55][55]; // 게임판
int rr, rc; // 루돌프 위치

struct Santa{
    int r, c;
    bool alive = true;
    int stun = 0; // 스턴 턴
    int score = 0;
};
Santa santas[35];

// 산타 이동 상우하좌
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int dist(int r1, int c1, int r2, int c2){
    return (r1 - r2) * (r1- r2) + (c1 - c2) * (c1 - c2);
}

void push(int idx, int ddr, int ddc, int k){
    board[santas[idx].r][santas[idx].c] = 0;

    int nr = santas[idx].r + ddr * k;
    int nc = santas[idx].c + ddc * k;

    if (nr < 1 || nr > N || nc < 1 || nc > N){
        santas[idx].alive = false;
        return;
    }

    if (board[nr][nc]){
        push(board[nr][nc], ddr, ddc, 1);
    }

    santas[idx].r = nr; santas[idx].c = nc;
    board[nr][nc] = idx;
}

void moveR(int turn){
    // 가까운 산타 향해 돌진 (거리 작은 순 -> r 큰 순 -> c 큰 순)
    int minDist = 987654321;
    int target = -1, tr = -1, tc = -1;
    for (int i = 1; i <= P; i++){
        if (!santas[i].alive) continue;

        int cur = dist(rr, rc, santas[i].r, santas[i].c);

        if (cur < minDist || (cur == minDist && santas[i].r > tr)
                          || (cur == minDist && santas[i].r == tr && santas[i].c > tc)){
            minDist = cur; tr = santas[i].r; tc = santas[i].c; target = i;
        }
    }

    // 한 칸 이동
    int ddr = (tr > rr) - (tr < rr);
    int ddc = (tc > rc) - (tc < rc);
    rr += ddr; rc += ddc;

    // 충돌 확인
    if (rr == santas[target].r && rc == santas[target].c) {
        santas[target].score += C;
        santas[target].stun = turn + 1;
        push(target, ddr, ddc, C);
    }
}

void moveS(int idx, int turn){
    Santa& s = santas[idx];

    int minDist = dist(s.r, s.c, rr, rc);
    int bd = -1;

    for (int i = 0; i < 4; i++){
        int nr = s.r + dr[i];
        int nc = s.c + dc[i];

        if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
        if (board[nr][nc] != 0) continue;

        int cur = dist(nr, nc, rr, rc);

        if (cur < minDist){
            minDist = cur; bd = i;
        }
    }

    // 한 칸 이동
    if (bd == -1) return;

    board[s.r][s.c] = 0;
    s.r += dr[bd]; s.c += dc[bd];
    board[s.r][s.c] = idx;

    if (s.r == rr && s.c == rc){ // 루돌프랑 충돌하는 경우
        s.score += D;
        s.stun = turn + 1;
        push(idx, -dr[bd], -dc[bd], D);
    }
}

int main() {
    cin >> N >> M >> P >> C >> D; // 각 요소
    cin >> rr >> rc; // 루돌프 초기 위치 

    for (int i = 0; i < P; i++){
        int num, sr, sc;
        cin >> num >> sr >> sc;

        santas[num].r = sr;
        santas[num].c = sc;
        board[sr][sc] = num;
    }

    for(int turn = 1; turn <= M; turn++){

        // 종료 조건 확인
        int alive_cnt = 0;
        for (int i = 1; i <= P; i++){
            if (santas[i].alive) alive_cnt++;
        }

        if (alive_cnt == 0) break;

        // 여기부터 게임 시작
        // 1. 루돌프 이동
        moveR(turn);
        // 2. 산타 이동
        for (int i = 1; i <= P; i++){
            if (!santas[i].alive) continue;
            if (santas[i].stun >= turn) continue;
            moveS(i, turn);
        }
        //3. 턴 끝날 때마다 점수 부여
        for (int i = 1; i <= P; i++){
            if (santas[i].alive) santas[i].score++;
        }
    }

    for (int i = 1; i <= P; i++){
        cout << santas[i].score << " ";
    }

    return 0;
}