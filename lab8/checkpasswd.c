#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAX_PASSWORD 10 

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  char user_id[MAXLINE];
  char password[MAXLINE];
  int ret, stat;
  int fd[2];

  /* The user will type in a user name on one line followed by a password 
     on the next.
     DO NOT add any prompts.  The only output of this program will be one 
	 of the messages defined above.
   */

  if(fgets(user_id, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  if(fgets(password, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  
  // TODO
  if (pipe(fd) == -1){
    perror("pipe");
    exit(1);
  }
  ret = fork();
  if (ret < 0) {
      perror("fork");
      exit(1);
  } else if (ret == 0) { // child
    close(fd[1]);
    dup2(fd[0], fileno(stdin));
    close(fd[0]);
    //execl("./validate", "validate", NULL);
    execlp("./validate", "validate", NULL);
    perror("execl failed");
    exit(1);
  } else { // parent
      // To close the reading end of pipe
      close(fd[0]);
      write(fd[1], user_id, MAX_PASSWORD);
      write(fd[1], password, MAX_PASSWORD);
      wait(&stat);
      if(WIFEXITED(stat)){
        int returned = WEXITSTATUS(stat);
        if(returned == 0){
          printf("%s", SUCCESS);
        }
        else if (returned == 2){
          printf("%s", INVALID);
        }
        else if (returned == 3){
          printf("%s", NO_USER); 
        }
        else {
          printf("%s", "Unknown Error");
        }     
      }
    // close writing end of pipe
    close(fd[1]);
  }
  return 0;
}
