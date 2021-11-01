//named pipe
//this is the process writer
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

void principal();

int main(void)
{	//creacion de proceso externo 1
	principal();
	return 0;
}

void principal()
{
	int des;//aqui no se declara como array
	char message[]="Procesos externos";
	
	//creacion de FIFO
	mkfifo("/tmp/Fifo",0666);//0666=permisos en octal esc y lect
	des =open("/tmp/Fifo", O_WRONLY);
	write(des,message,sizeof(message));
	close(des);
}
