#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void principal();

int main(void)
{
	principal();
	return 0;
}

void principal()
{
	int des[2];//descriptor de dos argumentos para pipe
	int pid;
	int nbytes;
	char *message="Cadena de lectura";
	char tam[50];
	
	//declaracion de pipe
	pipe(des);
	pid=fork();
	
	//comprobacion de fork
	switch(pid)
	{
		case 0:
			close(des[0]);
			write(des[1],message,strlen(message+1));//17=tamaño de cadena
			close(des[1]);
			exit(0);
			break;
		case -1:
			printf("\nError\n");
			break;
		default:
			close(des[1]);
			nbytes=read(des[0],tam,sizeof(tam));
			printf("Lectura en proceso padre: %s \n",message);
			printf("Bytes leidos:%d \n",nbytes);
			close(des[0]);
			break;
	}	
}
