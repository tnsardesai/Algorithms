/* 
 * File:   main.c
 * Author: tanmay
 *
 * Created on October 13, 2016, 8:08 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "perm.h"


void print_2D(matrix_ptr mat){
    int i, j;
    if (mat == NULL || mat->data_arr == NULL) {
        return;
    }
    
    printf("\nrows = %d, columns = %d\n", mat->rows, mat->cols);
    int ct = 0;
    for(i = 0; i < mat->rows; i++){
        for(j = 0; j < mat->cols; j++, ct++) {
            printf("%3d", mat->data_arr[i][j] );            
        }
        printf("\n");
    }    
}

void call_perm_rec_1(int N, int nr_vals){
    printf("\nCalled : perm_rec_1(%d, %d);\n", N, nr_vals);
    perm_rec_1(N, nr_vals); // you must implement this function.    
}

/*
 * Test generating permutations recursively and iteratively and returning an 
 * array with all the permutations.
 */
int main(int argc, char** argv) {        
    char str[10] = {'a','b','c','d','e'};
	printf("Original: %s\n", str);
    reverse_str(str,5);
    printf("Reversed: %s\n", str);
	
/*	
    call_perm_rec_1(3,2);  // you need to implement perm_rec_1
    call_perm_rec_1(5,2);
    call_perm_rec_1(4,3);

    call_perm_rec_1(2,4);
    call_perm_rec_1(4,2);  
 */     
    int N = 4;
    int nr_vals = 2;
    
    printf("\nIn Main, ITERATIVE, called : perm_iter(%d, %d);\n", N, nr_vals);   
    perm_iter(N, nr_vals); // you must implement this function.
/*            
    printf("\nIn Main, called : perm_rec_2(%d, %d);\n", N, nr_vals);       
    matrix_ptr res = perm_rec_2(N, nr_vals);  // you must implement this function.
    printf("\nIn Main, printing the res->data_arr table: \n");        
    print_2D(res);
    
    free_matrix_ptr(res); // you must implement this function.
 */  
    
    return (EXIT_SUCCESS);
}


