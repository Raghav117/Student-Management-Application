#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>


char menu();
int pymenu();
int pnmenu();
int checkfile();
int getch();

class student
{
private :

    int rollno;
    char fname[20],lname[20],cl[5],sec[3];

public :

    void getdata()
    {
	cout<<"\nEnter Student first name  :     ";
	gets(fname);

	cout<<"\nEnter Student last name  :      ";
	gets(lname);

	cout<<"\nEnter Student class  :     ";
	gets(cl);

	cout<<"\nEnter Student section  :     ";
	gets(sec);

	cout<<"\nEnter Student roll number :     ";
	cin>>rollno;

	cin.ignore();
     }

    void displaydata()
    {
	 cout<<"\nStudent first name :     "<<fname;
	 cout<<"\nStudent last name :     "<<lname;
	 cout<<"\nStudent class :     "<<cl;
	 cout<<"\nStudent section :     "<<sec;
	 cout<<"\nStudent roll number :     "<<rollno<<"\n\n";
    }

    void insertrecord();
    void displayrecord();
    void searchrecord();
    void deleterecord();
    void updaterecord();
    void deleteallrecord();

}s1;

class password1
{
private :

    char password[50];

public :

    password1()
    {
	strcpy(password,"\0");
    }

    void getpassword();
    void checkpassword();
    void insertpassword();
    void removepassword();
    void changepassword();
}p1;



/*      Functions Defination of Student class           */

void student :: insertrecord()
{
    ofstream fout;

    fout.open("file.dat" , ios :: app | ios :: binary );
    fout.write((char*)&s1,sizeof(s1));
    fout.close();

    cout<<"\n\n\t\t\tRecord inserted successfully... \n";
    getch();
}


void student :: displayrecord()
{
    ifstream fin;
    int c=5;

    fin.open("file.dat" , ios :: in | ios :: binary);

    if( !fin )
	cout<<"\nNo Record Found... \n";
    else
    {
	fin.read( ( char * ) &s1 , sizeof (s1)  );
	while( !fin.eof())
	{

	    if(c>15)
	    {
		cout<<"\n\t\t\tPress any key to Continue... \n";
		getch();
		clrscr();
		c=5;
	    }

	    displaydata();

	    fin.read( ( char * ) &s1 , sizeof (s1)  );
	    c+=5;

	}
	fin.close();
    }
    getch();
}


void student :: searchrecord()
{
    int i,n;
    cout<<"\nEnter the roll number to be searched :     ";
    cin>>n;

    ifstream fin;
    fin.open("file.dat" , ios :: in | ios :: binary);

    if( !fin)
	cout<<"\nNo record Found...   ";
    else
    {
	fin.read( ( char * ) &s1 , sizeof (s1)  );
	while( !fin.eof() )
	{
	    if(rollno==n)
	    {
		i=1;
		displaydata();
	    }
	    fin.read( ( char * ) &s1 , sizeof (s1)  );
	 }
	if(i!=1)
	    cout<<"\nNo Record Found... ";
	}
    fin.close();
    getch();
    }



void student :: deleterecord()
{
    int n,c=0;

    cout<<"\nEnter the roll number of student to be deleted :    ";
    cin>>n;

    ifstream fin;
    fin.open("file.dat" , ios :: in | ios :: binary);

    if( !fin)
	cout<<"\nNo record Found...   ";
    else
    {
	ofstream fout;
	fout.open("temp.dat" , ios :: out | ios :: binary);
	fin.read( ( char * ) &s1 , sizeof (s1)  );
	while( !fin.eof() )
	{

	    if(rollno!=n)
		fout.write(( char*)&s1 , sizeof (s1) );
	    else
		c=1;

	    fin.read( ( char * ) &s1 , sizeof (s1)  );
	 }
	fin.close();
	fout.close();
	remove("file.dat");
	rename("temp.dat","file.dat");
	if(c==1)
	    cout<<"\n\n\t\t\tRecord Deleted Successfully...\n ";
	else
	    cout<<"\nNo Record Found... \n";
	}
    getch();
    }


void student :: updaterecord()
{
    int n,y=0;
    cout<<"\nEnter the roll number of student to update record :   ";
    cin>>n;
    cin.ignore();

    fstream fin;
    fin.open("file.dat" , ios :: in | ios  :: binary | ios :: out );

    if(  !fin )
	cout<<"\nNo Record Found..\n ";
    else
    {
	fin.read(( char* )&s1,sizeof (s1));
	while(  !fin.eof() )
	{
	    if(rollno==n)
	    {
		getdata();
		fin.seekg(fin.tellg() - sizeof (s1) );
		fin.write( ( char* ) &s1 , sizeof (s1) );
		y=1;
	    }
	    fin.read(( char* )&s1 , sizeof ( s1 ) );
	}
	if(y==1)
	    cout<<"\n\n\t\t\tRecord Updated Successfully...";
	else
	    cout<<"\nNo Record Found... ";
	fin.close();
	}
    getch();
    }


void student :: deleteallrecord()
{
    remove("file.dat");
    cout<<"\n\n\n\t\t All Records Are Deleted Successfully ... \n";
    getch();
}


/*....... ......Functions Defination of password class ...............*/

void password1 :: getpassword()
{
    int k=-1;
    char i;
    while(k<7)
    {
	k=-1;
	i='\0';
	while ( int (i) != 13 )
	{
	    i=getch();
	    if( int (i)!=8 && int (i)!=13 )
	    {
		++k;
		cout<<"*";
		password[k]=i;
	    }
	    else if(int(i)==8)
	    {
		if(k!=-1)
		{
		    --k;
		    cout<<"\b \b";
		}
	    }
	}
	if(k<7)
	    cout<<"\n\n  Password is short re-enter again    ";
    }
    while(k<=50)
	password[++k]='\0';
 }


void password1 :: insertpassword()
{
    cout<<"\n Enter password for the application (min. 8 characters)         ";
    getpassword();
    ofstream fout;
    fout.open("pass.dat" , ios :: binary);
    fout.write( (char*)&p1 , sizeof (p1) );
    fout.close();

    cout<<"\n\n\t\t\t Password set successfully...  ";
    getch();
}


void password1 :: changepassword()
{
    cout<<"\n Enter new password :    ";
    getpassword();
    ofstream fout;
    fout.open( "pass.dat" , ios :: binary );
    fout.write( (char*)&p1 , sizeof (p1) );
    fout.close();

    cout<<"\n\n Password changed successfully... ";
    getch();
}



void password1 :: removepassword()
{
    remove("pass.dat");
    cout<<"\n Password deleted successfully... ";
    getch();
}


void password1 :: checkpassword()
{
    char password2[50];
    ifstream fin;
    fin.open("pass.dat" , ios :: binary);

    if(fin)
    {
	fin.read( (char*)&p1 , sizeof (p1) );
	cout<<"\n First enter your password  \t";

	while(1)
	    {
	    strcpy(password2,password);
	    getpassword();
	  if(strcmp(password2,password)==0)
	{
	    cout<<"\n\n Password match successfully...\n ";
	    getch();
	    break;
	}
	else
	{
	    strcpy(password,password2);
	    cout<<"\n\n\t\t\t Wrong Password \n";
	    cout<<"\n Please re-enter again  \t";
	}
	}
    }
}

/*                           Main Program                              */

void main()
{
    clrscr();
    p1.checkpassword();
    while(1)
    {
	clrscr();

	switch(menu())
	{
	    case '1' :
		clrscr();
		s1.displayrecord();
		break;

	    case '2' :
		clrscr();
		s1.getdata();
		s1.insertrecord();
		break;

	    case '3' :
		clrscr();
		s1.searchrecord();
		break;

	    case '4' :
		clrscr();
		s1.deleterecord();
		break;

	    case '5' :
		clrscr();
		s1.updaterecord();
		break;

	    case '6' :
		clrscr();
		s1.deleteallrecord();
		break;

	    case '7' :
		clrscr();
		if(checkfile()==0)
		{

		    switch(pnmenu())
		    {
			case '1' :
			    clrscr();
			    p1.insertpassword();
			    break;

			default :
			    cout<<"\nInvalid choice \n";
			    getch();
			    break;
		    }

		}
		else
		{
		    switch(pymenu())
		    {
			case '1' :
			    clrscr();
			    p1.checkpassword();
			    p1.changepassword();
			    break;

			case '2' :
			    clrscr();
			    p1.checkpassword();
			    p1.removepassword();
			    break;

			default :
			    cout<<"\nInvalid choice \n";
			    getch();
			    break;
		    }
		}
		break;

	    case '8' :
		clrscr();
		cout<<"\n\t\t  Thankyou for using this application... \n"
		    <<"\n Press any key to exit... \n";
		    getch();
		    exit(0);
	    default :
		cout<<"\nInvalid choice \n";
		getch();
		break;
	}
    }
}



char menu()
{
    char choice;
    cout<<"\t\t Welcome in Student Management Application \n \t\t\t"
	<<"\tBy Raghav Garg...\n";

    cout<<"\n1.     To display records     \n"
	<<"\n2.     To insert records     \n"
	<<"\n3.     To serch records     \n"
	<<"\n4.     To delete records     \n"
	<<"\n5.     To update records     \n"
	<<"\n6.     To delete all records     \n"
	<<"\n7.     Imformation about passwords     \n"
	<<"\n8.     To exit the application     \n"
	<<"\n     Enter your choice...     \n";

	choice=getch();
	return choice;
}

int checkfile()
{
    ifstream fin;
    fin.open("pass.dat" , ios :: binary);
    if(!fin)
	return 0;
    else
	fin.close();
    return 1;
}

int pymenu()
{
    char choice;
    cout<<"\n1.     To change password     \n"
	<<"\n2.     To remove password     \n"
	<<"\n     Enter your choice...     \n";

    choice=getch();
    return choice;
}

int pnmenu()
{
    char choice;
    cout<<"\n1.     To set password     \n"
	 <<"\n     Enter your choice     \n";

    choice=getch();
    return choice;
}

