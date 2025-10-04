from collections import deque
import copy

#topology sort

n = int(input()) #듣고자 하는 n 개의 강의
indegree = [0] * (n+1)
graph = [[] for i in range(n+1)]
time = [0] * (n+1)

for i in range(1, n+1):
    data = list(map(int, input().split()))
    time[i] = data[0]
    for x in data[1:-1]:
        indegree[i] += 1
        graph[x].append(i)

def topology():
    result = copy.deepcopy(time)
    q = deque()

    for i in range(1, n+1):
        if indegree[i] == 0:
            q.append(i)

    while q:
        now = q.popleft()
        for i in graph[now]:
            result[i] = max(result[i], result[now] + time[i])
            indegree[i] -= 1
            if (indegree[i] == 0):
                q.append(i)

    for i in range(1, n+1):
        print(result[i])

topology()