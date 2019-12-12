#include "module.h"

int main(int argc, char const *argv[])
{
	int n;
	printf("\n\n\tDONNER LE NOMBRE D'EQUATION : ");
	scanf("%d",&n);

	Systeme s = create_systeme(n);
	show_systeme(s);
	
	float *solution = resolution(s);

	printf("{ ");
	for (int i = 0; i < s->mat->nb_equation; i++)
	{
		printf("%g%s",solution[i],(i+1 == s->mat->nb_equation ? "":" ; ") );
	}
	printf(" }\n");

	return 0;
}