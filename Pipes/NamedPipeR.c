#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

//PROCESS READER
void principal();

int main(void)
{
	principal();
	return 0;
}

void principal()
{
	int des, nbytes;
	char tam[50];
	des=open("/tmp/Fifo", O_RDONLY);
	nbytes=read(des,tam,sizeof(tam));
	printf("\nMensaje leído por proceso 2: %s",tam);
	printf("\nNumero de bytes: %d\n",nbytes);
	close(des);
}
