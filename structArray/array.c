//I need to finish complement
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int table[1000001];

int main() {
    FILE *inputFile,*output;
    inputFile = fopen("../Input.txt", "r");
    output = fopen("./output.txt","w+");
    char command;
    int i, num, input, complement;

	for(i = 0; i < 1000001; i++) {
		table[i] = 0;
	}
    command = getc(inputFile);
    while(command != EOF) {
        if(command == 'I') {
            fscanf(inputFile,"(%d",&input);
            fprintf(output,"i ");
            table[input]++;
        }
        else if(command == 'D') {
            fscanf(inputFile,"(%d",&input);
            fprintf(output,"d ");
			if(table[input] > 0) table[input]--;
			else; 
        }
        else if(command == 'M') {
            fscanf(inputFile,"(%d",&input);
            if(table[input] > 0) fprintf(output,"yes ");
            else fprintf(output,"no ");
        }
        else if(command == 'S') {
            fscanf(inputFile,"(%d",&input);
            int result = 0;
            for(i = 1; i < input; i++){
                complement = input - i;
				if(table[complement] != 0 && table[i] != 0) {
					fprintf(output,"yes ");
					result = 1;
					break;
				}
            }
            if(result == 0) fprintf(output,"no ");
        }
        else if(command == 'C') {
            fscanf(inputFile, "(%d", &input);
            fprintf(output,"%d ",table[input]);
        }
        command = getc(inputFile);
    }
}

