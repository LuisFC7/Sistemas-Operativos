#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int Padre[2]={0,1};
int Hijo[2]={0,1};
int ID;
int cadena;
char *mensaje;


int main ( ) {

  pipe(Padre);
  pipe(Hijo);

  mensaje=(char*)malloc(sizeof(char));

  ID=fork();

  do
  {
    if(ID!=-1 && ID!=0)
    { 
      read (Hijo[1], mensaje, cadena); 
      close (Hijo[1]);
      close (Padre[1]);

      printf( "\n%sPadre: ", mensaje);
      scanf("%s", mensaje);

      cadena=strlen(mensaje);

      write(Padre[0], mensaje, cadena); 
      close(Padre[0]); 

    } 

    if (ID== 0)
    { 

      read(Padre[1], mensaje, cadena);
      close(Padre[1]);
      close(Hijo[1]);

      printf("\n%sHijo: ", mensaje);
      scanf("%s",mensaje);

      cadena=strlen(mensaje);

      write(Hijo[0], mensaje,cadena);
      close(Hijo[0]); 

      if (!strcmp(mensaje, "fin")) 
      { 
          exit (0); 
      } 

    }

  } while(strcmp(mensaje, "fin"));

  if (ID==-1 )
  {
    printf ( "\n\n\tError..." );

  } 

}