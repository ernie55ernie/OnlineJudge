'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
N = int(input())
graph = [0] * (N * N)
nodes = set()
total = 0
mod = 10 ** 9 + 7
for _ in range(N - 1):
    s = input()
    l = s.split()
    u, v, c = int(l[0]), int(l[1]), int(l[2])
    u, v = min(u, v), max(u, v)
    graph[(u - 1) * N + (v - 1)] = c
    for node in nodes:
        if node == u or node == v:
            continue
        else:
            a, b = min(node, v), max(node, v)
            if graph[(a - 1) * N + (b - 1)] != 0:
                if node > v:
                    value = c * 10 + graph[(a - 1) * N + (b - 1)]
                else:
                    value = graph[(a - 1) * N + (b - 1)] * 10 + c
                graph[(u - 1) * N + (node - 1)] = value
            
            a, b = min(node, u), max(node, u)
            if graph[(a - 1) * N + (b - 1)] != 0:
                if node > c:
                    value = c * 10 + graph[(a - 1) * N + (b - 1)]
                else:
                    value = graph[(a - 1) * N + (b - 1)] * 10 + c
                graph[(node - 1) * N + (v - 1)] = value
            # print(u, v, node, c, value)
            total = (total + value) % mod
    nodes.add(u)
    nodes.add(v)
    # print(u, v, c)
    total = (total + c) % mod

print(total)
