#include "main.h";

int main()
{

    reader();
}

char ** reader()
{

    char ch;
    char buffer[50960];
 

    do{
        ch=getc(stdin);

        
        if(ch == '\n'){
            //add to array
            printf("%s", buffer);

        } else{
        strcat(buffer,ch);

        // printf("%c", ch);

        }

    }while(ch != EOF);

    //remaining buffer should be added

    return NULL;




}