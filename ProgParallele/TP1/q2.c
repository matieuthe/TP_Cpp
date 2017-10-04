#include <stdio.h>   /* standard I/O routines */
#include <pthread.h> /* pthread functions and data structures */
#include <unistd.h>

#define SIZE_TAMP 10 //Taille tu tampon

int tampon[SIZE_TAMP][2];
int posLecture = 0;
int posEcriture = 0;

pthread_mutex_t mutStatut[SIZE_TAMP];

pthread_mutex_t mutexNb = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexPosLect = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexPosEcrit = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutLire = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutEcrire = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t peutLire = PTHREAD_COND_INITIALIZER;

void ecrire();
void lire();
void init();

int main(int argc, char* argv[]){
	init();
	
	exit(0);
}

void ecrire(){
	//Pour être tout seul à écrire
	pthread_mutex_lock(&mutEcrire);
	int continuer = 1;
	while(continuer){
		pthread_mutex_lock(&mutStatut[posEcriture]);
		
		if(tampon[posEcriture] == 0) continuer = 0;
		else if(tampon[posEcriture] == 1){ //Non Lue
			
		}else{
		
		}	
		pthread_mutex_unlock(&mutStatut[posEcriture]);
	}

	pthread_mutex_unlock(&mutEcrire);
}

void lire(){
	//Pour être tout seul à lire
	pthread_mutex_lock(&mutLire);
	
	//Bloque l'accès au statut de l'élément courant en lecture
	pthread_mutex_lock(&mutStatut[posLecture]);
	
	if(tampon[posLecture][0] == 0){
		pthread_mutex_unlock(&mutexNb);
		pthread_cond_wait(&peutLire, &mutLire);
			pthread_mutex_lock(&mutStatut[posLecture]);
	}
	
	tampon[posLecture][0] = 2; // 2 => en cours de lecture 
	pthread_mutex_unlock(&mutStatut[posLecture]);
	
	tampon[posLecture][1] = -1; // On met la valeur de la trame à -1
	
	//On rebloque l'accès au statut
	pthread_mutex_lock(&mutStatut[posLecture]);
	tampon[posLecture][0] = 0; // 0 => Lue 
	pthread_mutex_unlock(&mutStatut[posLecture]);
	
	//On modifie la position de lecture pour le thread suivant
	if(posLecture == (SIZE_TAMP - 1)) posLecture = 0;
	else posLecture++;
	
	pthread_mutex_unlock(&mutLire);
	pthread_exit(NULL);
}

void init(){
	int i;
	for(i = 0; i < SIZE_TAMP; i++) tampon[i][0] = 0; //Etat lue
	
	//On debloque bien les mutex
	pthread_mutex_unlock(&mutexNb);
	pthread_mutex_unlock(&mutexPosLect);
	pthread_mutex_unlock(&mutexPosEcrit);
	pthread_mutex_unlock(&mutLire);
	
	for(i = 0; i < SIZE_TAMP; i++) mutStatut[i] = PTHREAD_MUTEX_INITIALIZER;
}
