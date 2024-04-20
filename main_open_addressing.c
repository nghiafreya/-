#include <stdio.h>
#include <stdlib.h>
#include "open_addressing.h"
#include <time.h>
#include <sys/time.h>

int main(void) {
  DictOpenAddr *test_dict = create_dict(10000);
  
  const char *filename = "number.txt";
  char line[100]; // Assuming each line has at most 100 characters
  FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

   struct timeval start, end;
   gettimeofday(&start, NULL);
   int linesRead = 0;
  
    while (fgets(line, sizeof(line), file) != NULL) {
        int num = atoi(line); // Convert the line to an integer
        insert_hash(test_dict, num);
        
        linesRead++;
        
	    if (linesRead % 1000 == 0) { //to get the time when 10%, 20%, 30%, etc amount of work is done
	      gettimeofday(&end, NULL);
	      double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
	      printf("\nAfter %d: ,time %lf[sec]\n", linesRead, elapsed_time);
	    }
    }

    fclose(file);
    
  gettimeofday(&end, NULL);
  
  double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

  
  delete_dict(test_dict);

  return EXIT_SUCCESS;
}