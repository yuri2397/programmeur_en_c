#ifndef __MODULE__H__
#define __MODULE__H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct matrice
{
    int nb_equation;
    float **tab;      
}matrice,*Matrice;

typedef struct systeme
{
    Matrice mat;
    float *vecteur;
}systeme,*Systeme;

void singuliere(Matrice mat);
void error_exit(char *string);
Matrice create_matrice(int nb_equation);
void push_matrice(Matrice mat);
Systeme create_systeme(int nb_equation);
void show_systeme(Systeme s);
void trianguler(Systeme s);
void permutation(Systeme s, int i, int j);
int pivot_max(Matrice mat,int k);
void reduction(Systeme s,int j,int k, float u);
float* resolution(Systeme s);

#endif