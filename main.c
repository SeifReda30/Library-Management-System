#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int id;
    char bookname[100];
    int bookquantity;
}libsys;
int getdata(libsys data[])
{
    int i=0,count=0;
    FILE *fptr;
    fptr=fopen("libdata.txt","r");
    while (fscanf(fptr,"%d %d %[^\n]",&data[i].id,&data[i].bookquantity,data[i].bookname)!=EOF)
        {
                i++;
                count++;
        }
    fclose(fptr);
    return count;
}
void insertbook(FILE *fptr)
{
    libsys libinfo;
    fptr=fopen("libdata.txt","a");
    printf("\nEnter book ID : ");
    scanf("%d",&libinfo.id);
    printf("Enter book name : ");
    getchar();
    gets(libinfo.bookname);
    printf("Enter book quantity : ");
    scanf("%d",&libinfo.bookquantity);
    fprintf(fptr,"\n%d %d %s",libinfo.id,libinfo.bookquantity,libinfo.bookname);
    fclose(fptr);
}
void searchbyid(libsys data[],int key ,int n)
{
    int c=getdata(data);
    if (data[n].id==key && n<=c)
        printf("\nID found , book name : %s , book quantity : %d\n",data[n].bookname,data[n].bookquantity);
    else if (data[n].id!=key)
        searchbyid(data,key,n+1);
    else
        printf("\nNot Found\n");
}
void deletebook(libsys data[])
{
    FILE *fptr1,*fptr2;
    int key,c,i;
    fptr1=fopen("libdata.txt","a");
    fptr2=fopen("newlibdata.txt","w");
    printf("\nEnter the book id you want to delete\n");
    scanf("%d",&key);
    c=getdata(data);
       for(i=0;i<c;i++)
       {
        if(data[i].id==key)
          {
            continue;
          }
         else
          {
            fprintf(fptr2,"%d %d %s\n",data[i].id,data[i].bookquantity,data[i].bookname);
          }
       }
    fclose(fptr1);
    fclose(fptr2);
    remove("libdata.txt");
    rename("newlibdata.txt","libdata.txt");
}
int searchbyname(libsys data[])
{
   int pass,size,i,x,y,middle,low=0,high;
   size=getdata(data);
   high=size-1;
   char arr[30];
   char book_name[30];

   for (pass=1;pass<size;pass++)
   {
       for(i=0;i<size-pass;i++)
       {
           if(strcmp(data[i].bookname,data[i+1].bookname)>0)
           {
               x=data[i].id;
               data[i].id=data[i+1].id;
               data[i+1].id=x;
               y=data[i].bookquantity;
               data[i].bookquantity=data[i+1].bookquantity;
               data[i+1].bookquantity=y;
               strcpy(arr,data[i].bookname);
               strcpy(data[i].bookname,data[i+1].bookname);
               strcpy(data[i+1].bookname,arr);
           }
       }
   }
   printf("\nEnter book name : ");
   getchar();
   gets(book_name);
   while(low<=high)
   {
       middle=(low+high)/2;
       if(strcmp(book_name,data[middle].bookname)==0)
       {
           printf("\nName found , ID : %d , Quantity : %d\n",data[middle].id,data[middle].bookquantity);
           return 1;
       }
       else if (strcmp(book_name,data[middle].bookname)==-1)
       {
           high=middle-1;
       }
       else
       {
           low=middle+1;
       }
   }
   printf("\nNot found\n");
}
void displaybooks_sorted(libsys data[])
{
    int pass,size,i,x,y;
    size=getdata(data);
    getdata(data);
    char arr[30];
   for (pass=1;pass<size;pass++)
   {
       for(i=0;i<size-pass;i++)
       {
           if(strcmp(data[i].bookname,data[i+1].bookname)>0)
           {
               x=data[i].id;
               data[i].id=data[i+1].id;
               data[i+1].id=x;
               y=data[i].bookquantity;
               data[i].bookquantity=data[i+1].bookquantity;
               data[i+1].bookquantity=y;
               strcpy(arr,data[i].bookname);
               strcpy(data[i].bookname,data[i+1].bookname);
               strcpy(data[i+1].bookname,arr);
           }
       }
   }
   printf("\nID-Quantity-Book name\n");
   for (i=0;i<size;i++)
   {
       printf("\n%d %d %s\n",data[i].id,data[i].bookquantity,data[i].bookname);
   }
}
void displaybooks_unsorted(libsys data[])
{
    int i;
    int size=getdata(data);
    printf("\nID-Quantity-Book name\n");
    for (i=0;i<size;i++)
   {
       printf("\n%d %d %s\n",data[i].id,data[i].bookquantity,data[i].bookname);
   }

}
int main()
{
    int key;
    libsys data[10];
    int option;
    char choose;
    FILE *fptr;
    printf("Welcome to our library\n");
    do
    {
        printf("\n1-Insert a book\n");
        printf("2-Delete a book by id\n");
        printf("3-Search a book by id\n");
        printf("4-Search a book by name\n");
        printf("5-Display all books sorted\n");
        printf("6-Display all books unsorted\n");
        printf("\nChoose the number of operation : ");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                fptr=fopen("libdata.txt","r");
                insertbook(fptr);
                fclose(fptr);
                break;
            case 2:
                deletebook(data);
                break;
            case 3:
                getdata(data);
                printf("\nEnter the id of the book : ");
                scanf("%d",&key);
                searchbyid(data,key,0);
                break;
            case 4:
                getdata(data);
                searchbyname(data);
                break;
            case 5:
                displaybooks_sorted(data);
                break;
            case 6:
                displaybooks_unsorted(data);
                break;
            default:
                printf("Wrong option");
        }
        printf("\nAre you want to continue ? (y/n) : ");
        scanf(" %c",&choose);
    }while(choose=='y');
    printf("\nGood bye");
}
