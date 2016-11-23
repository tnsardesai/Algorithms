#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "perm.h"


// Implement the functions below. 
// You can add any helper function you need.

// Function to swap characters in a string.
void swap_char(char * a, char * b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print an array of size N
void print_arr(int * arr, int N){
    int i=0;
    for(i = 0; i < N; i++){
        printf("%3d", arr[i]);
    }
    printf("\n");
}

void rec_1(int * array, int i, int N, int nr_vals){
    int j;
    if(i == N){
        print_arr(array, N);
    }
    else {
        for(j=0;j<nr_vals; j++){
            array[i]=j;
            rec_1(array,i+1,N,nr_vals);
        }
    }
}

/* Recursive function that reverses the string str. 
 * N is the length of the string. 
 */
void reverse_str(char * str, int N){
    swap_char(&str[0],&str[N-1]);
    if (N>3)
        reverse_str(str+1,N-2);
}

//  Time complexity: number of rows = theta(nr_vals^N)
void free_matrix_ptr(matrix_ptr my_matrix){
    int i =0;
    for(i = 0; i < my_matrix->rows; i++){
        free(my_matrix->data_arr[i]);
    }
    free(my_matrix->data_arr);
    free(my_matrix);
}

//  Time complexity: the function rec_1 is a recursive function which runs
//  nr_vals steps for N times.
//  Therefore, time complexity = theta(nr_vals^N)
void perm_rec_1(int N, int nr_vals){
    int array[N];
    rec_1(array, 0, N, nr_vals);
}

void rec_2(int * array, matrix_ptr res, int i, int * j, int nr_vals){
    int k;
    if(i == res->cols){
        for(k=0;k<res->cols;k++){
            *(*(res->data_arr+*j)+k) = array[k];
        }
        (*j)++;
    }
    else {
        for(k=0;k<nr_vals; k++){
            array[i]=k;
            rec_2(array, res, i+1, j, nr_vals);
        }
    }
}

//  Time complexity: allocation the array takes theta(nr_vals^N)
//  the function rec_2 runs nr_vals steps for N values exactly like rec_1.
//  Therefore time complexity = theta(nr_vals^N) + theta(nr_vals^N)
//  Therefore = theta(nr_vals^N)
matrix_ptr perm_rec_2(int N, int nr_vals) {
    matrix_ptr res = (matrix_ptr) malloc(sizeof(struct matrix_2D_struct));
    res->cols = N;
    res->rows = pow(nr_vals,N);
    res->data_arr = (int**) malloc(res->rows*sizeof(int *));
    int i =0;
    for(i =0; i< res->rows;i++){
        res->data_arr[i] = (int *) malloc(res->cols*sizeof(int));
    }
    int array[res->cols];
    int j = 0;
    rec_2(array,res, 0, &j, nr_vals);
    return res;
}

/*  Time complexity: 
 *  N + (N + N + N -1)*(nr_vals^N) 
 *  So time complexity = theta(N*(nr_vals^N))  
*/
void perm_iter(int N, int nr_vals){    
    int array[N];
    int i = 0;
    for(i=0;i<N;i++)
    {
        array[i]= 0;
    }
    while(1){ 
        int counter = 0;
        int status = 0;
        print_arr(array, N);  
        for(counter=0;counter<N;counter++){
            if(array[counter] == nr_vals-1)
                status++;
        }
        if (status == N){
            break;
        }
        array[N-1]++;
        if(array[N-1] == nr_vals){
            array[N-1] = 0;
            for(counter=N-2; counter >= 0; counter--){
                array[counter]++;
                if(array[counter]< nr_vals){
                    break;
                }
                else {
                    array[counter] = 0;
                }
            }
        }
    }
}

