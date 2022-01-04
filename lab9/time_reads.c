/* The purpose of this program is to practice writing signal handling
 * functions and observing the behaviour of signals.
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>

/* Message to print in the signal handling function. */
#define MESSAGE "%ld reads were done in %ld seconds.\n"

/* Global variables to store number of read operations and seconds elapsed. 
 */
long num_reads, seconds;


/* The first command-line argument is the number of seconds to set a timer to run.
 * The second argument is the name of a binary file containing 100 ints.
 * Assume both of these arguments are correct.
 */
void handler(int sig) {
  fprintf(stdout, MESSAGE, num_reads, seconds);
  exit(0);
}

unsigned int alarm (unsigned int seconds){
  struct itimerval old, new;
  new.it_interval.tv_usec = 0;
  new.it_interval.tv_sec = 0;
  new.it_value.tv_usec = 0;
  new.it_value.tv_sec = (long int) seconds;
  if (setitimer (ITIMER_REAL, &new, &old) < 0)
    return 0;
  else
    return old.it_value.tv_sec;
}

int main(int argc, char **argv) {
  if (argc != 3) {
      fprintf(stderr, "Usage: time_reads s filename\n");
      exit(1);
  }
  seconds = strtol(argv[1], NULL, 10);

  struct sigaction act;
  act.sa_handler = handler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  //sigaction(SIGPROF,&act,NULL);
  sigaction(SIGALRM,&act,NULL);

  /* Set an alarm to go off in a little while. */
  alarm (seconds);

  FILE *fp;
  if ((fp = fopen(argv[2], "r")) == NULL) {
    perror("fopen");
    exit(1);
  }

  /* In an infinite loop, read an int from a random location in the file,
    * and print it to stderr.
    */
  srand(time(NULL));
  for (;;) {
    int value;
    int random_number = rand() % 99;
    fseek(fp, random_number * sizeof(int), SEEK_SET);
    fread(&value, sizeof(int), 1, fp);
    num_reads++;
    printf("%d\n", value);
  }
  fclose(fp);
  return 1; // something is wrong if we ever get here!
}
