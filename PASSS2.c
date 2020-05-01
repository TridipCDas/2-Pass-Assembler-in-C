#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
main(){
char label[10],opcode[10],operand[10],loc[10],op1[10],op2[10],loc1[10],loc2[10];
int convert,l,i;
FILE *fp,*fp1,*fp2,*fp3;
fp=fopen("inter.txt","r");
fp1=fopen("OPCODE.txt","r");
fp2=fopen("P2file.txt","w");
fp3=fopen("symtabl.txt","r");

fscanf(fp,"%s%s%s%s",loc,label,opcode,operand);

fprintf(fp2,"%s\t%s\t%s\t%s\n",loc,label,opcode,operand);

while(!feof(fp)){
fscanf(fp,"%s%s%s%s",loc,label,opcode,operand);

if((strcmp(opcode,"RSUB"))==0){
fprintf(fp2,"%s\t%s\t%s\t%s\t\t4C0000\n",loc,label,opcode,operand);
}

else if(((strcmp(opcode,"RESW"))==0) || ((strcmp(opcode,"RESB"))==0)){
   fprintf(fp2,"%s\t%s\t%s\t%s\n",loc,label,opcode,operand);
}

else if((strcmp(opcode,"WORD"))==0){
//Needs some changed
convert=atoi(operand);
fprintf(fp2,"%s\t%s\t%s\t%s\t\t%.6X\n",loc,label,opcode,operand,convert);
}

else if((strcmp(opcode,"BYTE"))==0){
        l=strlen(operand);
fprintf(fp2,"%s\t%s\t%s\t%s\t\t",loc,label,opcode,operand);
            if(operand[0]=='C'){
                for(i=2;i<l-1;i++)
                    fprintf(fp2,"%X",operand[i]);


                fprintf(fp2,"\n");
            }
                else if(operand[0]=='X'){
                 for(i=2;i<l-1;i++)
                        fprintf(fp2,"%c",operand[i]);


                fprintf(fp2,"\n");
                }
}

else if((strcmp(operand,"BUFFER,X"))==0){
                 fseek(fp3,0,SEEK_SET);
while(!feof(fp3)){
   fscanf(fp3,"%s %s",loc1,loc2);
   if((strcmp("BUFFER",loc1))==0)
    break;
   else continue;
    }

     //fseek(fp1,0,SEEK_SET);
    while(!feof(fp1)){
      fscanf(fp1,"%s%s",op1,op2);
      if((strcmp(op1,opcode))==0)
    break;
   else continue;
    }

fprintf(fp2,"%s\t%s\t%s\t%s\t%s9",loc,label,opcode,operand,op2);

l=strlen(loc2);
for(i=1;i<l;i++)
    fprintf(fp2,"%c",loc2[i]);

    fprintf(fp2,"\n");


}

else if((strcmp(opcode,"END"))==0){
fprintf(fp2,"%s\t%s\t%s\t%s\n",loc,label,opcode,operand);
break;
}

else {
    fseek(fp1,0,SEEK_SET);
while(!feof(fp1)){
      fscanf(fp1,"%s%s",op1,op2);
      if(strcmp(op1,opcode)==0)
        break;
        else continue;
      }
      fseek(fp3,0,SEEK_SET);
      while(!feof(fp3)){
   fscanf(fp3,"%s %s",loc1,loc2);
   if((strcmp(operand,loc1))==0)
    break;
   else continue;
    }

fprintf(fp2,"%s\t%s\t%s\t%s\t\t%s%s\n",loc,label,opcode,operand,op2,loc2);

}

}
}
