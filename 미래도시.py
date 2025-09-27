import sys
input = sys.stdin.readline
INF = int(1e9)

n, m = map(int, input().split()) #n=회사 수, m=경로 개수
graph = [[INF] * (n+1) for _ in range(n+1)] #노드 - 간선 정보 저장 2차원 배열

#그래프 정보 받아서 초기화
for i in range(1, n+1):
    graph[i][i] = 0

for i in range(m):
    v1, v2 = map(int, input().split())
    graph[v1][v2] = 1
    graph[v2][v1] = 1

#X, K 공백 구분
x, k = map(int, input().split()) #k먼저 방문 후 x 방문해야 함!

#플로이드 워셜 알고리즘을 이용해 영역별 최단 거리 초기화
for i in range(1, n+1):
    for j in range(1, n+1):
        for k in range(1, n+1):
            graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])


distance = graph[1][k] + graph[k][x]

if(distance >= INF):
    print("-1")
else: print(distance)