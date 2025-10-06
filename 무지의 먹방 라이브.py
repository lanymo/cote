#프로그래머스 42891
import heapq


def solution(food_times, k):

    if sum(food_times) <= k:
        return -1

    q = []
    for i in range(len(food_times)):
        heapq.heappush(q, (food_times[i], i+1))

    sum = 0
    prev = 0
    n = len(food_times)

    while sum + ((q[0][0] - prev)*n) <= k:
        now = heapq.heappop(q)[0]
        sum += (now-prev) * n
        prev = now
        len -= 1
    result = sorted(q, key = lambda x : x[1])
    return result[(k-sum) % n][1]


    '''망한코드ㅎㅎ...
    n = len(food_times)
    index = 0
    while (k):
        if (index == n):
            index = 0

        if (food_times[index] == 0):
            while (food_times[index] == 0):
                index += 1

        food_times[index] -= 1
        index += 1

        k -= 1

    if (index == n):
        return 1
    else:
        return index
    '''