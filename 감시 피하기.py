n = int(input())
board = [list(input().split()) for _ in range(n)]
spaces = [] #빈 공간 좌표 저장
teachers = [] #선생님 좌표 저장

for i in range(n):
    for j in range(n):
        if board[i][j] == 'X':
            spaces.append((i,j))
        elif board[i][j] == 'T':
            teachers.append((i, j))


def watched(x, y, dir):
    if dir == 0: #상
        while(x >= 0):
            if board[x][y] == 'O':
                return False
            if board[x][y] == 'S':
                return True
            x -= 1
    elif dir == 1: #하
        while (x < n):
            if board[x][y] == 'O':
                return False
            if board[x][y] == 'S':
                return True
            x += 1
    elif dir == 2: #좌
        while (y >= 0):
            if board[x][y] == 'O':
                return False
            if board[x][y] == 'S':
                return True
            y -= 1
    else: #우
        while (y < n):
            if board[x][y] == 'O':
                return False
            if board[x][y] == 'S':
                return True
            y += 1
    return False


def check(): #장애물 설치 후, 전체 감시 현황 확인
    for x, y in teachers:
        for d in range(4):
            if watched(x, y, d):
               return False
    return True

find = False

def dfs(start, count):
    global find
    if count == 3:
        if check():
            find = True
        return

    for i in range(start, len(spaces)): #모든 빈 공간 확인
        x, y = spaces[i]
        board[x][y] = 'O' #장애물 설치
        dfs(i+1, count + 1) #설치한 장애물 개수 증가 후 dfs. i에 이미 설치. 이후부터 체크
        board[x][y] = 'X' #백트래킹을 위해 원래 상태로 전환

dfs(0, 0)

if find == True:
    print("YES")
else:
    print("NO")