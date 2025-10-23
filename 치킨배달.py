from itertools import combinations

n, m = map(int, input().split()) #n: 도시의 크기, m: 최종 치킨집의 수
chicken, house = [], []


for r in range(n):
    road = list(map(int, input().split()))
    for c in range(n):
        if road[c] == 1:
            house.append((r,c))
        elif road[c] == 2:
            chicken.append((r,c))

candidates = list(combinations(chicken, m))


def calculate_distance(candidate):
    res = 0
    for hx, hy in house:
        tmp = 1e9
        for cx, cy in candidate:
            tmp = min(tmp, abs(hx - cx) + abs(hy - cy))
        res += tmp
    return res

result = 1e9
for candidate in candidates:
    result = min(result, calculate_distance(candidate))
print(result)