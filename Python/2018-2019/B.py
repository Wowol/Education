from datetime import datetime

z = int(input())
tuples = []
for i in range(z):
    line = input()
    s = line.split(" ")
    date = s[0]
    time = s[1]
    message = ""
    for x in range(2, len(s)):
        if x != 2: 
            message = message + " "
        message = message + s[x]

    d = s[0] + " " + s[1]
    tuples.append((datetime.strptime(d, '%d.%m.%Y %H:%M'), message))

tuples.sort(key=lambda x: x[0])

for i in tuples:
    print (i[0].strftime('%d.%m.%4Y %H:%M'), i[1])
    