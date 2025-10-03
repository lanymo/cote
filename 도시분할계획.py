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

n, m = map(int, input().split()) #n개의 집 m개의 길
parent = [0] + [i for i in range(1, n+1)]

# 간선 리스트
edges = []
result = 0

for _ in range(m):
    v1, v2, cost = map(int, input().split())
    edges.append((cost, v1, v2))

edges.sort()
high_cost = 0
for edge in edges:
    cost, v1, v2 = edge
    if (find_parent(parent,v1) != find_parent(parent,v2)):
        union(parent, v1, v2)
        result += cost
        high_cost = cost
print(result - high_cost)
