#include<windows.h>
#include<iostream>
#include<conio.h>


using namespace std;

int main()
{
    FILE *f1,*f2;
    int c1,c2,c=0;
    
    char file1[100],file2[100];
    
    cout<<"Digite el nombre del primer archivo"<<endl;
    fflush(stdin);
    gets(file1);
    
    cout<<"\nDigite el nombre del segundo archivo"<<endl;
    fflush(stdin);
    gets(file2);
    
    
    if(f1=fopen(file1, "rb"))
    {
        if(f2=fopen(file2, "rb"))
        {
            do
            {
                c1=getc(f1);
                c2=getc(f2);
                if(c1!=c2)
                {
                    cout<<c<<":\t"<<c1<<"\t"<<c2<<endl;
                }
                c++;
                
            }while(c1!= EOF && c2!=EOF);
        }
    }
    getch();
}
