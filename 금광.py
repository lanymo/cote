t = int(input()) #테스트 케이스 수
while (t):
    n, m = map(int, input().split())
    arr = list(map(int , input().split()))

    dp = []
    idx = 0
    for i in range(n):
        dp.append(arr[idx:idx+m])
        idx += m

    #dp[i][j] = arr[i][j] + max(dp[i-1][j-1], dp[i][j-1], dp[i+1][j-1]

    for j in range(1, m):
        for i in range(n):
            left_up = dp[i-1][j-1] if i - 1 >= 0 else 0
            left = dp[i][j-1]
            left_down = dp[i+1][j-1] if i + 1 < n else 0

            dp[i][j] += max(left, left_up, left_down)
    result = 0
    for i in range(n):
        result = max(result, dp[i][m-1])
    print(result)
    t -= 1

