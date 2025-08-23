input = input() #a1
row = int(input[1]) #1
col = int(ord(input[0]) - ord('a')) + 1 #1 (a~h : 1~8)

way = [(-2, 1), (-2, -1), (2, 1), (2, -1), 
       (1, 2), (-1, 2), (1, -2), (-1, -2)]

cnt = 0

for dr, dc in way:
    nr = row + dr
    nc = col + dc
    if nr >= 1 and nr <=8 and nc >= 1 and nc <= 8:
        cnt += 1

print(cnt)
