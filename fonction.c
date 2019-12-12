#include "module.h"

void error_exit(char *string)
{
    fprintf(stderr, "Excepetion : %s", string);
    exit(EXIT_FAILURE);
}

void singuliere(Matrice mat)
{
	if(mat->tab[mat->nb_equation-1][mat->nb_equation-1] == 0)
	{
		printf("Attention matrice singuliere !!!\n");
		exit(EXIT_FAILURE);
	}
}

Matrice create_matrice(int nb_equation)
{
    Matrice tmp = (Matrice)malloc(sizeof(matrice));
    tmp->tab = (float**)malloc(nb_equation*sizeof(float));
    tmp->nb_equation = nb_equation;
    if (!tmp)
        error_exit("Allocation de matrice echouee!!!\n");
    for (int i = 0; i < nb_equation; i++)// n fois
    {
        tmp->tab[i] = (float *)malloc(nb_equation * sizeof(float));
        if (!tmp->tab[i])
            error_exit("Allocation de matrice echouee!!!\n");
    }
    return tmp;
}

Systeme create_systeme(int nb_equation)
{
    Systeme tmp = (Systeme)malloc(sizeof(systeme));
    if (!tmp)
        error_exit("Creation du systeme lineaire!!!\n");
    tmp->mat = create_matrice(nb_equation);
    push_matrice(tmp->mat);
    tmp->vecteur = (float *)malloc(nb_equation * sizeof(float));
    if (!tmp->vecteur)
        error_exit("Memoire innalouer!!!");
    printf("DONNER L'ELEMENT DU VECTEUR : \n\n");
    for (int i = 0; i < nb_equation; i++)
    {
        printf("\tELEMENT %d :", i + 1);
        scanf("%g", &(tmp->vecteur[i]));
    }
    return tmp;
}

void push_matrice(Matrice mat)
{
    for (int i = 0; i < mat->nb_equation; i++)
    {
        printf("EQUATION %d : \n\n", i + 1);
        for (int j = 0; j < mat->nb_equation; j++)
        {
            printf("\tINCONNUE %d : ",j+1);
            scanf("%g", &(mat->tab[i][j]));
        }
        printf("\n");
    }
}

void show_systeme(Systeme s)
{
    for (int i = 0; i < s->mat->nb_equation; i++)
    {
        for (int j = 0; j < s->mat->nb_equation; j++)
        {
            printf("%g  ", s->mat->tab[i][j]);
        }
        printf(" %g", s->vecteur[i]);
        printf("\n");
    }
}

void reduction(Systeme s, int j, int k, float u)
{
    for (int i = 0; i < s->mat->nb_equation; i++)
    {
        s->mat->tab[j][i] = s->mat->tab[j][i] - u * s->mat->tab[k][i];
    }
    s->vecteur[j] = s->vecteur[j] - u * s->vecteur[k];
}

void permutation(Systeme s, int i, int j)
{
    float tmp;
    for (int k = 0; k < s->mat->nb_equation; k++)
    {
        tmp = s->mat->tab[i][k];
        s->mat->tab[i][k] = s->mat->tab[j][k];
        s->mat->tab[j][k] = tmp;
    }
    tmp = s->vecteur[i];
    s->vecteur[i] = s->vecteur[j];
    s->vecteur[j] = tmp;
}

int pivot_max(Matrice mat, int k)
{
	int imax = k;
	for (int i = k+1; i > mat->nb_equation; i++)
	{
		if(mat->tab[imax][k] < mat->tab[i][k])
			imax = i;
	}
	return imax;
}

void trianguler(Systeme s)
{
	float valeur_pivot,coef;
	for (int i = 0; i < s->mat->nb_equation;i++)
	{	
		int indice = pivot_max(s->mat,i);
		valeur_pivot = s->mat->tab[indice][i];
		if(valeur_pivot != 0)
		{
			if(indice != i)
				permutation(s,indice,i);
			for(int j = i+1;j < s->mat->nb_equation;j++)
			{
				coef = s->mat->tab[j][i] / s->mat->tab[i][i];
				reduction(s,j,i,coef);
			}
			singuliere(s->mat);
		}
		else
			error_exit("La matrice n'est pas inversible !!!");
	}
}


float* resolution(Systeme s)
{
	trianguler(s);
	float *solution = (float*)malloc(s->mat->nb_equation*sizeof(float));
	if(!solution)
		error_exit("Allocation de la memoire pour pour garder la solution !!!!\n");
	solution[s->mat->nb_equation-1] = s->vecteur[s->mat->nb_equation-1] / s->mat->tab[s->mat->nb_equation-1][s->mat->nb_equation-1];
	
	float sum;
	for (int i = s->mat->nb_equation-2; i > -1 ; i--)
	{
		sum = 0;
		for(int j = s->mat->nb_equation-1; j > i ; j--)
		{
			sum = sum + s->mat->tab[i][j]*solution[j];
		}
		solution[i] = (s->vecteur[i] - sum) / s->mat->tab[i][i];
	}
	return solution;
}