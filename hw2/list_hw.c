/* This program uses code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"


struct node_struct {
    Item item;
    link next;
};

struct list_struct {
    link first;
    int length;    
};



// ------------- link functions

/* Creates a new link, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
link newLink(Item value, link next_in) {
    link result = (link) malloc(sizeof (struct node_struct));
    result->item = value;
    result->next = next_in;
    return result;
}

void destroyLink(link the_link)  {
    if (the_link != NULL) {
        free(the_link);
    }
}

Item getLinkItem(link the_link) {
    if (the_link != NULL) {
        return the_link->item;    
    }
    else {
        printf("\n getLinkItem: Empty link. Returned -1.");
        return -1;    // NOTE: This line can be improved.
    }
}


link getLinkNext(link the_link) {
    if (the_link != NULL) {
        return the_link->next;
    }
    else {
        return NULL;
    }
}

void setLinkItem(link the_link, Item value) {
    if (the_link != NULL) {
        the_link->item = value;
    }
}

void setLinkNext(link the_link, link next) {
    if (the_link != NULL) {
        the_link->next = next;
    }
}



/*    --------  LIST functions    */

int listIsNULL(list the_list) {
    if (the_list == NULL) {
        printf("\nThe list pointer is NULL)\n");
        return 1;
    }     
    else {
        return 0;
    }    
}

/* Creates and returns an empty list. */
list newList() {
    list result = (list) malloc(sizeof (*result));
    result->first = NULL;
    result->length = 0;
    return result;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroyList(list the_list) {
    if (listIsNULL(the_list) == 1) {        
        return;
    }
    
    link current = the_list->first;
    while (1) {
        if (current == NULL) {
            break;
        }

        link next = current->next;
        destroyLink(current);
        current = next;
    }
    free(the_list);
}

link getFirst(list the_list) {
    if (listIsNULL(the_list) == 1) {        
        return NULL;
    }
    
    return the_list->first;
}

int getLength(list the_list) {
    if (listIsNULL(the_list) == 1) {        
        return -1;
    }
    
    return the_list->length;
}


/* Sets the data to empty (first is null, length is 0,...)
 * It does NOT free any memory.
 */ 
void setEmpty(list the_list) {
    the_list->first = NULL;    
    the_list->length = 0;
}


/* Inserts new_link to the specified list, at the position right after
 * the link called "previous". */
void insertLink(list my_list, link previous, link new_link) {
    if (listIsNULL(my_list) == 1) {        
        return;
    }    
    
    /* We need a special case when we want to insert to the beginning.
     * In that case, the previous link is NULL. */
    if (previous == NULL) {
        new_link->next = my_list->first;
        my_list->first = new_link;
    } else {
        new_link->next = previous->next;
        previous->next = new_link;
    }
    
    my_list->length += 1;
}

/* Inserts new_link to the beginning of the list. */
void insertAtBeginning(list my_list, link new_link) {
    setLinkNext(new_link, getFirst(my_list));  // replaces: new_link->next = my_list->first;
    my_list->first = new_link;
    my_list->length += 1;
}

/* Removes from the list and returns the link coming AFTER link x. 
 * This function DOES NOT remove link x itself. 
 */
link removeNext(list my_list, link x) {
    if (listIsNULL(my_list) == 1) {        
        return NULL;
    }     
    
    link temp;
    if (x == NULL) // try to delete the first node
    {
        temp = my_list->first;
        if (my_list->first != NULL) // There is at least one node in the list.
        {
            my_list->first = my_list->first->next;
            my_list->length -= 1;
        }
    } else {
        temp = x->next;
        x->next = x->next->next;  // IS THIS CODE SAFE? JUSTIFY YOUR ANSWER.
        my_list->length -= 1;
    }
    return temp;
}

/* Removes from the list and returns the link at the beginning of the list.
It does not free the memory for that node. */
link removeFirst(list my_list) {
    if (listIsNULL(my_list) == 1) {        
        return NULL;
    }    
    
    link first_node = my_list->first;
    if (first_node != NULL) {
        my_list->first = first_node->next;
        my_list->length -= 1;
    }
    return first_node;
}

void reverse(list the_list) {
    if (listIsNULL(the_list) == 1) {        
        return;
    }    
    
    link current = the_list->first;
    link previous = NULL;
    while (current != NULL) {
        link temp = current->next;
        current->next = previous;
        previous = current;
        current = temp;
    }
    the_list->first = previous;
}

void printList(list my_list) {
    if (listIsNULL(my_list) == 1) {        
        return;
    }     

    
    int i = 0;
    int n = my_list->length;
    link curr;    
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("item %d: %d\n", i, curr->item);
        i++;
    }
    printf("\n");
}


void printListHoriz(list my_list) {
    if (listIsNULL(my_list) == 1) {        
        return;
    }     

    
    int i = 0;
    int n = my_list->length;
    link curr;    
    printf("\n List length = %d\n List items:\n", my_list->length);
    for (i = 0, curr = my_list->first; (curr != NULL) && (i<n) ; curr = curr->next) {
        printf("%d    ", curr->item);
        i++;
    }
    printf("\n");
}

int computeLength(list my_list) {
     if (listIsNULL(my_list) == 1) {        
        return -1;
    }     
    
    int counter = 0;
    link i;
    for (i = my_list->first; i != NULL; i = i->next) {
        counter++;
    }
    return counter;
}

list listDeepCopy(list input) {    
    list result = newList();
    link in = getFirst(input);
    link previous = NULL;
    while (in != NULL) {
        link out = newLink(getLinkItem(in), NULL);
        insertLink(result, previous, out);
        previous = out;
        in = getLinkNext(in);
    }

    return result;
}

/* returns a new list that contains all values of input1 and all values 
 * of input2
 */
list concatLists(list input1, list input2) {
    list result = listDeepCopy(input1);
    list temp2 = listDeepCopy(input2);
    concatListsDestructive(result, temp2);
    free(temp2);
    return result;
}

/* Modifies target, by inserting at the end of it all links from source.  */
void concatListsDestructive(list target, list source) {
    link previous = NULL;
    link c;

    /* find the last link of target*/
    for (c = getFirst(target); c != NULL; c = getLinkNext(c)) {
        previous = c;
    }

    /* at this point, previous is the last link of target */
    setLinkNext(previous, getFirst(source));
    target->length = target->length + source->length;  // important      
    
    /* Source should not link to the moved nodes any more (when target and source 
     * lists get destroyed, each of them will attempt to free the nodes in 
     * source).
     */
    setEmpty(source);
}



/*----------------------------------------------------------------
 New functions for HW3.
 Finish their implementation below. 
 If you need to use helper functions you can define them and use them in this file.
 You should not change the behavior of any of the functions defined above.
 */

link getLastLink(list A){
    link c = getFirst(A);

    /* find the last link of target*/
    while(c->next != NULL){
        c = getLinkNext(c);
    }
    
    return c;
}

void insertAtPosition(list A, Item P, int pos){
    if(listIsNULL(A)){
        printf("A is not changed\n");
        return;
    }
    link new = newLink(P,NULL);
    link curr;
    int i = 0 ;
    int n = A->length;
    if (pos <= 0 || getFirst(A) == NULL){
        insertAtBeginning(A, new);
        return;
    }
    else if (pos >=n){
        pos = n;
    }
    for (i = 0, curr = A->first; (curr != NULL) && (i<n) ; curr = curr->next){
        if (pos == i+1){
            insertLink(A,curr,new);
            return;
        }
        i++;
    }
    return;
}

void deleteOccurrences(list A, Item V) {
    if(getFirst(A) == NULL){
        printf("Please check your list A.\n"
                "It is  empty or NULL.\n");
        return;
    }
    while (V == A->first->item){
        link fir = removeFirst(A);
        free(fir);
        if (A->first == NULL){
            return;
        }
    }
    link curr;
    int i = 0 ;
    int n = A->length;
    for (i = 0, curr = A->first; (curr->next != NULL) && (i< n-1) ; curr = curr->next){
        while (V == curr->next->item){
            if (curr->next->next == NULL){
                free(curr->next);
                curr->next=NULL;
                i++;
                return;
            }
            else {
                link out = removeNext(A,curr);
                free(out);
                i++;
            }
        }
        i++;
    }
    return;
}

list sublist(list A, list pos_list) {
    // Since getFirst returns NULL for list=NULL and list->first = NULL
    if(getFirst(A) == NULL || getFirst(pos_list) == NULL){
        printf("Please check your list A and pos_list.\n"
                "One or both of them are NULL or empty.\n");
        return NULL;
    }

    list result = newList();
    link curr;
    int i = 0 ;
    int n = A->length;
    link in = getFirst(pos_list);
    link previous = NULL;
    while (in != NULL) {
        for (i = 0, curr = A->first; (curr != NULL) && (i<n) ; curr = curr->next) {
            if (getLinkItem(in) < 0 || getLinkItem(in) >= getLength(A)){
                printf("Index in pos_list is out of bounds.\n");
                destroyList(result);
                return NULL;
            }
            else if( i == getLinkItem(in)){
                link out = newLink(getLinkItem(curr),NULL);
                insertLink(result, previous, out);
                previous = out;
                in = getLinkNext(in);
                break;
            }
            i++;
        }
    }
    return result;
}

void moveAllMaxAtEnd(list A) {
    if(getFirst(A) == NULL){
        printf("Please check your list A.\n"
                "It is  empty or NULL.\n");
        return;
    }
    int max = 0;
    link node = A->first;
    while(node != NULL){
        if(max < node->item ){
            max = node->item;
        }
        node = node->next;
    }
    link curr;
    link last;
    int i = 0 ;
    int n = A->length;
    for (i = 0, curr = A->first; (i< n-1) ; i++){
        if (A->first->item == max){
            last = getLastLink(A);
            last->next = A->first;
            A->first = A->first->next;
            last->next->next = NULL;
            curr = A->first;
            continue;
        }
        while (max == curr->next->item){
            last = getLastLink(A);
            last->next = curr->next;
            curr->next = curr->next->next;
            last->next->next = NULL;
            i++;
            if (i>n-1){
                break;
            }
        }
        curr = curr->next;
    }
    return;
}


