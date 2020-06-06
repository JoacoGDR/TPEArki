#include "shell.h"



#define SCREEN_LIMIT 120


int screen_width;
int screen_height;
char buffer[SCREEN_LIMIT] = {'\0'};
int buffer_size = 0;


int strcmp();
char getChar();
void putChar(char * c);

//son del libasm
void get_temp();
void printmem(int address);
void inforeg();
void printHexa(unsigned char h);
int getArgument();
int hexaString_to_int(char* str);
extern void execute_opcode();


void start_shell(/*int width, int height*/){
    //screen_width = width;
   // screen_height = height;
    
    syscall_write(">>");

    shell_main();

}

void shell_main(){
	char * c;
	while(1){
		//syscall_write(getChar());
	    c = getChar();
		if(c != -1){
            if(c == '\b'){
                if(buffer_size != 0){
                    buffer[buffer_size] = '\0';
                    buffer_size--;   
                     putChar(&c);

                }
            }
            else if(c=='\n'){
            
                buffer[buffer_size] = '\0';
                
                putChar(&c); //tiro un enter y despues me fijo de printear lo que sigue, pasaba que ponia todo junto y despues largaba un enter.

                //los commands se guardan en un arreglo, entonces nos devuelve la posicion de dicho command QUE QUERES?!
                int command = getCommand();
                if(command != -1){
                    executeCommand(command);
                    
                }else
                {
                    syscall_write("Command not found\n");
                }
                buffer_size = 0; 
                 syscall_write(">>");
                
                
            }
            else if(buffer_size < SCREEN_LIMIT){
                buffer[buffer_size] = c;
                buffer_size++;
                 putChar(&c);
            }
            //putChar(&c); este no lo uso y lo pongo en todos salvo el enter por que? -> porque sino cuando hago un enter, me lo tira y el ">>" queda volando y ta todo mal.
           
        }
 
    }
}

int getCommand(){
    for(int i = 0; i < NUMBER_OF_COMMANDS; i++){
        if(strcmp(commands[i], buffer) == 1) {
            return i;
        }
    }
    return -1;
    }



//retorna 1 si son iguales
int strcmp(char * str1, char*str2){
    int i= 0;
    for(i; str1[i] || str2[i] ; i++){
        if(str1[i] == 0 && str2[i] == ' ')
            return 1;
        if(str1[i] != str2[i])
            return 0;
    }


    if(str1[i] != str2[i])
        return 0;

    return 1;
}



void executeCommand(int id){
    int c;
    switch(id){
        case 0:
            inforeg();
            break;
        case 1:
            syscall_write("");
            int arg = getArgument();
            printmem(arg);
            syscall_write("\n");
            break;
        case 2:
            help();
            break;
        case 3:
            c = 5/0; //intento dividir por 0
            break;
        case 4:
           execute_opcode();
           break;
    }
}

void help(){
    for(int i = 0; i < NUMBER_OF_COMMANDS; i++){
        syscall_write(commands[i]);
        syscall_write(descriptions[i]);
        putChar("\n");
    }
}

int getArgument(){
    int i = 0;
    for(i ; buffer[i] != ' ' ; i++);
    for(i ; buffer[i] == ' ' ; i++);
    return hexaString_to_int(buffer + i);
}


int hexaString_to_int(char* str)
{
    // Initialize result
    int res = 0;

    // Iterate through all characters
    // of input string and update result
    for (int i = 0; str[i] != '\0'; ++i){
        if(str[i] >= 'A' && str[i] <= 'F'){
            res = res * 16 + str[i] - 'A' + 10;
        }
        else if(str[i] >= 'a' && str[i] <= 'f'){
            res = res * 16 + str[i] - 'a' + 10;
        }
        else
            res = res * 16 + str[i] - '0';
    }

    // return result.
    return res;
}

void printmem(int address){

    unsigned char * mem = address;
     for(int i=0;i<32;i++){
         printHexa( mem[i]);
     }
}

void printHexa(unsigned char hexa){
    //Cada char deberia imprimir 2 digitos hex
    unsigned char resp[3];
    resp[0] = (hexa/16);
    resp[1] = (hexa%16);
    resp[2] = 0;
    for(int i = 0; i<2; i++){
        if(resp[i]< 10){
            resp[i]+='0';}
        else{
            resp[i]+='A' - 10;
         }
     }
     syscall_write(resp);
    
    
}




/*
int getArgument(){
    while(1){
        char c = getChar();
        if(c != -1){
            if(c == '\b'){
                if(buffer_size != 0){
                    buffer[buffer_size] = '\0';
                    buffer_size--;   
                     putChar(&c);

                }
            }
            else if(c=='\n'){
                                                                //si no es una direccion válida entonces error
                return stringToNum(buffer);
            }
            else if(buffer_size < SCREEN_LIMIT){
                buffer[buffer_size] = c;
                buffer_size++;
                 putChar(&c);
            }

        }
    }
    
}
*/

