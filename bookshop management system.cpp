/*
Book Shop Management System
Group No. 24
Romil V. Shah - 91800545004
*/

#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include<stdlib.h>

using namespace std;

class book
{
    char book_number[30];
    char book_name[50];
    char author_name[20];
    int num_copies;

    public:
        void get_book_details()
        {
            cout<<"ENTER DETAILS ABOUT BOOK YOU WANT TO PURCHASE\n";
            cout<<"\nEnter The Book Number: ";
            cin>>book_number;
            cout<<"\nEnter The Name of The Book: ";
            cin.ignore();
            cin.getline(book_name,50);
            cout<<"\nEnter The Author's Name: ";
            cin.getline(author_name,50);
            fflush(stdin);
            cout<<"\nEnter No. Of Copies Available: ";
        	cin>>num_copies;
        	getch();
        }

        void show_book()
        {
            cout<<"\n\nBOOK DETAILS\n";
            cout<<"\nBook Number: "<<book_number;
            cout<<"\nBook Name: "<<book_name;
            cout<<"\nAuthor's Name: "<<author_name;
            cout<<"\nNo. of Copies Available : "<<num_copies;
        }

        void modify_book()
        {
            cout<<"\nBook number : "<<book_number;
            cout<<"\nModify Book Name : ";
            cin.ignore();
            cin.getline(book_name,50);
            cout<<"\nModify Author's Name: ";
            cin.getline(author_name,50);
            fflush(stdin);
            cout<<"\nEnter No. Of Copies : ";
            cin>>num_copies;
        }

        char* getbooknumber()
        {
            return book_number;
        }

        void report()
        {
            cout<<book_number<<setw(30)<<book_name<<setw(30)<<author_name<<setw(30)<<num_copies<<endl;
        }

};

fstream fp;
book bk;

void write_book()
{
    system("cls");
    int more_or_main;
    fp.open("book.txt",ios::out|ios::app);
    do
    {
        bk.get_book_details();
        fp.write((char*)&bk,sizeof(book));
        cout<<"\nPress 1 to add more books.";
        cout<<"\nPress 2 to return to main menu.\n";
        cout<<"Enter: ";
        cin>>more_or_main;
        system("cls");
    }while(more_or_main == 1);
    fp.close();
}

void display_a_book(char n[])
{

    int check=0;
    fp.open("book.txt",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.getbooknumber(),n)==0)
        {
            bk.show_book();
            check=1;
        }
    }

    fp.close();
    if(check==0)
    {
        cout<<"\n\nBook does not exist";
    }

    getch();
    system("cls");
}

void modify_book()
{
    system("cls");
    char n[20];
    int found=0;
    cout<<"MODIFY BOOK";
    cout<<"\n\nEnter Book Number: ";
    cin>>n;

    fp.open("book.txt",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.getbooknumber(),n)==0)
        {
            bk.show_book();
            cout<<"\n\nEnter The New Details of book"<<endl;
            bk.modify_book();
            int pos=-1*sizeof(bk);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&bk,sizeof(book));
            cout<<"\nRecord Updated Successfully...";
            found=1;

        }
    }
    fp.close();
    if(found==0)
    cout<<"\nRecord Not Found ";
    getch();
    system("cls");
}

void login()
{
	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="Alpha";
    char pass[10]="P@55W0RD";

    do
    {
        cout << ("LOGIN FORM");
        cout << ("\nENTER USERNAME :-  ");
        cin  >> uname;
        cout << ("ENTER PASSWORD :-  ");
        while(i<10)
        {
            pword[i]=getch();
            c=pword[i];
            if(c==13) break;
            else cout << ("*");
            i++;
        }
        cout << endl;
        pword[i]='\0';
        i=0;

		if(strcmp(uname,"Alpha")==0 && strcmp(pword,"P@55W0RD")==0)
        {
            cout << ("\nWELCOME TO KASHISH BOOKSTORES.\n\nYou have Successfully Logged In.");
            cout << ("\nPress any key to continue.......");
            getch();
            break;
        }
        else
        {
            cout << ("\nInvalid User/Password!\nPlease Retry\n\n\n");
            a++;
        }
    }
	while(a<=3);

	if (a>3)
	{
		cout << ("\nSorry you have entered the wrong username and password for four times!");
		getch();
		exit(0);
    }
		system("cls");

}
void delete_book()
{
    system("cls");
    char n[20];
    int flag=0;
    cout<<"DELETE BOOK";
    cout<<"\n\nEnter The Book's number You Want To Delete: ";
    cin>>n;
    fp.open("book.txt",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.txt",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.getbooknumber(),n)!=0)
        {
            fp2.write((char*)&bk,sizeof(book));
        }
        else
        {
            flag=1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.txt");
    rename("Temp.txt","book.txt");
    if(flag==1)
    {
        cout<<"\nRecord Deleted ..";
    }
    else
    {
        cout<<"\nRecord not found";

    }
    getch();
    system("cls");
}

void display_allb()
{
    system("cls");
    fp.open("book.txt",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }
    cout<<"BOOK LIST\n\n";
    cout<<"====================================================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(35)<<"Author"<<setw(30)<<"Copies"<<endl;
    cout<<"====================================================================================================\n";
    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    getch();
    system("cls");
}

int main()
{
    login();

    int option = 0;
    for(;;)
    {
        cout << "\n\nWELCOME TO KASHISH BOOK STORES\n";

        cout<<"\nPress 1 to ADD BOOKS";
        cout<<"\nPress 2 to SHOW ALL BOOKS";
        cout<<"\nPress 3 to CHECK AVAILABILITY";
        cout<<"\nPress 4 to MODIFY BOOKS";
        cout<<"\nPress 5 to DELETE BOOKS";
        cout<<"\nPress 6 to Exit";
        cout<<"\nOption: ";
        cin>>option;

        switch(option)
        {
            case 1:
                    system("cls");
                    write_book();
                    break;

            case 2:
                    display_allb();
                    break;

            case 3:
                    char num[20];
                    system("cls");
                    cout<<"Please Enter No. of the Book You want to Search for ==> ";
                    cin>>num;
                    display_a_book(num);
                    break;

            case 4:
                    modify_book();
                    break;

            case 5:
                    delete_book();
                    break;

            case 6:
                    exit(0);

            default:
                    cout<<"Please Enter Correct Option from the Menu!";
                    getch();
                    system("cls");
                    break;
        }
    }
}
