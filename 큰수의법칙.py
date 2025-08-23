n, m, k = map(int, input().split())
data = list(map(int, input().split()))

data.sort()
sum = 0

#가장 큰 수가 등장하는 횟수
count = int( m / (k+1)) * k
count += m % (k+1)

sum += (count) * data[n-1]
sum += (m - count) * data[n-2]
print(sum)