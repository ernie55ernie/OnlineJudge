'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
from itertools import product, repeat

line = input()
N, M, K = line.split()
N, M, K = int(N), int(M), int(K)
lines = []
for i in range(N):
    line = input()
    A, B, C = line.split()
    A, B, C = int(A), int(B), int(C)
    lines.append([A, B, C])

def func(i, j):
    return (lines[i - 1][0] * j * j + lines[i - 1][1])

pos = product(range(1, N + 1), repeat=M)
for po in pos:
    print(po)
    cs = []
    for m in range(M):
        cs.append(range(1, lines[po[m] - 1][2] + 1))
    # todo remove dup
    print(cs)
