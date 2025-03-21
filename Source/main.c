
#include <stdio.h>
#include <omp.h>

int main(int argc, const char * argv[]) {
    int id_thread, N, beta, numT, *a,i,findIndex=0;
    double t0,t1,t;
    
    //controllo N Threads dati in input
    if(argc >1 && atoi(argv[1])) {
        numT = atoi(argv[1]);
    } else {
        printf("ERROR, numero Threads assente o errato, shutdwon \n");
        exit(EXIT_FAILURE);
    }
    
    N=0;
    //Lettura dati input
    do {
    printf("\n Inserire il size dell vettore A \n :");
    scanf("%d",&N);
        if (N==0) {
            printf("\n Attenzione!, size del vettore A nullo, riprovare");
        }
    } while (N==0);
    
    a=(int*)calloc(N*sizeof(int));
    
    //Lettura vettore A
    printf("\n Inserire i numeri all'interno del vettore A \n");
    for(i=0; i < N; i++) {
        scanf("%d",&a[i]);
    }
    
     //Lettore scalare Beta
    do {
        printf("\n Inserire valore di Beta \n");
        scanf("%d",&beta);
        if(beta<0){
            printf("\n Attenzione!, valore di Beta minore di 0, riprovare");
        }
    } while (beta<0);

     //prima che avviene la parallelizazione
    t0=omp_get_wtime();
    printf("\n\n");

    printf("\n Inizio Paralellizazione su %d threads \n",numT);
    #pragma omp parallel for schedule(static) shared(N,a,beta,findIndex) private(i) num_threads(numT)
    for (i=0; i<N; i++) {
        if (a[i]==beta){
           #pragma omp atomic update
                findIndex=findIndex+1;
        }
        printf("\n sono il Thread %d, findIndex = %d \n",omp_get_thread_num(),findIndex);
      }
        

    //Seconda chiamata
    t1=omp_get_wtime();
    t=t1-t0;
    
    //Stampa risultato
    printf("\n Sono stati necessari %lf secondi per la ricerca \n",t);
    printf("\n lo scalare beta: %d, é stato trovato %d volte nel vettore a \n",beta,findIndex);
    
    //Free
    free(a);
    return 0;
}
