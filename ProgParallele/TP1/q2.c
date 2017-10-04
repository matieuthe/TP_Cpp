#include <stdio.h>   /* standard I/O routines */
#include <pthread.h> /* pthread functions and data structures */
#include <unistd.h>
#include <stdlib.h>

#define SIZE_TAMP 10 //Taille tu tampon

int tampon[SIZE_TAMP][2];

int trame = 1;

pthread_mutex_t mutStatut[SIZE_TAMP];

pthread_mutex_t mutLire = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutEcrire = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutRech = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t peutLire = PTHREAD_COND_INITIALIZER;

void* ecrire();
void* lire();
void init();

int main(int argc, char* argv[]){
	init();
	int nb = 200;
	pthread_t thread[nb];
	int choix = 1;
	
	for(int i = 0; i < nb; i++){
		if(choix){
			pthread_create(&thread[i], NULL, ecrire, NULL);
			choix = 0;
		}
		else{
			pthread_create(&thread[i], NULL, lire, NULL);
			choix = 1;
		}
    }
	exit(0);
}

void* ecrire(){
	//Pour être tout seul à écrire
	pthread_mutex_lock(&mutEcrire);
	pthread_mutex_lock(&mutRech);
	
	int posMin = -1;
	int min = -1;
	//On cherche la position du plus vieux ou une case vide
	for(int i = 0; i < SIZE_TAMP; i++){
		pthread_mutex_lock(&mutStatut[i]);
		if(tampon[i][0] == 0){
			posMin = i;
			i = SIZE_TAMP;
		}else if(tampon[i][0] == 1 && min < tampon[i][1]){
			posMin = i;
			min = tampon[i][1];
		}
		pthread_mutex_unlock(&mutStatut[i]);
	}
	pthread_mutex_unlock(&mutRech);

	//On ecrit à la position i
	//Bloque l'accès au statut de l'élément à lire
	pthread_mutex_lock(&mutStatut[posMin]);
	tampon[posMin][0] = 0; //On passe le statut à rien à lire
	pthread_mutex_unlock(&mutStatut[posMin]);
	
	tampon[posMin][1] = trame++;
	
	//Bloque l'accès au statut de l'élément à lire
	pthread_mutex_lock(&mutStatut[posMin]);
	tampon[posMin][0] = 1; //On passe le statut à non lu
	pthread_mutex_unlock(&mutStatut[posMin]);
	
	pthread_cond_broadcast(&peutLire);
	//On debloque l'ecriture
	pthread_mutex_unlock(&mutEcrire);
	pthread_exit(NULL);
}

void* lire(){
	//Pour être tout seul à lire
	pthread_mutex_lock(&mutLire);
	
	int posMin = -1;
	int min = -1;
	int continuer = 1;
	while(continuer){
		pthread_mutex_lock(&mutRech);
		//On cherche la position du plus vieux
		for(int i = 0; i < SIZE_TAMP; i++){
			pthread_mutex_lock(&mutStatut[i]);
		
			if(tampon[i][0] == 1 && min < tampon[i][1]){
				posMin = i;
				min = tampon[i][1];
			}
			pthread_mutex_unlock(&mutStatut[i]);
		}
		pthread_mutex_unlock(&mutRech);
		
		if(posMin == -1)  pthread_cond_wait(&peutLire, &mutLire);
		else continuer = 0;
	}
	
	
	//Bloque l'accès au statut de l'élément à lire
	pthread_mutex_lock(&mutStatut[posMin]);
	tampon[posMin][0] = 2; //On passe le statut à en cours de lecture
	pthread_mutex_unlock(&mutStatut[posMin]);
	
	//On lit la valeur
	printf("%d\n", posMin);
	sleep(0.5);
	
	//Bloque l'accès au statut de l'élément à lire
	pthread_mutex_lock(&mutStatut[posMin]);
	tampon[posMin][0] = 0; //On passe le statut à lu
	pthread_mutex_unlock(&mutStatut[posMin]);
	
	//On débloque l'accès en lecture
	pthread_mutex_unlock(&mutLire);
	pthread_exit(NULL);
}

void init(){
	int i;
	for(i = 0; i < SIZE_TAMP; i++) tampon[i][0] = 0; //Etat lue
	pthread_mutex_unlock(&mutLire);
	pthread_mutex_unlock(&mutEcrire);
	pthread_mutex_unlock(&mutRech);
	pthread_mutex_unlock(&mutLire);
	
	for(i = 0; i < SIZE_TAMP; i++){
		pthread_mutex_unlock(&mutStatut[i]);
	}	

}




