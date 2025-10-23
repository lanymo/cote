n, m = map(int, input().split())
board = []
tmp = [[0] * m for _ in range(n)]

for _ in range(n):
    board.append(list(map(int, input().split())))

dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

answer = 0

def virus(x,y):
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        if nx >= 0 and nx < n and ny >= 0 and ny < m:
            if tmp[nx][ny] == 0:
                tmp[nx][ny] = 2
                virus(nx, ny)

def get_safety():
    cnt = 0
    for i in range(n):
        for j in range(m):
            if tmp[i][j] == 0:
                cnt += 1
    return cnt

def dfs(count):
    global answer
    if count == 3:
        for i in range(n):
            for j in range(m):
                tmp[i][j] = board[i][j]
        for i in range(n):
            for j in range(m):
                if tmp[i][j] == 2:
                    virus(i, j)
        answer = max(answer, get_safety())
        return
    for i in range(n):
        for j in range(m):
            if board[i][j] == 0:
                board[i][j] = 1
                count += 1
                dfs(count)
                board[i][j] = 0
                count -= 1
dfs(0)
print(answer)