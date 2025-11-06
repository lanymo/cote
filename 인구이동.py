from collections import deque

n, l, r = map(int, input().split())

dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]

res = 0

maps = []
for _ in range(n):
    maps.append(list(map(int, input().split())))

def bfs(x, y, visited):
    q = deque()
    q.append((x, y))
    union = [(x, y)]
    visited[x][y] = True
    total = maps[x][y] #연합의 전체 인구 수

    while q:
        x, y = q.popleft()
        for i in range(4):
            nx, ny = x + dx[i], y + dy[i]
            if 0 <= nx < n and 0 <= ny < n and not visited[nx][ny]:
                diff = abs(maps[x][y] - maps[nx][ny])
                if (l <= diff <= r):
                    visited[nx][ny] = True
                    q.append((nx, ny))
                    union.append((nx, ny))
                    total += maps[nx][ny]
    return union, total

while True:
    visited = [[False] * n for _ in range(n)]
    moved = False

    for i in range(n):
        for j in range(n):
            if not visited[i][j]:
                union, total = bfs(i, j, visited)
                if len(union) > 1:
                    moved = True
                    new_pop = total // len(union)
                    for x, y in union:
                        maps[x][y] = new_pop
    if not moved:
        break
    res += 1

print(res)
