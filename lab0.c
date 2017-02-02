#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <getopt.h>

//#define BUFFERSIZE 1048576
#define BUFFERSIZE 8000000
void print(int signum)
{
  fprintf(stderr,"Segmentation fault occured \n");
  exit(3);
}

int main(int argc, char **argv){
  
  int i;
  char* inputfile;
  char* outputfile;
  int ifile=0;
  int ofile=0;
  int seg = 0;
  int catch=0;
  int opt=0;
  int longIndex=0;
  static const char *optString = "iosc";
  static struct option long_options[] = {
    {"input", required_argument, NULL, 'i'},
    {"output", required_argument, NULL,'o'},
    {"segfault", no_argument, NULL, 's'},
    {"catch", no_argument,NULL, 'c'},
    {NULL, no_argument, NULL, 0}
  };
  opt = getopt_long( argc, argv, optString, long_options, &longIndex );
  while( opt != -1 ) {
    switch( opt ) {
    case 'i':
      inputfile = optarg; 
      ifile=1;
      break;
    case 'o':
      outputfile  = optarg;
      ofile=1;
      break;
    case 's':
      seg=1;
      break;
    case 'c':
      catch=1;
      break;
    default:
   /* You won't actually get here. */
      exit(4);
      break;
    }

    opt = getopt_long( argc, argv, optString, long_options, &longIndex );
  }
  // if(ifile==1){
    // printf("%s\n",inputfile);
  // printf("%d\n", ifile);
    // }
  // if(ofile==1){
    // printf("%s\n",outputfile);
    // }
  //printf("%d\n", ofile);
  // printf("%d\n", seg);
  // printf("%d\n", catch);
  if (catch==1){
    signal(SIGSEGV,print);

  }
  if(seg==1){
    // memset((char *)0x0, 1, 100);
    const char *s = NULL;
    printf( "%c\n", s[0] );
  }
  if(ofile==1 && ifile==1){

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
  }
  else if(ifile==1 && ofile==0){
    close(STDIN_FILENO);
  }
  else if(ifile==0 && ofile==1){
    close(STDOUT_FILENO);
  }
  else{
  }
  int inputfiledescriptor, outputfiledescriptor;
  ssize_t inputreturnbytes, outputreturnbytes;
  char buffer[BUFFERSIZE];

  if(ifile==1){
    inputfiledescriptor = open (inputfile, O_RDONLY);
    //printf("%d\n", input_fd);
    if (inputfiledescriptor == -1) {
      perror ("Opening Input File");
      fprintf(stderr,"Cannot open input file \n");
      exit(1);
    }
  }
  else{
    inputfiledescriptor=STDIN_FILENO;
  }

  if(ofile==1){
    // if(access(outputfile, F_OK)!= -1){
    // perror("File already exists");
    // fprintf(stderr,"File already exists \n");
    // exit(2);
    // }
    outputfiledescriptor = open(outputfile, O_WRONLY | O_CREAT| O_TRUNC, 0644);
    //printf("%d\n", output_fd);
    if(outputfiledescriptor == -1){
      perror("Creating Output File");
      fprintf(stderr,"Cannot create output File \n");
      exit(2);
    }
  }
  else{
    outputfiledescriptor=STDOUT_FILENO;
  }

  /* Copy process */
  while((inputreturnbytes = read (inputfiledescriptor, &buffer, BUFFERSIZE)) >	0){
    outputreturnbytes = write (outputfiledescriptor, &buffer, (ssize_t) inputreturnbytes);
    if(outputreturnbytes != inputreturnbytes){
      /* Write error */
      perror("write");
      exit(4);
    }
  }
  /* Close file descriptors */
  close (inputfiledescriptor);
  close (outputfiledescriptor);

  exit(0);
  
  
}
