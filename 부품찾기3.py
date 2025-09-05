# 책에 나온 set을 활용한 풀이
# 한 번 등장했는지만 검사하면 된다 -> 집합 자료형을 쓰면 더 간단하게 사용 가능!
# set(): 집합 자료형을 초기화할 때 사용

n = int(input())
array = set(map(int, input().split()))

m = int(input())
want = list(map(int, input().split()))

for i in want:
    if i in array:
        print('yes', end = ' ')
    else:
        print('no', end = ' ')