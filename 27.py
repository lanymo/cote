def count_val(arr, x):
    n = len(arr)
    a = first(arr, x, 0, n-1)

    if a == None:
        return 0

    b = last(arr, x, 0, n-1)

    if b == None:
        return 0

    return b - a + 1

def first(arr, target, start, end):
    if start > end:
        return None
    mid = (start + end) // 2
    if (mid == 0 or target > arr[mid-1]) and arr[mid] == target:
        return mid
    elif (arr[mid] >= target):
        return first(arr, target, start, mid - 1)
    else:
        return first(arr, target, mid + 1, end)

def last(arr, target, start, end):
    if start > end:
        return None
    mid = (start + end) // 2
    if (mid == n-1 or target < arr[mid+1]) and arr[mid] == target:
        return mid
    elif (arr[mid] > target):
        return last(arr, target, start, mid - 1)
    else:
        return last(arr, target, mid + 1, end)


n, x = map(int, input().split())
data = list(map(int, input().split()))

#x가 등장하는 첫 위치와 마지막 위치 찾기
cnt = count_val(data, x)

if (cnt == 0):
    print(-1)
else:
    print(cnt)
