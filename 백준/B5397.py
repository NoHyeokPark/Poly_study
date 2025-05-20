import sys
input = sys.stdin.readline


m = int(input())
for _ in range(m):
    str1 = []
    str2 = []
    st = input()
    for s in st:
        if s == '-':
            if str1:
                str1.pop()
        elif s == '<':
            if str1:
                str2.append(str1.pop())
        elif s == '>':
            if str2:
                str1.append(str2.pop())
        else:
            str1.append(s)
    str2.reverse()
    print("".join(str1+str2))