#include<stdio.h>

int main()

{
int i,n=10,sum,res;
for(i=1;i<=n;i++)
{
	sum+=i;
	res=f1(1,i-5);
}
return 0;
}
int f1(int x,int y){
	return f2(x,y);
}
int f2(int x,int y){
	return f3(x,y);
}
int f3(int x,int y){
	return mydiv(x,y);
}
int mydiv(int x,int y){
	return x/y;
}

