#include<stdio.h>
#include<string.h>
#include<math.h>
int hexa(int hexadecimal_number){
int decimal_number = 0,remainder;
      int count = 0;
      while(hexadecimal_number > 0)
      {
            remainder = hexadecimal_number % 10;
            decimal_number = decimal_number + remainder * pow(16, count);
            hexadecimal_number = hexadecimal_number / 10;
            count++;
      }
      return decimal_number;
      }
main(){
    int locctr,intlocctr,hexlocctr;
    char label[10],opcode[10],operand[10];
FILE *fp,*fp1,*fp2;
fp=fopen("symt.txt","r+");

fp1=fopen("symtabl.txt","w+");
fp2=fopen("inter.txt","w+");

while(!feof(fp)){
fscanf(fp,"%s%s%s",label,opcode,operand);

if(strcmp(opcode,"START")==0)
  {
   hexlocctr=atoi(operand);             //ADDRESS IS STORED IN HEXA FORM HERE
   intlocctr=hexa(hexlocctr);
   fprintf(fp2,"%0X\t%s\t%s\t%s\n",intlocctr,label,opcode,operand);
   //fscanf(fp,"%s%s%s",label,opcode,operand);        //first
   fprintf(fp1,"%s\t%d\n",label,hexlocctr);
   fscanf(fp,"%s%s%s",label,opcode,operand);        //cloop
  }
  else{
  intlocctr=0;
  //hexlocctr=0;
  }

  while((strcmp(opcode,"END"))!=0){


    if((strcmp(label,"."))!=0){
            fprintf(fp2,"%0X\t%s\t%s\t%s\n",intlocctr,label,opcode,operand);
            fprintf(fp1,"%s\t%0X\n",label,intlocctr);
            if((strcmp(opcode,"WORD"))==0){
                    intlocctr=intlocctr+3;
            }
            else if((strcmp(opcode,"RESW"))==0){
                    intlocctr=intlocctr+(3*(atoi(operand)));
            }
            else if((strcmp(opcode,"RESB"))==0){
                    intlocctr=intlocctr+atoi(operand);
            }
            else if((strcmp(opcode,"BYTE"))==0){
                if(operand[0]=='C'){
                        intlocctr=intlocctr+(strlen(operand)-3);
                    }
                    else if(operand[0]=='X'){
                        intlocctr=intlocctr+1;
                    }
            }
            else {
                intlocctr+=3;
            }
              //cloop 1003
           // fscanf(fp," %s%s%s",label,opcode,operand);  //lda
            }
            else if((strcmp(label,"."))==0){
                fprintf(fp2,"%0X\t%s\t%s\t%s\n",intlocctr,label,opcode,operand);
                intlocctr+=3;

                //fscanf(fp," %s%s%s",label,opcode,operand); //comp
            }
            fscanf(fp," %s%s%s",label,opcode,operand);
}
}
 fprintf(fp2,"%0X\t%s\t%s\t%s\n",intlocctr,label,opcode,operand);
fclose(fp);
fclose(fp1);
}

