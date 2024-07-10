#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
struct node *temp=NULL;
struct node *top=NULL;//en ustteki eleman

void push(int veri)   //eleman ekleme islemi
{
    struct node * eleman=(struct node *)malloc(sizeof(struct node));
    eleman->data=veri;
    if(top==NULL)
    {
        top=eleman;
        eleman->next=NULL;
    }
    else
    {
        eleman->next=top;
        top=eleman;
    }
}

void pop()   //eleman cikartiliyor
{
    if(top==NULL)
    {
        printf("stack bos cikarilacak eleman yok \n");
    }
    else
    {
        printf("%d elemani stackten cikarildi \n",top->data);
        temp=top->next;
        free(top);
        top=temp;
    }
}

void yazdir()   //eleman yazdiriliyor
{
    if(top==NULL)
        printf("stack bos \n");
    else
    {
        temp=top;
        while(temp->next!=NULL)
        {
            printf(" %d \n",temp->data);
            temp=temp->next;
        }
        printf(" %d \n",temp->data);

    }
}

void peek()
{
    if(top==NULL)
    {
        printf("stack bos \n");
    }
    else
    {
        printf("yigindaki en son eleman :%d \n",top->data);
    }
}
int main()
{
    int secim,sayi;
    while(1)
    {
        printf("STACK(YIGIN) \n");
        printf("1-->push islemi \n");
        printf("2-->pop islemi \n");
        printf("3-->print islemi \n");
        printf("4-->peek(en ust deger) islemi \n");
        printf("5-->cikis \n");
       // printf("seciminizi yapiniz: \n");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            printf("stack e eklenecek sayi: ");
            scanf("%d",&sayi);
            push(sayi);
            break;
        case 2:
            pop();
            break;
        case 3:
            yazdir();
            break;
        case 4:
            peek();
            break;
        case 5:
            printf("cikis yapildi");
            return 0;

        }

    }
    return 0;
}
