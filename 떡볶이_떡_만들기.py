# 해설 없이 짠 코드

#n: 떡의 개수, m: 요청한 떡의 길이
n, m = map(int, input().split())
tteoks = list(map(int, input().split()))

#tteoks.sort()
start = 0
end = max(tteoks)

while(start <= end):
    left_sum = 0
    mid = (start + end) // 2
    for t in tteoks:
        if(t > mid):
            left_sum += (t - mid)
    if (left_sum < m):
        end = mid -1
    else:
        result = mid
        start = mid + 1

print(result)



