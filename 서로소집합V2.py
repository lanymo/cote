import sys
input = sys.stdin.readline

#경로 압축 기법을 이용한 find함수
#parent 테이블 갱신

def find_parent(parent, a):
    if parent[a] != a:
        parent[a] =  find_parent(parent, parent[a])
    return parent[a]

def union(parent, a, b):
    pa = find_parent(parent, a)
    pb = find_parent(parent, b)

    if(pa > pb):
        parent[a] = parent[b]
    else:
        parent[b] = parent[a]


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