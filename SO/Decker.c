#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>



// ATENÇÃO COMPLIAR COMO: gcc -o main *.c -lpthread 

pthread_mutex_t mutex; //declarando um mutex

//Buffer compartilhado. O buffer representa as cadeiras da sala de cinema
int buffer[5]; // Cadeiras do cinema numeradas de 0 a 5


// Primeira Função
void primeira_funcao(){ //Essa primeira thread vai entrar no sistema de reservas e selecionar os assentos que deseja.
    
    while(true){
        while(turn!=0){
            //pthread_mutex_lock(&mutex); //tentando o lock sobre o buffer
        
            buffer[0] = 123; //assento 0, usuario "123".
            //sleep(1); 
        
            buffer[1] = 234; //assento 1, usuario "234"
            //sleep(1);
            
            buffer[2] = 345;
            //sleep(1);
            
            buffer[3] = 456;
            //sleep(1);
            
            buffer[4] = 567;
            //sleep(1);
        
            turn=1;
            //pthread_mutex_unlock(&mutex); //saindo do buffer
            //sleep(1);
        }
    }
}

void segunda_funcao(){ //Essa segunda thread vai entrar no sistema de reservas e selecionar os assentos que deseja.
    
    while(1){
       
        pthread_mutex_lock(&mutex);  //tentando o lock sobre o buffer
    
        buffer[0] = 876;
        //sleep(1); 
        
        buffer[1] = 765;
        //sleep(1);
        
        buffer[2] = 654;
        //sleep(1);
        
        buffer[3] = 543;
        //sleep(1);
        
        buffer[4] = 432; 
        //sleep(1);
    
        
        pthread_mutex_unlock(&mutex); //saindo do buffer
        //sleep(1);
    }
}

void imprime(){ //Essa thread vai imprimir o que tiver dentro do buffer, ou seja, imprime o resultado final das reservas de cada assento da sala.
    
   
    
    pthread_mutex_lock(&mutex); //tentando o lock sobre o buffer
    
    for(int c=0;c <= 5; c++){ //função para imprimir todos os assentos
        printf("%d\n",buffer[c]);
    }
    
    pthread_mutex_unlock(&mutex);    //saindo do buffer
        sleep(1);
    

    
}
int main()
{
    
    pthread_mutex_init (&mutex , NULL);   //inicializando o mutex
    
    
    pthread_t * thread_1, * thread_2, * thread_3; //declaração de dois ponteiros para threads.
    
    //agora, alocamos essas threads - por enquanto elas são apenas ponteiros
    thread_1 = (pthread_t *) malloc (sizeof(*thread_1));
    thread_2 = (pthread_t *) malloc (sizeof(*thread_2));
    thread_3 = (pthread_t *) malloc (sizeof(*thread_3));
    
    //Agora que elas estao criadas e alocadas, ja podemos utuliza-las.
    //Usamos essas funções para efetivamente iniciar a execução das threads.
    pthread_create ( thread_1 , NULL, (void *) primeira_funcao, NULL);
    pthread_create (thread_2 , NULL, (void *) segunda_funcao, NULL);
    pthread_create (thread_3 , NULL, (void *) imprime, NULL);
    
   
    getchar(); //nao sei pra que serve esse getchar, ms é apenas pro programa nao fzr num sei o que.
    return 0;
}
