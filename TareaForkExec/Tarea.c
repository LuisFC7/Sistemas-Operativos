#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void principal();

int main(void)
{
    principal();
    system("pause");
    return 0;
}


void principal()
{
    pid_t pid;
    int cont=0;
    for(int i=0; i<2; i++)
    {
        pid=fork();
        if(pid<0){
            fprintf(stderr,"Error\n");
            exit(-1);
        } if(pid==0)
        {
            printf("\nHijo ID: %d, Padre ID: %d", getpid(),getppid());
            for(int j=0; j<1; j++)
            {
                pid=fork();
                if(pid!=0)
                {
                    printf("\nPadre ID: %d, Hijo ID: %d", getpid(),pid);
                    break;
                }
            }
            break;
        }
    }

    for(int k=1;k<4; k++)
    {
        wait(NULL);
    }

}