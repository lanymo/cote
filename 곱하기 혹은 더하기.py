s = input()

res = int(s[0])

for i in range(1, len(s)):
    print(res)
    if res == 1 or res == 0:
        res += int(s[i])
    elif s[i] == '1' or s[i] == '0':
        res += int(s[i])
    else:
        res *= int(s[i])
print(res)