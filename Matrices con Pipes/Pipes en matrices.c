#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void Multiplicacion(int**,int**,int**,int,int,int,int,int,int,int);
//int retornar(int **);

int main()
{
    srand (time(NULL));
    int **matA, **matB, **matC;
    int h, j, k; 
    int NFA, NCA, NFB, NCB, np, op, op2, i;
    int a, b;
    int pipe1[2];
    int pipe2[2];
    printf("\nIntroduzca el numero de procesos: \n");
    scanf("%i",& np);
    printf("Introduzca el numero de filas de la matriz A: \n");
    scanf("%i",& NFA);
    printf("Introduzca el numero de columnas de la matriz A: \n");
    scanf("%i",& NCA);
    printf("Introduzca el numero de filas de la matriz B: \n");
    scanf("%i",& NFB);
    printf("Introduzca el numero de columnas de la matriz B: \n");
    scanf("%i",& NCB);
    
    //validación de condiciones de programa
    if(NCA != NFB) 
    { 
	    printf("\nError en numero de filas y columnas.");  
	    exit(1);  
    }
    if(np > NFA)
    {
        printf("\nNumero de procesos debe ser menor o igual a filas.");  
	    exit(1);
    }

    matA=(int **) malloc(sizeof(int *)*NFA);  
    for(h=0; h<NFA; h++)
 	    matA[h]=(int *)malloc(sizeof(int)*NCA);
    
    matB=(int **) malloc(sizeof(int *)*NFB);
    for(h=0; h<NFB; h++)
 	    matB[h] = (int *)malloc(sizeof(int) * NCB);
        
    matC=(int **) malloc(sizeof(int *) * NFA);
    for(h=0; h<NFA; h++)  
 	    matC[h] = (int *)malloc(sizeof(int) * NCB);
    

    int numeros;

    //llenado de matrices
    for(h=0; h<NFA; h++)
    { 
	    for(j=0; j< NCA; j++)
        { 
            numeros = rand() % 5;
		    matA[h][j]= numeros;
	    } 
    }
    
    printf("\n\n Matriz A :\n");  
    for(h=0; h< NFA; h++)
    { 
	    printf("\n\t\t\t");

	    for(j=0; j < NCA; j++)
        { 	 
	       printf("%d\t", matA[h][j]);
        } 
    } 

    for(h=0; h<NFB; h++)
    {
	    for(j=0; j< NCB; j++){ 
            numeros = rand() % 5;
		    matB[h][j]= numeros; 
	    } 
    }

    printf("\n\n Matriz B :\n");  
    for(h=0; h< NFB; h++){ 
	    printf("\n\t\t\t");

	    for(j=0; j < NCB; j++){ 	 
	       printf("%d\t", matB[h][j]);
        } 
    } 

    op=(NFA/np);
    op2=NFA%np;

    int pid;//linea para padre e hijo

    for(int i = 0; i<np; i++)
    {
        if(i == (np-1)){
            b = i*op;
            a = ((i+1) * op);
            a += (op2-1);
            printf("\nProceso: %i\n", i+1);
            printf("%i a %i\n", b, a);

        }
        else{
            b = i*op;
            a = ((i+1) * op) - 1;
            printf("\nProceso: %i\n", i+1);
            printf("%i a %i\n", b, a);
        }
        pid=fork();
        if(pid<0){
            printf("Error...\n");
        }

        if(pid == 0){//hijo
            Multiplicacion(matA,matB,matC,a,NCA,NCB,h,j,k,b);
            close(pipe1[0]);//canal de lectura cerrado
            write(pipe1[1], &matC, sizeof(matC));
            printf("Parent(%d) \n", getpid());
            close(pipe1[1]);
            break;
        }

        if(pid > 0){//padre
            printf("Padre ID:%d\n", getpid());
            close(pipe1[1]);

            // now read the data (will block)
            read(pipe1[0], &matC, sizeof(matC));
            printf("Child(%d) \n", getpid());

            // close the read-descriptor
            close(pipe1[0]);
        }

    }

    for(i=0;i<np;i++)
        wait(NULL);

    for(h=0;h<NFA;h++)
        free(matA[h]);
    free(matA);

    for(h=0;h<NFB;h++)
        free(matB[h]);
    free(matB);

    for(h=0;h<NFA;h++)
        free(matC[h]);
    free(matC);

    return 0;
}

void Multiplicacion(int **matA, int **matB, int **matC, int a, int NCA, int NCB, int h, int j, int k, int b)
{
    printf("Hijo ID:%d\n", getpid());
    
    for(h=b; h < a+1; h++)
    { 
	    for(j=0; j < NCB; j++) 
	    { 
		    matC[h][j] = 0; 
 		    for(k=0; k<NCA; k++){
		        matC[h][j] = matC[h][j] + matA[h][k] * matB[k][j];
               
            } 
	    } 
    } 

    //retornar(matC);//aqui se retorna la matriz c

    printf("\n\n Resultado :\n");  
    for(h=b; h<a+1; h++)
    { 
	    printf("\n\t\t\t");
	    for(j=0; j < NCB; j++)
        { 	 
	       printf("%d\t", matC[h][j]);
        } 
    } 
    printf("\n\n");
}
