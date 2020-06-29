'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
name = input().split(' ') 
matrix = []
N, k = int(name[0]), int(name[1])
for i in range(N):
    tmp = input()
    tmp = [int(a) for a in tmp.split(' ')]
    matrix.append(tmp)
loc_add = {}
for idxi, i in enumerate(matrix):
    for idxj, j in enumerate(i):
        if idxj+1 < len(i):
            loc_add[(idxi,idxj, idxi, idxj+1)] = matrix[idxi][idxj] + matrix[idxi][idxj+1]
        if idxi+1 < len(matrix):
            loc_add[(idxi,idxj, idxi+1, idxj)] = matrix[idxi][idxj] + matrix[idxi+1][idxj]
sort_dict = sorted(loc_add.items(), key=lambda d: d[1], reverse=True)
sum1 = 0
sum2 = 0
cnt = 0

print(sort_dict)
def find_max(not_include, idx):
    a = sort_dict[idx-1][0][:2]
    b = sort_dict[idx-1][0][2:]
    if idx==0 or len(set(not_include))>k*2:
        return 0
    if a in not_include and b in not_include:
        return find_max(not_include, idx-1)
    else:
        tmp2 = find_max(not_include, idx-1)
        print("tmp2", tmp2)
        not_include.append(a)
        not_include.append(b)
        tmp1 = find_max(not_include, idx-1)
        if (sort_dict[idx-1][1] + tmp1) <= tmp2:
            not_include.pop(-1)
            not_include.pop(-1)
            print(sort_dict[idx-1][1] + tmp1)
            print(tmp2)
        return max(sort_dict[idx-1][1] + tmp1, tmp2)

# for idx in range(len(sort_dict)):
#     a = sort_dict[idx][0][:2]
#     b = sort_dict[idx][0][2:]
#     if a not in not_include and b not in not_include:
#         tmp = max(sum1+sort_dict[idx][1], sum2)
#         sum1 = sum2
#         sum2 = tmp

#         not_include.append(a)
#         not_include.append(b)
#         cnt+=1
#     if cnt==k:
#         break

print(find_max([],len(sort_dict)))