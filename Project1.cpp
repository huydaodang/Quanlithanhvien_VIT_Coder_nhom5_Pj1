#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

typedef struct Member{
	int ID;
	char Name[30];
	int Act_Point;
	int Gr_Id;	
	char Convert_Name[30];
}Member;

int size=200;
//Member **list;
int n=0;
char info[30];
Member **InitlistMember(int size)
{
	Member **list;
	list=(Member**)malloc(size*sizeof(Member*));
	for(int i=0 ; i<size ; i++)
	{
		list[i]=(Member*)malloc(sizeof(Member));
	}
	return list;
}
int clean_stdin() 
{
    while (getchar() != '\n') {
    }
    return 1;
}

bool Adjust(char name[30]);
char *convert( char name[30]);
void sort_name(Member **list);
char *Format_name(char name[30]);
void Add_Member(Member **list);
void Show_All_Member(Member **list,int size);
void Find_Member(Member **list,int size,char info[]);
void Edit_Member_Info(Member **list);
void Del_Member(Member **ListMembers);
void file(FILE *fout,Member **list);
void Menu(FILE *fout,Member **list);
int main()
{
	FILE *fout;
	FILE *fin;
	Member **list;
	list=InitlistMember(size);
	Menu(fout,list);
}
bool Adjust(char name[30])
{
  int k= strlen(name),d=0; 
   for(int i=0;i<k;i++) 
  { if(name[i]==' ') d++;
  }   
  if (d==0) return false;   
  return true;
}
char *Format_name(char name[30])
{
	int k=strlen(name);
    strcpy(name, strlwr(name));
	name[0]= toupper(name[0]);
	for (int i=0;i<k-1;i++)
	if(name[i]==' ') name[i+1]= toupper(name[i+1]);
	t:for (int i=0;i<k-1;i++)
	{
		if((name[i]==' ')&&(name[i+1]==' '))
		{  for(int d=i+1;d<k;d++)
			name[d]=name[d+1];
			goto t;
		}
	}
	return name;
}

char *convert( char name[30])  
{ 
  // VD: Nguyen Van Thuan --> Thuan Nguyen Van,  Tran Thi Thanh Thuy --> Thuy Tran Thi Thanh 
   int k= strlen(name)-1; // k l� d? d�i c?a t�n - 1
   int i=0;
   char ten[30], tam[10];          
  	while (name[k] !=' ')
  	  {
  	  	tam[i++] = name[k];
  	  	k = k -1;
  	  }
    tam[i++]='\0';
    name[k] = '\0'; 
    strcpy(ten, strrev(tam));
    strcat(ten, " ");
    strcat(ten, name);
    strcpy(name, ten);
    return name;
}
void sort_name(Member **list)  
{ 
  	int ID;
	char Name[30];
	int Act_Point;
	int Gr_Id;	
	char Convert_Name[30];
  for (int i=0;i<n;i++)      
  for (int j=i+1;j<n;j++)
  if(strcmp(list[i]->Convert_Name,list[j]->Convert_Name)>0)
  {
	strcpy(Name,list[i]->Name);
	strcpy(Convert_Name,list[i]->Convert_Name);
	ID = list[i]->ID;
	Gr_Id = list[i]->Gr_Id;
	Act_Point = list[i]->Act_Point;
	
	strcpy(list[i]->Name,list[j]->Name);
	strcpy(list[i]->Convert_Name,list[j]->Convert_Name);
	list[i]->ID = list[j]->ID;
	list[i]->Gr_Id = list[j]->Gr_Id;
	list[i]->Act_Point = list[j]->Act_Point;
	strcpy(list[j]->Name,Name);
	strcpy(list[j]->Convert_Name,Convert_Name);
	list[j]->ID = ID;
	list[j]->Gr_Id = Gr_Id;
	list[j]->Act_Point = Act_Point; 
  }
}

void Add_Member(Member **list)
{ // th�m th�nh vi�n d?n khi th�m du?c t�n d�ng
  system("cls");
  int done =1;
  char Name[30] ,ch;
        do {
        		fflush(stdin);
            	system("cls");
                printf ("\n De ket thuc nhap ID < 0");
				printf("\n Nhap ID thanh vien (ID la so va lon hon 0):\n");
                int check1=0;
				char c;
				int Id=0;
				do
				{
					check1=0;
					do 
					{
						printf("ID:\n"); 
					}while( (scanf("%d%c",&Id,&c)!=2 || c!='\n' ) && clean_stdin() );
					for(int k=0 ; k<n ; k++)
					{
						if(Id==list[k]->ID)
							check1=1;
					}
				}while(check1==1);
				list[n]->ID = Id;
                if(list[n]->ID==0)done=0;
                else
                if(list[n]->ID<0)
                {  
                    fflush(stdin);
                    system("cls");
                    return;
                }
                else
                {
                	
                    fflush(stdin);
                    printf("Nhap ten thanh vien:\n");
                    gets(Name);
			        fflush (stdin);
                }
                if(Adjust(Name)==0)
                    done=0;
                else
                { 
					done=1;
                    fflush(stdin);
                    strcpy(list[n]->Name,Name);
                    Format_name (list[n]->Name);
                    printf("Nhap diem hoat dong:\n");
                    scanf("%d",&list[n]->Act_Point);
                    printf("Nhap group id thanh vien( group id la so va lon hon 0):\n");
                    scanf("%d",&list[n]->Gr_Id);
                    if(list[n]->Gr_Id==0)done=0;
                    fflush(stdin);
                }
             }while(!done);   // Khi nao thi done = 1
                
            strcpy(list[n]->Convert_Name,list[n]->Name);
            convert(list[n]->Convert_Name);
			n++;
            sort_name(list);
            Add_Member(list);
            system("cls");
                                    //menu();  
			    
}
void Show_All_Member(Member **list,int size)
{
	printf("\t\t Thong tin thanh vien:\n");
	printf("Name                         ID        Gr_id     Act_Point\n");
	for(int i=0;i<size;i++)
	{
		printf("%-20s%10d%10d%10d\n",list[i]->Name,list[i]->ID,list[i]->Gr_Id,list[i]->Act_Point);
	}
}

void Find_Member(Member **list,int size,char info[])
{
	int i;
	char info1[30];
	strcpy(info1,info);
	Format_name(info1);
	int check =0;
	for(i=0;i<n;i++)
	{
		if(list[i]->ID==atoi(info)||list[i]->Gr_Id==atoi(info)||list[i]->Act_Point==atoi(info)||strstr(list[i]->Name,info1)!=NULL)
		{
			printf("%-20s%10d%10d%10d\n",list[i]->Name,list[i]->ID,list[i]->Gr_Id,list[i]->Act_Point);
			check=1;
		}
	}
	if(check==0)
		printf("Khong tim thay thanh vien co thong tin tren\n");
}
void Edit_Member_Info(Member **list)
{
	int Id,i,j;
	bool check;
	char ch[20];
	printf("Nhap ID thanh vien can sua thong tin: ");	
	scanf("%d",&Id);
	check==false;
	for (i=0;i<n;i++) //n la so thanh vien
	    {
    		if (list[i]->ID==Id)
    		{
		    	check=true;
		    	break;
		    }
    	} //i la so thu tu thanh vien tim duoc
	if (!check)
	{
		printf("Khong ton tai thanh vien!\n");
	}
	else
	{
		printf("Sua het thong tin: 1\n");
		printf("Sua mot thong tin: 2\n");
		do
		{
			scanf("%d",&j);
		}while(j!=1 && j!=2);
		if (j==1)
		{
			printf("Nhap lai thong tin thanh vien:\n");
			int check1=0;
			char c;
			do
			{
				check1=0;
				do 
				{
					printf("ID:\n"); 
				}while( (scanf("%d%c",&Id,&c)!=2 || c!='\n' || Id<0 ) && clean_stdin() );
				list[i]->ID=-1;
				for(int k=0 ; k<n ; k++)
				{
					if(Id==list[k]->ID)
						check1=1;
				}
			}while(check1==1);
			list[i]->ID = Id;
			printf("Ho Ten:\n");
			fflush(stdin);
			gets(list[i]->Name);
			Format_name(list[i]->Name);
			strcpy(list[i]->Convert_Name,list[i]->Name);
			convert(list[i]->Convert_Name);
			printf("Diem hoat dong:\n");
			scanf("%d",&list[i]->Act_Point);
			printf("Group ID:\n");
			scanf("%d",&list[i]->Gr_Id);
			sort_name(list);
		}
		else if (j==2)
		{
			printf("Thong tin muon sua:\n");
			fflush(stdin);
			gets(ch); //ch la thong tin name, id, group id hoac act point
			strlwr(ch);
			bool checkch=false; //checkch kiem tra chuoi ch co dung 1 trong 4 thong tin khong
			while (!checkch)
			{
				checkch=true;
				if (strcmp(ch,"name")==0)
				{
					printf("Nhap ho ten:\n");
					fflush(stdin);
					gets(list[i]->Name);
					Format_name(list[i]->Name);
					strcpy(list[i]->Convert_Name,list[i]->Name);
					convert(list[i]->Convert_Name);
					sort_name(list);
				}
				else if (strcmp(ch,"id")==0)
				{
					int check1=0;
					char c;
					do
					{
						check1=0;
						do 
						{
							printf("ID:\n"); 
						}while( (scanf("%d%c",&Id,&c)!=2 || c!='\n' || Id<0 ) && clean_stdin() );
						list[i]->ID=-1;
						for(int k=0 ; k<n ; k++)
						{
							if(Id==list[k]->ID)
								check1=1;
						}
					}while(check1==1);
					list[i]->ID = Id;
				}
				else if (strcmp(ch,"group id")==0)
				{
					printf("Nhap Group ID:\n"); scanf("%d",&list[i]->Gr_Id);
				}
				else if (strcmp(ch,"act point")==0)
				{
					printf("Nhap diem hoat dong:\n"); scanf("%d",&list[i]->Act_Point);
				}
				else
				{
					printf("Nhap lai thong tin muon sua:\n");
					gets(ch);
					strlwr(ch);
					checkch=false;
				}
				
			}
		}
		
	}
}

void Del_Member(Member **ListMembers)
{
    //tìm thành viên cần xóa
    //tìm bằng ID
    //có thể thay phần này bằng cách gọi hàm tìm thành viên rồi mới xóa
    int id;
    int i;
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"\n>> Nhap ID can tim: ";
    cin>>id;
    for(i=0;i<n;i++) //duyet mang de tim ID
        if(ListMembers[i]->ID==id)
        {
            cout<<">> Thanh vien can tim la: "<<endl;
            cout<<"ID: "<<ListMembers[i]->ID<<endl;
            cout<<"Name: "<<ListMembers[i]->Name<<endl;
            cout<<"Act_Point: "<<ListMembers[i]->Act_Point<<endl;
            cout<<"Gr_Id: "<<ListMembers[i]->Gr_Id<<endl;
            break;
        }
    if(i==n)
        cout<<">> Khong ton tai thanh vien co ID="<<id<<endl;
	else
	{
    cout<<"Ban muon xoa thanh vien nay? 1/0?"<<endl;
    int yes_no;
    cin>>yes_no;
    if(yes_no==1)
    {
        for(;i<n-1;i++)     
            ListMembers[i]=ListMembers[i+1];
        n--;
        cout<<">> Xoa thanh cong!"<<endl;

    }
    else
        cout<<"Khong thuc hien xoa!"<<endl;
	}
}
void file(FILE *fout,Member **list)
{
	fprintf(fout,"        Thong tin thanh vien doi tinh nguyen\n");
	fprintf(fout,"            Doi tinh nguyen vien CNTT & TT\n");
	fprintf(fout,"Name                         ID        Gr_id     Act_Point\n");
	for(int i=0;i<n;i++)
	{
		fprintf(fout,"%-20s%10d%10d%10d\n",list[i]->Name,list[i]->ID,list[i]->Gr_Id,list[i]->Act_Point);
	}
}
void Menu(FILE *fout,Member **list)
{
	while(1)
	{
		printf("        Chuong trinh quan li thong tin thanh vien\n");
		printf("            Doi tinh nguyen vien CNTT & TT\n");
		printf("Option1: Them thanh vien\n");
		printf("Option2: In ra thong tin thanh vien\n");
		printf("Option3: Tim kiem thanh vien\n");
		printf("Option4: Xoa thong tin thanh vien\n");
		printf("Option5: Sua thong tin thanh vien\n");
		printf("Option6: Luu file\n");
		printf("Option7: Exit\n");
	
		//Menu
		switch(getchar())
		{
			case '1'://Them thong tin thanh vien
				{
					Add_Member(list);
				};break;
			case '2'://In ra thong tin tat ca thanh vien
				{
					Show_All_Member(list,n);
				};break;
			case '3'://Tim kiem thong tin thanh vien co thi tra ve Success, else Fail
				{
					printf("Nhap vao thong tin cua thanh vien can tim\n");
					fflush(stdin);
					gets(info);
					Find_Member(list,n,info);
				};break;
			case '4'://Xoa thong tin thanh vien
				{
					Del_Member(list);
				};break;
			case '5'://Sua thong tin thanh vien
				{
					Edit_Member_Info(list);
				};break;
			case '6':
				{
					fout=fopen("C:/Users/Dao Dang Huy/Desktop/DSTVNVIT.txt","w");
					if(fout!=NULL)
					{
						file(fout,list);
						fclose(fout);
					}
				};break;
			case '7':exit(1);break;
			//default: continue;
		}
		fflush(stdin);
	}
}



