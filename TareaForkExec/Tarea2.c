#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
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
    char *const argv2[]={"Process",NULL};
    for(int i=0; i<2; i++)
    {
        pid =fork();
        if(pid<0)
        {
            fprintf(stderr,"Error\n");
            exit(-1);
        }
        if(pid==0)
        {
            printf("\nHijo ID: %d, Padre ID: %d\n",getpid(),getppid());
            execv("./Procesos",argv2);
            break;
        }
        else
        {
            printf("\nPadre ID: %d, Hijo ID: %d\n",getpid(),pid);
        }

    }
    for(int i=1; i<4; i++)
    {
        wait(NULL);
    }
    
}
