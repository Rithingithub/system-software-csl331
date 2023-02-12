#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    FILE *f1,*f2,*f3,*f4;

    f1 = fopen("input.txt","r");
    f2 = fopen("symtab.txt","r");
    f3 = fopen("optab.txt","w");
    f4 = fopen("output.txt","w");

    char label[10],opcode[10],operand[10],code[10],mneomonic[10];
    int locctr,start,length;

    fscanf(f1, "%s\t%s\t%s" , label, opcode, operand);

    if(strcmp(operand, "START")==0)
    {
        start = atoi(operand);
        locctr = start;
        fprintf(f4, "%s\t%s\t%s\n", label, opcode,operand);
        fscanf(f1, "%s\t%s\t%s" , label, opcode, operand);
    }
    else
    {
        locctr=0;
    }
    while (strcmp(opcode, "END")!=0)
    {
        fprintf(f4, "%d\t",locctr);

        if(strcmp(label, "**")!=0){
            fprintf(f3,"%s\t%d",label,locctr);
        }

        fscanf(f2,"%s\t%s",code,mneomonic);
        
        while (strcmp(code, "END")!=0)
        {
            if (strcmp(opcode, code)==0)
            {
                locctr+=3;
                break;
            }
            fscanf(f2,"%s\t%s",code, mneomonic);
        }

        if (strcmp(opcode,"WORD")==0){
            locctr+=3;
        }
        else if(strcmp(opcode,"RESW")==0){
            locctr+=(3*(atoi(operand)));
        }
        else if(strcmp(opcode,"BYTE")==0){
            locctr+=(atoi(operand));
        }
        else if(strcmp(opcode,"RESB")==0){
            ++locctr;
        }

        fprintf(f4,"%s\t%s\t%s",label,opcode,operand);
        fscanf(f1, "%s\t%s\t%s" , label, opcode, operand);
    }

    fprintf(f4, "%d\t%s\t%s\t%s",locctr,label,opcode,operand);
    length = locctr-start;
    printf("lenght is %d",length);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    
}
