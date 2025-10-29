def find(arr, start, end):
    if (start > end):
        return None
    mid = (start+end) // 2

    if arr[mid] == mid:
        return mid
    elif (arr[mid] > mid):
        return find(arr, start, mid-1)
    else:
        return find(arr, mid + 1, end)

n = int(input())
data = list(map(int, input().split()))
result = find(data, 0, n-1)

if result is None:
    print(-1)
else:
    print(result)
