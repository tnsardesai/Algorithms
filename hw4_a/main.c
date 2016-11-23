/* 
 * File:   main.c
 * Author: Tanmay Sardesai
 *
 * Created on November 5, 2016, 10:34 PM
 */

#include <stdio.h>
#include <stdlib.h>


// Solution to task1 part c is bar and foo.
int foo(int N,int* sols);
int bar(int N);

// Solution to task5
int rec(int* arr, int length);
/*
 * 
 */
int main(int argc, char** argv) {

    int result=bar(6);
    printf("%d\n",result);
    
    int array1[4]={3,6,1,8};
    result=rec(array1,4);
    printf("%d\n",result);
    
    int array2[5]={3,6,8,50,10000};
    result=rec(array2,5);
    printf("%d\n",result);
    
    int array3[4]={NULL};
    result=rec(array3,4);
    printf("%d\n",result);
    
    return (EXIT_SUCCESS);
}

// TASK 5:

int rec(int* arr, int length){
    if(arr[0] == NULL){
        return 1;
    }
    if(length == 0 ){
        return 0;
    }
    int res1 = arr[length-1];
    int res2 = arr[length-2];
    if(res2 <= res1){
        return rec(arr,length-1);
    }
    else{
        return 1;
    }
}

// Solution to task1 part c is bar and foo
int bar(int N){
    int sols[N+1];
    int i=0;
    for(i=0;i<N+1;i++){
        sols[i]=-1;
    }
    sols[0] = 5;
    sols[1] = 5;
    int result = foo(N,sols);
    
    return result;
}

int foo(int N,int* sols){
    int res1=0;
    int res2=0;
    if(sols[N/2]==-1){
        sols[N/2] = foo(N/2,sols);
    }
    res1 = 3*sols[N/2];
    if(sols[N-1]!=-1){
        sols[N-1] = foo(N-1,sols);
    }
    res2 = sols[N-1];
    if (res1 >= res2){
        return res1;
    }
    else{
        return res2;
    }
}
