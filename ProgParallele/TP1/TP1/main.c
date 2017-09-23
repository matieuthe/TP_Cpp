#include <stdio.h>   /* standard I/O routines */
#include <pthread.h> /* pthread functions and data structures */
#include <unistd.h>

#define MAX 10 //Nombre d'élément du tampon
#define NBTEST 25

//Commande pour compiler
//gcc tp1.c -o tp1 -lpthread
//http://forum.hardware.fr/hfr/Programmation/C/probleme-producteur-consommateur-sujet_143077_1.htm

int tamp[MAX];
int nbElements = 0; //nb element dans le tampon
int posEcriture = 0; //Position de l'écriture
int posLecture = 0; //Position de la lecture
int enEcriture = 0;
int enLecture = 0;
pthread_cond_t consommerPossible = PTHREAD_COND_INITIALIZER;
pthread_cond_t produirePossible = PTHREAD_COND_INITIALIZER;

pthread_mutex_t ecriture = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lecture = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexNb = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t bloqLecture = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t bloqEcriture = PTHREAD_MUTEX_INITIALIZER;

//Entête des fonctions
void messageInitiale(void);
void* put(int v);
void* get(void);
void creerThreadGet(int nb);
void afficheState(void);
void creerThreadPut(int nb, int val);

int main(int argc, char* argv[]){
    char chaine[20];
    char typeOp;
    int nbProc;
    int val;
    int continuer = 1;
    //On s'assure que les mutex soit débloqué
    pthread_mutex_unlock(&mutexNb);
    pthread_mutex_unlock(&lecture);
    pthread_mutex_unlock(&ecriture);
    pthread_mutex_unlock(&bloqLecture);
    pthread_mutex_unlock(&bloqEcriture);
    
    //On affiche les infos de départ
    messageInitiale();

    while(continuer){
        printf("--> ");
        //On réinit les valeurs
        typeOp = 'Z';
        nbProc = 0;
        val = 0;
        //On récupère l'entrée
        fgets(chaine, sizeof(chaine), stdin);
        //On parse la chaine
        sscanf(chaine,"%c %d %d", &typeOp, &nbProc, &val);
        
        switch (typeOp) {
            case 'Q': continuer = 0;//On arrête le programme
                break;
            case 'G': if(nbProc > 0) creerThreadGet(nbProc);
                break;
            case 'P': if(nbProc > 0) creerThreadPut(nbProc, val);
                break;
            case 'S': afficheState();
                break;
            default: printf("Erreur de saisi, veuillez réessayer \n");
                break;
        }
    }
    
    return 0;
}

void messageInitiale(){
    printf("------ Bienvenue dans le mini interpréteur ------\n");
    printf("Créer un processus get : G nombre_de_threads\n");
    printf("Créer un processus put : P nombre_de_threads valeur_à_insérer\n");
    printf("État du système : S\n");
    printf("Quitter le programme : Q\n");
}

void afficheState(){
    pthread_mutex_lock(&bloqEcriture);
    pthread_mutex_lock(&bloqLecture);
    pthread_mutex_lock(&ecriture);
    pthread_mutex_lock(&lecture);
    pthread_mutex_lock(&mutexNb);

    printf("%d threads en lecture\n", enLecture);
    printf("%d threads en Ecriture\n", enEcriture);
    for(int i = 0; i < MAX; i++){
        printf("%d ", tamp[i]);
    }
    printf("\n");
    pthread_mutex_unlock(&bloqEcriture);
    pthread_mutex_unlock(&bloqLecture);
    pthread_mutex_unlock(&ecriture);
    pthread_mutex_unlock(&lecture);
    pthread_mutex_unlock(&mutexNb);
}

void creerThreadGet(int nb){
    pthread_t thread[nb];
    
    for(int i = 0; i < nb; i++){
        pthread_create(&thread[i], NULL, get, NULL);
    }
    printf("%d thread(s) get créé(s)\n", nb);
}

void creerThreadPut(int nb, int val){
    pthread_t thread[nb];
    
    for(int i = 0; i < nb; i++){
        pthread_create(&thread[i], NULL, put, val);
    }
    printf("%d thread(s) put créé(s)\n", nb);
}

void* put(int v){
    pthread_mutex_lock(&bloqEcriture);
    enEcriture ++;
    pthread_mutex_unlock(&bloqEcriture);
    
    //Pour qu'un seul thread écrive à la fois
    pthread_mutex_lock(&ecriture);
    //On bloque l'accès à nbElements
    pthread_mutex_lock(&mutexNb);
    
    //On regarde la valeur de nbElements
    if(nbElements == MAX){
        //printf("tampon Plein\n");
        //On libère l'accès à nbElement
        pthread_mutex_unlock(&mutexNb);
        //On attend qu'une place se libère dans le tampon
        pthread_cond_wait(&produirePossible, &ecriture);
        //On rebloque l'accès à nbElement
        pthread_mutex_lock(&mutexNb);
    }
    //On écrit la valeur dans le tampon
    tamp[posEcriture] = v;
   // printf("Ecriture %d\n", nbElements);
    //On modifie la valeur de la position ou écrire
    if(posEcriture < MAX - 1){
        posEcriture ++;
    }else{
        posEcriture = 0;
    }
    
    //Si le nbElement vaut 0 on broadcast pour la lecture
    if(nbElements == 0)
        pthread_cond_broadcast(&consommerPossible);
    
    nbElements++;
    //On débloque l'accès à l'écriture et au nb d'éléments
    pthread_mutex_unlock(&mutexNb);
    pthread_mutex_unlock(&ecriture);
    
    pthread_mutex_lock(&bloqEcriture);
    enEcriture--;
    pthread_mutex_unlock(&bloqEcriture);
    pthread_exit(NULL);
}

void* get(){
    pthread_mutex_lock(&bloqLecture);
    enLecture++;
    pthread_mutex_unlock(&bloqLecture);
    
    //Pour qu'un seul thread lise à la fois
    pthread_mutex_lock(&lecture);
    //On bloque l'accès à nbElements
    pthread_mutex_lock(&mutexNb);
    
    //On regarde la valeur de nbElements
    if(nbElements == 0){
        //printf("tampon vide\n");
        //On libère l'accès à nbElement
        pthread_mutex_unlock(&mutexNb);
        //On attend qu'une place se libère dans le tampon
        pthread_cond_wait(&consommerPossible, &lecture);
        //On rebloque l'accès à nbElement
        pthread_mutex_lock(&mutexNb);
    }
    
    //On modifie la valeur de la position ou écrire
    tamp[posLecture] = -1;
    if(posLecture < MAX - 1)
        posLecture++;
    else
        posLecture = 0;
    
    //printf("Lecture\n");
    //Si le nbElement vaut 0 on broadcast pour l'écriture
    if(nbElements == MAX)
        pthread_cond_broadcast(&produirePossible);
    
    nbElements--;
    //On débloque l'accès à la lecture et au nb d'éléments
    pthread_mutex_unlock(&mutexNb);
    pthread_mutex_unlock(&lecture);
    
    pthread_mutex_lock(&bloqLecture);
    enLecture--;
    pthread_mutex_unlock(&bloqLecture);
    pthread_exit(NULL);
}










