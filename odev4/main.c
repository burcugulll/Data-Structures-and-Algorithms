#include <stdio.h>
#include <stdlib.h>
//20010011066 BURCU GÜL

typedef struct node
{
    int no;
    char ad[50];
    struct node *sol;
    struct node *sag;
} node;

node *kokOlustur(int no,const char *ad)
{
    node *root=(node*)malloc(sizeof(node));
    if(root!=NULL)
    {
        root->no=no;
        strcpy(root->ad, ad);
        root->sol=NULL;
        root->sag=NULL;
    }
    return root;
}

node *ekle(node *root,int no,const char *ad)
{
    if(root==NULL)
    {
        root=kokOlustur(no,ad);
    }
    else
    {
        if(no<root->no)
            root->sol=ekle(root->sol,no,ad);
        else
            root->sag=ekle(root->sag,no,ad);
    }
    return root;
}


void sil(node **root, const char *targetAd)
{
    if (*root == NULL)
    {
        return;
    }

    sil(&((*root)->sol), targetAd);
    sil(&((*root)->sag), targetAd);

    if (strcmp((*root)->ad, targetAd) == 0)
    {
        if ((*root)->sol == NULL && (*root)->sag == NULL)
        {
            free(*root);
            *root = NULL;
        }
        else if ((*root)->sol == NULL)
        {
            node *temp = *root;
            *root = (*root)->sag;
            free(temp);
        }
        else if ((*root)->sag == NULL)
        {
            node *temp = *root;
            *root = (*root)->sol;
            free(temp);
        }
        else
        {
            node *temp = (*root)->sag;
            while (temp->sol != NULL)
            {
                temp = temp->sol;
            }
            strcpy((*root)->ad, temp->ad);
            (*root)->no = temp->no;

            sil(&((*root)->sag), temp->ad);
        }
    }
}


int yukseklik(node * root)
{
    int left,right;
    if(root==NULL)
        return 0;
    else
    {
        left=yukseklik(root->sol);
        right=yukseklik(root->sag);

        if(left>=right)
            return left + 1;
        else
            return right + 1;

    }
}

float nolarinOrtalamasi(node* root, int* sum, int* count)
{
    if (root != NULL)
    {
        nolarinOrtalamasi(root->sol, sum, count);
        *sum += root->no;
        (*count)++;
        nolarinOrtalamasi(root->sag, sum, count);
    }
    return *count > 0 ? (float)*sum / *count : 0;
}


void ayniAdiListele(node *root, const char *targetName)
{
    if (root != NULL)
    {
        ayniAdiListele(root->sol, targetName);

        if (strcmp(root->ad, targetName) == 0)
        {
            printf("%d\t%s\n", root->no, root->ad);
        }

        ayniAdiListele(root->sag, targetName);
    }
}


void inOrder(node *root)
{
    if(root!=NULL)
    {
        inOrder(root->sol);
        printf("%d\t%s\n", root->no,root->ad);
        inOrder(root->sag);
    }
}

int main()
{
    int secim,sayi,n,no,sum = 0, count = 0;
    float ort;
    char ad[50];
    node * root=NULL;
    FILE *file = fopen("veri.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(file, "%d%s", &no, ad) == 2)
    {
        root = ekle(root, no, ad);
    }

    fclose(file);

    while(1)
    {
        printf("\nBinary Search Tree\n");
        printf("1-No'ya gore ekleme\n");
        printf("2-Ada gore silme\n");
        printf("3-Agac yuksekligi bulma\n");
        printf("4-Nolarin ortalamasini bulma\n");
        printf("5-Birden fazla ayni adi listele\n");
        printf("6-Inorder listeleme\n");
        printf("0-Cikis\n");
        printf("seciminizi yapiniz: ");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            printf("Eklenecek sayiyi giriniz: ");
            scanf("%d",&no);
            printf("Ad girin: ");
            scanf("%s", ad);
            root=ekle(root,no,ad);
            break;

        case 2:
            inOrder(root);
            printf("Silinecek adi girin: ");
            scanf("%s", ad);
            sil(&root, ad);
            break;

        case 3:
            sayi=yukseklik(root);
            printf("Yukseklik: %d\n",sayi);
            break;

        case 4:
            ort = nolarinOrtalamasi(root, &sum, &count);
            printf("Nolarin Ortalamasi: %.2f\n", ort);
            break;

        case 5:
            printf("No\tAd\n");
            ayniAdiListele(root, ad);
            break;

        case 6:
            system("cls");
            printf("No\tAd\n");
            inOrder(root);
            break;

        case 0:
            printf("Cikis yaptiniz");
            return 0;
        default:
            printf("Hatali secim yaptiniz");
            break;
        }

    }
    return 0;
}
