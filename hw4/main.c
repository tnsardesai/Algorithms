/* 
 * File:   edit_distance.c
 * Author: Tanmay Sardesai
 *
 * Created on November 4, 2016, 3:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void end_print();
void store_str(char* str1, char* str2);
int check_endcase(char* str1,char* str2);
void edit_distance(char* str1,char* str2);
int min(int i1,int i2, int i3);

struct block {
    int cost;
    char arrow;
};

/*
 * 
 */
int main(int argc, char** argv) {
    
    printf("Enter two words separated by a space (e.g.: cat someone).\n");
    printf("\tStop with : -1 - 1\n\n");
    
    // Main loop of the program.
    while(1){
        char str1[101];
        char str2[101];
        
        // Scans for input and stores prints the first and second.
        store_str(str1,str2);
        
        // Checks if the input is "-1 -1".
        if(check_endcase(str1,str2)){break;}
        
        // Function that does all the computations.
        edit_distance(str1,str2);
        
        // Prints a bunch "==".
        end_print();
    }
    
    printf("Exiting...");
    end_print();
    return (EXIT_SUCCESS);
}


void edit_distance(char* str1,char* str2){
    // Initializing the matrix of struct to store input in.
    // Initializing cost to 0 and arrow to x.
    int str1_length = strlen(str1);
    int str2_length = strlen(str2);
    struct block dm[str1_length+1][str2_length+1];
    int i=0;
    int j=0;
    dm[0][0].cost = 0;
    dm[0][0].arrow = 'd';
    for(i=1;i<str1_length+1;i++){
        dm[i][0].cost = 1+dm[i-1][0].cost;
        dm[i][0].arrow = 'u';
    }
    for(j=1;j<str2_length+1;j++){
        dm[0][j].cost = 1+dm[0][j-1].cost;
        dm[0][j].arrow = 'l';
    }
    //for(i=1;i<str1_length+1;i__)
    
    for(i=1;i<str1_length+1;i++){
        for(j=1;j<str2_length+1;j++){
            if(dm[i-1][j-1].cost == min(dm[i-1][j-1].cost, dm[i-1][j].cost, dm[i][j-1].cost )){
                dm[i][j].arrow = 'd';
                if(str1[i-1] == str2[j-1]){
                    dm[i][j].cost = dm[i-1][j-1].cost;
                }
                else{
                    dm[i][j].cost = dm[i-1][j-1].cost + 1;
                }
            }
            else if(dm[i-1][j].cost == min(dm[i-1][j-1].cost, dm[i-1][j].cost, dm[i][j-1].cost )){
                dm[i][j].cost = dm[i-1][j].cost + 1;
                dm[i][j].arrow = 'u';
            }
            else if(dm[i][j-1].cost == min(dm[i-1][j-1].cost, dm[i-1][j].cost, dm[i][j-1].cost )){
                dm[i][j].cost = dm[i][j-1].cost + 1;
                dm[i][j].arrow = 'l';
            }
        }
    }
    
    for(i=0;i<str1_length+1;i++){
        if(i==0){
            for(j=0; j<str2_length+2;j++){
                if(j<2){
                    printf("   |");
                }
                else{
                    printf("%3c|",str2[j-2]);
                }
            }
            printf("\n");
        
            for(j=0; j<str2_length+2;j++){
                printf("----");
            }
            printf("\n");
        }
        if(i<1){
            printf("   |");
        }
        if(i>=1){
            printf("%3c|", str1[i-1]);
        }
        for(j=0; j<str2_length+1;j++){
            printf("%3d|",dm[i][j].cost);
        }
        printf("\n");
        
        for(j=0; j<str2_length+2;j++){
            printf("----");
        }
        printf("\n");
    }
    
    
    printf("\nedit distance: %d\n",dm[str1_length][str2_length].cost);
    printf("Alignment: \n");
    
    char res1[101];
    char res2[101];
    char cost[101];
    int n=0;
    i=str1_length;j=str2_length;
    while(1){
        if(i == 0 && j==0){
            break;
        }
        if(dm[i][j].arrow == 'd'){
            res1[n] = str1[i-1];
            res2[n] = str2[j-1];
            if(res1[n] == res2[n]){
                cost[n] = '.';
            }
            else{
                cost[n] = 'x';
            }
            i--;
            j--;
            n++;
        }
        else if(dm[i][j].arrow == 'u'){
            res1[n] = str1[i-1];
            res2[n] = '-';
            cost[n] = 'x';
            i--;
            n++;
        }
        else if(dm[i][j].arrow == 'l'){
            res1[n] = '-';
            res2[n] = str2[j-1];
            cost[n] = 'x';
            j--;
            n++;
        }
    }
    
    for(i=n-1;i>=0;i--){
        printf("%c ",res1[i]);
    }
    printf("\n");
    for(i=n-1;i>=0;i--){
        printf("%c ",res2[i]);
    }
    printf("\n");
    for(i=n-1;i>=0;i--){
        printf("%c ",cost[i]);
    }
    printf("\n");
    
    return;
}

int min(int i1,int i2, int i3){
    int min = i1;
    if(i2 < min){
        min = i2;
    }
    if(i3 < min){
        min = i3;
    }    
    return min;
}

int check_endcase(char* str1,char* str2){
    if((strcmp(str1,"-1") == 0) && (strcmp(str2,"-1") == 0) ){
        return 1;
    }
    else{
        return 0;
    }
}

void store_str(char* str1, char* str2){
    scanf("%s",str1);
    scanf("%s",str2);
    printf("\nfirst: %s\n",str1);
    printf("second: %s\n\n",str2);
    return;
}

void end_print(){
    int print_counter=0;
    printf("\n");
    for(print_counter=0; print_counter<50;print_counter++)
    {
        printf("=");
    }
    printf("\n\n");
    return;
}


        /*for(i=0;i<str1_length+1;i++){
            for(j=0; j<str2_length+1;j++){
                printf("%d",dm[i][j].cost);
            }
            printf("\n");
        }
        for(i=0;i<str1_length+1;i++){
            for(j=0; j<str2_length+1;j++){
                printf("%c",dm[i][j].arrow);
            }
            printf("\n");
        }*/