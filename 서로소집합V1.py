import sys
input = sys.stdin.readline

#O(V)의 시간복잡도를 갖는 find
def find_parent(parent, a):
    if parent[a] != a:
        return find_parent(parent, parent[a])
    return a

def union(parent, a, b):
    pa = find_parent(parent, a)
    pb = find_parent(parent, b)

    if(pa > pb):
        parent[a] = pb
    else:
        parent[b] = pa


v, e = map(int, input().split()) #v: 노드 개수, e: 간선 개수
parent = [0] + [i for i in range(1, v+1)]

for i in range(e):
    v1, v2 = map(int, input().split())
    union(parent, v1, v2)

print("각 원소가 속한 집합: ", end='')
for i in range(1, v+1):
    print(find_parent(parent, i), end= ' ')
print()

print('부모 테이블: ' , end = '')
for i in range(1, v+1):
    print(parent[i], end= ' ')