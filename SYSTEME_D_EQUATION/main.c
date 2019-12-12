#include "header.h"
 #include <Windows.h>
int main()
{
	int n;
	do{
		printf("DONNER LE NOMBRE D\'EQUATION : \n");
		scanf("%d",&n);	
	}while(n<=0);
	Systeme my = createSysteme(n);
	cramer(my);
	system("pause");
}