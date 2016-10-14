/* 
 * File:   perm.h
 * Author: alex
 *
  */

#ifndef PERM_H
#define	PERM_H

struct matrix_2D_struct {
    int** data_arr;
    int rows;
    int cols;
};
typedef struct matrix_2D_struct * matrix_ptr;

/* Implement the functions below. 
 * You can write additional helper functions.
 * Do not modify the matrix_2D_struct or the matrix_ptr definitions.
 */ 

 /* Recursive function that reverses the string str. 
  * N is the length of the string.
  */
 void reverse_str(char * str, int N);

/* 
 * Generates RECURSIVELY and prints all the permutations with repetitions
 * of N objects taken from a set of nr_vals different objects.
 */
void perm_rec_1(int N, int nr_vals);        

/* 
 * Generates RECURSIVELY  and returns a matrix_ptr that holds all the permutations  
 * with repetitions of N objects taken from a set of nr_vals different objects.
 */
matrix_ptr perm_rec_2(int N, int nr_vals);

/* 
 * Generates ITERATIVELY and prints all the permutations with repetitions
 * of N objects taken from a set of nr_vals different objects.
 */
void perm_iter(int N, int nr_vals);

/* Frees the dynamic memory allocated for my_array.
 */
void free_matrix_ptr(matrix_ptr my_array);
    
#endif	/* PERM_H */


