#include<stdio.h>
#include<string.h>

typedef struct{
char name[15],code[6];
float price;
int qty;
}rec;
rec item;

void dbill();
int check(char []);
void Add();
void dlt();
void Display();
void display2(rec *,int);
void calc();
void edit();
void alert();

int main(){
int z;
alert();
printf("              Main Menu  \n\n");
printf("\n1:-Add Items");
printf("\n2:-Edit Items");
printf("\n3:-Calculate Bills");
printf("\n4:-Display All Items");
printf("\n5:-Delete Items\n");
printf("=========>      ");
scanf("%d",&z);	
switch(z){
	case 1:Add();break;
	case 2:edit();break;
	case 3:calc();break;
	case 4:Display();break;
	case 5:dlt();break;
	default: printf("Enter Valid Option");	break;
}
}
void Add(){
        
	int flag=1;//,code,price,qty;
	char code[20],ch;
	FILE *file;
        fflush(stdin);
	file=fopen("record1.txt","a+");
        printf("\nEnter the item code no. : ");
	scanf("%s",code);
        flag=check(code);
        if(flag==1){
         strcpy(item.code,code);
        printf("\nEnter the item Name : ");
	scanf("%s",item.name);
	printf("\nEnter the price : ");
	scanf("%f",&item.price);
	printf("\nEnter the quantity : ");
	scanf("%d",&item.qty);
	fseek(file,0,SEEK_END);fwrite(&item,sizeof(item),1,file);
	fclose(file);}
        else if(flag == 0){
      printf("----------------------------Code already used-----------------------\n\n\n");  
     }
main();
}

void Display(){
printf("S.No.        ITEM NAME	   ITEM CODE	  PRICE	    QUANTITY");
int i,j=1;
 FILE *file;
 file=fopen("record1.txt","rb");
 rewind(file);
 fflush(file);
 while(fread(&item,sizeof(item),1,file)){
  display2(&item,j);
  j++;
 }
printf("\n");
}

void display2(rec *item,int j)
{
 printf("\n");
 printf("%2d",j);
 printf("%20s",item->name);
 printf("%13s",item->code);
 printf("%13.2f",item->price);
 printf("%9d",item->qty);
}

void edit(){
 int flag=0,choice;
 char x[15],y[15],ch;
 FILE *file;
 int size;
 printf("EDIT RECORDS\n");
 printf("enter item code: ");
 scanf("%s",x);
 flag=check(x);
 if(flag==0){
  file=fopen("record1.txt","r+b");
  rewind(file);
  while (fread(&item,sizeof (item),1,file)){
   if(strcmp(item.code,x)==0){
    printf("name       = %s\n",item.name);
    printf("code       = %s\n",item.code);
    printf("rate       = %g\n",item.price);
    printf("quantity   = %d\n\n\n\n",item.qty);

    printf("1- edit name \n");
    printf("2- edit code \n");
    printf("3- edit rate \n");
    printf("4- edit quantity \n");
    printf(" enter your choice(1, 2, 3, 4) : ");
    scanf("%d",&choice);
     switch(choice){
      case 1:
    printf("EDIT RECORDS\n");
    printf(" enter new name :  ");
       scanf("%s",item.name);
       size=sizeof(item);
       fseek(file,-size,SEEK_CUR);fwrite(&item,sizeof(item),1,file);
       break;
      case 2:
    printf("EDIT RECORDS\n");
       printf("enter new code :  ");
       scanf("%s",item.code);
       size=sizeof(item);
       fseek(file,-size,SEEK_CUR);fwrite(&item,sizeof(item),1,file);
       break;
      case 3:
    printf("EDIT RECORDS\n");
      printf(" enter new price :  ");
       scanf("%f",&item.price);
       size=sizeof(item);
       fseek(file,-size,SEEK_CUR);fwrite(&item,sizeof(item),1,file);
       break;
      case 4:
       printf("EDIT RECORDS\n");
       printf(" enter new quantity :  ");
       scanf("%d",&item.qty);
       size=sizeof(item);
       fseek(file,-size,1);fwrite(&item,sizeof(item),1,file);
       break;
     }
     printf("--- item edited---");
     break;
    }
   
  }
 }
 if (flag==1){
  printf("item does not exist		");
  printf("TRY ABGAIN\n");
 }
 fclose(file);
}
int check(char x[15])
{
 FILE *file;
 int flag=1;
 char w[15];
 strcpy(w,x);
 file=fopen("record1.txt","rb");
 rewind(file);
 while (fread(&item,sizeof (item),1,file)){
  if(strcmp(item.code,w)==0){
   flag=0;
   break;
  }
 }
 fclose(file);
 return flag;
 }

void calc(){

 char x[50][6]={0};
 int j=29,q[50],size=0,i=1,a=0,n;
 float total=0,gtotal=0;
 FILE *file;
 file=fopen("record1.txt","r+b");
 rewind(file);
 printf("enter  \"end\" to finish input");
 while(1){
  printf("                    ");
  printf("                    ");
  printf("\nenter item code:");
  scanf("%s",x[a]);
  if(strcmp(x[a],"end")==0)
   break;
printf("\nenter quantity:");
  scanf("%d",&q[a]);
a++;
}
  dbill();
for(n=0;n<a;n++){
rewind(file);  
while(fread(&item,sizeof(item),1,file)){
   if((strcmp(item.code,x[n])==0)){
    total=item.price*q[n];
    printf("%4d",i);
    printf("%9s",item.name);
    printf("%13d",q[n]);
    printf("%15.2f",item.price);
    printf("%13.2f\n",total);
    gtotal=gtotal+total;
    size=sizeof(item);
    item.qty=item.qty-q[n];
    j+=2; i++;
    fseek(file,-size,SEEK_CUR);fwrite(&item,sizeof(item),1,file);
    break;
   }
   }
 }

 if(gtotal!=0){
  printf("TOTAL AMOUNT = NRs. %6.2f\n",gtotal);
 }
 fclose(file);
}
 /*function to display bill window*/
void dbill()
{
 int i;
 for (i=1;i<=10;i++)
  printf("*");
printf("Departmental Store");
 for (i=1;i<=10;i++)
       printf("*");
 printf("\n\n");

 printf("--------------------CUSTOMER'S BILL--------------------\n");
 printf("  SNo.   Item Name     Quantity     Rate          Total\n");

}
void dlt(){

 int flag;
 char x[15];
 FILE *file,*file1;
 printf("enter item code: ");
 scanf("%s",x);
 flag=check(x);
 if(flag==0){
  file1=fopen("record.txt","ab");
  file=fopen("record1.txt","rb");
  rewind(file);
  while (fread(&item,sizeof (item),1,file)){
   if(strcmp(item.code,x)!=0)
    fwrite(&item,sizeof(item),1,file1);
  }
  printf("---item deleted---\n");
  remove("record1.txt");
  rename("record.txt","record1.txt");
 }
 if (flag==1){
  printf("---item does not exist---\n");
  printf("TRY AGAIN\n");
 }
 fclose(file1);
 fclose(file);
}
void alert(){
FILE *file;
file=fopen("record1.txt","a+");
rewind(file);
while (fread(&item,sizeof (item),1,file)){
   if(item.qty<10){
printf("Only %d %s available.\n",item.qty,item.name);
} 
}
printf("\n\n\n");
}
