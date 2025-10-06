n, m = map(int,input().split())
sizes = list(map(int, input().split()))
cnt_size = [0] * (11)

for s in sizes:
    cnt_size[s] += 1

answer = 0

for i in range(1, m+1):
    n -= cnt_size[i]
    answer += (n*cnt_size[i])
print(answer)