n = int(input())
arr = list(map(int, input().split()))
ans = 0

arr.sort()
mem = 0

for a in arr:
    mem += 1
    if (mem >= a):
        ans += 1
        mem = 0
print(ans)
