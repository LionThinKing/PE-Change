#include<windows.h>
#include<iostream>
#include<conio.h>

using namespace std;

int main()
{
    int pos=0;
    FILE *file;
    char name[100];
    //char pe[]="90";
    int pe;
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
        fseek(file,(DH.e_lfanew+sizeof(NTH)),0);
        pos=DH.e_lfanew+sizeof(NTH);
        
        //NT Header
        cout<<"Signature:\t\t\t"<<NTH.Signature<<endl;
        //FileHeader
        cout<<"Machine:\t\t\t"<<NTH.FileHeader.Machine<<endl;
        cout<<"NumberOfSections:\t\t"<<NTH.FileHeader.NumberOfSections<<endl;
        cout<<"TimeDateStamp:\t\t\t"<<NTH.FileHeader.TimeDateStamp<<endl;
        cout<<"PointerToSymbolTable:\t\t"<<NTH.FileHeader.PointerToSymbolTable<<endl;
        cout<<"NumberOfSymbols:\t\t"<<NTH.FileHeader.NumberOfSymbols<<endl;
        cout<<"SizeOfOptionalHeader:\t\t"<<NTH.FileHeader.SizeOfOptionalHeader<<endl;
        cout<<"Characteristics:\t\t"<<NTH.FileHeader.Characteristics<<endl;
        //Optional Header
        cout<<endl;
        cout<<"Magic:\t\t\t\t"<<NTH.OptionalHeader.Magic<<endl;
        cout<<"MajorLinkerVersion:\t\t"<<NTH.OptionalHeader.MajorLinkerVersion<<endl;
        cout<<"MinorLinkerVersion:\t\t"<<NTH.OptionalHeader.MinorLinkerVersion<<endl;
        cout<<"SizeOfCode:\t\t\t"<<NTH.OptionalHeader.SizeOfCode<<endl;
        cout<<"SizeOfInitializedData:\t\t"<<NTH.OptionalHeader.SizeOfInitializedData<<endl;
        cout<<"SizeOfUninitializedData:\t"<<NTH.OptionalHeader.SizeOfUninitializedData<<endl;
        cout<<"AddressOfEntryPoint:\t\t"<<NTH.OptionalHeader.AddressOfEntryPoint<<endl;
        cout<<"BaseOfData:\t\t\t"<<NTH.OptionalHeader.BaseOfCode<<endl;
        cout<<"ImageBase:\t\t\t"<<NTH.OptionalHeader.ImageBase<<endl;
        cout<<"FileAlignment:\t\t\t"<<NTH.OptionalHeader.SectionAlignment<<endl;
        cout<<"MinorOperatingSystemVersion:\t"<<NTH.OptionalHeader.MinorOperatingSystemVersion<<endl;
        cout<<"MajorOperatingSystemVersion:\t"<<NTH.OptionalHeader.MajorOperatingSystemVersion<<endl;
        cout<<"MajorImageVersion:\t\t"<<NTH.OptionalHeader.MajorImageVersion<<endl;
        cout<<"MinorImageVersion:\t\t"<<NTH.OptionalHeader.MinorImageVersion<<endl;
        cout<<"MajorSubsystemVersion:\t\t"<<NTH.OptionalHeader.MajorSubsystemVersion<<endl;
        cout<<"MinorSubsystemVersion:\t\t"<<NTH.OptionalHeader.MinorSubsystemVersion<<endl;
        cout<<"Win32VersionValue:\t\t"<<NTH.OptionalHeader.Win32VersionValue<<endl;
        cout<<"SizeOfImage:\t\t\t"<<NTH.OptionalHeader.SizeOfImage<<endl;
        cout<<"SizeOfHeaders:\t\t\t"<<NTH.OptionalHeader.SizeOfHeaders<<endl;
        cout<<"CheckSum:\t\t\t"<<NTH.OptionalHeader.CheckSum<<endl;
        cout<<"Subsystem:\t\t"<<NTH.OptionalHeader.Subsystem<<endl;
        cout<<"DllCharacteristics:\t\t"<<NTH.OptionalHeader.DllCharacteristics<<endl;
        cout<<"SizeOfStackReserve:\t\t"<<NTH.OptionalHeader.SizeOfStackReserve<<endl;
        cout<<"SizeOfStackCommit:\t\t"<<NTH.OptionalHeader.SizeOfStackCommit<<endl;
        cout<<"SizeOfHeapReserve:\t\t"<<NTH.OptionalHeader.SizeOfHeapReserve<<endl;
        cout<<"SizeOfHeapCommit:\t\t"<<NTH.OptionalHeader.SizeOfHeapCommit<<endl;
        cout<<"LoaderFlags:\t\t\t"<<NTH.OptionalHeader.LoaderFlags<<endl;
        cout<<"NumberOfRvaAndSizes:\t\t"<<NTH.OptionalHeader.NumberOfRvaAndSizes<<endl;
        
        
        for(int i=0;i<NTH.FileHeader.NumberOfSections;i++)
        {
            fseek(file,pos,0);
            fread(&Secciones[i],sizeof(Secciones),1,file);
            pos=pos+sizeof(Secciones[i]);
        }
        cout<<endl;
        
        //Secciones
        for(int i=0;i<NTH.FileHeader.NumberOfSections;i++)
        {
            cout<<"Name:\t\t\t"<<Secciones[i].Name<<endl;
            cout<<"PhysicalAddress:\t"<<Secciones[i].Misc.PhysicalAddress<<endl;
            cout<<"VirtualSize:\t\t"<<Secciones[i].Misc.VirtualSize<<endl;
            cout<<"VirtualAddress:\t\t"<<Secciones[i].VirtualAddress<<endl;
            cout<<"SizeOfRawData:\t\t"<<Secciones[i].SizeOfRawData<<endl;
            cout<<"PointerToRawData:\t"<<Secciones[i].PointerToRawData<<endl;
            cout<<"PointerToRelocations:\t"<<Secciones[i].PointerToRelocations<<endl;
            cout<<"PointerToLinenumbers:\t"<<Secciones[i].PointerToLinenumbers<<endl;
            cout<<"NumberOfRelocations:\t"<<Secciones[i].NumberOfRelocations<<endl;
            cout<<"NumberOfLinenumbers:\t"<<Secciones[i].NumberOfLinenumbers<<endl;
            cout<<"Characteristics:\t"<<Secciones[i].Characteristics<<endl<<endl;
        }
        
        /*cout<<"Digite el Nuevo Entry Point"<<endl;
        cin>>pe;
        fseek(file,(DH.e_lfanew+40),0);
        fwrite(&pe,1,sizeof(int),file);
        */
        fclose(file);
    }
    
    
    getch();
}
