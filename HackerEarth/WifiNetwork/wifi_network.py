import math

NumEmployee = int(input())
employList = []
for employ in range(NumEmployee):
    location = list(map(int,input().split(' ')))
    employList.append([location[0],location[1]])

CgCa = list(map(int,input().split(' ')))
Cg = [CgCa[0],CgCa[1]]
Ca = [CgCa[2],CgCa[3]]
NumQuery = int(input())
RgList = []
RaList = []
for R in range(NumQuery):
    rang = list(map(int, input().split()))
    RgList.append(rang[0])
    RaList.append(rang[1])

# print(RgList)
# -------------------------
# Calculate Distance
distanceGList = []
distanceAList = []
for employ in employList:
    distanceGList.append(math.sqrt( ((employ[0]-Cg[0])**2)+((employ[1]-Cg[1])**2)))
    distanceAList.append(math.sqrt( ((employ[0]-Ca[0])**2)+((employ[1]-Ca[1])**2)))
    
# for i, j in zip(distanceGList,distanceAList):
#     print(i, j)

resultList = []   
for i in range(NumQuery):
    # isInGList = []
    # isInAList = []

    # print(RgList)
    noWIFIcounter = 0
    for j in range(NumEmployee):
        isInG = 1 if (distanceGList[j] <= RgList[i]) else 0
        # isInGList.append(isInG)
        isInA = 1 if distanceAList[j] <= RaList[i] else 0
        # isInAList.append(isInA)
        if not isInG and not isInA:
            # print('none', employList[j])
            noWIFIcounter += 1
        elif isInG and isInA:
            # print('both',employList[j])
            noWIFIcounter += 1
    resultList.append(noWIFIcounter)

for result in resultList:
    print(result)