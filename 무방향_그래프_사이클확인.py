import sys
input = sys.stdin.readline

def find_parent(parent, a):
    if (parent[a] != a):
        parent[a] = find_parent(parent, parent[a])
    return parent[a]

def union(parent, a, b):
    pa = find_parent(parent, a)
    pb = find_parent(parent, b)

    if pa < pb:  # 작은 번호를 루트로
        parent[pb] = pa
    else:
        parent[pa] = pb

v, e = map(int, input().split()) #v: 노드 개수, e: 간선 개수
parent = [0] + [i for i in range(1, v+1)]

cycle = False #사이클 발생 여부 플래그

for i in range(e):
    v1, v2 = map(int, input().split())
    if (find_parent(parent,v1) == find_parent(parent, v2)):
        cycle = True
        break
    else:
        union(parent, v1, v2)

if cycle:
    print("사이클이 발생했습니다.")
else:
    print("사이클이 발생하지 않았습니다.")