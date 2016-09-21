#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
  compile:
  gcc -o hw1_text_indexing hw1_text_indexing.c
  
  run with file data0.txt:
  ./hw1_text_indexing < data0.txt
  
  run with file data1.txt:
  ./hw1_text_indexing < data1.txt
 
  run with file data2 txt:
  ./hw1_text_indexing < data2.txt

  run with user input:
  ./hw1_text_indexing

  Limitations:
    - Along with the assumption that text is max 10000 characters.
      I have assumed that max size of one word is 100 characters.
*/


/* Function declarations */

int get_index_arr(char *str,int *buf);  // Get arrays of indexes and return array length.

void cleanup_str(char *str);  // Make the str passed lower case and remove special character (if there) at end. 

/*
  Uses sscanf to store the first word from index i from text to str.
  Also cleans the str.
*/
void get_str(int i, char *str, char *text);

/* 
  Sort the array of indexes of length len. 
  Here indxes points to text.
*/
void insertion_sort(char *text, int *index, int len); 

void print(char* text, int *index, int len);  // print the indexes and words in a nice format.

/*
  Implements binary search.
  Stores result in search_arr.
  search_arr[0] = iterations
  search_arr[1] = mid (-1 if not found)
*/
void search(char* text,int *index, int len, char* str,int* search_arr); 

int main(int argc, char** argv){

  /*
    Arrays for storing text and indexes.
  */
  char text[10001];
  int index[10001];

  /*
    Writes the text entered to text.
  */
  printf("Enter the text: ");
  scanf("%[^\n]s",text);
  printf("\n");

  /*
    Write indexes from text to array and set index_length.
  */
  int index_length=get_index_arr(text,index);

  /*
    Print words befor sorting.
    Inderectly Sort the words.
    Print the sorted words.
  */
  printf("Words and indexes (the printed words are 'cleaned'):\n");
  print(text,index,index_length);
  insertion_sort(text,index,index_length);
  printf("The sorted data (the printed words are 'cleaned'):\n");
  print(text,index,index_length);
  
  /*
    Binary Search.
  */
  printf("Binary search. Enter words to search for. To stop type -1\n");
  char search_str[100];
  // The loop runs forever and breaks when -1 is entered.
  while(1){
    printf("Enter text to search: ");
    scanf("%s",search_str);
    if (strcmp(search_str,"-1")==0){
      break;
    }
    int search_arr[2];
    printf("Entered text: %s\n",search_str);
    search(text,index,index_length,search_str,search_arr); // Implement the search function.
    // search_arr[0]=iterations;
    // search_arr[1]=mid(index if found) / -1(if not found)
    if (search_arr[1]==-1){
      printf("Clean word: %s \n| not found | %d iterations\n\n",search_str,search_arr[0]);
    }
    else{
      printf("Clean word: %s \n|   found   | %d iterations\n\n",search_str,search_arr[0]);
    }
  }

  /*
    Print the original text to verify it is the same.
  */
  printf("\nThe original text is still the same: %s\n", text);

  return 0;
}

void search(char* text,int *index, int len, char* str,int* search_arr){
  // Implement Binary Search.
  cleanup_str(str);
  int left=0;
  int right = len-1;
  int iterations = 0;
  while(left <= right){
    iterations = iterations + 1;
    int mid = (left+right)/2;
    char str2[100];
    get_str(index[mid],str2,text);
    if (strcmp(str,str2)==0){
      search_arr[0]=iterations;
      search_arr[1]=mid;
      return;
    }
    if (strcmp(str,str2)<0){
      right=mid-1;
    }
    else {
      left= mid+1;
    }
  }
  search_arr[0]=iterations;
  search_arr[1]=-1;
  return;
}

void print(char* text, int *index, int len){
  // Print in a nice format.
  char str1[100];
  int i;
  printf("--------------------------------------\n");
  printf("|%-5s|%-10s|%-25s\n","i","index[i]","words");
  printf("|-----|----------|--------------------\n");
  for(i = 0; i<len; i++){
    sscanf(&text[index[i]],"%s",str1);
    cleanup_str(str1);
    printf("|%-5d|%-10d|%-25s\n",i,index[i],str1);
  }
  printf("--------------------------------------\n");
  printf("\n");
}

int get_index_arr(char *str, int *buf){
  int temp1 = 0;  // Counter to parse through text.
  buf[0]=0;  // Assigning 0th as 0; As first word will be always at 0.
  int index_counter = 1;  // Index counter to assign values.
  for(temp1 = 0; str[temp1]!='\0'; ++temp1){
    // If there is a space then next index should be stored.
    if (str[temp1]==' '){
      buf[index_counter]=temp1+1;
      index_counter=index_counter+1;
    }
  }
  return index_counter;
}

void cleanup_str(char *str){
  int i = 0;
  int str_length=strlen(str);  // Store length of string. Faster loop & used for checking last char.
  for(i = 0; i<str_length; i++){  // Iteratively change every character tolower.
    str[i] = tolower(str[i]);
  }
  if (!isalpha(str[str_length-1])){  // If the last char is not alpha then replace with '\0'.
    str[str_length-1]='\0';
  }
}

void get_str(int i, char *str, char *text){  
  sscanf(&text[i],"%s", str);
  cleanup_str(str);
}

void insertion_sort(char *text, int *index, int len){
  int i=0;  
  int j=0;
  int key=0;
  
  // Implementing insertion sort.
  for(i=1; i < len ; i ++ ){
    key=index[i];
    j=i-1;
    char str1[100];
    char str2[100];
    get_str(key,str1,text);
    while (j>=0){
      get_str(index[j],str2,text);
      if(strcmp(str2,str1)<=0){
        break;
      }
      index[j+1]=index[j];
      j=j-1;
    }
    index[j+1]=key;
  }
}
