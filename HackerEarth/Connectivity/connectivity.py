'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
s = input()
l = s.split()
Q, N = int(l[0]), int(l[1])
connected_list = [0] * N * N

last_added = []
for _ in range(Q):
    s = input()
    l = s.split()
    if l[0] == 'PUSH':
        u, v = int(l[1]), int(l[2])
        u, v = min(u, v), max(u, v)
        last_added.append((u, v))
        connected_list[(u - 1) * N + (v - 1)] = connected_list[(u - 1) * N + (v - 1)] + 1
    else:
        u, v = last_added.pop()
        connected_list[(u - 1) * N + (v - 1)] = connected_list[(u - 1) * N + (v - 1)] - 1

    # check connected component
    c = 0
    connected = {}
    for i in range(N):
        if (i + 1) in connected:
            com = connected[i + 1]
        else:
            com = [i + 1]
            connected[i + 1] = com
            c = c + 1
        for j in range(i + 1, N):
            # print(i ,j, i * N + j, connected_list[i * N + j])
            if connected_list[i * N + j] > 0:
                com.append(j + 1)
                connected[j + 1] = com
    print(c)
    # print((u - 1) * N + (v - 1), connected_list)