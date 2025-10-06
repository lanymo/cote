n = int(input())
mon = list(map(int, input().split()))
mon.sort()

i = 1
for m in mon:
    if i < m:
        break
    i += m
print(i)