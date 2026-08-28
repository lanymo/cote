#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()

int N;
vector<vector<int>> scores;

void print_ranks(const vector<int>& a, int max_score){
    vector<int> count(max_score + 1, 0);
    for (int s : a){
        count[s]++;
    }

    vector<int> higher_cnt(max_score + 1, 0);
    int sum = 0;
    for (int s = max_score; s >= 0; s--){
        higher_cnt[s] = sum;
        sum += count[s];
    }

    for (int i = 0; i < N; i++){
        cout << higher_cnt[a[i]] + 1 << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(nullptr);

    cin >> N;
    scores.resize(3, vector<int>(N));

    vector<int> total_scores(N, 0);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            cin >> scores[i][j];
            total_scores[j] += scores[i][j];
        }
    }

    // Please write your code here.
    for (int i = 0; i < 3; i++){
        print_ranks(scores[i], 1000);
    }

    print_ranks(total_scores, 3000);

    return 0;
}
