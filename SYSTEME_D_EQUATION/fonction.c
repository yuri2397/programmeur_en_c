#include "header.h"

int puissance(int nombre,int puis){

	if(puis == 0)
		return 1;
	else{
		return nombre * puissance(nombre,puis-1);
	}
}

void getError(char *c){
	fprintf(stderr, "%s\n",c );
	exit(EXIT_FAILURE);
}

Matrice allocMatrice(int ligne,int colonne){
	Matrice m = (Matrice)malloc(sizeof(matrice));
	
	m->ligne = ligne;
	m->colonne = colonne;

	(*m).tab = (int**)malloc(m->ligne * sizeof(int));
	if(m->tab == NULL)
		getError("ERREUR : Impossible d'allouer la matrice associee\n");
	for (int i = 0; i < m->ligne; ++i)
	{
		m->tab[i] = (int*)malloc(m->colonne*sizeof(int));
	}
	return m;
}

void pushSysteme(Systeme s){

	for (int i = 0; i < s->mat->ligne; ++i)
	{
		printf("Equation %d : \n",i+1 );
		for(int j = 0;j < s->mat->colonne;j++)
		{
			printf("Coefficient %d du systeme  :: ",j+1 );
			scanf("%d",&(s->mat->tab[i][j]));
		}
		printf("DONNER L\'element %d du vecteur :: ",i+1 );
		scanf("%d",&(s->vecteur[i]));
	}
}

Systeme createSysteme(int nb_equation){
	Systeme s = (Systeme)malloc(sizeof(systeme));
	if(!s)
		getError("Erreur avec la creation d\'un systeme d\'equation\nVeuillez relancer le programme !!!\n");
	
	s->mat = allocMatrice(nb_equation,nb_equation);

	s->vecteur = (int*)malloc(nb_equation*sizeof(int));

	pushSysteme(s);
	return s;
}

void showSysteme(Systeme s){
	for (int i = 0; i < s->mat->ligne; i++)
	{
		for(int j = 0;j < s->mat->colonne;j++)
		{
			printf("%d ",s->mat->tab[i][j]);
		}
		printf("%d\n", s->vecteur[i]);
	}
}

Matrice reduireMatrice(Matrice mat,int l,int c){
	Matrice resultat = allocMatrice(mat->ligne-1,mat->colonne-1);
	int k=0,n=0;
	for (int i = 0; i < mat->ligne; i++)
	{
		n=0;
		for(int j=0;j< mat->colonne;j++){

			if(i != l && c != j)
				resultat->tab[k][n++] = mat->tab[i][j];
		}
		if(i != l)
			k++;
	}

	return resultat;
}

int determinant(Matrice mat){
	int final = 0;
	if(mat->ligne == 1){
		return mat->tab[0][0];
	}
	else
	{
		for(int i = 0; i < mat->ligne;i++){
			final += puissance(-1,2+i) * (mat->tab[0][i]) * determinant(reduireMatrice(mat,0,i));
		}
		return final;
	}
}


Matrice insertVecteur(Systeme s,int col){
	Matrice tmp = allocMatrice(s->mat->ligne,s->mat->colonne);

	int k=0;
	for (int i = 0; i < tmp->ligne; ++i)
	{
		for(int j = 0; j < tmp->colonne; j++)
		{
			if(col != j)
				tmp->tab[i][j] = s->mat->tab[i][j];
			else
				tmp->tab[i][j] = s->vecteur[k++];
		}
	}
	return tmp;
}

void cramer(Systeme s){
	int det = determinant(s->mat);
	if(det == 0)
	{
		printf("Le systeme a une infinite de soluttions\n");
		return;
	}
	/* on sait que a partir d'ici le systeme admet une solution unique*/
	float solution;
	printf("La solution : { ( ");
	for (int i = 0; i < s->mat->ligne; i++)
	{
		solution =(float)(determinant(insertVecteur(s,i)) )/det;
		printf("%.2f%s",solution,i+1 != s->mat->ligne ? SEPARE:SEPAREVIDE );
	}
	printf(") }\n");
}