//
//  main.c
//  DeadlockDetectionAlgorithm
//
//  Created by James Hall on 9/12/15.
//  Copyright (c) 2015 James Hall. All rights reserved.
//  Converting Bankers Algorithm to Deadlock Detection Algorithm.
//  Should be able to simulate Deadlock Detection and Recovery.

#include <stdio.h>
//#include <conio.h>// TODO: come back to this and figure out what it's for

/* Our Data Structure */
int max[5][5];// max [n][m] n = process, m = resources 
int alloc[5][5];
int need[5][5];
int avail[5];

int n, r;
void input();// Asks for all inputs
void show();// Shows all outpus
void cal();// Does all the heavy lifting.

int main()
{

    printf("------------------Deadlock Detection Algorithm ---------------------------\n");
    input();
    show();
    calculate();
//    getch(); working on this
    return 0;
}

void input()
{
    int i, j;
    printf("Enter the number of Processes\t ");
    scanf("%d", &n);
    printf("Enter the number of Resource Instances\t");
    scanf("%d",&r);
    printf("Enter the Max Matrix\n");
    for( i = 0; i < n; i++)
    {
        for(j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the Allocation Maxtrix\n ");
    for(i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter the available Resources\n ");
    for(j = 0; j < r; j++)
    {
        scanf("%d", &avail[j]);
    }
}
void show()
{
    int i, j;
    printf("Process\t Allocation\t Max\t Available\t ");
    for(i = 0; i < n; i++)
    {
        printf("\nP%d\t ", i+1);
        for(j = 0; j < r; j++)
        {
            printf("%d ", alloc[i][j]);
        }
        printf("\t ");
        for(j = 0; j < r; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\t");
        if (i == 0) {
            for (j = 0; j < r; j++)
            {
                printf("%d", avail[j]);
            }
        }
    }
}

void calculate()
{
    int finish[5], temp, need[5][5], flag = 1, k, c1 = 0;
    int dead[5];
    int safe[5];
    int i, j;
    for( i = 0; i < n; i ++ )
    {
        finish[i]=0;
    }
    //find need matrix
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    while(flag)
    {
        flag = 0;
        for (i = 0; i < n; i++)
        {
            int c = 0;
            for( j = 0; j < r; j++)
            {
                if ( ( finish[i]==0 ) && ( need[i][j] <= avail[j] ) )
                {
                    c++;
                    if(c==r)
                    {
                        for(k=0;k<r;k++)
                        {
                            avail[k]+= alloc[i][j];
                            finish[i] = 1;
                            flag = 1;
                        }
                        printf("\nP%d", i);
                        if (finish[i]==1)
                        {
                            i = n;
                        }
                    }
                }
            }
        }
    }
    j = 0;
    flag = 0;
    for(i = 0; i < n; i++)
    {
        if(finish[i] == 0)
        {
            dead[j] = i;
            j++;
            flag = 1;
        }
    }
    if(flag == 1)
    {
        printf("\n\nSystem is in Deadlock and the Deadlock process are \n");
        for(i = 0; i < n; i++)
        {
            printf("P%d\t", dead[i]);
        }
    }else{
        printf("\n No Deadlock Occur");
    }
}