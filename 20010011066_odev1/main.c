#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//20010011066 BURCU GÜL
struct Dersler
{
    char dersAdi[50];
    char dersKodu[20];
    int dersNotu;
    struct Dersler *next;
};

struct Ogrenci
{
    int ogrNo;
    char ogrAd[50];
    char ogrSoyad[50];
    struct Dersler *aldigidersler;
    struct Ogrenci *next;
};

struct Ogrenci *ogr_kok=NULL;


void ogrenciEkle(int ogr_no, const char *ogr_ad, const char *ogr_soyad)
{
    struct Ogrenci *gecici = ogr_kok;

    struct Ogrenci *yeniOgrenci = (struct Ogrenci *)malloc(sizeof(struct Ogrenci));
    strcpy(yeniOgrenci->ogrAd, ogr_ad);
    strcpy(yeniOgrenci->ogrSoyad, ogr_soyad);
    yeniOgrenci->ogrNo = ogr_no;
    yeniOgrenci->aldigidersler = NULL;
    yeniOgrenci->next = NULL;

    if (ogr_kok == NULL)
    {
        ogr_kok = yeniOgrenci;

    }
    else
    {
        while (gecici->next != NULL)
        {
            gecici = gecici->next;
        }
        gecici->next = yeniOgrenci;

    }
}


void dersEkle(struct Ogrenci *ogrenci, const char *dersAdi, const char *dersKodu, int dersNotu)
{
    struct Dersler *yeniDers = (struct Dersler *)malloc(sizeof(struct Dersler));
    strcpy(yeniDers->dersAdi, dersAdi);
    strcpy(yeniDers->dersKodu, dersKodu);
    yeniDers->dersNotu = dersNotu;
    yeniDers->next = NULL;

    if (ogrenci->aldigidersler == NULL)
    {
        ogrenci->aldigidersler = yeniDers;
    }
    else
    {
        struct Dersler *gecici = ogrenci->aldigidersler;
        while (gecici->next != NULL)
        {
            gecici = gecici->next;
        }
        gecici->next = yeniDers;
    }
}


void dosyadanVeriOku()
{
    FILE *dosya = fopen("veriler.txt", "r");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi!!!");
        return 1;
    }


    char satir[200];

    while (fgets(satir, sizeof(satir), dosya))
    {
        satir[strcspn(satir, "\n")] = '\0';

        if (satir[0] == '\0')
        {
            //okunan satır boşsa hiç işlem yapmadan diğer adıma geçildi
            continue;
        }



        if (isdigit(satir[0]))
        {
            int ogr_no=0;
            char ogr_ad[20];
            char ogr_soyad[20];


            sscanf(satir, "%d %s %s", &ogr_no, ogr_ad, ogr_soyad);
            // bu satırda ogrenci bilgileri txtden okundu

            //okunan bilgilere gore yeni ogrenci eklendi
            ogrenciEkle(ogr_no,ogr_ad,ogr_soyad);

        }
        else
        {

            if (ogr_kok != NULL)
            {
                char ders_ad[20];
                char ders_kod[20];
                int ders_not =0;

                sscanf(satir, "%s %s %d", ders_ad, ders_kod, &ders_not);
                // Bu satirda ders bilgileri txtden okundu

                struct Ogrenci *gecici = ogr_kok;

                while (gecici->next != NULL)
                {
                    gecici = gecici->next;
                }

                dersEkle(gecici, ders_ad, ders_kod, ders_not);
            }
        }
    }

    fclose(dosya);
}

void listele()
{
    struct Ogrenci *gecici = ogr_kok;

    while(gecici != NULL)
    {

        printf("%d : %s : %s\n",gecici->ogrNo,gecici->ogrAd,gecici->ogrSoyad);

        struct Dersler *ders_gecici = gecici->aldigidersler;

        while(ders_gecici != NULL)
        {
            printf("%s : %s : %d\n",ders_gecici->dersAdi,ders_gecici->dersKodu,ders_gecici->dersNotu);
            ders_gecici = ders_gecici->next;
        }
        printf("\n\n");
        gecici = gecici->next;
    }

}


int soyadaGoreSilme (char *soyad)
{
    struct Ogrenci *gecici = ogr_kok;
    struct Ogrenci *gecici_onceki = NULL;
    int silindi = 0;
    while(gecici != NULL)
    {


        if(!strcmp(gecici->ogrSoyad,soyad))
        {

            if(gecici == ogr_kok)
            {
                ogr_kok = ogr_kok->next;
                free(gecici);
                silindi++;
            }
            else if(gecici->next != NULL)
            {
                gecici_onceki->next = gecici->next;
                free(gecici);
                silindi++;
            }
            else
            {
                gecici_onceki->next = NULL;
                free(gecici);
                silindi++;
            }
        }

        gecici_onceki = gecici;
        gecici = gecici->next;
    }

    return silindi;

}

struct Ogrenci *sorted_ogr_kok = NULL;


float ortalamaPuanHesapla(struct Ogrenci *ogrenci)
{
    int toplamPuan = 0;
    int dersSayisi = 0;

    struct Dersler *ders_gecici = ogrenci->aldigidersler;
    while (ders_gecici != NULL)
    {
        toplamPuan += ders_gecici->dersNotu;
        dersSayisi++;
        ders_gecici = ders_gecici->next;
    }

    if (dersSayisi > 0)
    {
        return (float)toplamPuan / dersSayisi;
    }
    else
    {
        return 0.0;
    }
}


void ogrencileriOrtalamaPuanaGoreSiralama()
{
    struct Ogrenci *gecici = ogr_kok;

    while (gecici != NULL)
    {
        struct Ogrenci *yeniOgrenci = (struct Ogrenci *)malloc(sizeof(struct Ogrenci));
        memcpy(yeniOgrenci, gecici, sizeof(struct Ogrenci));
        yeniOgrenci->next = NULL;


        float ortalamaPuan = ortalamaPuanHesapla(gecici);
        if (sorted_ogr_kok == NULL || ortalamaPuan < ortalamaPuanHesapla(sorted_ogr_kok))
        {
            yeniOgrenci->next = sorted_ogr_kok;
            sorted_ogr_kok = yeniOgrenci;
        }
        else
        {
            struct Ogrenci *gecici_sorted = sorted_ogr_kok;
            while (gecici_sorted->next != NULL && ortalamaPuan >= ortalamaPuanHesapla(gecici_sorted->next))
            {
                gecici_sorted = gecici_sorted->next;
            }
            yeniOgrenci->next = gecici_sorted->next;
            gecici_sorted->next = yeniOgrenci;
        }

        gecici = gecici->next;
    }
}


void siraliOgrenciListesi()
{
    struct Ogrenci *gecici = sorted_ogr_kok;

    while (gecici != NULL)
    {
        printf("%d : %s : %s (Ortalama Puan: %.2f)\n", gecici->ogrNo, gecici->ogrAd, gecici->ogrSoyad, ortalamaPuanHesapla(gecici));
        gecici = gecici->next;
    }
}

int dersKodunaGoreArama(char *ders_kodu)
{
    struct Ogrenci *gecici = ogr_kok;
    int bulundumu = 0;
    while(gecici != NULL)
    {



        struct Dersler *ders_gecici = gecici->aldigidersler;

        while(ders_gecici != NULL)
        {
            if(!strcmp(ders_gecici->dersKodu,ders_kodu))
            {
                printf("%d : %s : %s Ogrencisi %s kodlu dersi almakta.Ders Notu:%d\n",gecici->ogrNo,gecici->ogrAd,gecici->ogrSoyad,ders_kodu,ders_gecici->dersNotu);
                bulundumu++;
            }

            ders_gecici = ders_gecici->next;
        }

        gecici = gecici->next;
    }

    return bulundumu;
}


int main()
{
    dosyadanVeriOku();
    printf("-------------Ilk Liste-------------\n");
    listele();

    ogrencileriOrtalamaPuanaGoreSiralama();
    printf("-----------Ortalama Puana Gore Kucukten Buyuge Sirali Liste-----------\n");
    siraliOgrenciListesi();

    int silindiMi = soyadaGoreSilme("Yilmaz");

    if(silindiMi)
    {
        printf("\nOgrenci basariyla silindi.");
    }
    else
    {
        printf("\nOgrenci bulunamadi.");
    }
    printf("\n-----------Silindikten sonraki liste-----------\n");
    listele();


    printf("-----------Koda gore arama sonrasi liste-----------\n");
    int bulunanlar = dersKodunaGoreArama("FZK102");

    if(bulunanlar == 0)
    {
        printf("Bu ders koduna ait hic ogrenci bulunamadi.");
    }
    else
    {
        printf("Bu ders koduna ait %d ogrenci bulundu.",bulunanlar);
    }
    return 0;
}

