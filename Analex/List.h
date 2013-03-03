//
//  List.c
//  Analizador Lexico
//
//  Created by Brounie on 17/02/13.
//
//

#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct test_struct
{
    char *val;
    struct test_struct *next;
};

struct test_struct *head = NULL;
struct test_struct *curr = NULL;

struct test_struct* create_list(char *val)
{
    printf("\n creating list with headnode as [%s]\n",val);
    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->val = (char *)malloc(sizeof(char)*100);
    strcpy(ptr->val,val);
    //ptr->val = val;
    ptr->next = NULL;
    
    head = curr = ptr;
    return ptr;
}



struct test_struct* add_to_list(char *val, bool add_to_end)
{
    if(NULL == head)
    {
        return (create_list(val));
    }
    
    if(add_to_end)
        printf("\n Adding node to end of list with value [%s]\n",val);
    else
        printf("\n Adding node to beginning of list with value [%s]\n",val);
    
    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->val = (char *)malloc(sizeof(char)*100);
    strcpy(ptr->val,val);
    ptr->next = NULL;
    
    if(add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}

struct test_struct* search_in_list(char *val, struct test_struct **prev)
{
    struct test_struct *ptr = head;
    struct test_struct *tmp = NULL;
    bool found = false;
    
    printf("\n Searching the list for value [%s] \n",val);
    
    while(ptr != NULL)
    {
        if(strcmp( ptr->val, val))
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }
    
    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

int delete_from_list(char *val)
{
    struct test_struct *prev = NULL;
    struct test_struct *del = NULL;
    
    printf("\n Deleting value [%s] from list\n",val);
    
    del = search_in_list(val,&prev);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
            prev->next = del->next;
        
        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }
    
    free(del);
    del = NULL;
    
    return 0;
}


char* get_first(void)
{
    
    if(NULL == head)
    {
        return NULL;
    }
    
    return head->val;
    
}
char* get_second(void)
{
    
    if(NULL == head)
    {
        return NULL;
    }
    
    return head->next->val;
    
}

char* pop_first(void)
{
    if(NULL == head)
    {
        return NULL;
    }
    
    char *resultado = (char *)malloc(sizeof(char)*100);
    strcpy(resultado,head->val);
    head = head->next;
    //free(head);
    return resultado;
    
}


void print_list(void)
{
    struct test_struct *ptr = head;
    
    printf("\n -------Printing list Start------- \n");
    while(ptr != NULL)
    {
        printf("\n [%s] \n",ptr->val);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");
    
    return;
}
