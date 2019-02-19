from collections import deque

def topo(degrees, graph):  
    q = deque()
    for k, v in degrees.items():
        if v == 0:
            q.append(k)

    while len(q) > 0:
        k = q.pop()
        for neighboor in graph[k]:
            degrees[neighboor] -= 1
            if degrees[neighboor] == 0:
                q.append(neighboor)
            if degrees[neighboor] < 0:
                print("NIE")
                return

    for k, v in degrees.items():
        if (v > 0):
            print("NIE")
            return
    print("TAK")

z = int(input())
degrees = {}
graph = {}
for i in range(z):
    line = input()
    s = line.split(" ")
    x = s[1]
    y = s[4]

    if x not in degrees:
        degrees[x] = 0

    if y not in graph:
        graph[y] = []

    if y not in degrees:
        degrees[y] = 0
    degrees[y] += 1

    if x not in graph:
        graph[x] = []
    graph[x].append(y)
topo(degrees, graph)

    




#     for x in range(2, len(s)):
#         if x != 2: 
#             message = message + " "
#         message = message + s[x]
# tuples.sort(key=lambda x: x[0])

# for i in tuples:
#     print (i[0].strftime('%d.%m.%4Y %H:%M'), i[1])
    