#include <stdio.h>
#include <stdlib.h>

struct node {
int data;
struct node * left;
struct node * right;
};
struct node *kokDugumOlustur(int veri)
{
    struct node * root=(struct node *)malloc(sizeof (struct node));
    root->data=veri;
    root->left=NULL;
    root->right=NULL;
    return root;
};

struct node *elemanEkle(struct node *root,int veri)
{
    if(root==NULL)
    {
        root=kokDugumOlustur(veri);

    }
    else
    {
       if(veri<root->data)
            root->left=elemanEkle(root->left,veri);
        else
            root->right=elemanEkle(root->right,veri);
    }
    return root;

};

void preorder(struct node * root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(struct node * root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void postorder(struct node * root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }


}
int main()
{
    struct node * eleman=NULL;
    int sayi,i=0;
    while(i<7)
    {
        printf("sayi girin: \n");
        scanf("%d",&sayi);
        eleman=elemanEkle(eleman,sayi);
        i++;
    }

    printf("\nPreOrder: ");
    preorder(eleman);
    printf("\nInOrder: ");
    inorder(eleman);
    printf("\nPostOrder: ");
    postorder(eleman);


}
