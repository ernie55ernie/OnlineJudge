'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here

line = input()
N, M = line.split()
N, M = int(N), int(M)
result = [0] * N
result[0] = M
siblings = [[]] # sibling dynamic stocks
types = ['f'] # dynamic or fix
qtys = [1]
parents = [0] # parent

def func(traverse_idx):
    for d in siblings[traverse_idx]:
        result[d] = result[traverse_idx] // qtys[d]
        func(d)

for i in range(N - 1):
    line = input()
    strs = line.split()
    siblings.append([])
    if strs[0] == '1': # dynamic stock
        p, qty = int(strs[1]), int(strs[2])
        s = result[p - 1] // qty
        result[i + 1] = s

        siblings[p - 1].append(i + 1) # dynamic stocks of p - 1
        types.append('d')
        parents.append(p - 1)
        qtys.append(qty)
    elif strs[0] == '2': # fixed stock
        p, qty, s = int(strs[1]), int(strs[2]), int(strs[3])
        cum_qty = qty
        idx = p - 1
        if types[p - 1] == 'd': # if parent is dynamic stoch find its parent
            idx = parents[idx]
            cum_qty = cum_qty * qtys[idx]
            while types[idx] == 'd':
                idx = parents[idx]
                cum_qty = cum_qty * qtys[idx]

        # if result[idx] >= cum_qty * s:
        #     result[idx] = result[idx] - cum_qty * s # update ancestor fixed stock
        #     result[i + 1] = s
        # else:
        #     result[i + 1] = result[idx] // cum_qty
        #     result[idx] = 0# result[idx] - result[idx] // cum_qty * cum_qty
        result[idx] = result[idx] - cum_qty * s # update ancestor fixed stock
        result[i + 1] = s

        if types[p - 1] == 'd':
            # starting from ancestor fixed stock update sibling dynamic stock
            for d in siblings[idx]:
                result[d] = result[parents[idx]] // qtys[d]
                func(d)

            # idx = parents[idx]
            # cum_qty = cum_qty * qtys[idx]
            # while types[idx] == 'd':
            #     idx = parents[idx]
            #     cum_qty = cum_qty * qtys[idx]

        # for d in siblings[p - 1]:
        #     result[d] = result[parents[p - 1]] // qtys[d]
        types.append('f')
        parents.append(p - 1)
        qtys.append(qty)

    # print(siblings)
    # print(parents)
    # for res in result:
    #     print(res)
    # print('\n')
    
for res in result:
    print(res)