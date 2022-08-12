#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define FALSE 0
#define TRUE 1  
#define N 2   //numero de threads


 int turn;    //de quem é a vez de executar
 int interested[N];   //Demonstrar interesse na zona critica
// ATENÇÃO COMPLIAR COMO: gcc -o main *.c -lpthread 
//Buffer compartilhado. O buffer representa as cadeiras da sala de cinema
int buffer[5]; // Cadeiras do cinema numeradas de 0 a 5


            // THREAD 1
void primeira_funcao(){ //Essa primeira thread vai entrar no sistema de reservas e selecionar os assentos que deseja.

  printf("%s\n", "pedindo permissao zona critica thread 1");
  turn =1; //diz para o controle que quer ter a vez na zona critica
  int process =1; //diz qual o ID do processo
  
  enter_region(process); //chamando função de controle da zona critica (MUTEX)
    
  printf("%s\n", "Zona critica permitida para thread 1");

  if(buffer[0] == 0){   //verifica se o asseto ja foi reservado
    buffer[0] = 123; //assento 0, usuario "123".
    printf("%d\n", buffer[0]);  //mostra o usuario que reservou o assento
    }
  else printf("Assentos nao disponiveis\n");
            

  if(buffer[1] == 0){             
    buffer[1] = 234; //assento 1, usuario "234"
    printf("%d\n", buffer[1]);
  }
  else printf("Assentos nao disponiveis\n");
            
            
  if(buffer[2] == 0){             
    buffer[2] = 345;
    printf("%d\n", buffer[2]);
  }
  else printf("Assentos nao disponiveis\n");
            
            
  if(buffer[3] == 0){
    buffer[3] = 456;
    printf("%d\n", buffer[3]);
  }
  else printf("Assentos nao disponiveis\n");
            
            
  if(buffer[4] == 0){
    buffer[4] = 567;
    printf("%d\n", buffer[4]);
  }
  else printf("Assentos nao disponiveis\n");
            

    
  printf("%s\n", "fim da execução da thread 1");

  leave_region( process);  //chama a função que libera o processo da zona critica
  printf("%s\n", "thread 1 deixou a zona critica");
}

            // THREAD 2
void segunda_funcao(void){ //Essa segunda thread vai entrar no sistema de reservas e selecionar os assentos que deseja.
  printf("%s\n", "pedindo permissao zona critica thread 2");
  turn=0;  //diz para o controle que quer ter a vez na zona critica
  int process=0;  //diz qual o ID do processo
  
  enter_region(process);  //chamando função de controle da zona critica (MUTEX)


  printf("%s\n", "Zona critica permitida para thread 2");  
  if( buffer[0]==0){
  buffer[0] = 876; //assento 0, usuario "876".
  printf("%d\n",buffer[0]);
  }
  else printf("Assentos nao disponiveis\n");
            
  if( buffer[1]==0){             
  buffer[1] = 765; //assento 1, usuario "765"
  printf("%d\n",buffer[1]);
  }
  else printf("Assentos nao disponiveis\n");
                      
  if( buffer[2]==0){             
  buffer[2] = 654;
  printf("%d\n",buffer[2]);
  }
  else printf("Assentos nao disponiveis\n");
                      
  if( buffer[3]==0){
  buffer[3] = 543;
  printf("%d\n",buffer[3]);
  }
  else printf("Assentos nao disponiveis\n");
                      
  if( buffer[4]==0){
  buffer[4] = 432;
  printf("%d\n",buffer[4]);
  }
  else printf("Assentos nao disponiveis\n");
       
  printf("%s\n", "fim da execução da thread 2");

  leave_region(process);  //chama a função que libera o processo da zona critica

  printf("%s\n", "thread 2 deixou a zona critica");
  
    
}

            //CONTROLE DA ZONA CRITICA
int enter_region(int process){    //processo 1 ou 0
  printf("%s\n", "CONTROLE DE ENTRADA PARA ZONA CRITICA");
  printf("processo : %d\n", process);
  int other;    //numero do outro processo
  other = 1 - process;    //oposto do processo
  interested[process] = TRUE;   //mostra que vc esta interessado
  turn = process;     //altera o valor de turn
  while(turn == process && interested[other]==TRUE){      //quando o processo esta na zona critica mas outro processo quer utilizar tbm a zona
    printf("%s\n", "Aguardando outro processo sair da zona critica");
  }
  printf("%s\n", "SAINDO DO CONTROLE DE ENTRADA PARA ZONA CRITICA");
}

            //AVISO DE SAIDA DA ZONA CRITICA
int leave_region(int process){    //processo que esta saindo da zona critica
  interested[process]=FALSE;    //indica a saida da regiao critica
}



int main(){
    
    
    
    pthread_t * thread_1, * thread_2, * thread_3; //declaração de dois ponteiros para threads.
    
    //agora, alocamos essas threads - por enquanto elas são apenas ponteiros
    thread_1 = (pthread_t *) malloc (sizeof(*thread_1));
    printf("%s\n", "chamando thread 1");
    thread_2 = (pthread_t *) malloc (sizeof(*thread_2));
    printf("%s\n", "chamando thread 2");
    thread_3 = (pthread_t *) malloc (sizeof(*thread_3));
    
    
    //Agora que elas estao criadas e alocadas, ja podemos utuliza-las.
    //Usamos essas funções para efetivamente iniciar a execução das threads.
    pthread_create (thread_1 , NULL, (void *) primeira_funcao, NULL);
    pthread_create (thread_2 , NULL, (void *) segunda_funcao, NULL);
    //pthread_create (thread_3 , NULL, (void *) imprime, NULL);
    
   
    getchar(); //nao sei pra que serve esse getchar, ms é apenas pro programa nao fzr num sei o que.
    return 0;
}
