#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};
struct node * start=NULL;
struct node *temp=NULL;
struct node *temp2=NULL;
struct node *prev=NULL;

void basaEkle(int sayi)
{
    struct node *eleman=(struct node *)malloc(sizeof(struct node));
    eleman->data=sayi;
    if (start==NULL)
    {
        start=eleman;
        start->next=start;
        start->prev=start;
    }
    else
    {
        if(start->next==start)
        {
            start->next=eleman;
            start->prev=eleman;
            eleman->next=start;
            eleman->prev=start;
            start=eleman;
        }
        else
        {
            temp=start;
            while(temp->next!=start)
            {
                temp=temp->next;
            }
            temp->next=eleman;
            eleman->prev=temp;
            eleman->next=start;
            start->prev=eleman;
            start=eleman;
        }
    }

}
void sonaEkle(int sayi)
{
    struct node * eleman=(struct node *)malloc(sizeof(struct node));
    eleman->data=sayi;
    eleman->next=start;
    if (start==NULL)
    {
        start=eleman;
        eleman->next=start;
        eleman->prev=start;
    }
    else
    {
        if(start->next==start)
        {
            start->next=eleman;
            start->prev=eleman;
            eleman->next=start;
            eleman->prev=start;
        }
        else
        {
            temp=start;
            while(temp->next!=start)
            {
                temp=temp->next;
            }
            temp->next=eleman;
            eleman->prev=temp;
            eleman->next=start;
            start->prev=eleman;
        }
    }
}
void bastanSil()
{
    if(start==NULL)
    {
        printf("liste bos silinecek eleman yok \n ");
    }
    else
    {
        if(start->next==start)
        {
            free(start);
            start=NULL;
        }
        else
        {
            temp=start;
            while(temp->next!=start)
            {
                temp=temp->next;
            }
            temp2=start->next;
            free(start);
            temp->next=temp2;
            temp2->prev=temp;
            start=temp2;

        }
    }
}
void sondanSil()
{
    if(start==NULL)
    {
        printf("liste bos silinecek eleman yok \n");
    }
    else
    {
        if(start->next==start)
        {
            free(start);
            start=NULL;
        }
        else
        {
            temp=start;
            while(temp->next!=start)
            {
                temp=temp->next;
            }
            temp2=temp->prev;
            free(temp);
            temp2->next=start;
            start->prev=temp2;

        }

    }
}
int elemanSay()
{
    int adet=0;
    if(start==NULL)
        return 0;
    else
    {
        temp=start;
        while(temp->next!=start)
        {
            adet++;
            temp=temp->next;
        }
        adet++;
    }
    return adet;
}
int elemanToplam()
{
    int toplam=0;
    if(start==NULL)
        return 0;
    else
    {
        temp=start;
        while(temp->next!=start)
        {
            toplam+=temp->data;
            temp=temp->next;

        }
        toplam+=temp->data;
    }
    return toplam;
}
void listele()
{
    system("cls");
    if (start==NULL)
    {
        printf("liste bos \n");
    }
    else
    {
        temp=start;
        while(temp->next!=start)
        {
            printf("%d - >",temp->data);
            temp=temp->next;
        }
        printf("%d ",temp->data);

    }
}
int main()
{
    while (1)
    {
         int sayi,secim;
    printf("\n1-->basa ekle\n");
    printf("2-->sona ekle\n");
    printf("3-->bastan sil\n");
    printf("4-->sondan sil\n");
    printf("5-->eleman say\n");
    printf("6-->eleman topla\n");
    printf("7-->listele\n");
    printf("8-->cikis\n");
    printf("seciminizi yapiniz: \n");
    scanf("%d",&secim);
    switch(secim)
    {
    case 1:
        printf("basa eklemek istediginiz sayi:");
        scanf("%d",&sayi);
        basaEkle(sayi);
        break;
    case 2:
        printf("sona eklemek istediginiz sayi:");
        scanf("%d",&sayi);
        sonaEkle(sayi);
        break;
    case 3:
        bastanSil();
        break;
    case 4:
        sondanSil();
        break;
    case 5:
        printf("eleman adeti:%d ",elemanSay());
        break;
    case 6:
        printf("eleman toplami: %d",elemanToplam());
        break;
    case 7:
        listele();
        break;
    case 8:
        return;

    }
    }



    return 0;
}
