/* 
 * File:   main.c
 * Author: Tanmay Sardesai
 *
 * Created on November 9, 2016, 11:19 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


// stores a point
struct point{
    int x;
    int y;
};

// stores an array of points and length of the the array
struct points {
    struct point* array;
    int length;
};

// Creates a test file with N random points. Here points is x, y
void create_file(int n);

// Scanfs the input file and stores evreything in the stuct points.
struct points* store_input();

// Destorys the struct allocated in store_input(); 
void free_points(struct points* points_ptr);

// Returns the index of the lowest point in the struct.
// In case of a tie leftmost point is picked
int lowest_point_index(struct points* my_input);

// Calculates the cross product of (p1-p0)x(p2-p0)
int cross_product(struct point p1,struct point p2,struct point p3);

// Gives the square of the distance between p1 and p2.
int distance_sq(struct point p1,struct point p2);

// This is the function that has the main algorithm of computing a convex hull.
void jarvis_march(struct points* my_input);

// Called from jarvis_march. This writes to a file called result.txt
void write_result(int* result, int N, struct points* my_input);

/*
 * Main Function.  
 */
int main(int argc, char** argv) {

    // Create 2 file with random numbers.
    create_file(1000);
    create_file(10);
    
    struct points* input = store_input();
    
    jarvis_march(input);

    free_points(input);
    return (EXIT_SUCCESS);
}


void jarvis_march(struct points* my_input){
    
    int result[my_input->length];               // This array stores the result.
    int min_i = lowest_point_index(my_input);   // This is the min point of my input.
    
    int i=0;
    result[i] = min_i;                          // The min_i is the first point of the hull.
    for(i=1;i<my_input->length;i++){            // Initialize everything else to -1.
        result[i] = -1;
    }
    
    i=0;
    printf("\n\n%d\n\n x = %d , y = %d \n",
        result[i],my_input->array[result[i]].x,my_input->array[result[i]].y);
        
    while(1){
        int j=0;
        int polar_min=0;                        // Assume 0 is min and start looking for mins
        int previous= result[i];                // Previous is the point for which we want to find the polar min
        for(j=0;j<my_input->length;j++){        // Do this on all the inputs
            if(j!=previous){                    // Do this for everything except previous
                int cross = cross_product(my_input->array[polar_min],
                            my_input->array[j],my_input->array[previous]); // Calculates the cross product.
                if(cross < 0){ // is cross product is negative.
                    polar_min = j;
                }
                if(cross == 0){ // if cross product is 0.
                    // See which one is the furtest.
                    int d1_sq =distance_sq(my_input->array[polar_min],
                                my_input->array[previous]); 
                    int d2_sq =distance_sq(my_input->array[j],
                                my_input->array[previous]);
                    if(d2_sq > d1_sq){
                        polar_min = j;
                    }
                }
            }
        }
        if(polar_min==min_i){ // Once we get our polar_min as min_i then we break as we have reached the start.
            break;
        }
        i++;
        result[i]=polar_min;  // If we didn't break then write to result
        printf("\n\n%d\n\n x = %d , y = %d \n",result[i],
                    my_input->array[result[i]].x,my_input->array[result[i]].y);
    }
    
    // Write the result to a file.
    write_result(result,i+1,my_input);
    
    return;
}

void write_result(int* result,int N, struct points* my_input){
    FILE *fp;

    // Create a result.txt
    fp = fopen("result.txt","w+");
    
    // From here to the first for loop we store data like the input.
    fprintf(fp,"%d\n",my_input->length);
    int i=0;
    for(i=0;i<my_input->length;i++){
        fprintf(fp,"%d %d\n",my_input->array[i].x,
                my_input->array[i].y);
    }
    
    // This is going to store the number of points in the result and then the result.
    fprintf(fp,"%d\n",N);
    for(i=0; i<N;i++){
        fprintf(fp,"%d %d\n",my_input->array[result[i]].x,
                my_input->array[result[i]].y);
    }
    
    // Close the file.
    fclose(fp);
    return;
}

int distance_sq(struct point p1,struct point p2){
    // Sqaure of the distance.
    int result = pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2);
    return result;
}

int cross_product(struct point p1,struct point p2,struct point p0){
    // Cross product using the determinant.
    int result = (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
    return result;
}

int lowest_point_index(struct points* my_input){
    
    int i = 0;
    int min_i = 0;     // Assume that the minumum index is at 0.
    for(i=1; i< my_input->length; i++){
        // if y at i is smaller then swap.
        if(my_input->array[min_i].y > my_input->array[i].y){
            min_i = i;
        }
        // if y at i is equal then check for which has smaller value of x.
        if(my_input->array[min_i].y == my_input->array[i].y){
            if(my_input->array[min_i].x > my_input->array[i].x){
                min_i = i;
            }
        }
    }
    
    return min_i;
}

void free_points(struct points* points_ptr){
    // First free the array and then the struct.
    free(points_ptr->array);
    free(points_ptr);
    
    return;
}

struct points* store_input(){

    // Allocate memory for the result.    
    struct points* result = (struct points*) malloc(sizeof(struct points));
    int i=0;
    char s[10];
    scanf("%s",s);
    // Store length.
    result->length = atoi(s);
    // Allocate memory for the array in the result.
    result->array = (struct point*)malloc(result->length*sizeof(struct point));
    
    // Store items in the array.
    for(i=0;i<result->length;i++){
        char s1[10];
        scanf("%s",s1);
        result->array[i].x = atoi(s1);
        
        char s2[10];
        scanf("%s",s2);
        result->array[i].y = atoi(s2);
    }
    
    return result;
}

void create_file(int N){
    
    // The max number of points should be 0 to 1000;
    if(N > 1000 || N < 0 ){
        printf("Enter a number between 0 and 1000.\n");
        return;
    }
    FILE *fp;
    char filename[100];
    
    // File name will be of the form test_N.txt
    sprintf(filename,"test_%d.txt", N);
    fp = fopen(filename,"w+");
    
    fprintf(fp,"%d\n",N);
    
    int i =0;
    // Generate random points and store in the file.
    srand(time (NULL));
    for(i=0; i<N;i++){
        int r1 = rand() % (2000);
        r1 = r1 - 1000;
        int r2 = rand() % (2000);
        r2 = r2 - 1000;
        
        fprintf(fp,"%d %d\n",r1,r2);
    }
    
    // Close the file.
    fclose(fp);
    
    return;
}

