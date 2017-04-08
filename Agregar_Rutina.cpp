#include<windows.h>
#include<iostream>
#include<conio.h>

using namespace std;

int main()
{
    int pos=0,inicio,fin,c,VirtualPos;
    IMAGE_NT_HEADERS NTH;
    IMAGE_DOS_HEADER DH;
    IMAGE_OPTIONAL_HEADER OH;
    IMAGE_SECTION_HEADER Secciones[20];
    FILE *file;
    char name[100];
    
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
        
        cout<<"Digite la posicion donde desea Agregar la rutina"<<endl;
        cin>>pos;
        
        fseek(file,pos,0);
		
		//Agregando rutina
        //Xor byte ptr ds:[eax],5A
        c=128;      fwrite(&c,1,1,file);
        c=48;       fwrite(&c,1,1,file);
        c=90;       fwrite(&c,1,1,file);
            
        //Inc eax    
        c=64;       fwrite(&c,1,1,file);
            
        //Cmp eax,ebx
        c=59;       fwrite(&c,1,1,file);
        c=195;      fwrite(&c,1,1,file);
            
        //jnz pos+eax
        c=117;      fwrite(&c,1,1,file);
        c=248;      fwrite(&c,1,1,file);
            
        //RET
        c=195;      fwrite(&c,1,1,file);
        
        //Fin de rutina 
        

        //Mov ecx,EntryPoint
        c=185;      fwrite(&c,1,1,file);
        c=NTH.OptionalHeader.AddressOfEntryPoint+NTH.OptionalHeader.ImageBase;
        fwrite(&c,1,sizeof(DWORD),file);
        
        //sacando direccion virtual
        for(int i=0;i<NTH.FileHeader.NumberOfSections;i++)
        {
            if(pos<Secciones[i].PointerToRawData)
            {
                VirtualPos=(pos-Secciones[i-1].PointerToRawData)+Secciones[i-1].VirtualAddress;
            }
        }
        
        //Mov edx, rutina
        c=186;  fwrite(&c,1,1,file);
        fwrite(&VirtualPos,1,sizeof(DWORD),file);
        
        
       /* //Mov eax,Inicio de seccion
            c=184;      fwrite(&c,1,1,file);
            c=NTH.OptionalHeader.ImageBase+Secciones[0].VirtualAddress;
            fwrite(&c,1,sizeof(DWORD),file);
                
            //Mov ebx, fin de seccion
        	c=187;      fwrite(&c,1,1,file);	
            c=NTH.OptionalHeader.ImageBase+Secciones[0].VirtualAddress+Secciones[0].SizeOfRawData;
            fwrite(&c,1,sizeof(DWORD),file);
            
            //Call rutina
            c=255;      fwrite(&c,1,1,file);
            c=210;      fwrite(&c,1,1,file);
            

         */   
        for(int k=0;k<(NTH.FileHeader.NumberOfSections-1);k++)
        {           
            //Mov eax,Inicio de seccion
            c=184;      fwrite(&c,1,1,file);
            c=NTH.OptionalHeader.ImageBase+Secciones[k].VirtualAddress;
            fwrite(&c,1,sizeof(DWORD),file);
                
            //Mov ebx, fin de seccion
        	c=187;      fwrite(&c,1,1,file);	
            c=NTH.OptionalHeader.ImageBase+Secciones[k].VirtualAddress+Secciones[k].SizeOfRawData;
            fwrite(&c,1,sizeof(DWORD),file);
            
            //Call rutina
            c=255;      fwrite(&c,1,1,file);
            c=210;      fwrite(&c,1,1,file);
        }
        
        
        fclose(file);
    }
    getch();
}
