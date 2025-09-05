#답지 없이 짠 코드

def binary_search(array, target, start, end):
    while(start <= end):
        mid = (start + end) // 2
        if (array[mid] == target):
            return mid
        elif (array[mid] > target):
            end = mid -1
        else:
            start = mid + 1



n = int(input())
have = list(map(int, input().split()))
m = int(input())
want = list(map(int, input().split()))

have.sort()

for w in want:
    result = binary_search(have, w, 0, n-1)
    if (result == None):
        print("no", end=' ')
    else:
        print("yes", end= ' ')
