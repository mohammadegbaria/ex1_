#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <AsciiArtTool.h>
#include <RLEList.h>

void encode(FILE* input, FILE* output)
{
   RLEList List = asciiArtRead(input);
   asciiArtPrintEncoded(List, output);
}
void invert(FILE* input, FILE* output)
{
   RLEList list = asciiArtRead(input);
   RLEListMap(list, MapFunction);
}
char MapFunction(char c)
{
    if(c==' ')
       return '@';
    if (c=='@')
       return ' ';
return c ;   
}
void error(char* message, char* filename)
{
  fprintf(stderr,"%s %s\n", message, filename ? filename : "");
    
}
FILE* initInputFile(int argc, char** argv) {
	if (argc < 3) {
		return stdin;
	}

	return fopen(argv[2], "r");
}

FILE* initOutputFile(int argc, char** argv) {
	if (argc < 3) {
		return stdout;
	}

	return fopen(argv[3], "w");
}
int main(int argc,char** argv){
if(argc>4)
  error("Usage: copy <file1> <file2>",NULL);
 FILE* input=initInputFile(argc,argv); 
 if (!input)
 {
     error("Error: cannot open", argv[1]);
 }
 FILE* output=initInputFile(argc,argv); 
 if (!output)
 {
     error("Error: cannot open", argv[2]);
 }
if(strcmp(argv[1],"-e")==0)
   encode(argv[2], argv[3]);
if(strcmp(argv[1],"-i")==0)
   invert(argv[2], argv[3]);
fclose(input);
fclose(output);
}