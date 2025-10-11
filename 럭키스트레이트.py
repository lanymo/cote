n = list(map(int, input())) #현재 점수

ha = len(n) // 2
left_sum = sum(n[0:ha])
right_sum = sum(n[ha:])

if (left_sum == right_sum):
    print("LUCKY")
else:
    print("READY")