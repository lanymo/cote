n = int(input()) #삼각형의 크기

dp = []

for _ in range(n):
    dp.append(list(map(int, input().split())))

for i in range(1, n):
    for j in range(i+1):
        up_left = dp[i-1][j-1] if j - 1 >= 0 else 0
        up = dp[i-1][j] if j != i else 0

        dp[i][j] += max(up_left, up)
print(max(dp[n-1]))