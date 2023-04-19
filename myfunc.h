#include <windows.h>
#include <stdlib.h>
#include<conio.h>
#include <string.h>
#include<string.h>

void menu();
void display();
void search();
void insert();
void delete1();
void update();
void about();


struct details
{
	char name[50];
	char type[50];
	float rate;
	int manufacture;
	int expiry;
	int quantity;
}x;



void menu()
{
system("cls");
printf("\n\t*************** WELCOME TO MEDICINE RECORD MANAGEMENT SYSTEM ******************\n\n");
printf(" \n\t  ::::::::::::::::::::::::::  | MEDICINE MENU |  :::::::::::::::::::::::::: \n");
printf("\n\n\t[1] Add  Medicine Records\n   \t[2] Delete Medicine Records\n   \t[3] Update Medicine Records\n \t[4] Display Medicine Records\n \t[5] Search Medicine Records\n \t[6] About Us \n \t[7] Exit \n");
printf ("\n\t Press the Options From above to Proceed Further : ");
switch(getch())
{
    case '1':
        insert();
    break;
   case '2':
       delete1();
    break;
    case '3':
        update();
    break;
    case '4':
        display();
    break;
    case '5':
        search();
	break;
	case '6':
        about();
    break;
    case '7':
        exit(0);
    break;
    default:
            printf("\n\n\t !!!Enter Options from 1 to 7 only !!!");
            printf("\n\t ! Press Any Key for continue.......");
            getch();
            system("cls");
menu();
}
}

  
void about()
{
    system("cls");
    printf("This mini project in C for Medicine Record Management System , which is a console application without graphic.\nIn this project, you can add, modify, view and delete records of medicines.\nYou can also search for medicines added into stock. Search can be done by medicine name.\n");
    printf("\n\npress any key to go back...!!!");
    getch();
    menu();
}




void login()
{
	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10];
    char user[10]="admin";
    char pass[10]="admin";
    do
{

    printf("\n  ::::::::::::::::::::::::::  LOGIN FORM  ::::::::::::::::::::::::::  ");
    printf(" \n                       ENTER USERNAME:-");
	scanf("%s", &uname);
	printf(" \n                       ENTER PASSWORD:-");
	while(i<7)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	i=0;
		if(strcmp(uname,"admin")==0 && strcmp(pword,"admin")==0)
	{
	printf("  \n\n\n       WELCOME TO MEDICINE RECORD MANAGEMENT SYSTEM !!!! LOGIN IS SUCCESSFUL");
	    printf("\n LOADING PLEASE WAIT... \n");
    for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(500);
    }
	printf("\n\n\n\t\t\t\tPress any key to continue...");
	getch();
	menu();
	break;
	}
	else
	{
		printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;

		getch();

	}
}
	while(a<=2);
	if (a>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");

		getch();

		}
		system("cls");
}

void insert()
{
  int i,n;
  
	FILE *s;
	s=fopen("medicine.txt","a");
	printf("\n");
	printf("Enter Name: \n");
	scanf("%s",x.name);
	printf("Medicine type: \n");
	scanf("%s",x.type);
	printf("Enter Rate: \n");
	scanf("%f",&x.rate);
	printf("Enter Manufacture date yy: \n");
	scanf("%d",&x.manufacture);
	printf("Enter Expiry yy: \n");
	scanf("%d",&x.expiry);
	printf("Enter Quantity: \n");
	scanf("%d",&x.quantity);
	fwrite(&x,sizeof(x),2,s);
	fflush(s);
	fclose(s);
	printf("The Medicine Record has been Inserted !!!");
	getch();
	menu();
}
void display()
{
   FILE *s;
   s=fopen("medicine.txt","r");
   if(s==NULL)
   {
   	printf("NOTHING TO SHOW");
   }
   else
   {	
   	while((fread(&x,sizeof(x),2,s)))
   	{
			printf("\nMEDICINE NAME: %s",x.name);
			printf("\nMEDICINE TYPE: %s\n",x.type);
			printf("RATE: %f\n",x.rate);
			printf("MANUFACTURE: %d\n",x.manufacture);
			printf("EXPIRY: %d\n",x.expiry);
			printf("QUANTITY: %d\n",x.quantity);
   		}
   		fclose(s);
  }
  getch();
  menu();	
}
void search()
{
	char m[20];
	printf("\n\t Enter Name of Medicine to Search: ");
	scanf("%s",m);
	FILE *s;
	s=fopen("medicine.txt","r");
	while(fread(&x,sizeof(x),2,s))
	{
		if(strcasecmp(m,x.name)==0)
		{	
			printf("\nName: %s",x.name);
			printf("\nMEDICINE TYPE: %s",x.type);
			printf("\nRate: %f",x.rate);
			printf("\nManufacture: %d",x.manufacture);
			printf("\nExpiry: %d",x.expiry);
			printf("\nQuantity: %d",x.quantity);
		}
	}
	getch();
	menu();
}
void delete1()
{
  FILE *s,*p;
  char n[20];
  s=fopen("medicine.txt","r");
  p=fopen("delete.txt","w");
  printf("\n \t ENTER MEDICINE YOU WANT TO DELETE : ");
  scanf("%s",n);
  while(fread(&x,sizeof(x),2,s))
  {
  	if(strcasecmp(n,x.name)!=0)
  	{
  		fwrite(&x,sizeof(x),2,p);
  	}
  	if(strcasecmp(n,x.name)==0)
  	{
  		printf("Deleted Successfully");
  		getch();
  	}
  }	
  fclose(s);
  fclose(p);
  s=fopen("medicine.txt","w");
  p=fopen("delete.txt","r");
  while(fread(&x,sizeof(x),2,p))
  {
  	fwrite(&x,sizeof(x),2,s);
  }
  fclose(s);
  fclose(p);
  
  menu();
  }
  
  void update()
{
  FILE *s,*p;
  char n[20];
  s=fopen("medicine.txt","r");
  p=fopen("delete.txt","w");
  printf("\n \t ENTER MEDICINE YOU WANT TO UPDATE: ");
  scanf("%s",n);
  while(fread(&x,sizeof(x),2,s))
  {
  	if(stricmp(n,x.name)!=0)
  	{
  		fwrite(&x,sizeof(x),2,p);
  	}
  	
  	else
  	{
  	printf("Enter the name : ");
    scanf("%s",x.name);
	printf("Enter the type of medicine : ");
	scanf("%s",x.type);
	printf("Enter the rate of the medicine :  ");
	scanf("%f",&x.rate);
    printf("Enter the units of the medicine : ");
    scanf("%d",&x.quantity);
    printf("Enter the manufacturing date : ");
    scanf("%d",&x.manufacture);
    printf("Enter the expiry date : ");
    scanf("%d",&x.expiry);
    fwrite(&x,sizeof(x),2,p);
	printf("\nUPDATED SUCCESSFULLY !!!!");	
	  }
  }	
  fclose(s);
  fclose(p);
  s=fopen("medicine.txt","w");
  p=fopen("delete.txt","r");
  while(fread(&x,sizeof(x),2,p))
  {
  	fwrite(&x,sizeof(x),2,s);
  }
  fclose(s);
  fclose(p);
  
  
  getch();
  menu();  
  
  }

