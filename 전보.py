import sys
import heapq
input = sys.stdin.readline
INF = int(1e9)

n, m, c = map(int, input().split())
graph = [[] for _  in range(n+1)]
distance = [INF] * (n+1)

for _ in range(m):
    v1, v2, t = map(int, input().split())
    graph[v1].append((v2,t)) #direct graph

def dijkstra(start):
    q = []
    distance[start] = 0
    heapq.heappush(q, (distance[start], start))
    while q:
        dist, now = heapq.heappop(q)
        if (distance[now] < dist):
            continue
        for node in graph[now]:
            cost = dist + node[1]
            if (cost < distance[node[0]]):
                distance[node[0]] = cost
                heapq.heappush(q, (cost, node[0]))

dijkstra(c)

cnt = 0
max_distance = 0
for d in distance:
    if d != INF:
        cnt += 1
        max_distance = max(max_distance, d)

print(cnt-1, max_distance)