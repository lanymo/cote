#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define pii pair<int, int>

// -> DFS 이용하면 될듯? N * M이 작아서 시간 복잡도에 영향 X 

int N, M;
int energy[11][11];
int score =  0;

vector<vector<int>> all_modules; // 하나의 모듈을 저장할 벡터 목록
vector<int> selected_cells; // 현재 조합으로 뽑은 5개 

int dr[] = {-1, 1 , 0, 0};
int dc[] = {0, 0, -1, 1};

// 5개 칸이 서로 연결되어 있는지 확인하는 함수
bool is_connected(const vector<int>& cells){

    bool inCell[16] = {false};

    for (int idx : cells){
        inCell[idx] = true;
    }

    queue<int> q;
    bool visited[16] = {false};

    q.push(cells[0]);
    visited[cells[0]] = true;
    int cnt = 1;

    while (!q.empty()) {
        int cur = q.front(); q.pop();

        int cr = cur / M;
        int cc = cur % M;

        for (int i = 0; i < 4; i++){
            int nr = cr + dr[i];
            int nc = cc + dc[i];

            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;

            int next_idx = nr * M + nc;

            if (inCell[next_idx] && !visited[next_idx]){
                q.push(next_idx);
                visited[next_idx] = true;
                cnt++;
            }
        }
    }

    return cnt == 5;
}

// int idx = r * M + c; 
void get_combinations(int idx, int cnt){
    if (cnt == 5){
        if (is_connected(selected_cells)){
            all_modules.push_back(selected_cells);
        }

        return;
    }

    if (idx >= N * M) return;

    selected_cells.push_back(idx);
    get_combinations(idx + 1, cnt + 1); // 선택
    selected_cells.pop_back();
    get_combinations(idx + 1, cnt); // 선택 X
}

int main() {
    cin >> N >> M;
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> energy[i][j];
        }
    }

    get_combinations(0, 0); // 모든 조합 찾기

    int max_score = -987654321;

    // 겹치는 두 개의 모듈 선택 
    for (int i = 0; i < all_modules.size(); i++){
        for (int j = i + 1; j < all_modules.size(); j++){

            int dup_cnt = 0;

            bool check[16] = {false};

            for (int c : all_modules[i]) check[c] = true;
            for (int c : all_modules[j]){
                if (check[c]) dup_cnt++;
            }

            if (dup_cnt == 2){
                int cur = 0;

                for (int c : all_modules[i]){
                    cur += energy[c / M][c % M];
                }

                for (int c : all_modules[j]){
                    cur += energy[c / M][c % M];
                }

                max_score = max(max_score, cur);
            }
        }
    }
    
    cout << max_score << "\n";
    return 0;
}