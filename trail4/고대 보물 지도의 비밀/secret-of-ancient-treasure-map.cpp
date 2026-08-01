#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int N, K;
int arr[100001];
int dp[100001][11];

int main() {
    // Please write your code here.
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= K; j++){
            dp[i][j] = -INF;
        }
    }

    int ans = -INF;

    for (int i = 1; i <= N; i++){
        int val = arr[i];

        if (val < 0){ // 음수인 경우
            for (int j = 1; j <= K; j++){
                if (j == 1){
                    if (dp[i-1][0] != -INF){
                        dp[i][j] = dp[i-1][0] + val;
                    }else{
                        dp[i][j] = val;
                    }
                }else if (dp[i-1][j-1] != -INF){
                    dp[i][j] = dp[i-1][j-1] + val;
                }
                ans = max(ans, dp[i][j]);
            }
        }else{ // 양수인 경우 + 0인 경우
            for (int j = 0; j <= K; j++){
                if (j == 0){
                    if (dp[i-1][0] != -INF){
                        dp[i][j] = dp[i-1][0] + val;
                    }else{
                        dp[i][j] = val;
                    }
                }else if (dp[i-1][j] != -INF){
                    dp[i][j] = dp[i-1][j] + val;
                }
                ans = max(ans, dp[i][j]);
            }
        }
    }

    cout << ans;

    return 0;
}