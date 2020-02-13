#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#define MAX_CMD_ARG 10
#define BUFSIZ 256

const char *prompt = "myshell> ";
char* cmdvector[MAX_CMD_ARG];
char  cmdline[BUFSIZ];

int pipe_function(char **cmd)
{
  int i;
  int k =0;
  pid_t pid1;
  pid_t pid2;
  int fd[2];
  char **cmdvectorpipe1;
  char **cmdvectorpipe2;
  int redI = 0;
  int redO = 0;

  for(int count = 0; cmd[count] != NULL; count++)
  {
      if(strcmp(cmd[count], ">"))
      {
        redO = 1;
      }

      else if(strcmp(cmd[count], "<"))
      {
        redI = 1;
      }
  }

  for(i = 0; cmd[i] != NULL; i++)
  {
    if(!strcmp(cmd[i], "|"))
    {
      cmdvectorpipe1[i] = NULL;
      break;
    }
    cmdvectorpipe1[i] = cmd[i];

  }

  for(i = i+1; cmdvector[i] != NULL; i++)
  {
    cmdvectorpipe2[k] = cmd[i];
    k++;

  }

  pipe(fd);

  pid1 = fork();

  switch(pid1)
  {
    case -1:
      perror("Fork error");
      break;

    case 0:
      if(redI)
      {
        redirection_in(cmdvectorpipe1);
      }

      dup2(fd[1], STDOUT_FILENO);
      close(fd[1]);
      close(fd[0]);
        execvp(cmdvectorpipe1[0], cmdvectorpipe1);
      exit(0);
  }

  pid2 = fork();

  switch(pid2)
  {
    case -1:
      perror("Fork error");
      break;

    case 0:
      if(redO)
      {
        redirection_out(cmdvectorpipe2);
      }

      dup2(fd[1], STDOUT_FILENO);
      close(fd[1]);
      close(fd[0]);
        execvp(cmdvectorpipe2[0], cmdvectorpipe2);
      exit(0);
  }

}


void fatal(char *str)
{
  perror(str);
  exit(1);
}

int redirection_out(char **argv)
{
    int i;
    int fd;

    for(i = 0; argv[i] != NULL; i++)
    {
      if(!strcmp(argv[i], ">"))
      {
        break;
      }
    }

    if(argv[i])
    {
      if(!argv[i+1])
        {
           return -1;
        }

        else
        {
          if((fd = open(argv[i+1], O_RDWR | O_CREAT | S_IROTH, 0644)) == -1)
          {
            perror(argv[i+1]);
            return -1;
          }
        }

        dup2(fd, STDOUT_FILENO);
        close(fd);
        argv[i] = NULL;
        argv[i+1] = NULL;
        for(i = i; argv[i] != NULL; i++)
        {
          argv[i] = argv[i+2];
        }

        argv[i] =NULL;
    }
    return 0;


}

int redirection_in(char** argv)
{
  int i;
  int fd;

  for(i = 0; argv[i] != NULL; i++)
  {
    if(!strcmp(argv[i], "<"))
    {
      break;
    }
  }

  if(argv[i])
  {
    if(!argv[i])
    {
      return -1;
    }

    else
    {
      if((fd = open(argv[i+1], O_RDONLY)) == -1)
      {
        perror(argv[i+1]);
        return -1;
      }
    }

    dup2(fd, STDIN_FILENO);
    close(fd);

    for(i = i; argv[i] != NULL; i++)
    {
      argv[i] = argv[i+2];
    }

    argv[i] = NULL;
  }

  return 0;
}



int background_check(int argc,char* argv[]) //background 모드를 체크 해주는 함수
{
    for(int i =0; i <argc; i++)
    {
      if(strcmp("&", cmdvector[i]) == 0)
      {
        return 1; //문자에 &가 존재하면 1을 return 한다.
      }
    }

    return 0;
}


void cd_function( int argc, char* argv[]){ //cd 함수

    if( argc == 1 )
    {
        chdir( getenv( "HOME" ) );
    }

    else if( argc == 2 )
    {
       if(chdir(argv[1]))
       {
          printf( "No directory\n" );
       }
    }

    else
    {
      printf("USAGE: cd [dir]\n");
    }
    
}


int makelist(char *s, const char *delimiters, char** list, int MAX_LIST)
{ 


  int i = 0;
  int numtokens = 0;
  char *snew = NULL;

  if( (s==NULL) || (delimiters==NULL) )
{
    return -1;
  }

  snew = s + strspn(s, delimiters); /* Skip delimiters */
  if( (list[numtokens]=strtok(snew, delimiters)) == NULL )
    {
    return numtokens;}
  
  numtokens = 1;
  
  while(1){

     if( (list[numtokens]=strtok(NULL, delimiters)) == NULL)
  break;
     if(numtokens == (MAX_LIST-1)) return -1;
     numtokens++;
  }

  return numtokens;

}



int main(int argc, char**argv)
{
  int i=0;
  pid_t pid;
  int number = 0;
  int background_check_num = 0;


  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);

  while (1)
  {
    fputs(prompt, stdout);
    fgets(cmdline, BUFSIZ, stdin);

   
    
    cmdline[strlen(cmdline) -1] = '\0';

    number = makelist(cmdline, " \t", cmdvector, MAX_CMD_ARG);


    if(cmdvector[0] != 0 && strcmp("exit", cmdvector[0]) == 0)
        {
          exit(0);
        }

      

    switch(pid=fork())
    {
      case 0:

        signal(SIGINT, SIGKILL);
        signal(SIGQUIT, SIGKILL);
        signal(SIGTSTP, SIGKILL);

        background_check_num = background_check(number, cmdvector); //0이면 fore, 1이면 back
        

        redirection_out(cmdvector);
        redirection_in(cmdvector);

        /*for(int i =0; cmdvector[i] != NULL; i++)
        {
            if(strcmp("|", cmdvector[i]))
            {
               pipe_function(cmdvector);
               break;
            }
        }*/
       

        if(strcmp("cd", cmdvector[0]) == 0)
        {
       
          cd_function(number, cmdvector);
        }


        if (background_check_num)
        {
      
          background_check_num = 0;
          break;
        }

        if(cmdvector[0] != 0 && strcmp("exit", cmdvector[0]) == 0)
        {
          exit(0);
        }


        else
        {
         execvp(cmdvector[0], cmdvector);
          
        }
        
      default:
            wait(NULL);
    }
  

  
  }

  
  return 0;

}