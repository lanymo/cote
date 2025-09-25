#간단한 다익스트라 알고리즘 소스코드(O(V^2))

import sys
input = sys.stdin.readline
INF = int(1e9)

n, m = map(int, input().split())
start = int(input())

graph = [[] for i in range(n+1)] #노드, 간선 정보 저장하는 그래프 배열(1~N)
visited = [False] * (n+1) #노드 방문 여부 체크
distance = [INF] * (n+1) #거리 배열

for _ in range(m):
    v1, v2, d = map(int, input().split())
    graph[v1].append((v2, d)) #direct graph

def get_smallest_node():
    min_value = INF
    index = 0
    for i in range(1, n+1):
        if (distance[i] < min_value) and not visited[i]:
            min_value = distance[i]
            index = i
    return index

def dijkstra(start):
    distance[start] = 0
    visited[start] = True
    for edge in graph[start]:
        distance[edge[0]] = edge[1]

    for i in range(n-1):
        now = get_smallest_node()
        visited[now] = True
        for edge in graph[now]:
            cost = distance[now] + edge[1]
            if (cost < distance[edge[0]]):
                distance[edge[0]] = cost


dijkstra(start)

for i in range(1, n+1):
    if (distance[i] == INF):
        print("INFINITY")
    else:
        print(distance[i])
