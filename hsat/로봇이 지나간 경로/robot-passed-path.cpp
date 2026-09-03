#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define pii pair<int, int>

int H, W;
vector<vector<char>> grid;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};
char dir_char[] = {'^', '<', 'v', '>'};

int main() {
    cin >> H >> W;

    grid.resize(H, vector<char>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }

    // 시작 지점 찾기
    int sr = -1, sc = -1, sd = -1;
    for (int r = 0; r < H; r++){
        for (int c = 0; c < W; c++){
            if (grid[r][c] != '#') continue;

            int cnt = 0;
            int dir = -1;

            for (int d = 0; d < 4; d++){
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '#'){
                    cnt++;
                    dir = d;
                }
            }

            if (cnt == 1){
                sr = r;
                sc = c;
                sd = dir;
            }
        }
    }

    cout << sr + 1 << " " << sc + 1 << "\n";
    cout << dir_char[sd] << "\n"; 

    // 명령어 찾기
    string ans = "";
    grid[sr][sc] = '.';
    int r = sr, c = sc, d = sd;
    while(true){
        bool moved = false;

        int r1 = r + dr[d], c1 = c + dc[d];
        int r2 = r + dr[d] * 2, c2 = c + dc[d] * 2;

        if (r2 >= 0 && r2 < H && c2 >= 0 && c2 < W && grid[r1][c1] == '#' && grid[r2][c2] == '#'){
            grid[r1][c1] = '.';
            grid[r2][c2] = '.';
            moved = true;
            ans += 'A';
            r = r2; c = c2;
            continue;
        }

        // 좌측 이동 확인
        int ld = (d + 1) % 4;
        int lr1 = r + dr[ld], lc1 = c + dc[ld];
        int lr2 = r + dr[ld] * 2, lc2 = c + dc[ld] * 2;
        if (lr2 >= 0 && lr2 < H && lc2 >= 0 && lc2 < W && grid[lr1][lc1] == '#' && grid[lr2][lc2] == '#'){
            moved = true;
            d = ld;
            ans += 'L';
            continue;
        }

        // 우측 이동 확인
        int rd = (d + 3) % 4;
        int rr1 = r + dr[rd], rc1 = c + dc[rd];
        int rr2 = r + dr[rd] * 2, rc2 = c + dc[rd] * 2;

        if (rr2 >= 0 && rr2 < H && rc2 >= 0 && rc2 < W && grid[rr1][rc1] == '#' && grid[rr2][rc2] == '#'){
            moved = true;
            d = rd;
            ans += 'R';
            continue;
        }

        if (!moved) break;
    }

    cout << ans;
    return 0;
}
