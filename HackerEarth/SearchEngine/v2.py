'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here

import re


test_cases = 0
line_count = 0
output = []
next_two_int = 1
DBList = []
QueryList = []
case = 0
# Read file
go = 1
while case <= test_cases:
    line = input()
    # print(line)
    if line_count == 0:
        test_cases = int(line)
    elif line_count == next_two_int:
        # print(line_count, next_two_int)                
        N = int(line.split(' ')[0])
        Q = int(line.split(' ')[1])
        next_two_int += (N+Q+1)
        # print(next_two_int)
        next_query_start = line_count + N+1
        last_query = line_count + N+Q
        # print(last_query)
        DBList = []
        QueryList = []
    elif line_count < next_query_start:
        DBList.append(line)
    else:
        QueryList.append(line)
        if line_count == last_query:
            # print(DBList)
            # print(QueryList)
            # print('case',case)
            case += 1
            output.append('Case '+str(case)+':')
            for query in QueryList:
                count = 0
                for db in DBList:
                    # if query in db:
                    if re.search(r'\b' + query + r'\b', db):
                    	# print(query)
                    	# print(db)
                    	# print()
                    	count += 1
                # print('BERT',count)
                output.append(count)
            # print(case, test_cases)
            if case == test_cases:
                break
    line_count += 1
        
for i in output:
    print(i)











