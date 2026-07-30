#include <iostream>
#include <algorithm>
using namespace std;

const int INF = -1e9;

int dp[1001][4]; // 현재 층, 현재 횟수에서 동전 개수 합
int coin[1001]; 

int main() {
    // Please write your code here.
    int n; cin >> n;

    for (int i = 1; i <= n; i++){
        cin >> coin[i];
    }

    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= 3; j++){
            dp[i][j] = INF;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= 3; j++){
            
            // i 번째 층에 도착 by 2단계
            if (i >= 2 && dp[i-2][j] != INF){
                dp[i][j] = max(dp[i][j], dp[i-2][j] + coin[i]);
            }

            // i 번째 층에 도착 by 1단계
            if (j > 0 && dp[i-1][j-1] != INF){
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + coin[i]);
            }
        }
    }

    int ans = INF;
    for (int j = 0; j <= 3; j++){
        ans = max(ans, dp[n][j]);
    }

    cout << ans << "\n";
    return 0;
}