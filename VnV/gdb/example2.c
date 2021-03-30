#include<stdio.h>

int main()

{
int k,res;
printf("Welcome,pid
for(k=1;k<=6;k++)
{
	  res = fact(k);

  printf("%d\n",res);
}
	return 0;
}
int fact(int n){
	int f=1,i;
	for(i=1;i<=n;i++)
		f=f*i;
	return f;
}
