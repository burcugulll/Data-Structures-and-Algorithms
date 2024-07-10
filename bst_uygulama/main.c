#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node * left;
    struct node * right;
}node;

node *kokOlustur(int veri)
{
    node *root=(node*)malloc(sizeof(node));
    root->data=veri;
    root->left=NULL;
    root->right=NULL;
    return root;
}

node *ekle(node *root,int veri)
{
    if(root==NULL)
    {
        root=kokOlustur(veri);
    }
    else
    {
        if(veri<root->data)
            root->left=ekle(root->left,veri);
        else
            root->right=ekle(root->right,veri);
    }
    return root;
}

void inOrder(node *root)
{
    if(root!=NULL)
    {
        inOrder(root->left);
        printf("%d ",root->data);
        inOrder(root->right);
    }

}

int dugumSayisi(node *root)
{
    if(root==NULL)
        return 0;
    else
    {
        return dugumSayisi(root->left) +1 + dugumSayisi(root->right);
    }
}

int yukseklik(node * root)
{
    int sol,sag;
    if(root==NULL)
        return 0;
    else
    {
        sol=yukseklik(root->left);
        sag=yukseklik(root->right);
        if(sol>sag)
            return sol+1;
        else
            return sag+1;
    }
}

int enKucukData(node *root)
{
    node *temp=root;
    if(root==NULL)
        return 0;
    else
    {
        while(temp->left!=NULL)
            temp=temp->left;
            return temp->data;
    }
}

int enBuyukData(node * root)
{
    node * temp=root;
    if(root==NULL)
        return 0;
    else
    {
        while(temp->right!=NULL)
            temp=temp->right;
        return temp->data;
    }
}
int sayac=0;
int ara(node * root,int arananSayi)
{
    if(root==NULL)
        return 0;
    else
    {
        sayac++;
        if(root->data==arananSayi)
            return sayac;
        else if(arananSayi<root->data)
            ara(root->left,arananSayi);
        else
            ara(root->right,arananSayi);
    }
}

int main()
{
    int secim,sayi,n;
    node * root=NULL;
    while(1)
    {
        printf("\nBST UYGULAMASI\n");
        printf("1-ekle\n");
        printf("2-yazdir\n");
        printf("3-dugum sayisi\n");
        printf("4-yukseklik\n");
        printf("5-en kucuk veri\n");
        printf("6-en buyuk veri\n");
        printf("7-ara\n");
        printf("0-cikis\n");
        printf("seciminizi yapiniz: ");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            printf("sayi: ");
            scanf("%d",&sayi);
            root=ekle(root,sayi);
            break;
        case 2:
            system("cls");
            inOrder(root);
            break;
        case 3:
            system("cls");
            sayi=dugumSayisi(root);
            printf("Dugum sayisi: %d",sayi);
            break;
        case 4:
            system("cls");
            sayi=yukseklik(root);
            printf("Yukseklik: %d",sayi);
            break;
        case 5:
            system("cls");
            sayi=enKucukData(root);
            printf("en kucuk veri: %d",sayi);
            break;
        case 6:
            system("cls");
            sayi=enBuyukData(root);
            printf("en buyuk veri: %d",sayi);
            break;
        case 7:
            printf("aranan sayi: ");
            scanf("%d",&sayi);
            n=ara(root,sayi);
            if(n==0)
                printf("%d sayisi agac yapisinda yok\n",sayi);
            else
                printf("%d adimda bulundu ",n);
            sayac=0;
            break;

        case 0:
            printf("cikis yaptiniz");
            return 0;
        default:
            printf("hatali secim yaptiniz");
            break;
        }
    }
    return 0;
}
