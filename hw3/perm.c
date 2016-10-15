#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "perm.h"


// Implement the functions below. 
// You can add any helper function you need.

void swap_char(char * a, char * b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

/* Recursive function that reverses the string str. 
 * N is the length of the string. 
 */
void reverse_str(char * str, int N){
    swap_char(&str[0],&str[N-1]);
    if (N>3)
        reverse_str(str+1,N-2);
}

//  Time complexity: 
void free_matrix_ptr(matrix_ptr my_matrix){
    // your code here
}

//  Time complexity: 
void perm_rec_1(int N, int nr_vals){
    // your code here
}

//  Time complexity: 
matrix_ptr perm_rec_2(int N, int nr_vals) {
    // your code here    return res;
    return NULL;
}

//  Time complexity: 
void perm_iter(int N, int nr_vals){    
    // your code here
}

