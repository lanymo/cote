#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int N, M, K; // 미로 크기, 참가자 수, 
int board[15][15]; // 미로 격자, 0: 빈 칸, 1~9: 내구도

struct Participant{
    int r, c;
    bool escaped = false;
};
vector<Participant> ps;

int tr, tc; // 출구 좌표

// 상하좌우, 상하 우선!
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

// 전체 이동거리 합
int totalMove = 0;
int remain; // 남아 있는 참가자 수

int dist(int r, int c) {return abs(r - tr) + abs(c - tc);}

void moveAll(){
    
    for (auto& p : ps){
        if (p.escaped == true) continue;

        int cur = dist(p.r, p.c);

        for (int d = 0; d < 4; d++){
            int nr = p.r + dr[d];
            int nc = p.c + dc[d];

            if (nr < 1 || nr > N || nc < 1 || nc > N || board[nr][nc] != 0) continue;
            if (dist(nr, nc) >= cur) continue;

            p.r = nr; p.c = nc;
            totalMove++;
            break;
        }

        if (p.r == tr && p.c == tc){
            remain--;
            p.escaped = true;
        }
    }

}

bool inSquare(int r, int c, int sr, int sc, int L){
    return sr <= r && r <= sr + L -1 && sc <= c && c <= sc + L -1;
}

void rotateMaze(){

    // 정사각형 영역 선택
    for (int L = 2; L <= N; L++){
        for (int sr = 1; sr + L -1 <= N; sr++){
            for (int sc = 1; sc + L -1 <= N; sc++){
                if (!inSquare(tr, tc, sr, sc ,L)) continue;

                bool hasP = false;
                for (auto& p : ps){
                    if (!p.escaped && inSquare(p.r, p.c, sr, sc, L)){
                        hasP = true;
                        break;
                    }
                }
                if (!hasP) continue;

                // (sr + i, sc + j) -> 
                int tmp[15][15];
                for (int i = 0; i < L; i++){
                    for (int j = 0; j < L; j++){
                        tmp[j][L-1-i] = board[sr+i][sc+j];
                    }
                }

                for (int i = 0; i < L; i++){
                    for (int j = 0; j < L; j++){
                        int v = tmp[i][j];
                        board[sr + i][sc + j] = (v > 0) ? v - 1 : 0;
                    }
                }

                // 참가자와 출구 정보 수정
                for (auto& p : ps){
                    if (p.escaped) continue;
                    if (!inSquare(p.r, p.c, sr, sc, L)) continue;
                    int i = p.r - sr, j = p.c - sc;
                    p.r = sr + j;
                    p.c = sc + L - 1 - i;
                }

                int i = tr - sr, j = tc - sc;
                tr = sr + j;
                tc = sc + L -1 - i;


                return;
            }
        }
    }
}

int main() {
    cin >> N >> M >> K;

    remain = M;

    // 보드 입력
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            cin >> board[i][j];
        }
    }

    // 참가자 정보
    for (int i = 0; i < M; i++){
        int r, c; 
        cin >> r >> c;
        Participant p;
        p.r = r; p.c = c;
        ps.push_back(p);
    }

    // 처음 출구 정보
    cin >> tr >> tc;

    while (K--){
        // 움직이기
        moveAll();

        if (remain == 0) break;
    
        // 회전
        rotateMaze();
    }

    cout << totalMove << "\n";
    cout << tr << " " << tc;

    return 0;
}