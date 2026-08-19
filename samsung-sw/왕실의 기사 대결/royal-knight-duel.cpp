#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int L, N, Q;
int board[45][45]; // 체스판 (0: 빈칸, 1: 함정, 2: 벽)
int knight_at[45][45];

struct Knight{
    int r, c, h, w, k, damage = 0;
    bool alive = true;
    
};

vector<Knight> knights;

// d(0: 위, 1: 오른, 2: 아래, 3: 왼)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void rebuild(){
    memset(knight_at, -1, sizeof(knight_at));
    for (int i = 1; i <= N; i++){
        if (!knights[i].alive) continue;

        Knight& kn = knights[i];
        for (int x = kn.r; x < kn.h + kn.r; x++){
            for (int y = kn.c; y < kn.w + kn.c; y++){
                knight_at[x][y] = i;
            }
        }
    }
}

vector<int> moveKnight(int i, int d){
    // i번째(i-1) 기사가 d 방향으로 한 칸 이동
    // 해당 칸에 다른 기사가 있다면 연쇄적으로 한 칸 밀림
    // 이동하려는 방향 끝에 벽이 있다면 모든 기사 이동 X
    // alive = false라면 명령 수행 X skip. 

    if (!knights[i].alive) return {};

    bool visited[35] = {false};
    queue<int> q; // 기사 번호를 담는 queue
    vector<int> pushed;

    q.push(i); visited[i] = true;

    while(!q.empty()){
        int cur = q.front(); q.pop();

        pushed.push_back(cur);

        int nr = knights[cur].r + dr[d];
        int nc = knights[cur].c + dc[d];

        for (int x = nr; x < nr + knights[cur].h; x++){
            for (int y = nc; y < nc + knights[cur].w; y++){
                if (x < 1 || x > L || y < 1 || y > L) return {};
                if (board[x][y] == 2) return{};

                int other = knight_at[x][y];
                if (other != -1 && !visited[other]){
                    q.push(other);
                    visited[other] = true;
                }
            }
        }
    }

    for (int idx : pushed){
        knights[idx].r += dr[d];
        knights[idx].c += dc[d];
    }

    rebuild();
    return pushed;
}

void getDamage(int i, vector<int> pushed){
    // i(i-1) 번째 기사는 피해 X 
    // 밀려난 기사들의 피해량
    // : 이동한 곳에서 w*h 내에 놓여있는 함정 수(board가 1) 만큼 피해 입음

    for (int idx : pushed){
        if (idx == i) continue;
        if (!knights[idx].alive) continue;

        Knight& kn = knights[idx];
        int cnt = 0;

        for (int x = kn.r; x < kn.h + kn.r; x++){
            for (int y = kn.c; y < kn.w + kn.c; y++){
                if (board[x][y] == 1) cnt++;
            }
        }

        kn.damage += cnt;
        kn.k -= cnt;

        if (kn.k <= 0) kn.alive = false;
    }
    
    rebuild();
}

int main() {
    // 초기 입력
    cin >> L >> N >> Q;
    
    knights.push_back(Knight());
    memset(knight_at, -1, sizeof(knight_at)); 

    // 체스판 정보 받기
    for (int i = 1; i <= L; i++){
        for (int j = 1; j <= L; j++){
            cin >> board[i][j];
        }
    }

    // 초기 기사 정보(기사끼리 겹침 X, 벽과 겹침 X)
    for (int i = 1; i <= N; i++){
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        Knight kn;
        kn.r = r; kn.c = c; kn.h = h; kn.w = w; kn.k = k;
        knights.push_back(kn);

        for (int x = r; x < r + h; x++){
            for (int y = c; y < c + w; y++){
                knight_at[x][y] = i;
            }
        }
    }

    // 명령 정보 수행 
    while(Q--){
        int i, d;
        cin >> i >> d;

        vector<int> pushed = moveKnight(i, d);
        getDamage(i, pushed);
    }

    int ans = 0;
    for (auto& kn : knights){
        if (kn.alive) ans += kn.damage;
    }

    cout << ans;

    return 0;
}