#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int N;
int red_cards[205];
int blue_cards[205];
int dp[205][105]; // dp[idx][red_cnt]


int main() {
    // Please write your code here.
    cin >> N;

    for (int i = 1; i <= 2 * N; i++){
        cin >> red_cards[i] >> blue_cards[i];
    }

    for (int i = 0; i <= 2 * N; i++){
        for (int j = 0; j <= N; j++){
            dp[i][j] = -INF;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= 2*N; i++){
        for (int j = 0; j <= min(i, N); j++){
            if (j > 0 && dp[i-1][j-1] != -INF){
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + red_cards[i]);
            }

            if (dp[i-1][j] != -INF){
                dp[i][j] = max(dp[i][j], dp[i-1][j] + blue_cards[i]);
            }
        }
        
    }

    cout << dp[2 * N][N];

    return 0;
}