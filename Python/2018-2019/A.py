import string

first = input()
second = input()

d = {}

for a in string.ascii_lowercase:
    d[a] = 0

for a in string.ascii_uppercase:
    d[a] = 0

for a in first:
    if a != " ":
        d[a] = d[a]+1

for a in second:
    if a != " ":
        if d[a] > 0:
            d[a] = d[a] - 1
        else:
            print("NO")
            quit()
print("YES")


