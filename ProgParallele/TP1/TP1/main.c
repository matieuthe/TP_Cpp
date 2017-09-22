#include <stdio.h>   /* standard I/O routines */
#include <pthread.h> /* pthread functions and data structures */
#include <unistd.h>

#define MAX 3 //Nombre d'élément du tampon
#define NBTEST 25

//Commande pour compiler
//gcc tp1.c -o tp1 -lpthread
//http://forum.hardware.fr/hfr/Programmation/C/probleme-producteur-consommateur-sujet_143077_1.htm

int tamp[MAX];
int nbElements = 0; //nb element dans le tampon
int posEcriture = 0; //Position de l'écriture
int posLecture = 0; //Position de la lecture
pthread_cond_t consommerPossible = PTHREAD_COND_INITIALIZER;
pthread_cond_t produirePossible = PTHREAD_COND_INITIALIZER;

pthread_mutex_t plein = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ecriture = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t vide = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lecture = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t varNb = PTHREAD_MUTEX_INITIALIZER;

void* put(void * v){
    //Un seul thread peut écrire à la fois dans le tampon
    pthread_mutex_lock(&ecriture);
    
    //Si le nombre d'élément est égale à la taille du tampon, on attends
    if(nbElements == MAX){
        printf("Tampon plein\n");
        pthread_cond_wait(&produirePossible, &plein);
    }
    
    //On met la valeur dans le tampon
    tamp[posEcriture] = 4;
    printf("Ecriture \n");
    //On change la valeur de la position d'écriture
    if(posEcriture < MAX - 1)   posEcriture++;
    else    posEcriture = 0;
    
    //sleep (1);
    
    pthread_mutex_lock(&varNb);
    nbElements++;
    pthread_mutex_unlock(&varNb);
    
    if(nbElements == 1){
       // printf("broadcast\n");
        pthread_cond_broadcast(&consommerPossible);
    }
    //On débloque écriture pour permettre à un autre thread d'écrire
    pthread_mutex_unlock(&ecriture);
    pthread_exit(NULL);
}

void* get(){
    //Un seul thread peut lire à la fois dans le tampon
    pthread_mutex_lock(&lecture);
    
    //Si le nombre d'élément est égale à la taille du tampon, on attends
    if(nbElements == 0){
        printf("Tampon vide\n");
        pthread_cond_wait(&consommerPossible, &vide);
    }
    printf("Lecture\n");
    //On change la valeur de la position de lecture
    if(posLecture < MAX - 1)
        posLecture++;
    else
        posLecture = 0;
    
    //sleep (1);
    
    pthread_mutex_lock(&varNb);
    nbElements--;
    pthread_mutex_unlock(&varNb);
    if(nbElements == (MAX - 1)){
       // printf("broadcast\n");
        pthread_cond_broadcast(&produirePossible);
    }
    //On débloque lecture pour permettre à un autre thread de lire
    pthread_mutex_unlock(&lecture);
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    int booleen = 1;
    pthread_mutex_unlock(&lecture);
    pthread_mutex_unlock(&ecriture);
    pthread_mutex_unlock(&plein);
    pthread_mutex_unlock(&vide);
    pthread_mutex_unlock(&varNb);
    
    pthread_t treahd[NBTEST];
    
    //pthread_attr_t attribut[NBTEST];a
    int a = 25;
    for(int i = 0; i < NBTEST; i++){
        if(booleen){
            //pthread_attr_init(&attribut[i]);
            pthread_create(&treahd[i], NULL, put, (void*)&a);
            sleep(0.5);
            if(booleen == 1) booleen++;
            else booleen = 0;
        }else{
            //pthread_attr_init(&attribut[i]);
            pthread_create(&treahd[i], NULL, get, NULL);
            sleep(0.5);
            booleen = 1;
        }
        
    }
    
    //On attend la fermeture de tous les threads avant de fermer
    for(int i = 0; i < 25; i++){
        pthread_join(treahd[i],NULL);
    }
    return 0;
}












