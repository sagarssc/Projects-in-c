#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int ch(int *,int *,int *,int);
int not(int);

int xor(int ,int );
int h2b(char **,int ,int,int );

char* b2h(int *);
int maj(int *,int *,int *,int);

int suma(int *,int);
int sume(int *,int);

int sha512(int *ar,int alen);
int comparehash(int *,int );

int public_key_e(int ,int ,int);
int private_key_d(int ,int);
int cipher_text(int e,int n,char* msg); //Encryption
int plain_text(int *ct,int n,int d,int r); //Decryption

int main(){
 int cmh,pl,n,p,q,z,r,phi,e,d,i=0,tru;
 int ct[20],ctt[20];
 char msg[100],ch,s[128];
 FILE *f2;
printf("\n\n\n--------------------------Encryption/Decryption----------------------------\n\n\n\n");
printf("            Enter Your Choice \n");
printf("        1=> For Private and Public key generation:\n");
printf("        2=> For Message Encryption:\n");
printf("        3=> For Message Decryption:\n	   ==>");
scanf("%d",&z);
switch(z){
case 1: printf("	Enter Two prime No.\n	   ==>");
        scanf("%d %d",&p,&q);
        n=p*q;                 /*  Public key n */
        phi=(p-1)*(q-1);
        e=public_key_e(phi,p,q);
        d=private_key_d(phi,e);
        printf("	Public Key n = %d  and  e = %d\n",n,e);
        printf("	Private Key d = %d\n",d);
        main();
        break;
case 2: printf("	Please Enter the Message:\n	    ==>");
        scanf("%s",msg);
        printf("	Enter the value of public key e:\n	 ==>");
        scanf("%d",&e);
        printf("	Enter the value of public key n:\n	==>");
        scanf("%d",&n);
        cipher_text(e,n,msg);
        main();
        break;
case 3: printf("	Please Enter the no. of cipher text blocks:\n	  ==>");
        scanf("%d",&r);
        for(i=0;i<r;i++){
        printf("Cipher Text %d:",i+1);
        scanf("%d",&ct[i]);
        ctt[i]=ct[i];
          }
        printf("	Please Enter the Hash Code:\n	  ==>");
        scanf("%s",s);
        f2=fopen("hash2.txt","a+");
        fseek(f2,0,SEEK_END);fwrite(&s,sizeof(s),1,f2);
	fclose(f2);
        
        cmh=comparehash(ctt,r);
       if(cmh==1){
        printf("	Enter the of public key n:\n	==>");
        scanf("%d",&n);
        printf("	Enter the value of private key d:\n	==>");
        scanf("%d",&d);
       // for(i=0;i<r;i++){
        //printf("Cipher Text %d : %d\n",i+1,ct[i]);
        //}
        plain_text(ct,n,d,r);}
        else if(cmh==0){
        printf("-------------DATA HAS BEEN ALTERED-------------\n\n\n");
        printf("Want to decrypt:\n 1: Yes\n 2: No\n");
        scanf("%d",&tru);
        if(tru==1){
         
        printf("\n\n\n	Enter the of public key n:\n	==>");
        scanf("%d",&n);
        printf("	Enter the value of private key d:\n	==>");
        scanf("%d",&d);
       // for(i=0;i<r;i++){
        //printf("Cipher Text %d : %d\n",i+1,ct[i]);
        //}
        plain_text(ct,n,d,r);
        }
        else {break;} 
        }
        break;
default: printf("	Please Enter the valid No.\n");        
}


/*
printf("p    q   n     phi    r     e       d\n");
printf("%d  %d   %d    %d    %d     %d      %d\n",p,q,n,phi,r,e,d);

printf("enter the cipher Text\n");
scanf("%ld",&ct);*/
return 0;
}


/* Public Key e Generation*/
int public_key_e(int r,int p,int q){ //r=phi
int s=2,t=0,z,a,i;
while(r!=1){
  if(r%s==0){
    r=r/s; 
     a=s;
        }
  else{
    s++;
      }
}
while(t!=1){
   a++;z=0;
 for(i=1;i<=a;i++){  
  if(a%i==0){z++;}
   }
if(a!=p && a!=q && z==2){
   t=1;
   return a;
   }
  
  }
/*end of function*/
}

/* Private Key Generation*/
int private_key_d(int phi,int e){
int a,b,c=e,d,j,k,l,m,temp1,temp2,temp3,i=0;

while(c!=1){
  if(i==0){
    j=1;k=0;
    l=phi;
     d=0;
    }
  else if(i==1){
    a=0;b=1;
    c=e;
    d=l/c;
    }
  else if(i>1){
   temp1=a;  /*Storing in a temp variable*/
   temp2=b;
   temp3=c;

   a=j-a*d;  /*an=a(n-2)-d*a(n-1);*/
   b=k-b*d;  /*bn=a(n-2)-d*c(n-1);*/
   c=l-c*d;  /*cn=a(n-2)-d*c(n-1);*/

   j=temp1;
   k=temp2;
   l=temp3;
   d=l/c;
   }
i++;
}
if(b<0){
return (b+phi);
}
else if(b>phi){
return (b%phi);
}
else{
return b;
}
/*end of function*/
}


int cipher_text(int e,int n,char* b){
int cr,m,i,k,l,c,q,p=0,*ar=NULL,pt,w,alen,index;
char hs,ch[20],s[20],str[200],str1[4];
l=strlen(b);
int j[l];
printf("--------Cipher Text-------\n");
for(i=0;i<l;i++){
c=1;*s=NULL;*ch=NULL;
                                /*generating numeric value of text*/
j[i]=b[i];
if(j[i]>=65 && j[i]<=90){
j[i]=j[i]-64;
}
if(j[i]==32){
j[i]=53;
}
if(j[i]>=97 && j[i]<=123){
j[i]=j[i]-70;
} 
                                  /*Encryption*/
for(k=0;k<e;k++){
c=(c*j[i])%n;
}
                           /*conversion int to string and adding 0 before the no. if <10 */
sprintf(ch,"%d",c);
sprintf(s,"%d",p);
if(c<10){
strcat(s,ch);
strcat(str,s);
}
else{
strcat(str,ch);
}}
                       /*Deviding  String into small blocks of size 4*/
k=strlen(str);
m=k;
if(k%4!=0){
k=k/4+1;
}
else{
k=k/4;
}
for(i=0;i<k;i++){
for(q=0;q<4;q++){
str1[q]=str[q+(4*i)];
}        
                   /*conversion string to int and storing in array*/
if( ar == NULL )
     {
       ar = malloc(sizeof(atoi(str1)));
       *ar =atoi(str1);
     }
    else
    { 
       ar = realloc(ar,sizeof(ar)*i);  
        index = i;
       *(ar+index)=atoi(str1);
   }
printf("Cipher Text %d = %d\n",i+1,ar[i]);    
alen=i+1;
}
//printf("alen = %d",alen);
sha512(ar,alen);
FILE *f1;
f1=fopen("hash.txt","r");
printf("--------------Hash Code--------------\n");
rewind(f1);
while((hs=fgetc(f1))!=EOF){
printf("%c",hs);
}
fclose(f1);
f1=fopen("hash.txt","w+");
fclose(f1);
printf("\n");
           /*end of function*/
}

                             int plain_text(int *c,int n,int d,int r){
int k,m,i,a,pl,j=0,cmh;
char ch,temp[100],s1[128],s2[128];

for(k=r-1;k>=0;k--){
while(c[k]>0){
a=c[k]%100; //temp variable block
pl=1;
for(i=0;i<d;i++){
pl=(a*pl)%n;    //formula
}
if(pl>=1 && pl<=26){
pl=pl+64;
}
if(pl==53){
pl=32;
}
if(pl>=27 && pl<=52){
pl=pl+70;
}
temp[j]=pl;
//printf("temp =  %c\n",temp[j]);
j++;
c[k]=c[k]/100;
}}
printf("\nTest Message:\n==> ");
for(m=j;m>0;m--){
printf("%c",temp[m-1]);
}
FILE *f1,*f2;
 f1=fopen("hash.txt","w+");     
 f2=fopen("hash2.txt","w+");
        fclose(f1);
        fclose(f2);
printf("\n");
/*end of function*/
}


int comparehash(int *c,int r){
int cq=0,i=1;
char s1[128],s2[128];
FILE *f1,*f2;
*s1=NULL;*s2=NULL;
//printf("s1 = %s \n s2 = %s\n",s1,s2);
sha512(c,r);
f1=fopen("hash.txt","r");
f2=fopen("hash2.txt","r");
while(cq<128){
fseek(f1,cq,SEEK_SET);
fseek(f2,cq,SEEK_SET);
s1[cq]=fgetc(f1);
s2[cq]=fgetc(f2);
if(s1[cq]!=s2[cq]){
i=0;
break;
}
cq++;
}
//printf("s1 = %s \n s2 = %s\n",s1,s2);
return i;
/*end of Function*/
}
                               int sha512(int *ar,int alen){
int x[8][64],a[8][64],y[16][64],j,temp[65],temp11[65],cha[64],maja[64],sumx[64],sumy[64],p,k,l,kt[4][64],c,av;
char *arrr[16],ar1[16][16],*constt[4];
int count,w,pt,byt,q,i,tem,len,arr[100][16];
char *cv[8],s[20],op[8][16];


                 /* length calculation */
count=alen*4; //alen=cipher text block
//printf("count = %d\n",count);
w=alen*4*4;  //hexa to binary bit required
//printf("w = %d\n",w);
pt=1024-((w+128)%1024);//no of zeros of padding length including 1
//printf("pt = %d\n",pt);
byt=(w+128+pt)/4;
//printf("byt = %d\n",byt);
int aq[byt];
i=0;q=0;

                        /*storing cipher text value in array by 4 bit value*/
while(i<count){
if(q<alen){
  while(ar[q]!=0){
  aq[i]=ar[q]%10;
  ar[q]=ar[q]/10;
  i++;
   }
q++;
}
else{break;}
}

while(i<count){
aq[i]=0;
i++;
}
tem=byt-(count+32);        /* padding length */

//printf("tem = %d\n",tem);       
                         /*padding*/
aq[count]=1;
for(i=1;i<tem;i++){
aq[count+i]=0;
}
                        /*Appending length*/
i=0;
len=count;
while(len!=0){
aq[count+tem+i]=len%10;
len=len/10;
i++;
}
//printf("\n\n");
for(q=count+tem+i;q<byt;q++){
aq[q]=0;
}

//printf("\n\n");                  /*hexadecimal form*/
for(i=0;i<byt/16;i++){
for(q=0;q<16;q++){
arr[i][q]=aq[q+(i*16)];
}
}
                               /*conversion int to string*/
 for(i=0;i<16;i++){
 for(q=0;q<16;q++){
 sprintf(s,"%d",arr[i][q]);
 strcat(ar1[i],s);
 }
  arrr[i]=ar1[i];
 //printf("%s\n",arrr[i]);
 }

//printf("\n\n");
         
                                      //Additive constant
constt[0]="ABC4362679A10FEC";
constt[1]="F3E5491ADDAC7E4B";
constt[2]="594AFB2C7F82472C";
constt[3]="9E385AD247B16C8F";

                                     //Chaining Variables
cv[0]="6A09E667F3BCC908";
cv[1]="BB67AE8584CAA73B";
cv[2]="3C6EF372FE94F82B";
cv[3]="A54FF53A5F1D36F1";
cv[4]="510E527FADE682D1";
cv[5]="9B05688C2B3E6C1F";
cv[6]="1F83D9ABFB41BD6B";
cv[7]="5BE0CD19137E2179";

                               //Binary conversion of Chaining Variables
for(i=0;i<8;i++){
for(j=0;j<64;j++){
x[i][j]=h2b(cv,i,j,8);
a[i][j]=x[i][j];
}}
                                   //Binary conversion of Chipher Text              
for(i=0;i<16;i++){
for(j=0;j<64;j++){
y[i][j]=h2b(arrr,i,j,16);
}}
                                 //Binary conversion of Additive constant
for(i=0;i<4;i++){
for(j=0;j<64;j++){
kt[i][j]=h2b(constt,i,j,4);
}}

for(c=0;c<80;c++){
                                       /* process block */
for(i=0;i<64;i++){
cha[i]=ch(x[4],x[5],x[6],i);
maja[i]=maj(x[0],x[1],x[2],i);
sumx[i]=suma(x[0],i);
sumy[i]=sume(x[4],i);
}
                                            /* Temp1 Addition = ch+h+sume+wt+kt */
for(i=63;i>=0;i--){
k=cha[i];l=x[7][i];                                       /* ch+h*/
if(k==0 && l==0 && p==0){temp[i]=0;p=0;}
else if(k==1 && l==0 && p==0){temp[i]=1;p=0;}
else if(k==0 && l==1 && p==0){temp[i]=1;p=0;}
else if(k==1 && l==1 && p==0){temp[i]=0;p=1;}

else if(k==0 && l==0 && p==1){temp[i]=1;p=0;}
else if(k==1 && l==0 && p==1){temp[i]=0;p=1;}
else if(k==0 && l==1 && p==1){temp[i]=0;p=1;}
else if(k==1 && l==1 && p==1){temp[i]=1;p=1;}
}

p=0;                                                /* + Sume*/
for(i=63;i>=0;i--){
k=temp[i];l=sumy[i];
if(k==0 && l==0 && p==0){temp[i]=0;p=0;}
else if(k==1 && l==0 && p==0){temp[i]=1;p=0;}
else if(k==0 && l==1 && p==0){temp[i]=1;p=0;}
else if(k==1 && l==1 && p==0){temp[i]=0;p=1;}

else if(k==0 && l==0 && p==1){temp[i]=1;p=0;}
else if(k==1 && l==0 && p==1){temp[i]=0;p=1;}
else if(k==0 && l==1 && p==1){temp[i]=0;p=1;}
else if(k==1 && l==1 && p==1){temp[i]=1;p=1;}
}

p=0;                                               /* + w[i]*/
for(i=63;i>=0;i--){
k=temp[i];l=y[c%16][i];
if(k==0 && l==0 && p==0){temp[i]=0;p=0;}
else if(k==1 && l==0 && p==0){temp[i]=1;p=0;}
else if(k==0 && l==1 && p==0){temp[i]=1;p=0;}
else if(k==1 && l==1 && p==0){temp[i]=0;p=1;}

else if(k==0 && l==0 && p==1){temp[i]=1;p=0;}
else if(k==1 && l==0 && p==1){temp[i]=0;p=1;}
else if(k==0 && l==1 && p==1){temp[i]=0;p=1;}
else if(k==1 && l==1 && p==1){temp[i]=1;p=1;}
}

p=0;                                               /* + kt[i]*/
for(i=63;i>=0;i--){
k=temp[i];
if(c>=0 && c<20) {l=kt[0][i];}
if(c>=20 && c<40) {l=kt[1][i];}
if(c>=40 && c<60) {l=kt[1][i];}
if(c>=60 && c<80) {l=kt[1][i];}

if(k==0 && l==0 && p==0){temp[i]=0;p=0;}
else if(k==1 && l==0 && p==0){temp[i]=1;p=0;}
else if(k==0 && l==1 && p==0){temp[i]=1;p=0;}
else if(k==1 && l==1 && p==0){temp[i]=0;p=1;}

else if(k==0 && l==0 && p==1){temp[i]=1;p=0;}
else if(k==1 && l==0 && p==1){temp[i]=0;p=1;}
else if(k==0 && l==1 && p==1){temp[i]=0;p=1;}
else if(k==1 && l==1 && p==1){temp[i]=1;p=1;}
}                           /* Temp2 Addition=suma+maj*/
p=0;
for(i=63;i>=0;i--){
k=sumx[i];l=maja[i];                                       /* suma+maj*/
if(k==0 && l==0 && p==0){temp11[i]=0;p=0;}
else if(k==1 && l==0 && p==0){temp11[i]=1;p=0;}
else if(k==0 && l==1 && p==0){temp11[i]=1;p=0;}
else if(k==1 && l==1 && p==0){temp11[i]=0;p=1;}

else if(k==0 && l==0 && p==1){temp11[i]=1;p=0;}
else if(k==1 && l==0 && p==1){temp11[i]=0;p=1;}
else if(k==0 && l==1 && p==1){temp11[i]=0;p=1;}
else if(k==1 && l==1 && p==1){temp11[i]=1;p=1;}
}
p=0;
for(i=63;i>=0;i--){
k=temp[i];l=temp11[i];                                       /*a = temp1+temp2*/
if(k==0 && l==0 && p==0){x[0][i]=0;p=0;}
else if(k==1 && l==0 && p==0){x[0][i]=1;p=0;}
else if(k==0 && l==1 && p==0){x[0][i]=1;p=0;}
else if(k==1 && l==1 && p==0){x[0][i]=0;p=1;}

else if(k==0 && l==0 && p==1){x[0][i]=1;p=0;}
else if(k==1 && l==0 && p==1){x[0][i]=0;p=1;}
else if(k==0 && l==1 && p==1){x[0][i]=0;p=1;}
else if(k==1 && l==1 && p==1){x[0][i]=1;p=1;}
}
for(i=0;i<64;i++){
x[1][i]=a[0][i];
x[2][i]=a[1][i];
x[3][i]=a[2][i];
}

p=0;
for(i=63;i>=0;i--){
k=x[3][i];l=temp[i];                                       /*e = d+temp1*/
if(k==0 && l==0 && p==0){x[4][i]=0;p=0;}
else if(k==1 && l==0 && p==0){x[4][i]=1;p=0;}
else if(k==0 && l==1 && p==0){x[4][i]=1;p=0;}
else if(k==1 && l==1 && p==0){x[4][i]=0;p=1;}

else if(k==0 && l==0 && p==1){x[4][i]=1;p=0;}
else if(k==1 && l==0 && p==1){x[4][i]=0;p=1;}
else if(k==0 && l==1 && p==1){x[4][i]=0;p=1;}
else if(k==1 && l==1 && p==1){x[4][i]=1;p=1;}
}

for(i=0;i<64;i++){
x[5][i]=a[4][i];
x[6][i]=a[5][i];
x[7][i]=a[6][i];
}
                                    /*Storing chaining variable in a array for next process*/
 for(i=0;i<8;i++){
  for(j=0;j<64;j++){
   a[i][j]=x[i][j];
   }
  }

}
//printf("\n\n");
/*printf("----------------------------------hash code message digest(binary form)----------------------------------------\n");
 for(i=0;i<8;i++){
  for(j=0;j<64;j++){
   printf("%d",x[i][j]);
   }
  printf("\n");
  }*/
//printf("\n\n");
for(i=0;i<8;i++){
*op[i]=b2h(x[i]);
}
//printf("\n\n\n\n");
/*------------------end of main function----------------------*/



}
int h2b(char **ar,int m,int n,int e){
int k=0,j=0,i=0,a[e][64];
char *w;
while(j!=e){
w=ar[j];i=0,k=0;
while(i!=16){
if(w[i]=='0'){
a[j][k]=0;k++;
a[j][k]=0;k++;
a[j][k]=0;k++;
a[j][k]=0;k++;
}
else if(w[i]=='1'){
a[j][k]=0;k++;
a[j][k]=0;k++;
a[j][k]=0;k++;
a[j][k]=1;k++;
}
else if(w[i]=='2'){
a[j][k]=0;k++;
a[j][k]=0;k++;
a[j][k]=1;k++;
a[j][k]=0;k++;
}
else if(w[i]=='3'){
a[j][k]=0;k++;
a[j][k]=0;k++;
a[j][k]=1;k++;
a[j][k]=1;k++;
}
else if(w[i]=='4'){
a[j][k]=0;k++;
a[j][k]=1;k++;
a[j][k]=0;k++;
a[j][k]=0;k++;
}
else if(w[i]=='5'){
a[j][k]=0;k++;
a[j][k]=1;k++;
a[j][k]=0;k++;
a[j][k]=1;k++;
}
else if(w[i]=='6'){
a[j][k]=0;k++;
a[j][k]=1;k++;
a[j][k]=1;k++;
a[j][k]=0;k++;
}
else if(w[i]=='7'){
a[j][k]=0;k++;
a[j][k]=1;k++;
a[j][k]=1;k++;
a[j][k]=1;k++;
}
else if(w[i]=='8'){
a[j][k]=1;k++;
a[j][k]=0;k++;
a[j][k]=0;k++;
a[j][k]=0;k++;
}
else if(w[i]=='9'){
a[j][k]=1;k++;
a[j][k]=0;k++;
a[j][k]=0;k++;
a[j][k]=1;k++;
}
else if(w[i]=='A'){
a[j][k]=1;k++;
a[j][k]=0;k++;
a[j][k]=1;k++;
a[j][k]=0;k++;
}
else if(w[i]=='B'){
a[j][k]=1;k++;
a[j][k]=0;k++;
a[j][k]=1;k++;
a[j][k]=1;k++;
}
else if(w[i]=='C'){
a[j][k]=1;k++;
a[j][k]=1;k++;
a[j][k]=0;k++;
a[j][k]=0;k++;
}
else if(w[i]=='D'){
a[j][k]=1;k++;
a[j][k]=1;k++;
a[j][k]=0;k++;
a[j][k]=1;k++;
}
else if(w[i]=='E'){
a[j][k]=1;k++;
a[j][k]=1;k++;
a[j][k]=1;k++;
a[j][k]=0;k++;
}
else if(w[i]=='F'){
a[j][k]=1;k++;
a[j][k]=1;k++;
a[j][k]=1;k++;
a[j][k]=1;k++;
}
i++;
}
j++;
}
return a[m][n];

}

int and(int a ,int b){
int c;
if(a==0 && b==0)
{c=0;}
else if(a==1 && b==0)
{c=0;}
else if(a==0 && b==1)
{c=0;}
else if(a==1 && b==1)
{c=1;}
return c;
}

int not(int a){
if(a==0){
return 1;
}
if(a==1){
return 0;
}
}

int xor(int a,int b){
int c;
if(a==0 && b==0)
{c=0;}
else if(a==1 && b==0)
{c=1;}
else if(a==0 && b==1)
{c=1;}
else if(a==1 && b==1)
{c=0;}
return c;
}

int ch(int *a,int *b ,int *c,int q){ //a=binary form of e   b=binary form of f    c=binary form of g
int w,x,y,z,i,ch[64];
for(i=0;i<64;i++){
x=and(a[i],b[i]);
y=not(a[i]);
z=and(y,c[i]);
w=xor(x,z);
ch[i]=w;
}
return ch[q];
}


int maj(int *a,int *b,int *c,int q){
int v,w,x,y,z,i,ch[64];
for(i=0;i<64;i++){
x=and(a[i],b[i]);
y=and(a[i],c[i]);
z=and(c[i],c[i]);
w=xor(x,y);
v=xor(w,z);
ch[i]=v;
}
return ch[q];
}


int suma(int *a,int q){
int w,ch[64],k,b[64],c[64],i,d[64],j=0;
for(i=28;i<64;i++){
b[i]=a[j];
j++;
}
for(i=0;i<28;i++){
b[i]=a[j];
j++;
}
j=0;
for(i=34;i<64;i++){
c[i]=a[j];
j++;
}
for(i=0;i<34;i++){
c[i]=a[j];
j++;
}

j=0;
for(i=39;i<64;i++){
d[i]=a[j];
j++;
}
for(i=0;i<39;i++){
d[i]=a[j];
j++;
}

for(i=0;i<64;i++){
w=xor(b[i],c[i]);
k=xor(w,d[i]);
ch[i]=k;
}
return ch[q];
}


int sume(int *a,int q){
int w,ch[64],k,b[64],c[64],i,d[64],j=0;
for(i=14;i<64;i++){
b[i]=a[j];
j++;
}
for(i=0;i<14;i++){
b[i]=a[j];
j++;
}
j=0;
for(i=18;i<64;i++){
c[i]=a[j];
j++;
}
for(i=0;i<18;i++){
c[i]=a[j];
j++;
}

j=0;
for(i=41;i<64;i++){
d[i]=a[j];
j++;
}
for(i=0;i<41;i++){
d[i]=a[j];
j++;
}

for(i=0;i<64;i++){
w=xor(b[i],c[i]);
k=xor(w,d[i]);
ch[i]=k;
}
return ch[q];
}



char* b2h(int *a){
int i,j,k,n,b[16][4],sum,z;
char s[16],str[200],ch[16]; 
FILE *f1; 
for(j=0;j<16;j++){
  i=0;
  for(k=3;k>=0;k--){
   b[j][i]=a[k+(j*4)];
  i++;
  } 
 }
*s=NULL;*ch=NULL;

for(i=0;i<16;i++){

 sum=0;
 for(j=0;j<4;j++){
  sum=sum+(b[i][j]*pow(2,j));
 }
 if(sum>=0 && sum <10){
 //printf("%d",sum);
sprintf(ch,"%d",sum);
strcat(s,ch);
}
 
 else if(sum == 10){//printf("A");
strcat(s,"A");
}
 else if(sum == 11){//printf("B");
strcat(s,"B");
}
 else if(sum == 12){//printf("C");
strcat(s,"C");
}
 else if(sum == 13){//printf("D");
strcat(s,"D");
}
 else if(sum == 14){//printf("E");
strcat(s,"E");
}
 else if(sum == 15){//printf("F");
strcat(s,"F");
}

}
f1=fopen("hash.txt","a+");
fseek(f1,0,SEEK_END);fwrite(&s,sizeof(s),1,f1);
	fclose(f1);

printf("\n");

}
