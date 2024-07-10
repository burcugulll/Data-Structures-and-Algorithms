#include <stdio.h>
#include <stdlib.h>

#define BOY 10

struct yigin
{
    int dizi[BOY];
    int indis;    //top
};

struct yigin y1;

void elemanEkle(int sayi)  //push
{
    if(y1.indis== BOY -1)
    {
        printf("yigin doludur, eleman eklenemez \n");
    }
    else
    {
        y1.indis++;
        y1.dizi[y1.indis]=sayi;
    }
}

void elemanCikar()   //pop
{
    if(y1.indis==-1)
    {
        printf("yigin bostur,eleman cikarilamaz \n");
    }
    else
    {
        int cikanSayi=y1.dizi[y1.indis];
        y1.indis--;
        printf("%d sayisi yigindan cikarildi \n",cikanSayi);
    }
}

void yazdir()
{
    system("cls");
    if(y1.indis==-1)
    {
        printf("yigin bos \n");
    }
    else
    {
        int i;
        for(i=y1.indis; i>-1; i--)
        {
            printf(" %d \n",y1.dizi[i]);
        }
    }
}
int main()
{
    y1.indis=-1;
    int secim,sayi;
    while(1)
    {

        printf("\nYIGIN (STACK) \n");
        printf("1-->eleman ekle(push) \n");
        printf("2-->eleman cikar(pop) \n");
        printf("3-->yazdir(display) \n");
        printf("4-->CIKIS(exit) \n");
        printf("seciminizi yapiniz: \n");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            printf("eklenecek sayi: ");
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
            printf("cikis yaptiniz \n");
            return ;

        }

    }
    return 0;
}
