from itertools import combinations

l, c = map(int, input().split(' '))

word = ['a', 'e', 'i', 'o', 'u']
array = input().split(' ')

#정렬
array.sort()

for password in combinations(array, l):
    count = 0
    for i in password:
        if(i in word):
            count += 1

    if (count and count <= l - 2):
        print(''.join(password))
