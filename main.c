#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include "qdbmp.c"
#define LL long long int

void imgsve(BMP *img1,BMP *img2,LL ** a1,LL ** a2,LL ** a3)
{
	UINT width,height;
    UCHAR r,g,b,val;
    USHORT depth;
    UINT x, y;

    width = BMP_GetWidth(img1);
    height = BMP_GetHeight(img1);
    depth = BMP_GetDepth(img1);
		if(depth==32||depth==24)
      {
       	 for ( x = 0 ; x < width ; ++x )
            {
                for ( y = 0 ; y < height ; ++y )
                {
                    BMP_SetPixelRGB(img2,x,y,(UCHAR)a1[x][y],(UCHAR)a2[x][y],(UCHAR)a3[x][y]);
                }
           	}
  	  }  
}
int isprime(LL n) {
    if(n%3==0) return n==3;
    LL  p = 5;
  while (p*p <= n) {
    if (n%p==0) return 0;
    p += 2;
    if (n%p==0) return 0;
    p += 4;
  }
  return 1;
}
 LL rand_prime(int lower, int upper) {
  LL spread = upper - lower + 1;
  while(1) {
    LL p = 1 | (rand() % spread + lower);
    if (isprime(p)) return p;
  }
}

LL modpow(LL b, LL e, LL m) {
    long result = 1;

    while (e > 0) {
        if ((e & 1) == 1) {
            //multiply in this bit's contribution while using modulus to keep
            //result small
            result = (result * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return result;
}

int encode(int message, int n, int e)
{
	return modpow(message,e,n);
}

int decode(LL encoded, LL p, LL q, LL e)
{
	LL n = p*q;
	LL ph = (p-1)*(q-1);
	LL d, i;
	for (i=0; ((e*i)% ph)!=1; i++){}
	d = i;
	return(modpow(encoded, d, n));
}
int gcf( int n , int m )
{
	if( n == 0 || m == 0 )
		return 0 ;

	if( n < 0 ) 
		n = - n ;
	if( m < 0 ) 
		m = - m ;

	while( 1 ) 
		if( n > m )
			n -= m ;
		else if ( n < m )
			m -= n ;
		else
			break ;

	return n ;
}
int coprime(int a,int b)
{
	if(gcf(a,b)==1)
	{
	return 1;
	}
	else
	{
		return 0;
	}
}
void shuffle(LL ** m,int *a,LL height, LL width)
{
	UINT i,j;
	LL w=0,t=0,k=0;
	LL y=height;
	LL x=width;
	LL **m1 = (LL **) malloc(sizeof(LL *) * y); //reserve enough space for RGB for each pixel
        for ( i = 0; i < y; i++){
                m1[i] = (LL *) malloc(sizeof(LL) * x);
        }
    LL **m2 = (LL **) malloc(sizeof(LL *) * y); //reserve enough space for RGB for each pixel
        for ( i = 0; i < y; i++){
                m2[i] = (LL *) malloc(sizeof(LL) * x);
        }
      
	for(i =	0 ; i<y ; i++)
	{
		for( j = 0; j<x ; j++)
			m1[i][j]=m[j][i];
	}
	
	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
		t=a[k];
		int q=(ceil((double)t/x));
			if(t%x==0)
			w=x;
			else
			w=t%x;
		m2[i][j]=m1[q-1][w-1];
		k++;
		}
	}
	
	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		m[i][j]=m2[j][i];
	}
}

void random(int *ele,int size)
{
	UINT i;
	for ( i = 1; i <=size; ++i)
	  ele[i-1] = i;
	
	for ( i = size-1 ; i > 0; --i) {
  	
  	int w = rand()%i; // generate random index
  	
	// swap items
  	int t = ele[i];
  	ele[i] = ele[w];
  	ele[w] = t;
	}
}
void display(int ** m, int height,int width)
{
	int x,y;
	for ( x = 0 ; x < width ; ++x )
            {
                for ( y = 0 ; y < height ; ++y )
              {
                	printf("%d ",m[x][y]);
				}
				printf("\n");
			}
}
int main()
{
    UINT width, height;
    UINT x,y;
    UCHAR r,g,b;
    USHORT depth;
    BMP *img1,*img2;
	LL i;
    img1 = BMP_ReadFile("lena3.bmp");
	
    if(img1 == NULL)
    {
       printf("Error!");
    }

    width = BMP_GetWidth(img1);
    height = BMP_GetHeight(img1);
    depth = BMP_GetDepth(img1);
    UINT qaz=width*height;
    
    int *rand = (int *) malloc(sizeof(int *) * qaz); //random pixel array;
    
    random(rand,qaz);
    
	LL **a1 = (LL **) malloc(sizeof(LL *) * width); //reserve enough space for RGB for each pixel
        for ( i = 0; i < width; i++){
                a1[i] = (LL *) malloc(sizeof(LL) * height);
        }
    
	LL **a2 = (LL **) malloc(sizeof(LL *) * width); //reserve enough space for RGB for each pixel
        for ( i = 0; i < width; i++){
                a2[i] = (LL *) malloc(sizeof(LL) * height);
		}
		
	LL **a3 = (LL **) malloc(sizeof(LL *) * width); //reserve enough space for RGB for each pixel
        for ( i = 0; i < width; i++){
                a3[i] = (LL *) malloc(sizeof(LL) * height);
		}
	
    img2 = BMP_Create(width,height,depth);
    
	if(depth==32||depth==24)
      {
       	 for ( x = 0 ; x < width ; ++x )
            {
                for ( y = 0 ; y < height ; ++y )
                {
                    BMP_GetPixelRGB(img1, x, y, &r, &g, &b );
                  	a1[x][y]=(int)r;
                  	a2[x][y]=(int)g;
                  	a3[x][y]=(int)b;
                    BMP_SetPixelRGB(img2,x,y,(UCHAR)a1[x][y],(UCHAR)a2[x][y],(UCHAR)a3[x][y]);
                }
           	}
  	  }
  	printf("\n---------------------------------------------------------\n\n");
	printf("\t\t -------------\n");
	printf("\t\t|SELECT METHOD|\n");
	printf("\t\t -------------\n");	
	printf("\n\t 1. IMAGE SHUFFLING\n");
	printf("\n\t 2. IMAGE ENCRYPTION\n");
	printf("\n\t 3. IMAGE ENCRYPTION WITH DECRYPTION\n");
	printf("\n\t 4. IMPROVED ENCRYPTION\n");
	printf("\n---------------------------------------------------------\n\n");	
	
	printf("Enter choice: ");
	int ch;
	scanf("%d",&ch);
  	srand(time(NULL));
	LL p = rand_prime(10000,10000000); //should be automatically generated
	LL q = rand_prime(10000,10000000);
	LL n = p * q;
	LL ph=(p-1)*(q-1);
	LL v,e,d;
	printf("\n\n If a successfull process, return NULL....\n");
	switch(ch)
	{
		case 1:
			shuffle(a1,rand,(LL)height,(LL)width);
   	 		shuffle(a2,rand,(LL)height,(LL)width);
  	 		shuffle(a3,rand,(LL)height,(LL)width);
  	 		imgsve(img1,img2,a1,a2,a3);// saving image into another image
  	 		BMP_WriteFile(img2,"Myshuffle.bmp");
  	 		break;
  	 		
  	 	case 2:
  	 		
  	 	for(v=2;v<ph;v++)
		{
			if( coprime(v,n)==1 && coprime(v,ph)==1)
			{
				e=v;
				break;
			}
		}
		if(depth==32||depth==24)
     	 {
       	 for ( x = 0 ; x < width ; ++x )
            {
                for ( y = 0 ; y < height ; ++y )
                {
	 			a1[x][y]=encode(a1[x][y],n, e);
	 			a2[x][y]=encode(a2[x][y],n, e);
	 			a3[x][y]=encode(a3[x][y],n, e);
	 			}
	 		}
	 	 }
	  		imgsve(img1,img2,a1,a2,a3);
  	  		BMP_WriteFile(img2,"MyEncryption.bmp");
  	 		break;
  	 		
  	 	case 3:
  	 		for(v=2;v<ph;v++)
			{
				if( coprime(v,n)==1 && coprime(v,ph)==1)
				{
					e=v;
					break;
				}
			}
			if(depth==32||depth==24)
     		 {
       	 	    for ( x = 0 ; x < width ; ++x )//encryption
            	{
                  for ( y = 0 ; y < height ; ++y )
                  {
	 			  a1[x][y]=encode(a1[x][y],n, e);
	 			  a2[x][y]=encode(a2[x][y],n, e);
	 			  a3[x][y]=encode(a3[x][y],n, e);
	 		      }
	 		    }
	 		 }
	 		 for (i=0; ((e*i)% ph)!=1; i++){}
				d = i;
			if(depth==32||depth==24)//decryption
      		{
       	 		for ( x = 0 ; x < width ; ++x )
            	{
                	for ( y = 0 ; y < height ; ++y )
                	{
	 				a1[x][y]=modpow(a1[x][y],d,n);
	 				a2[x][y]=modpow(a2[x][y],d,n);
	 				a3[x][y]=modpow(a3[x][y],d,n);
	 				}
	 			}
	 		}
	 		imgsve(img1,img2,a1,a2,a3);
  	  		BMP_WriteFile(img2,"MyEncrypDecrypt.bmp");
  	  		break;
  	  	case 4:
  	  		shuffle(a1,rand,(LL)height,(LL)width);
   	 		shuffle(a2,rand,(LL)height,(LL)width);
  	 		shuffle(a3,rand,(LL)height,(LL)width);
  	 		for(v=2;v<ph;v++)
			{
				if( coprime(v,n)==1 && coprime(v,ph)==1)
				{
					e=v;
					break;
				}
			}
			if(depth==32||depth==24)
     		 {
       	 	    for ( x = 0 ; x < width ; ++x )//encryption
            	{
                  for ( y = 0 ; y < height ; ++y )
                  {
	 			  a1[x][y]=encode(a1[x][y],n, e);
	 			  a2[x][y]=encode(a2[x][y],n, e);
	 			  a3[x][y]=encode(a3[x][y],n, e);
	 		      }
	 		    }
	 		 }
	 		 imgsve(img1,img2,a1,a2,a3);
  	  		 BMP_WriteFile(img2,"MyImprovedEncryption.bmp");
  	  		 break;
  	  		 default:
  	  		 	printf("Wrong choice");
  	  		
	}
    //	 display(a1,(int)height,(int)width);
  	//imgsve(img1,img2,a1,a2,a3);
    //BMP_WriteFile(img2,"beta.bmp");
    printf("\n%s\n",BMP_GetErrorDescription());
	
    return 0;
}
