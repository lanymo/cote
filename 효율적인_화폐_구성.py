n, m = map(int, input().split())

arr = [0] * n
for i in range(n):
    arr[i] = int(input()) #화폐 단위 저장 배열

d = [10001] * (m+1)
d[0] = 0

for a in arr:
    for i in range(a, m+1):
        if (d[i - a] != 10001):
            d[i] = min(d[i], d[i-a] + 1)
if (d[m] == 10001):
    print(-1)
else:
    print(d[m])

