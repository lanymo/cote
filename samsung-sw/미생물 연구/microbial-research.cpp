#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
const int MAXN = 16;
const int MAXQ = 51;

int N, Q;
int board[MAXN][MAXN];
vector<pii> cells[MAXQ];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};
bool visited[MAXN][MAXN]; 

void collect(){
    for (int i = 0; i <= Q; i++){
        cells[i].clear();
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (board[i][j]) cells[board[i][j]].push_back({i, j});
        }
    }
}

void check_divided(){
    // bfs로 나눠지면 삭제 
    for (int id = 1; id <= Q; id++){
        if (cells[id].empty()) continue;

        memset(visited, false, sizeof(visited));
        queue<pii> q;

        q.push({cells[id][0].first, cells[id][0].second});
        visited[cells[id][0].first][cells[id][0].second] = true;
        int cnt = 1;

        while (!q.empty()){
            pii cur = q.front(); q.pop();

            for (int i = 0; i < 4; i++){
                int nr = cur.first + dr[i];
                int nc = cur.second + dc[i];

                if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
                if (visited[nr][nc] != false) continue;
                if (board[nr][nc] != id) continue;

                cnt++;
                q.push({nr, nc});
                visited[nr][nc] = true;
            }
        }

        if (cnt < cells[id].size()){
            for (auto p : cells[id]){
                int x = p.first, y = p.second;
                board[x][y] = 0; 
            }
        }
    }
}

void transfer(){
    int tmp[MAXN][MAXN] = {0};

    vector<pii> order;

    for (int id = 1; id <= Q; id++){
        if (!cells[id].empty()){
            order.push_back(make_pair(-(int)cells[id].size(), id));
        }
    }
    
    sort(all(order));

    for (auto o : order){
        int id = o.second;

        int mnx= N, mny = N;
        for (auto p : cells[id]){
            mnx = min(mnx, p.first);
            mny = min(mny, p.second);
        }

        bool placed = false;
        for (int ox = 0; ox < N && !placed; ox++){
            for (int oy = 0; oy < N && !placed; oy++){

                bool ok = true;

                for (auto p : cells[id]){
                    int nx = ox + p.first - mnx;
                    int ny = oy + p.second - mny;

                    if (nx < 0 || nx >= N || ny < 0 || ny >= N || tmp[nx][ny] != 0) {
                        ok = false;
                        break;
                    }
                }

                if (ok){
                    for (auto p : cells[id]){
                        tmp[ox + p.first - mnx][oy + p.second - mny] = id;
                    }
                    placed = true;
                }
            }
        }

    }

    memcpy(board, tmp, sizeof(board));

}

bool adj[MAXQ][MAXQ];
int tdr[2] = {0, 1};
int tdc[2] = {1, 0};

int calc(){

    memset(adj, false, sizeof(adj));

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (board[i][j] == 0) continue;

            for (int k = 0; k < 2; k++){
                int ni = i + tdr[k];
                int nj = j + tdc[k];

                if (ni < 0 || ni >= N || nj < 0 || nj >= N || board[ni][nj] == 0 || board[ni][nj] == board[i][j]) continue;

                int a = min(board[i][j], board[ni][nj]);
                int b = max(board[i][j], board[ni][nj]);
                adj[a][b] = true;
            }
        }
    }

    int score = 0;

    for (int a = 1; a <= Q; a++){
        for (int b = a + 1; b <= Q; b++){
            if (adj[a][b]) score += cells[a].size() * cells[b].size();
        }
    }

    return score;
}

int main() {
    cin >> N >> Q;
    int r1, r2, c1, c2;

    for (int t = 1; t <= Q; t++){
        cin >> r1 >> c1 >> r2 >> c2;

        // 투입 (r1 < r2, c1 < c2)
        for (int i = r1; i < r2; i++){
            for (int j = c1; j < c2; j++){
                board[i][j] = t;
            }
        }
        collect();

        // 분리 여부 확인 + 삭제
        check_divided();
        collect();

        // 배양 이동
        transfer();
        collect();

        // 계산 결과 출력
        int res = calc();
        cout << res << "\n";
        
    }
    
    return 0;
}