st = input()
alpha = ""
digit = 0
for s in st:
    if s.isalpha():
        alpha += s
    if s.isdigit():
        digit += int(s)

alpha = sorted(alpha)
answer = ""
for a in alpha:
    answer += a
answer += str(digit)
print(answer)