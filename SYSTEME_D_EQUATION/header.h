#ifndef __HEADER_H__
#define __HEADER_H__
#include <stdio.h>
#include <stdlib.h>
#define SEPARE " ; "
#define SEPAREVIDE ""

typedef struct matrice{
	int ligne;
	int colonne;
	int **tab;
}matrice,*Matrice;

typedef struct systeme{
	Matrice mat;
	int *vecteur;
}systeme,*Systeme;

void getError(char *c);

Systeme createSysteme(int n);

Matrice allocMatrice(int ligne,int colonne);

void pushSysteme(Systeme s);

void showSysteme(Systeme s);

Matrice reduireMatrice(Matrice mat,int l,int c);

int determinant(Matrice mat);

Matrice insertVecteur(Systeme s,int col);

void cramer(Systeme s);

#endif