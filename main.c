#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

int i;



struct PhoneBook
{
    int number ;
    char   gender[2] , nr[12], lastname[20], firstname[20], email[30] ;

};

int search( struct PhoneBook *l )
{
    int k;
    printf("Do you want to search by Phone Number or Name?\n");
    printf("[1] By Number\n");
    printf("[2] By Name\n");
    printf("Choice : ");
    scanf("%d" , &k);
    switch(k)
    {
    
      case 1:
      
       char num[12];
       printf("\nNumber : ");
       scanf("%s" ,  &num);
      
       int gasit = 0 ;
       system("cls");
       for (int j=0;j<i;j++)
       {
         if(strcmp(num , l[j].nr)==0)
         {
            system("cls");
            printf(" Name : %s %s\nNumber : %s\nEmail : %s\n"  , l[j].firstname , l[j].lastname , l[j].nr , l[j].email );
            if(strcmp(l[j].gender , "0")==0)
            printf("Gender : Male\n");
            else if(strcmp(l[j].gender , "1")==0)
            printf("Gender : Female\n");
            gasit=1;
            getch();
            printf("Press some key to continue");
            return l[j].number;
         }
         
       }
       if(gasit==0)
         {
         printf("The contact dosen't exist \n");
         printf("Press some key to continue");
         getch();  
         }
         break;



       case 2:
       char fname[20] , lname[20];
       printf("\nFirst Name : ");
       scanf("%s" ,  &fname);
       printf("\nLast Name : ");
       scanf("%s" , &lname);
      
        gasit = 0 ;
       for (int j=0;j<i;j++)
       {
         if(strcmp( fname, l[j].firstname)==0  &&  strcmp(lname , l[j].lastname)==0)
         {
            system("cls");
            printf(" Name : %s %s\nNumber : %s\nEmail : %s\n"  , l[j].firstname , l[j].lastname , l[j].nr , l[j].email );
            if(strcmp(l[j].gender , "0")==0)
            printf("Gender : Male\n");
            else if(strcmp(l[j].gender , "1")==0)
            printf("Gender : Female\n");
            gasit=1;
            getch();
            printf("Press some key to continue");
            return l[j].number;
         }
         
       }
       if(gasit==0)
         {
         printf("The contact dosen't exist \n");
         printf("Press some key to continue");
         getch();
         
         }
         break;

      }
    



}

void viewcontacts()
{
    struct PhoneBook a[50];
    FILE *in;
    in=fopen("database.txt" , "r");
    fread(&a , sizeof(struct PhoneBook) , i , in);
    fclose(in);

    printf("----------------------------------------------------------------------------\n");
    printf("|Nr| First Name | Last Name |   Number   |         Email           | Gender|\n");

    for(int j=0;j<i ; j++)
    {
        printf("----------------------------------------------------------------------------\n");
        printf("|%2d|%12s|%11s|%12s|%24s |" ,a[j].number+1 , a[j].firstname , a[j].lastname , a[j].nr , a[j].email );
        if(strcmp(a[j].gender , "0")==0)
        printf("  Male |\n");
        else if(strcmp(a[j].gender , "1")==0)
        printf("Female |\n");
        

    }
    printf("----------------------------------------------------------------------------\n");
    printf("Contacts[ %d / 50 ]\n" , i);

    int k;

    printf("Do you want to search somone ? \n");
    printf("[1] Yes\n");
    printf("[2] No\n");
    printf("Answer : ");
    scanf("%d" , &k);
    if(k==1)
    {
        struct PhoneBook o;
        system("cls");
        search(a);
    }

}


void Add()
{

    struct PhoneBook new;

    new.number=i;
    
    while (getc(stdin) != '\n');
    printf("Gender( 0 for men and 1 for women) : \n");
    scanf_s("%s", &new.gender, 2);

    printf("Number : ");
    scanf_s("%s", &new.nr, 12);

    printf("\nLast Name : ");
    scanf_s("%s", &new.lastname, 20);

    printf("\nFirst Name : ");
    scanf_s("%s", &new.firstname, 20);

    printf("\nEmail : ");
    scanf_s("%s", &new.email, 30);

    FILE *f;
    f=fopen("database.txt", "a");
    if(f==NULL)
    printf("Contact couldn't be saved");
    else{
    fwrite(&new ,sizeof(struct PhoneBook), 1  , f);
    fclose(f);
    i++;
    FILE *las;
    las=fopen("last.txt" , "w");
    fprintf(las , "%d" , i );
    fclose(las);
    }

    system("cls");
    char x;

    printf("Do you want to add another contact ? (0 means NO , 1 means YES)\n");
    printf("[1] Yes\n");
    printf("[0] No\n");
    printf("Choice: ");
    scanf("%d" , &x);
    if (x == 1)
    {
    system("cls");
    Add();
    }
     

}



void update()
{
    struct PhoneBook a[50];

    FILE *in;
    in=fopen("database.txt" , "r");
    fread(&a , sizeof(struct PhoneBook) , i , in);
    fclose(in);

    printf("____Search the contact you want to update ____\n");
    int p = search(a);
    char x[10];

    system("cls");
    printf("What you want to update ?(Name , Number , Email )\n");
    printf("Answer(name , number , email) : ");
    scanf("%s", &x);
    if(strcmp(x ,"name")==0)
    {
       char fname[12] , lname[12];
       printf("New First Name : \n");
       scanf("%s" , fname);
       strcpy(a[p].firstname , fname);
       printf("New Last Name : \n");
       scanf("%s" , lname);
       strcpy(a[p].lastname , lname);

       
    }
    else if(strcmp(x ,"number")==0)
    {
        char num[12] ;
       printf("New Nnumber : ");
       scanf("%s" , num);
       strcpy(a[p].nr , num);
       
    }
    else if(strcmp(x ,"email")==0)
    {
        char emai[12] ;
       printf("New Email : ");
       scanf("%s" , emai);
       strcpy(a[p].email , emai);
    }

    else{
        printf("You typed something wrong  , Try again");
    }

    FILE *f;
    f=fopen("database.txt", "w");
    if(f==NULL)
    printf("Contact couldn't be saved");
    else{
    fwrite(&a ,sizeof(struct PhoneBook), i  , f);
    fclose(f);
    }

}

void delete()
{
    struct PhoneBook a[50];

    FILE *in;
    in=fopen("database.txt" , "r");
    fread(&a , sizeof(struct PhoneBook) , i , in);
    fclose(in);

    printf("____Search the contact you want to delete ____\n");
    int p = search(a);
    char x[10];
    
    for(int j=p ; j<i-1;j++)
    {
    a[j]=a[j+1];
    a[j].number--;
    }

    i--;
    FILE *las;
    las=fopen("last.txt" , "w");
    fprintf(las , "%d" , i );
    fclose(las);

    FILE *f;
    f=fopen("database.txt", "w");
    if(f==NULL)
    printf("Contact couldn't be deletetd");
    else{
    fwrite(&a ,sizeof(struct PhoneBook), i  , f);
    fclose(f);
    }
    system("cls");
    printf("The contact was deleted succsessfuly\nPress a key to continue");
    getch();
}

int Menu_Add_Update_Delete()
{
    printf("\x1b[31m");
    printf("_______[ ADD or UPDATE or DELETE ]_______\n");

    int x;
    printf("\033[0;32m");

    printf("[1] Add a contact \n");
    printf("[2] Uppdate a contact \n");
    printf("[3] Delete a contact \n");
    printf("[4] Back \n");

    printf("Choice : ");
    scanf("%d", &x );

    switch (x) {

    case 1:
    system("cls");
    Add();
    system("cls");
    Menu_Add_Update_Delete();
    break;

    case 2:
    system("cls");
    update();
    system("cls");
    Menu_Add_Update_Delete();
    break;

    case 3:
    system("cls");
    delete();
    system("cls");
    Menu_Add_Update_Delete();
    break;

    case 4:
    return 0;
    system("cls");
    
    default:
    Menu_Add_Update_Delete();
    }

}

void menu()
{
    
    system("cls");
    printf("\x1b[31m");
    printf("_______[ Phone Book ]_______\n");

    int x;
    printf("\033[0;32m");

    printf("[1] Add or Update or Delete \n");
    printf("[2] View and Search \n");
    printf("[3] Exit \n");

    printf("Choice : ");
    scanf_s("%d", &x );

    switch (x) {

    case 1:
        system("cls");
        Menu_Add_Update_Delete();
        system ("cls");
        menu();
        break;

    case 2:
        system("cls");
        viewcontacts();
        system("cls");
        menu();
        break;

    case 3:
    exit(1);

    default:
        menu();
    }



}

int main()
{

    FILE *number ;
    number=fopen("last.txt" , "r");
    fscanf(number , "%d" , &i);
    fclose(number);
    menu();
    return 0;
}