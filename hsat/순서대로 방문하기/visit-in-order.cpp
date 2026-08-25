#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> grid;
vector<pair<int, int>> points;
bool visited[5][5];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};
int ans = 0;

void dfs(int r, int c, int target_idx){
    if (r == points[m-1].first && c == points[m-1].second){
        ans++;
        return;
    }

    if (r == points[target_idx].first && c == points[target_idx].second){
        target_idx++;
    }

    for (int d = 0; d < 4; d++){
        int nr = r + dr[d];
        int nc = c + dc[d];

        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
        if (grid[nr][nc] == 1 || visited[nr][nc] == true) continue;

        bool possible = true;

        for (int i = target_idx + 1; i < m; i++){
            if (nr == points[i].first && nc == points[i].second){
                possible = false;
                break;
            }
        }

        if (possible){
            visited[nr][nc] = true;
            dfs(nr, nc, target_idx);
            visited[nr][nc] = false;
        }
    }
}

int main() {
    cin >> n >> m;

    grid.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    points.resize(m);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = {x - 1, y - 1};
    }

    // Please write your code here.
    visited[points[0].first][points[0].second] = true;
    dfs(points[0].first, points[0].second, 1);

    cout << ans;

    return 0;
}
