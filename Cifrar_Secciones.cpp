#include<windows.h>
#include<iostream>
#include<conio.h>

using namespace std;

int main()
{
    int pos=0;
    FILE *file;
    char name[100];
    int pe,inicio,fin,read,write;
    IMAGE_NT_HEADERS NTH;
    IMAGE_DOS_HEADER DH;
    IMAGE_OPTIONAL_HEADER OH;
    IMAGE_SECTION_HEADER Secciones[20];
    
    cout<<"Digite el nombre del archivo"<<endl;
    fflush(stdin);
    gets(name);
    
    file=fopen(name,"rb+");
    if(file!=NULL)
    {
        fread(&DH,sizeof(DH),1,file);
        fseek(file,DH.e_lfanew,0);
        fread(&NTH,sizeof(NTH),1,file); 
        cout<<"Entry Point:\t"<<NTH.OptionalHeader.AddressOfEntryPoint<<endl;
        cout<<"Numero de Secciones:\t"<<NTH.FileHeader.NumberOfSections<<endl;
        fseek(file,(DH.e_lfanew+sizeof(NTH)),0);
        pos=DH.e_lfanew+sizeof(NTH);
        
        for(int i=0;i<NTH.FileHeader.NumberOfSections;i++)
        {
            fseek(file,pos,0);
            fread(&Secciones[i],sizeof(Secciones),1,file);
            pos=pos+sizeof(Secciones[i]);
        }
        cout<<endl;
        
        inicio=Secciones[0].PointerToRawData;
        fin=Secciones[1].PointerToRawData;
        cout<<"Inicio:\t"<<inicio<<endl;
        cout<<"Fin:\t"<<fin<<endl;
        while(inicio<fin)
        {
            fseek(file,inicio,0);   
            fread(&read,1,1,file);
            if(inicio==1024){cout<<read<<endl;}
            fseek(file,inicio,0);
            write=read^90;
            fwrite(&write,1,1,file);
            inicio+=1;
        }
        fclose(file);
    }
    getch();
}



