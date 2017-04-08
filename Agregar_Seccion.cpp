#include<windows.h>
#include<iostream>
#include<conio.h>

using namespace std;



int main()
{
    
    char Name[100],name[100];
    FILE *file;
    int pos,VirtualSize,VirtualAddress,SizeOfRawData,PointerToRawData,PointerToRelocations=0,PointerToLinenumbers=0,NumberOfRelocations=0,NumberOfLinenumbers=0,Characteristics=536871136;
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
        
        fseek(file,pos,0);
        
        cout<<"Digite el Nombre de la Seccion"<<endl;
        fflush(stdin);
        gets(Name);
        
        cout<<"Digite Virtual Size"<<endl;
        cin>>VirtualSize;
                
        VirtualAddress=Secciones[NTH.FileHeader.NumberOfSections-1].VirtualAddress + Secciones[0].VirtualAddress;
        
        cout<<"Digite SIzeOfRawData"<<endl;
        cin>>SizeOfRawData;
        
        PointerToRawData=0;
        
        //cout<<"Digite PointerToRawData"<<endl;
        //cin>>PointerToRawData;
        
        fwrite(Name,1,sizeof(Secciones[0].Name),file);
        fwrite(&VirtualSize,1,sizeof(Secciones[0].Misc.VirtualSize),file);
        fwrite(&VirtualAddress,1,sizeof(Secciones[0].VirtualAddress),file);
        fwrite(&SizeOfRawData,1,sizeof(Secciones[0].SizeOfRawData),file);
        fwrite(&PointerToRawData,1,sizeof(Secciones[0].PointerToRawData),file);
        fwrite(&PointerToRelocations,1,sizeof(Secciones[0].PointerToRelocations),file);
        fwrite(&PointerToLinenumbers,1,sizeof(Secciones[0].PointerToLinenumbers),file);
        fwrite(&NumberOfRelocations,1,sizeof(Secciones[0].NumberOfRelocations),file);
        fwrite(&NumberOfLinenumbers,1,sizeof(Secciones[0].NumberOfLinenumbers),file);
        fwrite(&Characteristics,1,sizeof(Secciones[0].Characteristics),file);
        
        fseek(file,(DH.e_lfanew+6),0);
        NTH.FileHeader.NumberOfSections+=1;
        fwrite((&NTH.FileHeader.NumberOfSections),1,sizeof(NTH.FileHeader.NumberOfSections),file);
        
        //Modificamos el SizeOfImage Debe ser multiplo de SectionAlignement
        fseek(file,(DH.e_lfanew+80),0);
        
        NTH.OptionalHeader.SizeOfImage=VirtualAddress+VirtualSize;
        fwrite((&NTH.OptionalHeader.SizeOfImage),1,sizeof(NTH.OptionalHeader.SizeOfImage),file);
        
        fclose(file);
    }
    getch();
}
