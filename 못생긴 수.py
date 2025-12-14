n = int(input()) # n 번째 못생긴 수 찾기

ugly_num = [0] * n
ugly_num[0] = 1

x2= x3= x5 = 0
nxt2, nxt3, nxt5 = 2, 3, 5

for i in range(1, n):
    ugly_num[i] = min(nxt2, nxt3, nxt5)

    if (ugly_num[i] == nxt2):
        x2 += 1
        nxt2 = ugly_num[x2] * 2
    if ugly_num[i] == nxt3:
        x3 += 1
        nxt3 = ugly_num[x3] * 3
    if ugly_num[i] == nxt5:
        x5 += 1
        nxt5 = ugly_num[x5] * 5

print(ugly_num[n-1])