/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------

#include<stdlib.h>
#include "List.h"


// Private Structs -----------------------------------------------------------
typedef struct nodeN* Node;

typedef struct nodeN
{
    int data;
    struct nodeN *prev;
    struct nodeN *next;
} nodeN;

typedef struct listL
{
    Node head, tail, curr;
    int length, cursor;
} listL;

// Constructors-Destructors ---------------------------------------------------
/* Creates a new Node object reference with initialized fields */
Node n(int nData)
{
    Node newNode = malloc(sizeof(nodeN));
    newNode->data = nData;
    newNode->prev = NULL;
    newNode->next = NULL;
    return(newNode);
}

/* Creates a new empty list */
List newList(void)
{
    List l = malloc(sizeof(struct listL));
    l->curr = NULL;
    l->head = NULL;
    l->tail = NULL;
    l->cursor = -1;
    l->length = 0;
    return l;
}

/* Frees all heap memory associated with its list argument and sets list to null */
void freeList(List* pL)
{
    if ((*pL) == NULL)
        printf("Empty List -- free");
    else
    {
        while(!isEmpty(*pL))
            deleteFront(*pL);

        free(*pL);
        *pL = NULL;
    }


}

// Access functions -----------------------------------------------------------
/* Returns number of elements in this list */
int length(List L)
{
    if (L == NULL)
    {
        printf("Empty List.");
        exit(1);
    }
    return L->length;
}

/* Returns index of the cursor element in this list. */
/* Returns -1 if cursor element is undefined */
int getIndex(List L)
{
    if (L == NULL)
    {
        printf("Empty List. Cursor is undefined.");
        exit(1);
    }
    return L->cursor;
}

/* Returns front element in this list. */
/* Pre: length() > 0 */
int front(List L)
{
    if (length(L) > 0 )
        return L->head->data;
    else
    {
        printf("Empty List.");
        exit(1);
    }
    return -1;
}

/* Returns bacl element in this list */
/* Pre: length() > 0 */
int back(List L)
{
    if (length(L) > 0)
        return L->tail->data;
    else
    {
        printf("Empty List -- back");
        exit(1);
    }
}

/* Returns cursor element in this list */
/* Pre: length() > 0, getIndex() >= 0 */
int getElement(List L)
{
    if (L == NULL)
    {
        printf("Empty List -- element");
        exit(1);
    }
    if (length(L) > 0 && getIndex(L) >= 0)
        return L->curr->data;
    return -1;
}
/* Returns 1 if list A and B are the same integer sequence. */
int equals(List A, List B)
{
    Node one = A->head;
    Node two = B->head;
    while (one != NULL && two != NULL)
    {
        if (one->data != two->data)
            return 0;
        one = one->next;
        two = two->next;
    }
    return 1;
}
/* Returns 1 for true if this list is empty.*/
int isEmpty(List L)
{
    int flag = 0;
    if (length(L) == 0)
        flag = 1;
    return flag;
}

// Manipulation procedures ----------------------------------------------------
/* Resets this list to the empty state */
void clear(List L)
{
    L->curr = NULL;
    L->head = NULL;
    L->tail = NULL;
    L->cursor = -1;
    L->length = 0;
}
/* if 0<=i<=length()-1, moves cursor to element at index i.*/
/* otherwise becomes undefined*/
void moveTo(List L, int i)
{
    if (0 <= i && i <= length(L) - 1)
    {
        L->curr = L->head;
        int j;
        for (j = 0; j < i; j++)
            L->curr = L->curr->next;
    }
    else
    {
        L->curr = NULL;
        L->cursor = -1;
    }
    L->cursor = i;
}

/* if 0<getIndex()<=length()-1, moves cursor a step toward the beginning of this list */
/* if getIndex()==-1, cursor is undefined */
/* if getIndex()==0, cursor is undefined */
void movePrev(List L)
{
    int i = getIndex(L);

    if (i > 0 && i <= length(L) - 1)
        moveTo(L, i - 1);
    else if (i <= 0)
    {
        L->curr = NULL;
        L->cursor = -1;
    }
}

/* if 0<=getIndex()<length()-1, moves cursor a step toward the end of this list */
/* if getIndex()==1, cursor is undefined. */
/* if geIndex()==length()-1, cursor is undefined */
void moveNext(List L)
{
    int i = getIndex(L);
    if (i >= 0 && i < length(L) - 1)
        moveTo(L, i + 1);
    else
    {
        L->curr = NULL;
        L->cursor = -1;
    }
}

/* Inserts a new element before the beginnning element */
void prepend(List L, int data)
{
    Node node = n(data);

    if (length(L) <= 0)
        L->tail = node;
    else
    {
        node->next = L->head;
        L->head->prev = node;
    }
    L->head = node;
    L->length++;
}

/* Inserts a new element after the last element */
void append(List L, int data)
{
    Node node = n(data);

    if(length(L) <= 0)
        L->head = node;
    else
    {
        L->tail->next = node;
        node->prev = L->tail;
    }

    L->tail = node;
    L->length++;
}

/* Inserts a new element before the cursor element */
/* Pre: length()>0, getIndex()>=0 */
void insertBefore(List L, int data)
{
    Node node = n(data);

    if (!(L->length > 0 && getIndex(L) >= 0))
        return;

    if (L->curr->prev != NULL)
    {
        L->curr->prev->next = node;
        node->prev = L->curr->prev;
    }
    else
        L->head = node;

    L->curr->prev = node;
    node->next = L->curr;

    L->length++;
}

/* Inserts a new element after the cursor element */
/* Pre: length()>0, getIndex()>=0*/
void insertAfter(List L, int data)
{
    Node node = n(data);
    if (!(L->length > 0 && getIndex(L) >= 0))
        return;

    if (L->curr->next != NULL)
    {
        L->curr->next->prev = node;
        node->next = L->curr->next;
    }
    else
        L->tail = node;

    L->curr->next = node;
    node->prev = L->curr;

    L->length++;
}

/* Deletes front element in this list */
void deleteFront(List L)
{
    Node N = NULL;
    if (length(L) <= 0)
    {
        printf("Empty List -- deletefront");
        exit(1);
    }

    //N = L->head;
    if(length(L) > 1)
    {
        L->head = L->head->next;
    }
    else
        L->head = L->tail = NULL;
    L->length--;
    free(&(L->head));
}

/* Deletes back element in this list */
void deleteBack(List L)
{
    if (length(L) <= 0)
        printf("Empty List");
    else
    {
        L->tail = L->tail->prev;
        L->tail->next = NULL;
        L->cursor = -1;
        L->length--;
    }
}

/* Deletes cursor element, cursor is then undefined */
/* Pre: length()>0, getIndex()>=0*/
void delete(List L)
{
    if (L->curr == L->head)
        deleteFront(L);
    else if (L->curr == L->tail)
        deleteBack(L);
    else if (length(L) <= 0)
        printf("Empty List");
    else
    {
        L->curr->next->prev = L->curr->prev;
        L->curr->prev->next = L->curr->next;
    }
    L->curr = NULL;
    L->cursor = -1;
}
// Other operations -----------------------------------------------------------
/* Prints this list to the file pointed by out */
void printList(FILE* out, List L)
{
    Node i;
    for (i = L->head; i != NULL; i = i->next)
        fprintf(out, "%d ", i->data);
}

/* Returns a new list with the same integer sequences as this list.*/
List copyList(List L)
{
    List nList = newList();
    Node i;
    for (i = L->head; i != NULL; i = i->next)
        append(nList, i->data);
    return nList;
}
