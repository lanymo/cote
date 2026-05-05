#include <iostream>
#include <vector>

using namespace std;

int N, K;
vector<vector<int>> grid;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

int dp[101][101]; // 해당 차이 이하로만 이동해서 K 길이를 만들 수 있는지

int solve(int r, int c, int diff){
    if (dp[r][c] != -1) return dp[r][c];

    int max_len = 1;
    for (int i = 0; i < 4; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];

        if ( nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

        int height_diff = grid[nr][nc] - grid[r][c];
        if (height_diff > 0 && height_diff <= diff){
            max_len = max(max_len, 1 + solve(nr, nc, diff));
        }
    }
    return dp[r][c] = max_len;
}

bool check(int diff){
    for (int i = 0; i < N; i++){
        for (int j =0; j < N; j++){
            dp[i][j] = -1;
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (solve(i, j, diff) >= K) return true;
        }
    }

    return false;
}


int main() {
    cin >> N >> K; // 등산로의 길이는 K 이상이어야 함 

    grid.resize(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j]; // 산의 정보를 의미하는 grid 
        }
    }

    // Please write your code here.
    int low = 0, high = 1000000000;
    int answer = -1;

    while (low <= high){
        int mid = (low + high) / 2;

        if (check(mid)){
            answer = mid;
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }

    cout << answer << "\n";

    return 0;
}
