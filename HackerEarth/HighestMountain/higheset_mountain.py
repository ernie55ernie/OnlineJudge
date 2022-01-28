'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
def iteration(moun, idx):
    up = 0
    down = 0
    upidx = idx
    downidx = idx
    while upidx+1 < len(moun) and moun[upidx]+1 == moun[upidx+1]:
        up+=1
        upidx+=1
    while downidx-1 >= 0 and moun[downidx]+1 == moun[downidx-1]:
        down+=1
        downidx-=1
    if up > down:
        return moun[upidx], upidx
    else:
        return moun[downidx], downidx

case = int(input())
for i in range(case):
    num = input()
    num = input()
    moun = input().split(' ')
    moun = [int(i) for i in moun]
    index = [idx for idx, i in enumerate(moun) if i==1]
    maxh = 0
    maxl = 0
    for idx in index:
        H, L = iteration(moun, idx)
        if H > maxh:
            maxh = H
            maxl = L
    if len(index)==0:
        print('Case #'+str(i+1)+': -1 -1')
    else:
        print('Case #'+str(i+1)+': '+str(maxh)+' '+str(maxl))


