#include<stdio.h>
#include<string.h>

long  c_int(long  x/*, int nbits*/){
	//if(nbits==0)
	int 	nbits=32;
	//printf("x=%d,n=%d\n",x,nbits); 
	//""" C cast to int32, int16, int8... """
	long u=(long) 1 << (nbits - 1); 
	u=(long)  (x &( u - 1)) - (x & u);
	return u; 
}

long   c_uint(long x/*, int nbits*/){
	//if(nbits==0)
		int nbits=32; 
	//""" C cast to uint32, uint16, uint8... """
	//printf("x=%d,n=%d\n",x,nbits);
	long u=(long) 1 << nbits;
	u=x & (u - 1);
	//printf("u=%ld\n",u); 
	return u;
}

// int tkk[] = {406398, 561666268 + 1526272306};
// int b = tkk[0];

/*if PY2:
  d = map(ord, source)
else:
d = source.encode('utf-8')
*/
//char *d=source; 
long   RL(long a, char *b){
	//printf("RL:\n"); 
	int   s=0; 
	long xa=0; 
	long  d=0; 
	long rex=0; 
	s=strlen(b);
	s--;
	s--; 
	//  for c in range(0, len(b) - 2, 3):
	for(int c=0;c<s; c++){
		//printf("c/3: %d\n",c%3); 
		if(c%3!=0)
			continue;
		//printf("c=%d\n",c); 
		 d = b[c + 2]; 
		//printf("d=%c\n",d); 
		if (d >= 'a')
			d = d - 87;
		else
			d-=0x30; 
		//printf("d=%d\n",d); 
		 xa = c_uint(a);
		//printf("xa=%ld\n",xa); 
		if (b[c + 1]== '+') 
			d = xa >> d;  
		else
			d=xa << d; 

		if (b[c] == '+')
			a = a + d & 4294967295;
		else
			a= a ^ d; 
		//printf("d=%ld\n",d);
	}
	//printf("d=%ld\n",a);
	rex=c_int(a);
	//printf("rex=%ld\n",rex);
	return rex; 
}



char * _calculate_tk(char *tk,char *source){
	char *d=source;
	long  tkk[] = {406398, 561666268 + 1526272306};
	long  b = tkk[0];
	long  a = b; 
	for (int i=0; i<strlen(d); i++) {
		//printf("%d,%d\n",a,d[i]) ; 
		a = RL(a + d[i], "+-a^+6"); 
	}
	a = RL(a, "+-3^+b+-f");
	//printf("a=%ld\n",a);
	a ^= tkk[1];
	//printf("a=%ld\n",a);
	//if( a ! > 0&&a!=0  ) 
	if(a<0)
		a=((a & 2147483647) + 2147483648); 
	//printf("a=%ld\n",a);
	a %= 1000000; 
	//tk = '{0:d}.{1:d}'.format(a, a ^ b);
	//printf("a=%ld\n",a);
	sprintf(tk,"%ld.%ld",a,a^b); 
	//printf("%s\n",tk); 
	return tk;
}

int main(){
	//char *u=(char *)malloc(1024*1024*500);
	//if(u)
	//memset(u,1,1024*1024*500); 
	//while (1)sleep (1); 
	//printf(file); 
	//printf("%d\n",5^7); 
	char *g="h";
	char tk[20]; 
	char *u= 
	_calculate_tk(tk,g); 
	printf("%s\n",u); 
}
