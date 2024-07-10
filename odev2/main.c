#include <stdio.h>
#include <stdlib.h>

struct sunucu
{
    int id;
    int yuk;
    int max_kapasite;
    struct sunucu *next;
    struct sunucu *prev;
};

struct sunucu *bas=NULL;

struct sunucu *gecici=NULL;


void sirala()
{
    if (bas == NULL)
        return;

    gecici = bas;
    struct sunucu *geciciOnceki = NULL;
    int degisiklikYapildi = 1;

    while (degisiklikYapildi)
    {
        degisiklikYapildi = 0;
        gecici = bas;
        geciciOnceki = gecici->prev;

        while (gecici->next != bas)
        {
            struct sunucu *geciciSonraki = gecici->next;

            if (gecici->yuk > geciciSonraki->yuk)
            {
                struct sunucu *geciciSonrakiSonraki = geciciSonraki->next;

                if (geciciOnceki != geciciSonraki)
                {
                    geciciOnceki->next = geciciSonraki;
                    geciciSonraki->prev = geciciOnceki;
                }
                else
                {
                    geciciOnceki->next = geciciSonraki;
                }

                geciciSonraki->next = gecici;
                gecici->prev = geciciSonraki;
                gecici->next = geciciSonrakiSonraki;
                geciciSonrakiSonraki->prev = gecici;

                if (gecici == bas)
                {
                    bas = geciciSonraki;
                }

                degisiklikYapildi = 1;
            }

            geciciOnceki = gecici;
            gecici = geciciSonraki;
        }
    }
}


int uretici(int yuk)
{
    gecici = bas;
    while(yuk != 0)
    {
        if(bas->prev->max_kapasite == bas->prev->yuk)
        {

            sirala();
            return yuk;


        }

        if(yuk <= gecici->max_kapasite - gecici->yuk)
        {
            gecici->yuk+=yuk;
            break;
        }
        else
        {
            int sunucu_kapasitesi = gecici->max_kapasite - gecici->yuk;

            yuk-=sunucu_kapasitesi;
            gecici->yuk = gecici->max_kapasite;
        }
        gecici=gecici->next;
    }
    return 0;
    sirala();
}

void tuketici(int yuk)
{
    gecici = bas->prev;
    while(yuk !=0)
    {
        if(bas->yuk == 0)
        {
            break;
        }

        if(yuk <= gecici->yuk)
        {
            gecici->yuk-=yuk;
            break;
        }
        else
        {
            int sunucu_kapasitesi = gecici->yuk;

            yuk-=sunucu_kapasitesi;
            gecici->yuk = 0;
        }
        gecici=gecici->prev;
    }
}


void listele()
{
    gecici=bas;
    while(gecici->next!=bas)
    {
        printf("Id: %d , Yuk: %d , Max-Kapasite: %d\n",gecici->id,gecici->yuk,gecici->max_kapasite);
        gecici=gecici->next;
    }
    printf("Id: %d , Yuk: %d , Max-Kapasite: %d\n",gecici->id,gecici->yuk,gecici->max_kapasite);
}



void sunucuEkle(int id,
                int yuk,
                int max_kapasite)
{
    struct sunucu *yeniSunucu ;
    yeniSunucu=(struct sunucu*)malloc(sizeof(struct sunucu));

    yeniSunucu->id=id;
    yeniSunucu->max_kapasite=max_kapasite;
    yeniSunucu->yuk=yuk;
    yeniSunucu->next=NULL;
    yeniSunucu->prev=NULL;

    if(bas == NULL)
    {
        bas = yeniSunucu;
        bas->next=bas;
        bas->prev=bas;
    }
    else
    {
        gecici=bas;
        while(gecici->next!=bas)
        {
            gecici=gecici->next;
        }
        gecici->next=yeniSunucu;
        yeniSunucu->prev=gecici;
        yeniSunucu->next=bas;
        bas->prev=yeniSunucu;
    }

}


int main()
{
    sunucuEkle(101,50,400);
    sunucuEkle(102,0,200);
    sunucuEkle(103,350,500);
    sunucuEkle(104,100,200);
    sunucuEkle(105,20,120);
    sunucuEkle(106,15,50);
    sirala();
    printf("Ilk Liste\n\n");
    listele();
    int kalan_yuk = uretici(2500);
    printf("\n\nYuk Uretildikten Sonraki Liste\n\n");
    listele();
    if(kalan_yuk > 0){
        printf("\nTum sunucular dolu, daha fazla yuk alamaz. Kalan Yuk Miktari: %d\n",kalan_yuk);
    }

    tuketici(505);
    printf("\n\nYuk Tuketildikten Sonraki Liste\n\n");
    listele();


    return 0;
}
