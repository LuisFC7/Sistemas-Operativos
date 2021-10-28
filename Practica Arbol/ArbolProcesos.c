#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void principal();
void Arbolprocesos();
void Hijo1(int niveles);
void Hijo2(int niveles);

int main (void) 
{ 
    principal();
    return 0; 
} 

void principal()
{
    Arbolprocesos();
}
void Arbolprocesos() 
{
  int pid;
  int flag = 0; 
  int niveles;
  int eleccion = 0; 
  int cont = 0;

  if (eleccion==0) 
  {
    printf ("\nNiveles: " );
    scanf ("%d", &niveles);
    eleccion++;
  } 

  for (cont=0 ; cont<2 ; cont++) 
  {
    pid = fork ();
    switch (pid) {
      case 0:
        if (cont==0) 
        {
            printf("\nHijo ID: %d, Padre ID: %d\n", getpid(),getppid());
            Hijo1(niveles);
        }
        if (cont==1) 
        { 
            printf("\nHijo ID: %d, Padre ID: %d\n", getpid(),getppid());
            Hijo2(niveles);
        }
        exit(0);
      case -1:
        printf("\n\tError");
        exit (0);
      default:
        if (cont==0) 
        {
          printf("\nPadre: %d.\n", getpid ());
        }
        wait(&flag);
    }
  }
  printf ( "\n\n" );
}

void Hijo1( int niveles) 
{
  int cont = 0;
  int bandera = 0;
  int pid;

  for (cont= 0 ; cont<2 ; cont++ ) 
  {
    pid=fork();
    switch (pid)
    {
      case 0:
        printf("\nHijo ID: %d, Padre ID: %d\n", getpid(),getppid());
        if (niveles>1)
        {
            Hijo1(niveles-1);
        }
        exit ( 0 );
      case -1:
        printf ( "\n\n\tError." );
        exit ( 0 );
      default:
        wait(&bandera);
    }
  }
}

void Hijo2(int niveles) 
{ 
  int cont = 0;
  int bandera = 0;
  int pid; 

  for (cont=0; cont<3; cont++) 
  {
    pid=fork ( );
    switch (pid) {
      case 0:
        printf("\nHijo ID: %d, Padre ID: %d\n", getpid(),getppid());
        if (niveles>1) 
        {
          Hijo2(niveles-1); 
        } 
        exit(0);
      case -1:
        printf ( "\n\n\tError" );
        exit(0);
      default:
        wait(&bandera);
        break;
    } 
  } 
} 
