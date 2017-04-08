#include<windows.h>
#include<iostream>
#include<conio.h>

using namespace std;

int main()
{
    int pos=0,inicio,fin,contador=0,c,espacio=0;
    FILE *file;
    char name[100];
    int pe;
    fpos_t num;
    IMAGE_NT_HEADERS NTH;
    IMAGE_DOS_HEADER DH;
    
    cout<<"Digite el nombre del archivo"<<endl;
    fflush(stdin);
    gets(name);
    
    file=fopen(name,"rb+");
    if(file!=NULL)
    {
        fread(&DH,sizeof(DH),1,file);
        fseek(file,DH.e_lfanew,0);
        fread(&NTH,sizeof(NTH),1,file); 
        espacio=19+(12*NTH.FileHeader.NumberOfSections);
        cout<<"Buscando Espacio de:\t"<<espacio<<" Bytes"<<endl;
        pos=1000;
        fseek(file,pos,0);
        do
        {
            c=getc(file);
            pos+=1;
            
            if(c==0)
            {
                if(inicio==0)
                {
                    inicio=pos;
                }
                else
                {
                    contador+=1;
                }
            }
            else
            {
                if(contador<espacio)
                {
                    inicio=0;
                    contador=0;
                }
                else
                {
                    fin=inicio+contador;
                    break;
                }
            }
        }while(c!=EOF);
        
            
            
        cout<<"Inicio:\t"<<inicio<<endl;
        cout<<"Fin:\t"<<fin<<endl;
        cout<<"Bytes Add:\t"<<contador<<endl;
        fclose(file);
    }
    getch();
}
