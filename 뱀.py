n = int(input())  # 보드의 크기 n * n
k = int(input())  # 사과의 개수 k개
board = [[0] * (n + 1) for _ in range(n + 1)]

for _ in range(k):
    r, c = map(int, input().split())
    board[r][c] = 1

l = int(input())  # 방향 변환 횟수
direc = []
for _ in range(l):
    x, c = input().split()
    direc.append((int(x), c))

# 동서남북 이동 방향 설정
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]


def turn(direction, c):
    if c == 'L':
        direction = (direction - 1) % 4  # dx, dy 하나 감소해야 함
    else:
        direction = (direction + 1) % 4  # dx, dy 하나 증가해야 함
    return direction


def check_bound(x, y):
    if (x >= 1 and x <= n and y >= 1 and y <= n and board[x][y] != 2):
        return True
    return False


def sol():
    x, y = 1, 1  # 좌측 처음부터 시작
    board[x][y] = 2  # 뱀 위치 기록
    direction = 0  # 동쪽부터 시작
    idx = 0
    q = [(x, y)]
    t = 0  # return 시간
    while True:
        nx = x + dx[direction]
        ny = y + dy[direction]

        if check_bound(nx, ny):
            if board[nx][ny] == 1:
                board[nx][ny] = 2
                q.append((nx, ny))
            if board[nx][ny] == 0:
                board[nx][ny] = 2
                q.append((nx, ny))
                prev_x, prev_y = q.pop(0)
                board[prev_x][prev_y] = 0
        else:
            t += 1
            break
        x, y = nx, ny
        t += 1
        if idx < l and t == direc[idx][0]:
            direction = turn(direction, direc[idx][1])
            idx += 1
    return t


print(sol())
