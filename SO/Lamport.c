#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include<time.h>
#include <conio.h>
#include<dos.h>
#include <stdlib.h>

int main()
{
	int cadeira[15];
	int usuario=0;
	
	int assento=0;
	int cs=0, prc=0;
	double run=5;
	char key='a';
	time_t t1,t2;

		for(int i=0; i<=15;i++){  //FOR para lipar o vetor
			cadeira[i]=0;
		
		}


	printf("Precione uma tecla para o processo entrar na zona critica\n");
	printf("\nPressione Q para sair\n");
	t1 = time(NULL) - 5;
	while (key !='q')
	{
	
	
		while(!kbhit())
			if(cs!=0)
			{
			t2 = time(NULL);
			if(t2-t1 > run)
			{
				//printf("Usuario %d", prc-1);
				printf("Usuario %d saiu da tela de reservas\n ", usuario);
				
				cs=0;
				printf("\n\n\\\\\\\\\\\\\\   Cadeiras disponiveis   \\\\\\\\\\\\ \n\n"); //FOR para mostrar as cadeiras disponiveis
				for(int i=0; i<=15;i++){
				printf("Cadeira %d - Usuario:%d \n ", i,cadeira[i]);
				}
				
			}
	}
	key = getch();
	if(key!='q')
	{
	if(cs!=0)
		printf("outro usuario ainda esta escolhendo os assentos\n");
	else
	{	//ZONA CRITICA
		srand(time(NULL));
		usuario = rand();	//seleciona uma ID de usuario
		printf("\nUsuario %d esta escolhendo seus assentos na sala\n", usuario);
		
		cs=1;
		prc++;
	
		
		
		for(int i=1; i<=3;i++){
			
			
			assento = rand() % 15;
			
			if(cadeira[assento] == 0){ // verifica se tem usuario pra esse assento, se nao tiver ele executa
				cadeira[assento]=usuario;
				printf(" Cadeira %d reservada por usuario:%d \n",assento, cadeira[assento]); 
				
				
			}
			else{
				printf("CADEIRA %d NAO DISPONIVEL \n", assento);
				
			}
		}
		
		
		
		t1 = time(NULL);
		//FIM DA ZONA CRITICA
	}
}
}
}

