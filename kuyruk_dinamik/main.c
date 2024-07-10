#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
struct node *temp=NULL;
struct node *front=NULL;    //bastaki dugumu tutar
struct node *rear=NULL;    //kuyruktaki son dugumu tutar

void elemanEkle(int veri)
{
    struct node *eleman=(struct node *)malloc(sizeof(struct node));
    eleman->data=veri;
    if(front==NULL)
    {
        front=eleman;
        front->next=front;
        rear=eleman;
        rear->next=NULL;
    }
    else if(front->next==front)
    {
        rear->next=eleman;
        rear=eleman;
        rear->next=NULL;
        front->next=rear;
    }
    else
    {
        rear->next=eleman;
        rear=eleman;
        rear->next=NULL;
    }
}
void elemanCikar()
{
    if(front==NULL)
    {
        printf("kuyruk bostur\n");
    }
    else
    {
        printf("%d elemani kuyruktan cikarildi \n",front->data);
        temp=front->next;
        free(front);
        front=temp;
    }
}
void yazdir()
{
    system("cls");
    if (front==NULL)
    {
        printf("kuyruk bostur\n");
    }
    else
    {
        temp=front;
        while(temp->next!=NULL)
        {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("%d ",temp->data);
    }
}
int main()
{
    int secim,sayi;
    while(1)
    {
        printf("\nKUYRUK (QUEUE) \n");
        printf("\n1-->eleman ekle\n");
        printf("2-->eleman cikar\n");
        printf("3-->yazdir\n");
        printf("4-->cikis\n");
        printf("seciminizi yapin: \n");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            printf("sayi girin: \n");
            scanf("%d",&sayi);
            elemanEkle(sayi);
            break;
        case 2:
            elemanCikar();
            break;
        case 3:
            yazdir();
            break;
        case 4:
            return 0;

        }

    }
    return 0;
}
