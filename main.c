#include "main.h";

int main()
{
    reader();
}

void copyArray(char *line, char buffer){
            printf("%s", line);

}


char ** reader()
{

    char ch;
    char buffer= malloc(sizeof(char) * 50960);
    // char line;
    int lineSize;

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

 while ((read = getline(&line, &len, stdin)) != -1) {
     if(read > 50960)
      fprintf( stderr, "Error: Line too long\n");
      
    printf("Retrieved line of length %zu :\n", read);
    // printf("%s", line);

    copyArray(line, buffer);


  }

    // do{
    //     if(lineSize>=50960){
    //         fprintf( stderr, "Error: Line too long\n");
    //         //TODO: flush until \n is found
    //     }

    //     ch=getc(stdin);
    //     // strcat(buffer,ch);
    //     // buffer[&buffer+ lineSize] = ch;

    //     append(buffer, ch, lineSize);

    //     lineSize++;
        
    //     if(ch == '\n'){
    //         printf("%s", buffer);

    //         line = malloc(sizeof(char)*lineSize);
    //         if(line == NULL){
    //             printf("%s\n", "Error: Bad Malloc");
	// 		    exit(-1);
    //         }
    //         // strcpy(line, buffer);
    //         copyArray(line, buffer, lineSize);

    //         //pass the string to the queue
    //         // EnqueueString(q1, buffer);

    //         lineSize=0;
    //         // buffer = NULL;
            
    //     } else{
            
        
    //     // printf("%c", ch);

    //     }

    // }while(ch != EOF);

    //remaining buffer should be added
    // free(buffer);
    // free(ch);

    return NULL;




}

