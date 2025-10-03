import sys
input = sys.stdin.readline

def find_parent(parent, x):
    if (parent[x] != x):
        parent[x] = find_parent(parent, parent[x])
    return parent[x]

def union(parent, a, b):
    pa = find_parent(parent, a)
    pb = find_parent(parent, b)

    if pa < pb:  # 작은 번호를 루트로
        parent[pb] = pa
    else:
        parent[pa] = pb

n,m = map(int, input().split()) #0~N번까지의 번호, M은 연산 개수
parent = [0] + [i for i in range(1, n+1)]

for i in range(m):
    opt, v1, v2 = map(int, input().split())
    if opt == 0:
        union(parent, v1, v2)
    elif opt == 1:
        if find_parent(parent, v1) == find_parent(parent, v2):
            print("YES")
        else:
            print("NO")