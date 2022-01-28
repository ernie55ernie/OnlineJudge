'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
N = input()
paths = {}
maxnum=0
for i in range(int(N)-1):
    route = input().split(' ')
    if int(route[2])>maxnum:
        maxnum = int(route[2])
    if route[0] in paths.keys():
        paths[route[0]].append((route[1],int(route[2])))
    else:
        paths[route[0]] = [(route[1], int(route[2]))]
    if route[1] in paths.keys():
        paths[route[1]].append((route[0],int(route[2])))
    else:
        paths[route[1]] = [(route[0], int(route[2]))]

# all_route = []
# def find_route(paths, start, idx, longest):
#     if idx in paths.keys():
#         l = []
#         all_route.append(longest)
#         for path in paths[idx]:
#             if start==path[0]:
#                 continue
#             dist = longest + path[1]
#             start = idx
#             tmp, start = find_route(paths, start, path[0], dist)
#             l.append(tmp)
#         tmp1 = max(l) if len(l)!=0 else longest
#         return tmp1, start
#     else:
#         return longest, start
# a = []
# for i in paths.keys():
#     if len(paths[i])==1: # and paths[i][0][1]==maxnum:
#         a.append(i)
# print(a)
all_route = []
def DFS(graph, src, prev_len,  max_len, visited): 
    visited[src] = 1
    curr_len = 0
    adjacent = None
    for i in range(len(graph[src])):      
        adjacent = graph[src][i]  
        if (not visited[adjacent[0]]):        
            curr_len = prev_len + adjacent[1] 
            DFS(graph, adjacent[0], curr_len,  
                            max_len, visited) 
        all_route.append(curr_len)
        if (max_len[0] < curr_len):  
            max_len[0] = curr_len  
        curr_len = 0

def longestCable(graph, n): 
    max_len = [-999999999999]  
    for i in range(1, n + 1): 
        visited = [False] * (n + 1)  
        DFS(graph, i, 0, max_len, visited) 
        all_route.append(max_len[0])
    return max_len[0]

graph = [[] for i in range(int(N) + 1)] 
for i in paths.keys():
    graph[int(i)].append([int(paths[i][0][0]),int(paths[i][0][1])])
longestCable(graph, int(N))
sort_route = sorted(all_route, reverse=True)
sort_route = [i for i in sort_route if i!=sort_route[0]]
print(sort_route[0])


