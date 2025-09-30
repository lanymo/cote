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

v,e = map(int, input().split())
parent = [0] + [i for i in range(1, v+1)]

# 간선 리스트
edges = []
result = 0

for _ in range(e):
    v1, v2, cost = map(int, input().split())
    edges.append((cost, v1, v2))

edges.sort()

for edge in edges:
    cost, a, b = edge
    if find_parent(parent, a) != find_parent(parent,b):
        union(parent,a, b)
        result += cost
print(result)

