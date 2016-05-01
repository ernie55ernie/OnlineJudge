#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SZ 10

int table[SZ][SZ];
int P[] = {1, 2, 3, 4, 3};

int MCM(int i, int j)
{
    if(i==j) return 0;

    else
    {
        int min = INT_MAX;

        for(int k=i;k<j;k++) // bug was here: for(int k=i;k<=j;k++)
        {
            if(table[i][k]==0)
                table[i][k] = MCM(i,k);
            if(table[k+1][j]==0)
                table[k+1][j] = MCM(k+1,j);
            int sum = table[i][k] + table[k+1][j] + P[i-1]*P[j]*P[k];
            if(sum<min)
                min = sum;  
        }
        return min;
    }
}

int main()
{
    int size = sizeof(P)/sizeof(P[0]);
    printf("Minimum number of mutiplications is %d",MCM(1,size-1));
    return 0;
}