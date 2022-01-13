#include<stdio.h>
#include<stdlib.h>

struct node
{
    char vr ;
    int freq ;
    struct node *next ;
};

void add(char x, int y, struct node **temp)
{
    struct node *r, *z;
    z = *temp ;
    if(z == NULL)
    {
        r = (struct node*)malloc(sizeof(struct node));
        r->vr = x;
        r->freq = y;
        *temp = r;
        r->next = (struct node*)malloc(sizeof(struct node));
        r = r->next;
        r->next = NULL;
    }
    else
    {
        if(z->vr == x)
        z->freq = z->freq + y ;

    else
        {
        r->vr = x;
        r->freq = y;
        r->next = (struct node*)malloc(sizeof(struct node));
        r = r->next;
        r->next = NULL;
    }
    }
}

void Display(struct node *node)
{
    while(node->next != NULL)
    {
    printf(" %c->%d ", node->vr,node->freq);
    node = node->next;
    }
    printf("\n");
}

void remove_func(char x, int y, struct node *temp)
{
    if(temp == NULL)
        printf(" Bag is empty.\n");
    else
    {
        while(temp != NULL)
    {
        if(temp->vr != x)
            temp = temp->next ;
        else
        {
            if(y > temp->freq || y == temp->freq)
            {
                printf("\nChoose number lesser than copies of variable in bag.\n");
                return temp ;
            }
            else
            {
            temp->freq = temp->freq - y ;
            return temp ;
            }
        }
    }
    }
}

void main()
{
    struct node *bag1 = NULL,*bag2 = NULL,*bag3 = NULL ;

    printf("Driver Script for functions of the program.\n");
    add('a',3,&bag1);
    printf("\n1st Bag (After entering 'a' 3 times into bag1) :");
    Display(bag1);

    add('b',6,&bag1);
    printf("\n1st Bag (After entering 'b' 6 times into bag1) :");
    Display(bag1);

    add('c',4,&bag1);
    printf("\n1st Bag (After entering 'c' 4 times into bag1) :");
    Display(bag1);

    add('a',6,&bag1);
    printf("\n1st Bag (After entering 'a' 6 times into bag1) :");
    Display(bag1);

    remove_func('a',7,bag1);
    printf("\n1st Bag (After removing 'a' 7 times from bag1) :");
    Display(bag1);

    remove_func('b',5,bag1);
    printf("\n1st Bag (After removing 'b' 5 times from bag1) :");
    Display(bag1);

    printf("\n2nd Bag (Trying to remove 'a' 2 times from bag2) :");
    remove_func('a',2,bag2);

    return 0;
}
