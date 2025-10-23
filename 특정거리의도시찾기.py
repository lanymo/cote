from collections import deque

n, m, k, x = map(int, input().split())
graph = [[] for _ in range(n+1)]

for _ in range(m):
    v1, v2 = map(int, input().split())
    graph[v1].append(v2)

distance = [-1] * (n+1)
distance[x] = 0
#visited = [False] * (n+1)

#x부터 시작해서 도달하는 도시 BFS
q = deque([x])
while q:
    now = q.popleft()
    for node in graph[now]:
        if distance[node] == -1:
            distance[node] = distance[now] + 1
            q.append(node)

flag = False
for i in range(1, n+1):
    if distance[i] == k:
        print(i)
        flag = True

if not flag:
    print(-1)