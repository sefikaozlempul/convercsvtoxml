#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<locale.h>
#include<wchar.h>
char *replace(const char *s ,const char *oldW,const char *newW)
{
    char *result;
    int i,cnt=0;
    int newWlen=strlen(newW);
    int oldWlen=strlen(oldW);
    for(i=0;s[i]!='\0';i++)
    {
        if(strstr(&s[i],oldW)==&s[i])
        {
        cnt++;
        i+=oldWlen-1;
        }
    }
    result=(char*)malloc(i+cnt*(newWlen-oldWlen)+1);
    i=0;
    while (*s)
    {
       if(strstr(s,oldW)==s)
       {
           strcpy(&result[i],newW);
           i+=newWlen;
           s+=oldWlen;
       }
       else
          result[i++]=*s++;
    }
    result[i]='\0';
    return result; 
}
void lower_string(char s[])
{
    int c=0;
    while (s[c]!='\0')
    {
        if(s[c]>='A'&& s[c]<='Z')
        {
            s[c]=s[c]+32;
        }
        c++;
    }
}
char *trim(char *s)
{
    if(s)
    {
        while (*s && isspace(*s))
            ++s;
        if(*s)
        {
            register char *p=s;
            while(*p)
                ++p;
            do{
                --p;
            }while ((p!=s)&& isspace(*p));
            *(p+1)='\0';
        }
    }
    return s;
}
int main (int argc, char *argv[]) 
{
    printf("\nENTER THE FOLLOWING COMMAND lINE TO GET HELP : ./2017510067 inputfile.csv outputfile.xml -separator P1 -opsys P2 -h");
    printf("       \n");
    setlocale(LC_ALL,"en_US.UTF-8");
    FILE *fp = fopen(argv[1], "r"); //Input csv file
    FILE *tempfp = fopen(argv[1], "r");//Temp Input csv file
    FILE *outputfile=fopen(argv[2],"w");//OutPut File
    if (!fp) {
        printf("Can't open file\n");
        return 0;
    }
    char *sep; //Keep seperator
    char *sepdouble; //Keep consecutive seperator 
    char *sepdoublenew;   // Keep to replace seperator
    char sepcom[10];
    strcpy(sepcom,argv[3]);
    if(strstr(sepcom,"-separator"))
    {
         if(*argv[4]=='1')
       { 
        sep=",";
        sepdouble=",,";
        sepdoublenew=",      ,";
      } 
       else if(*argv[4]=='2')
       {
        sep="\t";
        sepdouble="\t\t";
        sepdoublenew="\t          \t";
       } 
       else if(*argv[4]=='3')
      {
        sep=";";
        sepdouble=";;";
        sepdoublenew=";      ;";
      }
    }
    else
    {
        printf("\nYOU ENTERED COMMAND LINE INCORRETLY\n");
        printf("YOU MUST ENTER -separator for arguman[3]\n");
        printf("\n");
        exit(0);
    }
    char ops[20];
    strcpy(ops,argv[5]);
    if(strstr(ops,"-opsys"))
    {
         char* endof; // End of line character
        if(*argv[6]=='1')
        {
             endof="\r\n"; //WINDOWS
        }
         else if(*argv[6]=='2')
        {
             endof="\n"; //LINUX
        }
         else if(*argv[6]=='3')
        {
               endof="\r"; //MACOS
        }
    }
    else 
    {
        printf("\nYOU ENTERED COMMAND LINE INCORRECTLY\n");
        printf("\nYOU MUST ENTER -opsys for arguman[5]\n");
        printf("\n");
        exit(0);
    }
    if(argv[7]!=NULL)
    {
      char help[10];
       strcpy(help,argv[7]);
        if(strstr(help,"-h")) 
       {   
        printf("\n");
        printf("Enter input csv file with .csv \n");
        printf("Enter output xml file with .xml \n");
        printf("For P1: ===>  1 = comma separator 2 = tab separator 3=semicolon separator\n");
        printf("Write -separator and enter a space and separator character \n");
        printf("For P2: ===>  1 = windows 2 = linux 3=macos \n");
        printf("Write -opsys ,enter a space and end of line format number\n");
        printf("For example command line : ");
        printf("./2017510067 Contacts.csv Contacts.xml -separator 1 -opsys 1 \n");
         printf("\n");
       }
    }
    else
    {
     printf("\nTHE INPUT CSV FILE HAS BEEN CONVERTED TO OUTPUT XML FILE\n");
     printf("\n");
    char outf[100]; //Keep output file full name such as outputfile.xml
    strcpy(outf,argv[1]);
    char rootname[100];// Keep output forename such as output
    strcpy(rootname,outf);
    char *token=strtok(rootname,".");  //Keep xml row name 
    // printf("<%s>\n",token);
     fprintf(outputfile,"<%s>\n",token); 
    char buf[__INT16_MAX__]; //Keep to content of inputfile  array
    char tempbuf[__INT16_MAX__]; //Keep to content of inputfile  temparray
    char string[__INT16_MAX__];//Keep to buf array
    char tempstring[__INT16_MAX__];//Keep to buf temp array
    char str[__INT16_MAX__];
    int row_count = 0;
    int field_count = 0;
    fgets(buf, __INT16_MAX__, fp);
    strcpy(str,buf);
    while (fgets(buf, __INT16_MAX__, fp)) 
    {
        field_count = 0;
        row_count++;
         strcpy(string,buf);
        char *rs=NULL; // if string array have consecutive seperator, replace of white space between two seperator
        rs=  replace(string,sepdouble,sepdoublenew);
        char *field = strtok(rs, sep);//Keep to words of inputfile (XML attributes)
        while (field) 
        {     
            field = strtok(NULL, sep);
            field_count++;
        }
    }
    char parts[field_count][row_count];
    if(*sep=='\t')
    {
        char *ts=NULL;
         ts=replace(str,"  ","_");
         char*ptt=strtok(ts,"_"); 
         for(int i=0;i<field_count;i++)
        {  
           lower_string(ptt);
          lower_string(parts[i]);
          strcpy(trim(parts[i]),trim(ptt));
           ptt=strtok(NULL,"_");  
        }
    }
    else if(*sep!='\t')
    {
        char*ptt=strtok(str,sep); 
       for(int i=0;i<field_count;i++)
      {   
         ptt=  replace(ptt," ","_"); 
         ptt=  replace(ptt,"\"",""); 
         lower_string(ptt);
         lower_string(parts[i]);
         strcpy(trim(parts[i]),trim(ptt));
         ptt=strtok(NULL,sep);
      }
    }
   row_count=0;   
   trim(tempbuf);
   while (fgets(tempbuf, __INT16_MAX__, tempfp)) 
    {
        field_count = 0;
        row_count++;
          if (row_count == 1) {
            continue;
        }
         strcpy(tempstring,tempbuf);
        char *rs=NULL;
        rs=  replace(tempstring,sepdouble,sepdoublenew);
        char *field = strtok(rs, sep);
        int k=0; //Index of array 
      //  printf("     <row id=\"%d\">\n",row_count-1);
        fprintf(outputfile,"     <row id=\"%d\">\n",row_count-1);
        while (field) 
        {   
            if(*sep=='\t')
            {
                char *rs=NULL;            
                rs=  replace(parts[k]," ","_");
               //  printf("         <%s>%s</%s>\n",trim(rs),trim(field),trim(rs)) ;
                 fprintf(outputfile,"         <%s>%s</%s>\n",trim(rs),trim(field),trim(rs)) ;
                 field = strtok(NULL, "\t");
                 field_count++;
                 k++;
            }
            else if(*sep!='\t')
            {   
              // printf("         <%s>%s</%s>\n",trim(parts[k]),trim(field),trim(parts[k])) ;
               fprintf(outputfile,"         <%s>%s</%s>\n",trim(parts[k]),trim(field),trim(parts[k])) ;
               field = strtok(NULL, sep);
               field_count++;
               k++;
            }
        }
      //  printf("     </row>");
        fprintf(outputfile,"     </row>");
       // printf("\n");
        fprintf(outputfile,"\n");
    }
  //  printf("</%s>\n",token); 
    fprintf(outputfile,"</%s>\n",token); 
    fclose(fp);
    fclose(outputfile);
    }
    return 0;
}