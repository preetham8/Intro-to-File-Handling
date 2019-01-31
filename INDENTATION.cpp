#include<stdio.h>
#include<string.h>
#include<malloc.h>

int main()
{
	int counter=0,index,indent,index1=0; //initialized all variables
	char *c,*d; //input and output strings
	long numbytes; //size of input file
	
	FILE *fptr; //input file pointer
	FILE *fptr1; //output file pointer

	fptr=fopen("testfile.cpp","r"); //input file opened in read mode
	fptr1=fopen("output.txt","w"); //output file opened in write mode
	
	if(fptr==NULL || fptr1==NULL) //checking unable to open file
		printf("File could not be opened.\n");
		
	fseek(fptr,0L,SEEK_END); 
	numbytes=ftell(fptr); //finding size of input file
	fseek(fptr,0L,SEEK_SET); //resetting pointer to start of file
	
	c=(char*)calloc(numbytes,sizeof(char)); //initialize input string
	d=(char*)calloc(numbytes+1000,sizeof(char)); //initialize output string
	
	fread(c,sizeof(char),numbytes,fptr); //copying input file to input string for processing
	
	for(index=0;c[index]!='\0';index++)
	{
		
		d[index1++]=c[index]; //copying from input to output string
		if(c[index]=='{' && (c[index-1]!='\'' && c[index+1]!='\'')) //checking for closing { even if code contains it in ''
			counter++;
		if(c[index+1]=='}' && (c[index-1]!='\'' && c[index+1]!='\'')) //checking for closing } even if code contains it in ''
			counter--;
		if(c[index]=='\n') //making indents
			for(indent=0;indent<counter;indent++)
				d[index1++]='	';
	}
	d[index1]='\0'; //output file EOF
	fputs(d,fptr1); //writing to output file
	fclose(fptr); //close input file
	fclose(fptr1); //close output file
	free(c);
	free(d);
	return 0;
}
