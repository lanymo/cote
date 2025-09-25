import heapq
import sys
input = sys.stdin.readline
INF = int(1e9)

n, m = map(int, input().split())
start = int(input())

graph = [[] for i in range(n+1)] #노드, 간선 정보 저장하는 그래프 배열(1~N)
distance = [INF] * (n+1) #거리 배열

for _ in range(m):
    v1, v2, d = map(int, input().split())
    graph[v1].append((v2, d)) #direct graph

def dijkstra(start):
    q = [] #우선순위를 저장할 priority queue
    distance[start] = 0
    heapq.heappush(q, (distance[start], start))

    while q:
        dist, now = heapq.heappop(q)
        if distance[now] < dist:
            continue
        for node in graph[now]:
            cost = dist + node[1]
            if (cost < distance[node[0]]):
                distance[node[0]] = cost
                heapq.heappush(q,(distance[node[0]], node[0]))
dijkstra(start)
for i in range(1, n+1):
    if (distance[i] == INF):
        print("INFINITY")
    else:
        print(distance[i])

