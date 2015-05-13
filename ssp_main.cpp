//HEADER FILES
//<<!!============================!!>>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<process.h>
#include<iomanip.h>
#include<math.h>
#include<time.h>
#include<windows.h>
//<<!!============================!!>>
//HEADER FILES OVER !!!


		//FUNCTION PROTOTYPES
//<<!!============================!!>>
void welcome_screen();
void showtime();
void gotoxy( int , int );
void login_main();
void encode ( char [] , char [] ) ;
void decode ( char [] , char [] ) ;
void login_box_display() ;
void login_success () ;
void msg_box(char[]) ;
void header () ;
void exit_screen();
void convert(char []);
void main_menu();
void items_menu();
void items_control();
void sales_menu();
void sales_control();
void credit_menu();
void credit_control();
void admin_menu();
void admin_control();
void sales_history ( ); 
void bill_show ();
void show_data(char[] , char[]);
void search_customer(char[] , float* val = 0 , int inv_no = 0);
void search_product(char[] );
int  scan(char [],char []);


		//GLOBAL VARIABLES
//<<!!============================!!>>
char curr_date[15];
int mid = 84 ;
char enter[]=" >> HIT \'ENTER\' TO CONTINUE << ";
char name[50] = "" ;

class login_credits
{
	public:
		char username[50];
		char password[50];
	
	login_credits()
	{
		strcpy(username,"admin");
		strcpy(password,"admin*");
	}
};

		// CLASS DEFINITIONS
//<<!!===========================!!>>
class product
{
public:
	char barcode[20] ;
	char name[50];
	float price;
	int stock ; 
	int enter_data( int flag = 0 );
	void show_data(char[] , int offset = 0 );
	int edit_data();
	void add_stock();
	float give_price(int qty=1)
	{
		return qty*price;
	}

	product()
	{
		strcpy (barcode , "0000") ;
		strcpy(name,"");
		price=0.0;
		stock = -1 ;
	}
};

class credit
{
public:
	float cr_val ;
	char date[15];
	int invoice_no ;
	
	credit()
	{
		cr_val = -1.00;
		strcpy(date,"NT ASSIGND");
		invoice_no = 0 ;
	}
};

class customer
{
public:
	char ccode[10] ;
	int  icode ;
	char name[50];
	char ctc_no[15];
	int cr_entries ;
	credit cr[50];
	float tot_cr;
	int enter_data( int flag = 0 , int );
	void show_data ( char[] , int offset = 0 ) ;
	int repay_cr();
	int  credit_entry(float* val = 0 , int inv_no = 0 );
	int  credit_pay();
	void get_ccode(int);
	
	customer()
	{
		strcpy(name,"");
		strcpy(ccode,"SSP");
		strcpy ( ctc_no , "" );
		icode = 0 ;
		cr_entries=0;
		tot_cr = 0.00 ;
	}
};

struct item_bill
{
	product prd ;
	int qty ; 
};


class bill
{
public :
	int bill_no ;
	char bill_date[15] ;
	item_bill item[100];
	int item_count ; 
	float total ;
	float dis;
	float net_total ;
	int cash ;
	int credit ;
	char name[50] ;

	int new_bill ( int );
	int bill_checkout ( ) ;
	void show_data ( char[] , int offset = 0 ) ;
	
	bill () 
	{
		bill_no = -1 ;
		item_count = 0 ;
		strcpy ( bill_date , "" );
		total = 0.00 ;
		dis = 0.00 ;
		net_total = 0.00 ;
		cash = credit = 0 ;
	}
};





		//MAIN() FUNCTION
//<<!!============================!!>>
void main()
{
	int flag = 0 , i = 0  , j = 0 ;
	char ch='' , choice='';
	fstream file ;
	
	file.open("log_crd.bin",ios::out|ios::noreplace);
	file.close();	
	file.open("prod_list.bin",ios::out|ios::noreplace);
	file.close();	
	file.open("cust_list.bin",ios::out|ios::noreplace);
	file.close();	
	file.open("bill_list.bin",ios::out|ios::noreplace);
	file.close();

/*	fstream afile("cust_list.bin",ios::in|ios::binary);
	fstream bfile("cust_list.bin",ios::out|ios::binary);
	customer c;
	customer c_;
	char temp [10]="";
	while(afile.read((char*)&c,sizeof(customer)))
	{
		strcpy(c_.ccode,c.ccode);
		strcpy(c_.name,c.name);
		c_.ctc_no = c.ctc_no;
		c_.cr_entries = c.cr_entries ;
		c_.tot_cr = c.tot_cr ;
		for ( i = 0 ; i < 50 ; ++ i)
			c_.cr[i] = c.cr[i] ;
		j = 0 ;	
		strcpy(temp,"");
		for ( i = 3 ; c.ccode[i]!='\0';++i)
		{
			temp[j++] = c.ccode[i] ;
		}
		temp[j] = '\0' ;
		c_.icode = atoi(temp);
		bfile.write((char*)&c_,sizeof(customer));
	}
	
	bfile.close();
	afile.close();*/
	
	login_main();
	do{
		header();
		main_menu();
		
		if ( flag == 0 )
			msg_box("!!==WELCOME TO SUPER STORE, PONNANI==!!");
			
		if ( flag == 1 )
			msg_box("!!==INVALID CHOICE==!!");
		
		if ( flag == 2 )
			msg_box("!!!===<<< UNDER CONSTRUCTION >>>===!!!");
		
		flag = 0 ;
		ch = '' ;
		i = 0 ;
		
		
		cout<<endl;
		gotoxy(69,35);	
		cout<<"===>>  YOUR CHOICE    :    "<<endl;
		while ( (int)ch!= 13 )
		{
			gotoxy ( 97 , 35 );	
			 ch=getch();
			
			if ( !i && (int)ch == 13 ) 
			{	
				ch = '' ;
				continue ;
			}
			
			if ( (int)ch != 13 && (int)ch != 8 )
			{
				i = 1 ;
				choice = ch ;
			}
			

			if ( i && (int)ch == 13 ) break ;

			if ( i && (int)ch == 8 )
			{
				i = 0 ;
				gotoxy(97,35);cout<<" ";
				ch='' ;
			}
		
			if ( i>=0 ) 
			{
				gotoxy ( 97 , 35 ) ;
				printf("%c" , ch);
				cout<<endl;
			}

			
		}

		if ( (int)choice >= 49 && (int)choice <=54 ) flag = 0 ;
		else if ( (int) choice == 13 || choice == '' ) flag = 0 ;
		else flag = 1 ;
		
		switch ( choice )
		{
			case '1':
				items_control();
				break;
			case '2':
				sales_control();
				break;
			case '3':
				credit_control();
				break;
			case '4':
				admin_control();
				break;
			case '5':
				flag = 2 ;
				break;
			case '6':
				break;			
			default:
				break;
		}
		
	}while( choice != '6' ) ;
	
	exit_screen();

}

//<<!!============================!!>>


void welcome_screen()
{
	int i = 0 ;
	
	system("title -- SUPER STORE BILLING SYSTEM -- PONNANI --");
	
	gotoxy(50,6);
	for ( ; i<=65 ; ++i )
		cout << (char) 223 ;
	cout<<endl ;
	gotoxy(51,7);
	cout<<" .oooooo..o ooooo     ooo ooooooooo.   oooooooooooo ooooooooo."<<endl;   
	gotoxy(51,8);
	cout<<"d8P'    `Y8 `888'     `8' `888   `Y88. `888'     `8 `888   `Y88."<<endl; 
	gotoxy(51,9);
	cout<<"Y88bo.       888       8   888   .d88'  888          888   .d88'"<<endl; 
	gotoxy(51,10);
	cout<<" `\"Y8888o.   888       8   888ooo88P'   888oooo8     888ooo88P'"<<endl;  
	gotoxy(51,11);
	cout<<"      \"Y88b  888       8   888          888    \"     888`88b."<<endl;    
	gotoxy(51,12);
	cout<<"oo     .d8P  `88.    .8'   888          888       o  888  `88b."<<endl;  
	gotoxy(51,13);
	cout<<"8\"\"88888P'     `YbodP'    o888o        o888ooooood8 o888o  o888o"<<endl; 
	gotoxy(51,16);																 
																 
																	 
	cout<<" .oooooo..o ooooooooooooo   .oooooo.   ooooooooo.   oooooooooooo "<<endl;
	gotoxy(51,17);
	cout<<"d8P'    `Y8 8'   888   `8  d8P'  `Y8b  `888   `Y88. `888'     `8 "<<endl;
	gotoxy(51,18);
	cout<<"Y88bo.           888      888      888  888   .d88'  888         "<<endl;
	gotoxy(51,19);
	cout<<" `\"Y8888o.       888      888      888  888ooo88P'   888oooo8    "<<endl;
	gotoxy(51,20);
	cout<<"     `\"Y88b      888      888      888  888`88b.     888    \"    "<<endl;
	gotoxy(51,21);
	cout<<"oo     .d8P      888      `88b    d88'  888  `88b.   888       o "<<endl;
	gotoxy(51,22);
	cout<<"8\"\"88888P'      o888o      `Y8bood8P'  o888o  o888o o888ooooood8 	"<<endl;

	gotoxy(50,23);
	for ( i=0 ; i<=65 ; ++i )
		cout << (char) 220 ;
	cout<<endl ;	
	
	gotoxy(0,25);
	showtime();
	cout<<endl;
}

void header()
{
	int i = 0 ;
	system("title -- SUPER STORE BILLING SYSTEM -- PONNANI --");
	system("cls");
	cout<<endl;
	gotoxy(53,2); 
	cout<<"____ ____ ____ ____ ____ _________ ____ ____ ____ ____ ______ "<<endl;
	gotoxy(53,3);
	cout<<"||S |||U |||P |||E |||R |||       |||S |||T |||O |||R |||E ||"<<endl;
	gotoxy(53,4);
	cout<<"||__|||__|||__|||__|||__|||_______|||__|||__|||__|||__|||__||"<<endl;
	gotoxy(53,5);
	cout<<"|/__\\|/__\\|/__\\|/__\\|/__\\|/_______\\|/__\\|/__\\|/__\\|/__\\|/__\\|"<<endl;
	
	gotoxy(50,6);
	for ( ; i<=65 ; ++i )
		cout << (char) 220 ;
	cout<<endl<<endl<<endl ;
	showtime();
	
}

		//LOGIN & AUTHENTICATION
//<<!!================================!!>>

void login_main()
{
	int flag = 1 , i = 0 , j = 0 ;
	char user[25] = "" , pwd_ = '' , pwd[25] = "" ;
	
	login_credits log ;
	
	fstream file("log_crd.bin",ios::in|ios::binary) ;
	file.getline(log.username,50,'\n');
	file.getline(log.password,50,'\n');
	file.close() ;
	
	if( !strcmp(log.username,"") && !strcmp(log.password,"") ) 
	{
		strcpy ( log.username , "admin" );
		strcpy ( log.password , "*admin*" );
	}		
	else
	{
		decode(log.username,log.password);
	}

	
 	do{
		system("cls");
		
		if ( flag == 1 ) 
			msg_box("!!==WELCOME TO SUPER STORE, PONNANI==!!");
			
		if ( flag == 2 )
			msg_box("!!==LOGIN FAILED==!!");
		
		flag = 1 ;
		pwd_ = '';
		strcpy( pwd,"" ) ;
		i = 0 ;
		
		welcome_screen() ;
		
		login_box_display();
		
		gotoxy( 87 , 33 ) ;
		cin.getline(user , 25);
		
		if(!strcmp(user,"")) continue ;
		
		gotoxy( 87 , 35 ) ;
		
		while ( (int)pwd_ != 13 )
		{
				
			pwd_=getch();
			
			if ( !i && (int)pwd_ == 13 ) 
			{	
				pwd_ = '' ;
				continue ;
			}
			
			if ( (int)pwd_ != 8 && (int)pwd_ != 13 ) 
				if ( i !=19 )
					pwd[i++] = pwd_ ;
				
			if ( (int)pwd_ == 8 )
				if ( i != 0 )
						--i ;
				else
						i = 0 ;		
		
			if ( i>=0 ) 
			{
				gotoxy ( 87 , 35 ) ;
				printf("                    ") ;
				cout<<endl;
				gotoxy ( 87 , 35 ) ;
				for ( j=0 ; j<i ; ++j)
					printf("*");
			}
			
		}
		pwd[i] = '\0';
		
		if (!strcmp(log.username,"admin") && !strcmp(log.password,"*admin*"))
		{
			encode ( user , pwd ) ;
			file.open("log_crd.bin",ios::out|ios::binary) ;
			file<<user<<'\n'<<pwd;
			file.close() ;
			flag = 0 ;
		}
		else
		{
				if (!(!strcmp(log.username,user) && !strcmp(log.password,pwd)))
					flag = 2 ;
				else 
					flag = 0 ;
 		}
		
	}while( flag );
	
	login_success () ;
	
}

void encode ( char user [] , char pwd [] )
{
	int i = 0 , j = 0 ;
	char temp[50] = "" , t[5] = "" ;
	
	for ( i = 0 ; user[i] != '\0' ; ++i )
	{
			if ( (int) user[i] >= 100 ) { temp[j] = '3' ; j = j + 4 ; }
			else if ( (int) user[i] >= 10 ) { temp[j] = '2' ; j = j + 3 ; }
			else { temp[j] = '1' ; j = j + 2 ; }
			itoa ( (int)user[i] , t , 10 ) ;
			strcat( temp , t ) ;
			
	}
	
	strcpy ( user , temp );
	strcpy ( temp , "" ) ;
	strcpy ( t , "" ) ; 
	i = j = 0 ;
	temp[0]='\0';
	char temp_[50]="";
	for ( i = 0 ; pwd[i] != '\0' ; ++i )
	{
			if(!i)strcpy(temp , "" );
			if ( (int) pwd[i] >= 100 ) { temp_[j] = '3' ; j = j + 4 ; }
			else if ( (int) pwd[i] >= 10 ) { temp_[j] = '2' ; j = j + 3 ; }
			else { temp_[j] = '1' ; j = j + 2 ; }
			itoa ( (int)pwd[i] , t , 10 ) ;
			strcat( temp_ , t ) ;
	}
	
	strcpy ( pwd , temp_ );	
}

void decode ( char user [] , char pwd [] )
{
	int i = 0 , j = 0 , z = 0 ,  val = 0 ; 
	char temp[50] = "" , t[5] = "" ;
	char ch = '' ;
	int flag = 0 ;
	
	for ( i = 0 ; user[i] != '\0' ; ++i )
	{
		j = 0 ;
		strcpy(t,"");
		int times = (int)(user[i]) - 48 ;
		
		for ( z = 1 ; z <= times ; ++z )
		{
			++i ;
			t [j++] = user[i] ;
			if ( user[i+1] == '\0' ) break ;
		}
		t[j]='\0';
		
		val = atoi (t) ;
		temp[flag++] = (char)val ;
				
		if ( user[i+1] == '\0' ) break ;
	}
	
	strcpy ( user , temp ) ;
	strcpy ( temp , ""  ) ;
	flag = 0 ; 
	
	for ( i = 0 ; pwd[i] != '\0' ; ++i )
	{
		j = 0 ;
		strcpy(t,"");
		int times = (int)(pwd[i]) - 48 ;
		
		for ( z = 1 ; z <= times ; ++z )
		{
			++i ;
			t [j++] = pwd[i] ;
			if ( pwd[i+1] == '\0' ) break ;
		}
		t[j]='\0';
		
		val = atoi (t) ;
		temp[flag++] = (char)val ;
				
		if ( pwd[i+1] == '\0' ) break ;
	}
	
	strcpy ( pwd , temp ) ;	
	
}


void login_box_display()
{
	int i=0;

	gotoxy(80,28) ;
	cout<<"LOGIN "<<endl;
	gotoxy(79,29) ;
	cout<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<endl;
	cout<<endl;
	gotoxy(58,31) ;
	for(i=0;i<50;++i)
		cout<<(char)220;
	cout<<endl;
	gotoxy(58,32);
	cout<<(char)219<<"                                                "<<(char)219<<endl;
	gotoxy(58,33);
	cout<<(char)186<<"      >> USERNAME      :                        "<<(char)186<<endl;
	gotoxy(58,34);
	cout<<(char)186<<"                                                "<<(char)186<<endl;
	gotoxy(58,35);
	cout<<(char)186<<"      >> PASSWORD      :                        "<<(char)186<<endl;
	gotoxy(58,36);
	cout<<(char)219<<"                                                "<<(char)219<<endl;
	gotoxy(58,37);
	for(i=0;i<50;++i)
		cout<<(char)223;
	cout<<endl;
}
//<<!!================================!!>>


void login_success()
{
	int flag = 0 , i = 0 ;
	char bar[200] = "" ;
	char sgl[2] = "" ; sgl[0]=':' ; sgl[1]='\0';
	
	
 	do{
		system("cls");
		
			for ( i = 0 ; i < 29 ; ++i )
				strcat ( bar , sgl ) ;
			
			msg_box(bar);


		++flag  ;
		
		welcome_screen() ;
		
		login_box_display();
			
		gotoxy(80,28) ;
		cout<<"LOGIN "<<endl;
		gotoxy(79,29) ;
		cout<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<endl;
		cout<<endl;
		gotoxy(58,31) ;
		for(i=0;i<50;++i)
			cout<<(char)220;
		cout<<endl;
		gotoxy(58,32);
		cout<<(char)219<<"                                                "<<(char)219<<endl;
		gotoxy(58,33);
		cout<<(char)186<<"                                                "<<(char)186<<endl;
		gotoxy(58,34);
		cout<<(char)186<<"                                                "<<(char)186<<endl;
		gotoxy(58,35);
		cout<<(char)186<<"                                                "<<(char)186<<endl;
		gotoxy(58,36);
		cout<<(char)219<<"                                                "<<(char)219<<endl;
		gotoxy(58,37);
		for(i=0;i<50;++i)
			cout<<(char)223;
		cout<<endl;	
		
		gotoxy(71,34);
			cout<<"!!==LOGIN SUCCESSFULL==!!";	
		
		cout<<endl ; gotoxy(0,0) ;
		
		for(i=0;i<80000000;++i) ;
		
		++flag ;
		
	}while( flag<=9 );
	
	msg_box(enter);
	
	char ch = '' ;
	
	while((int)ch!=13)
	{
		ch=getch();
		printf("");
	}
}




		//MSG BOX FEATURE
//<<!!============================!!>>
void msg_box( char msg[] )
{
	int i = 0 ;
	
	int size = strlen(msg) ;
	
	cout<<endl ;
	gotoxy ( 9 , 50 ) ;
	
	for(i=1;i<=150;++i)
		cout<<(char)220;
	cout<<endl ;
	
	gotoxy ( 9 , 51 ); cout<<(char)219<<endl ;
	gotoxy ( 158 , 51 ); cout<<(char)219<<endl ;
	gotoxy ( 9 , 52 ); cout<<(char)186<<endl ;
	gotoxy ( 158 , 52 ); cout<<(char)186<<endl ;
	gotoxy ( 9 , 53 ); cout<<(char)219<<endl ;
	gotoxy ( 158 , 53 ); cout<<(char)219<<endl ;	
	
	gotoxy ( 9 , 54 ) ;
	
	for(i=1;i<=150;++i)
		cout<<(char)223;
	cout<<endl ;
	
	size /= 2 ;
	gotoxy ( 10 , 52 ) ;
	for ( i = 0 ; i < 148 ; ++i ) cout << " " ;
	cout<<endl;
	
	gotoxy ( mid - size , 52 ) ;
	cout<<msg<<endl ;
}
//<<!!============================!!>>


void main_menu()
{
	int i=0;

	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(79 , 13) ;
	cout<<"MAIN MENU"<<endl;
	gotoxy(78,14);
	cout<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<endl;			//11
	
	gotoxy(58,16);
	for(i=0;i<51;++i)cout<<(char)220;
	cout<<endl;
	
	gotoxy(58,17); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,18); cout<<(char)186<<"  >> 1.  ITEMS & STOCK CENTRAL                   "<<(char)186<<endl;
	gotoxy(58,19); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,20); cout<<(char)186<<"  >> 2.  SALES & BILLING CENTRAL                 "<<(char)186<<endl;
	gotoxy(58,21); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,22); cout<<(char)186<<"  >> 3.  CREDIT & DEBIT CENTRAL                  "<<(char)186<<endl;
	gotoxy(58,23); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,24); cout<<(char)186<<"  >> 4.  ADMIN TOOLS                             "<<(char)186<<endl;
	gotoxy(58,25); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,26); cout<<(char)186<<"  >> 5.  LOG OFF                                 "<<(char)186<<endl;
	gotoxy(58,27); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,28); cout<<(char)186<<"  >> 6.  EXIT                                    "<<(char)186<<endl;
	gotoxy(58,29); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,30);
	for(i=0;i<51;++i)
		cout<<(char)223;
	cout<<endl;

}

void items_menu()
{
	int i=0;

	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(73 , 13) ;
	cout<<"ITEMS & STOCK CENTRAL"<<endl;
	gotoxy(72,14);
	for(i = 1 ; i <= strlen("ITEMS & STOCK CENTRAL")+2 ; ++i )
		cout<<char(205);
		
	cout<<endl;
	gotoxy(58,16);
	for(i=0;i<51;++i)cout<<(char)220;
	cout<<endl;
	
	gotoxy(58,17); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,18); cout<<(char)186<<"  >> 1.  NEW PRODUCT ENTRY                       "<<(char)186<<endl;
	gotoxy(58,19); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,20); cout<<(char)186<<"  >> 2.  EDIT PRODUCT ENTRY                      "<<(char)186<<endl;
	gotoxy(58,21); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,22); cout<<(char)186<<"  >> 3.  SEARCH PRODUCT ENTRY                    "<<(char)186<<endl;
	gotoxy(58,23); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,24); cout<<(char)186<<"  >> 4.  ADD PRODUCT STOCK                       "<<(char)186<<endl;
	gotoxy(58,25); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,26); cout<<(char)186<<"  >> 5.  VIEW ALL-ITEMS LIST                     "<<(char)186<<endl;
	gotoxy(58,27); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,28); cout<<(char)186<<"  >> 0.  MAIN MENU                               "<<(char)186<<endl;
	gotoxy(58,29); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,30);
	for(i=0;i<51;++i)
		cout<<(char)223;
	cout<<endl;
}

void items_control()
{
	int flag = 0 , i = 0 , go = 1 ;
	char ch='' , choice='';
	product p , p_ ;
	fstream mainfile , newfile ;
	
	do{
		header();
		items_menu();
		
		if ( flag == 0 )
			msg_box("!!==WELCOME TO SUPER STORE, PONNANI==!!");
			
		if ( flag == 1 )
			msg_box("!!==INVALID CHOICE==!!");
		
		if ( flag == 2 )
			msg_box("!!!===<<< UNDER CONSTRUCTION >>>===!!!");
			
		if ( flag == 3 )
			msg_box("!!!===NO PRODUCT ENTRIES CREATED===!!!");
		
		flag = 0 ;
		ch = '' ;
		i = 0 ;
		go = 0 ;
		
		
		cout<<endl;
		gotoxy(69,35);	
		cout<<"===>>  YOUR CHOICE    :    "<<endl;
	
		while ( (int)ch!= 13 )
		{
			gotoxy ( 97 , 35 );	
			 ch=getch();
			
			if ( !i && (int)ch == 13 ) 
			{	
				ch = '' ;
				continue ;
			}
			
			if ( (int)ch != 13 && (int)ch != 8 )
			{
				i = 1 ;
				choice = ch ;
			}
			

			if ( i && (int)ch == 13 ) break ;

			if ( i && (int)ch == 8 )
			{
				i = 0 ;
				gotoxy(97,35);cout<<" ";
				ch='' ;
			}
		
			if ( i>=0 ) 
			{
				gotoxy ( 97 , 35 ) ;
				printf("%c" , ch);
				cout<<endl;
			}

			
		}

		if ( (int)choice >= 48 && (int)choice <=53 ) flag = 0 ;
		else if ( (int) choice == 13 || choice == '' ) flag = 0 ;
		else flag = 1 ;
		
		switch ( choice )
		{
			case '1':
			
				do
				{
					if ( !go )
						go = p.enter_data();
					else
						go = p.enter_data(3);
						
					if ( go )
					{
						mainfile.open("prod_list.bin",ios::app|ios::binary);

						mainfile.write((char*)&p , sizeof(product) );
						
						mainfile.close();
					}
					
				}while(go);
				break;
			case '2':			
				mainfile.open("prod_list.bin",ios::in|ios::binary);
				if(!mainfile.read((char*)&p,sizeof(product)))
				{
					mainfile.close();
					flag = 3 ;
				}
				else 
				{
					mainfile.close();
					search_product("EDIT");
				}
				
				break;
			case '3':
				flag = 2 ;
				break;
			case '4':
				mainfile.open("prod_list.bin",ios::in|ios::binary);
				
				if(!mainfile.read((char*)&p,sizeof(product)))
				{
					flag = 3 ;
					mainfile.close();
				}
				else 
				{
					mainfile.close();
					search_product("STCK");
				}
				break;
			case '5':
				mainfile.open("prod_list.bin",ios::in|ios::binary);
				
				if(!mainfile.read((char*)&p,sizeof(product)))
				{
					flag = 3 ;
					mainfile.close();
				}
				else 
				{
					mainfile.close();
					show_data( "PRODUCT" , "ALL" );
				}
				break;
			case '0':
				return ;
				break;			
			default:
				break;
		}
		
	}while( choice != '0' ) ;
	
	return ;

}

void sales_menu()
{
	int i=0;

	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(72 , 13) ;
	cout<<"SALES & BILLING CENTRAL"<<endl;
	gotoxy(71,14);
	for(i = 1 ; i <= strlen("SALES & BILLING CENTRAL")+2 ; ++i )
		cout<<char(205);
		
	cout<<endl;
	gotoxy(58,16);
	for(i=0;i<51;++i)cout<<(char)220;
	cout<<endl;
	
	gotoxy(58,17); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,18); cout<<(char)186<<"  >> 1.  INVOICE BILLING                         "<<(char)186<<endl;
	gotoxy(58,19); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,20); cout<<(char)186<<"  >> 2.  VIEW PAST INVOICES                      "<<(char)186<<endl;
	gotoxy(58,21); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,22); cout<<(char)186<<"  >> 3.  SALES HISTORY                           "<<(char)186<<endl;
	gotoxy(58,23); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,24); cout<<(char)186<<"  >> 0.  MAIN MENU                               "<<(char)186<<endl;
	gotoxy(58,25); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,26);
	for(i=0;i<51;++i)
		cout<<(char)223;
	cout<<endl;
}

void sales_control()
{
	int flag = 0 , i = 0 ;
	char ch='' , choice='';
	fstream mainfile , newfile ;
	bill b ;
	
	do{
		header();
		sales_menu();
		
		if ( flag == 0 )
			msg_box("!!==WELCOME TO SUPER STORE, PONNANI==!!");
			
		if ( flag == 1 )
			msg_box("!!==INVALID CHOICE==!!");
		
		if ( flag == 2 )
			msg_box("!!!===<<< UNDER CONSTRUCTION >>>===!!!");
		
		flag = 0 ;
		ch = '' ;
		i = 0 ;
		
		
		cout<<endl;
		gotoxy(69,35);	
		cout<<"===>>  YOUR CHOICE    :    "<<endl;
	
		while ( (int)ch!= 13 )
		{
			gotoxy ( 97 , 35 );	
			 ch=getch();
			
			if ( !i && (int)ch == 13 ) 
			{	
				ch = '' ;
				continue ;
			}
			
			if ( (int)ch != 13 && (int)ch != 8 )
			{
				i = 1 ;
				choice = ch ;
			}
			

			if ( i && (int)ch == 13 ) break ;

			if ( i && (int)ch == 8 )
			{
				i = 0 ;
				gotoxy(97,35);cout<<" ";
				ch='' ;
			}
		
			if ( i>=0 ) 
			{
				gotoxy ( 97 , 35 ) ;
				printf("%c" , ch);
				cout<<endl;
			}

			
		}

		if ( (int)choice >= 48 && (int)choice <=51 ) flag = 0 ;
		else if ( (int) choice == 13 || choice == '' ) flag = 0 ;
		else flag = 1 ;

		switch ( choice )
		{
			case '1':
				mainfile.open("bill_list.bin" , ios::in | ios::binary ) ;
				mainfile.seekg(0,ios::end);
				int pos = mainfile.tellg();
				pos = pos / sizeof(bill);
				mainfile.close () ;
				
				do
				{
					flag = b.new_bill(++pos);
					
					if ( flag == 2 )
					{
						
						mainfile.open("bill_list.bin",ios::app|ios::binary) ;
						mainfile.write((char*)&b , sizeof(bill) ) ;
						mainfile.close();
					}
					
					if ( flag == -1 )
						break ; 
					
				}while(!flag||flag) ; 
				
				break;
			case '2':
				bill_show();
				break;
			case '3':
				sales_history();
				break;
			case '0':
				return ;
				break;			
			default:
				break;
		}
		
	}while( choice != '0' ) ;
	
	return ;

}


void credit_menu()
{
	int i=0;

	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(73 , 13) ;
	cout<<"CREDIT & DEBIT CENTRAL"<<endl;
	gotoxy(72,14);
	for(i = 1 ; i <= strlen("CREDIT & DEBIT CENTRAL")+2 ; ++i )
		cout<<char(205);
		
	cout<<endl;
	gotoxy(58,16);
	for(i=0;i<51;++i)cout<<(char)220;
	cout<<endl;
	
	gotoxy(58,17); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,18); cout<<(char)186<<"  >> 1.  NEW CUSTOMER ENTRY                      "<<(char)186<<endl;
	gotoxy(58,19); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,20); cout<<(char)186<<"  >> 2.  NEW CREDIT ENTRY                        "<<(char)186<<endl;
	gotoxy(58,21); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,22); cout<<(char)186<<"  >> 3.  CREDIT PAYMENT                          "<<(char)186<<endl;
	gotoxy(58,23); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,24); cout<<(char)186<<"  >> 4.  VIEW ALL-CREDITED CUSTOMERS             "<<(char)186<<endl;
	gotoxy(58,25); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,26); cout<<(char)186<<"  >> 5.  VIEW CUSTOMER CREDIT HISTORY            "<<(char)186<<endl;
	gotoxy(58,27); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,28); cout<<(char)186<<"  >> 0.  MAIN MENU                               "<<(char)186<<endl;
	gotoxy(58,29); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,30);
	for(i=0;i<51;++i)
		cout<<(char)223;
	cout<<endl;
}

void credit_control()	
{
	int flag = 0 , i = 0 , go = 1 , ccp = 0  ;
	float k = 0 ;
	char ch='' , choice='';
	customer c , c1 ;
	fstream mainfile , newfile ;
	
	do{
		header();
		credit_menu();
		
		if ( flag == 0 )
			msg_box("!!==WELCOME TO SUPER STORE, PONNANI==!!");
			
		if ( flag == 1 )
			msg_box("!!==INVALID CHOICE==!!");
		
		if ( flag == 2 )
			msg_box("!!!===<<< UNDER CONSTRUCTION >>>===!!!");
			
		if ( flag == 3 )
			msg_box("!!!===NO CUSTOMER ENTRIES CREATED===!!!");
		
		flag = 0 ;
		ch = '' ;
		i = 0 ;
		go = 0 ;
		ccp = 0 ;
		
		cout<<endl;
		gotoxy(69,35);	
		cout<<"===>>  YOUR CHOICE    :    "<<endl;
	
		while ( (int)ch!= 13 )
		{
			gotoxy ( 97 , 35 );	
			 ch=getch();
			
			if ( !i && (int)ch == 13 ) 
			{	
				ch = '' ;
				continue ;
			}
			
			if ( (int)ch != 13 && (int)ch != 8 )
			{
				i = 1 ;
				choice = ch ;
			}
			

			if ( i && (int)ch == 13 ) break ;

			if ( i && (int)ch == 8 )
			{
				i = 0 ;
				gotoxy(97,35);cout<<" ";
				ch='' ;
			}
		
			if ( i>=0 ) 
			{
				gotoxy ( 97 , 35 ) ;
				printf("%c" , ch);
				cout<<endl;
			}

			
		}

		if ( (int)choice >= 48 && (int)choice <=53 ) flag = 0 ;
		else if ( (int) choice == 13 || choice == '' ) flag = 0 ;
		else flag = 1 ;

		switch ( choice )
		{
			case '1':
				mainfile.open("cust_list.bin",ios::in|ios::binary);
				while(mainfile.read((char*)&c , sizeof(customer)))
					++ccp ;
				mainfile.close();
				
				do
				{	
					
					if ( !go )
						go = c.enter_data(0,++ccp);
					else
						go = c.enter_data(3,++ccp);
						
					if ( go )
					{
						if(ccp>1)
						{
							flag = 0 ;
							mainfile.open("cust_list.bin",ios::in|ios::binary);
							newfile.open ("temp.bin",ios::out|ios::binary);
							while(mainfile.read((char*)&c1 , sizeof(customer)))
							{
								if( !strcmp(c1.name , "HERE") && !flag ) 
								{
									c.icode = c1.icode ;
									c.get_ccode(c.icode);
									newfile.write((char*)&c,sizeof(customer));
									flag = 1 ; 
								}
								if ( !flag || flag == 2 )
								{
									newfile.write((char*)&c1,sizeof(customer));
								}
								if ( flag == 1 ) flag = 2 ;
							}
							if(!flag)
							{
								c.icode = ccp ;
								c.get_ccode(ccp);
								newfile.write((char*)&c,sizeof(customer));
							}
							mainfile.close();
							newfile.close();
							remove("cust_list.bin");
							rename("temp.bin","cust_list.bin");
						}
						else
						{
							mainfile.open("cust_list.bin",ios::app|ios::binary);
							mainfile.write((char*)&c,sizeof(customer));
							mainfile.close();
						}
					}
					
				}while(go);
				break;
			case '2':
				mainfile.open("cust_list.bin",ios::in|ios::binary);
				if(!mainfile.read((char*)&c,sizeof(customer)))
				{
					flag = 3 ;
					mainfile.close();			
				}
				else 
				{
					mainfile.close();			
					search_customer( "CREDIT ENTRY" , &k );
				}
				
				break;
			case '3':
				mainfile.open("cust_list.bin",ios::in|ios::binary);
				if(!mainfile.read((char*)&c,sizeof(customer)))
				{
					flag = 3 ;
					mainfile.close();			
				}
				else 
				{	
					mainfile.close();			
					search_customer( "CREDIT PAY" , &k ) ;
				}
				break;
			case '4':
				mainfile.open("cust_list.bin",ios::in|ios::binary);
				if(!mainfile.read((char*)&c,sizeof(customer)))
				{
					flag = 3 ;
					mainfile.close();					
				}
				else 
				{
					mainfile.close();					
					show_data( "CUSTOMER" , "ALL" );
				}
				mainfile.close();
				break;
			case '5':
				mainfile.open("cust_list.bin",ios::in|ios::binary);
				if(!mainfile.read((char*)&c,sizeof(customer)))
				{
					mainfile.close();
					flag = 3 ;
				}
				else
				{
					mainfile.close();
					search_customer( "SPECIFIC" , &k )  ;
				}
				break ;
			case '0':
				return ;
				break;			
			default:
				break;
		}
		
	}while( choice != '0' ) ;
	
	return ;

}

void admin_menu()
{
	int i=0;

	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(78 , 13) ;
	cout<<"ADMIN TOOLS"<<endl;
	gotoxy(77,14);
	for(i = 1 ; i <= strlen("ADMIN TOOLS")+2 ; ++i )
		cout<<char(205);
	cout<<endl;
	
	gotoxy(58,16);
	for(i=0;i<51;++i)cout<<(char)220;
	cout<<endl;
	
	gotoxy(58,17); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,18); cout<<(char)186<<"  >> 1.  CHANGE USERNAME & PASSWORD              "<<(char)186<<endl;
	gotoxy(58,19); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,20); cout<<(char)186<<"  >> 2.  BACKUP SYSTEM                           "<<(char)186<<endl;
	gotoxy(58,21); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,22); cout<<(char)186<<"  >> 3.  DAILY CLOSING                           "<<(char)186<<endl;
	gotoxy(58,23); cout<<(char)186<<"                                                 "<<(char)186<<endl;	
	gotoxy(58,24); cout<<(char)186<<"  >> 4.  ACTIVITY LOG                            "<<(char)186<<endl;
	gotoxy(58,25); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,26); cout<<(char)186<<"  >> 5.  DATABASE STATUS                         "<<(char)186<<endl;
	gotoxy(58,27); cout<<(char)186<<"                                                 "<<(char)186<<endl;
	gotoxy(58,28); cout<<(char)186<<"  >> 0.  MAIN MENU                               "<<(char)186<<endl;
	gotoxy(58,29); cout<<(char)219<<"                                                 "<<(char)219<<endl;
	gotoxy(58,30);
	for(i=0;i<51;++i)
		cout<<(char)223;
	cout<<endl;
}

void admin_control()
{
	int flag = 0 , i = 0 ;
	char ch='' , choice='';
	
	do{
		header();
		admin_menu();
		
		if ( flag == 0 )
			msg_box("!!==WELCOME TO SUPER STORE, PONNANI==!!");
			
		if ( flag == 1 )
			msg_box("!!==INVALID CHOICE==!!");
		
		if ( flag == 2 )
			msg_box("!!!===<<< UNDER CONSTRUCTION >>>===!!!");
			
		if ( flag == 3 )
			msg_box("!!!===BACKUP SUCCESSFULLY CREATED===!!!");
		
		if ( flag == 4 )
			msg_box("** !! SORRY !! ** CONNECT TO INTERNET TO CREATE BACKUP **");
		
		flag = 0 ;
		ch = '' ;
		i = 0 ;
		
		
		cout<<endl;
		gotoxy(69,35);	
		cout<<"===>>  YOUR CHOICE    :    "<<endl;
	
		while ( (int)ch!= 13 )
		{
			gotoxy ( 97 , 35 );	
			 ch=getch();
			
			if ( !i && (int)ch == 13 ) 
			{	
				ch = '' ;
				msg_box("!!==WELCOME TO SUPER STORE, PONNANI==!!");
				continue ;
			}
			
			if ( (int)ch != 13 && (int)ch != 8 )
			{
				i = 1 ;
				choice = ch ;
			}
			

			if ( i && (int)ch == 13 ) break ;

			if ( i && (int)ch == 8 )
			{
				i = 0 ;
				gotoxy(97,35);cout<<" ";
				ch='' ;
			}
		
			if ( i>=0 ) 
			{
				gotoxy ( 97 , 35 ) ;
				printf("%c" , ch);
				cout<<endl;
			}

			
		}

		if ( (int)choice >= 48 && (int)choice <=53 ) flag = 0 ;
		else if ( (int) choice == 13 || choice == '' ) flag = 0 ;
		else flag = 1 ;

		switch ( choice )
		{
			case '1':
				flag = 2 ;
				break;
			case '2':
				
				char str[150]="" , dir[150] = "" ;
				flag = 0 ;
				fstream file ;
				
				msg_box("... .. . PLEASE WAIT . .. ...");
				
				system("ping www.google.com > net.txt");
				
				file.open("net.txt" , ios::in ) ;
				while(!file.eof())
				{
					file.getline ( str , 150 );
					if ( !strcmp ( str , "Ping request could not find host www.google.com. Please check the name and try again."))
						flag = 4 ;
					if ( !strcmp ( str , "Reply from 192.168.43.1: Destination net unreachable."))
						flag = 4 ;
					if ( flag == 4 ) break ;
				}
				file.close() ;
				remove("net.txt");
				
				if ( flag == 4 )
				{
					break ;
				}
				
				strcpy( dir , "C:\\Users\\azharakbar\\OneDrive\\" );
				strcat( dir , curr_date ) ;
				
				strcpy(str,"mkdir ");
				strcat(str , dir);
				system (str);
				
				strcpy(str,"copy /y ssp_main.cpp ");
				strcat(str , dir);
				system(str);
				
				strcpy(str,"copy /y cust_list.bin ");
				strcat(str , dir);
				system(str);
				
				strcpy(str,"copy /y prod_list.bin ");
				strcat(str , dir);
				system(str);
				
				strcpy(str,"copy /y bill_list.bin ");
				strcat(str , dir);
				system(str);
				
				strcpy(str,"start ");
				strcpy( dir , "C:\\Users\\azharakbar\\OneDrive\\" );
				strcat(str , dir);
				system(str);
				
				flag = 3 ;
				
				break;
			case '3':
				flag = 2 ;
				break;
			case '4':
				flag = 2 ;
				break;
			case '5':
				flag = 2 ;
				break;
			case '0':
				return ;
				break;			
			default:
				break;
		}
		
	}while( choice != '0' ) ;
	
	return ;

}

void show_data(char cname[] , char type[] )
{
	int i = 0 , z =  1 , total = 0 , total_credit = 0 , total_stock_out = 0 , j = 0 , tab = 0 ;
	char msg[150]="" , tot[10]="" , ch = '';
	fstream file ;
	customer c ;
	product p ;
	
	if ( !strcmpi(cname , "CUSTOMER") )
	{
		file.open("cust_list.bin",ios::in|ios::binary);
		while(file.read((char*)&c,sizeof(customer)))
		{
			++total ;
			if(c.tot_cr) ++total_credit ;
		}
		file.close();
			
		if ( !strcmpi(type , "ALL") )
		{
			strcat( msg , "|| ** TOTAL CUSTOMERS = ");
			strcat( msg , itoa(total,tot,10) );
			strcat( msg , " ** || ** TOTAL CREDITED CUSTOMERS = ");
			strcat( msg , itoa(total_credit,tot,10));
			strcat( msg , " ** ||");
		}
	}
	
	if ( !strcmpi(cname , "PRODUCT") )
	{
		file.open("prod_list.bin",ios::in|ios::binary);
		while(file.read((char*)&p,sizeof( product )))
		{
			++total ;
			if ( p.stock == 0 ) ++total_stock_out ;
		}
		file.close();
			
		if ( !strcmpi(type , "ALL") )
		{
			strcat( msg , "|| ** TOTAL PRODUCTS = ");
			strcat( msg , itoa(total,tot,10) );
			strcat( msg , " ** || ** TOTAL PRODUCTS OUT OF STOCK = ");
			strcat( msg , itoa(total_stock_out,tot,10));
			strcat( msg , " ** ||");
		}
	}
	
	if ( !strcmpi(cname , "CUSTOMER") && !strcmpi(type , "ALL"))
	{
	
		file.open("cust_list.bin",ios::in|ios::binary);
TEMPLATE_CUST:

		header();
		msg_box(msg);
		gotoxy(0,0);cout<<endl;
		gotoxy(73 , 13) ;
		cout<<"ALL-CREDITED CUSTOMERS"<<endl;
		gotoxy(72,14);
		for(j = 1 ; j <= strlen("ALL-CREDITED CUSTOMERS")+2 ; ++j )
			cout<<char(205);
		cout<<endl;	
		
		gotoxy ( 0 , 16 ) ;
		for ( j = 0 ; j < 168 ; ++j ) cout<<(char)223;
		cout<<endl;
		gotoxy ( 0 , 20 ) ;
		for ( j = 0 ; j < 168 ; ++j ) cout<<(char)220;
		cout<<endl;
		gotoxy ( 5 , 18 ) ;  cout << "CODE"<<endl;
		gotoxy ( 25 , 18 );  cout << "CUSTOMER NAME" <<endl ;
		gotoxy ( 105 , 18 ); cout << "NET CREDIT (INR) "<<endl;
		gotoxy ( 140 , 18 ); cout << "CONTACT NUMBER" <<endl;
			
		if ( i == 13 ) 
		{
			i = 0 ;
			file.seekp(-1*sizeof(customer),ios::cur);
			goto TEMP_CUST ;
		}
		
		i = 0;
		
TEMP_CUST:
		while(file.read((char*)&c,sizeof(customer)))
		{
			cout<<endl;
			c.show_data("ALL", 22+(2*i));
			++i;
			cout<<endl;
			if ( i == 13 && file.read((char*)&c,sizeof(customer)) )
			{
				gotoxy(65 , 49);
				cout<<"!!...HIT >> ENTER << TO VIEW MORE...!!"<<endl;
				
				ch = '';
				while( (int)ch!=13 )	{ gotoxy(105,49); ch=getch(); }
				goto TEMPLATE_CUST;
			}
		}


		file.close();	
	}
	
	
	if ( !strcmpi(cname , "PRODUCT") && !strcmpi(type , "ALL"))
	{
	
		file.open("prod_list.bin",ios::in|ios::binary);
TEMPLATE_PROD:

		header();
		msg_box(msg);
		gotoxy(0,0);cout<<endl;
		gotoxy(78 , 13) ;
		cout<<"ALL PRODUCTS"<<endl;
		gotoxy(77 ,14);
		for(j = 1 ; j <= strlen("ALL PRODUCTS")+2 ; ++j )
			cout<<char(205);
		cout<<endl;	
		
		gotoxy ( 0 , 16 ) ;
		for ( j = 0 ; j < 168 ; ++j ) cout<<(char)223;
		cout<<endl;
		gotoxy ( 0 , 20 ) ;
		for ( j = 0 ; j < 168 ; ++j ) cout<<(char)220;
		cout<<endl;
		gotoxy ( 5 , 18 ) ;  cout << "BARCODE"<<endl;
		gotoxy ( 35 , 18 );  cout << "PRODUCT NAME" <<endl ;
		gotoxy ( 105 , 18 ); cout << "UNIT PRICE (INR) "<<endl;
		gotoxy ( 140 , 18 ); cout << "STOCK" <<endl;
			
		if ( i == 13 ) 
		{
			i = 0 ;
			file.seekp(-1*sizeof(product),ios::cur);
			goto TEMP_PROD ;
		}
		
		i = 0;
		
TEMP_PROD:
		while(file.read((char*)&p,sizeof(product)))
		{
			cout<<endl;
			p.show_data("ALL", 22+(2*i));
			++i;
			cout<<endl;
			if ( i == 13 && file.read((char*)&p,sizeof(product)) )
			{
				gotoxy(65 , 49);
				cout<<"!!...HIT >> ENTER << TO VIEW MORE...!!"<<endl;
				
				ch = '';
				while( (int)ch!=13 )	{ gotoxy(105,49); ch=getch(); }
				goto TEMPLATE_PROD;
			}
		}


		file.close();	
	}	
	
	
	
	ch = '' ;
	gotoxy(62 , 49);
	cout<<"!!...HIT >> ENTER << TO GO BACK TO MENU...!!"<<endl;
	while((int)ch!=13 )	{ gotoxy(107,49); ch=getch(); }	
	return ;
	

}

void search_customer( char purpose [] , float* val , int inv_no )
{
	int i=0 , j=0 , flag = 0 , rslt = 0 ;
	char ch = '' , cust_name[50] = "" , temp[150] = "" , msg[150] = "" ;
	fstream mainfile , newfile ;
	customer c , c_found , c_found_same ;

	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(77 , 13) ;
	cout<<"CUSTOMER SEARCH"<<endl;
	gotoxy(76,14);
	for(i = 1 ; i <= strlen("CUSTOMER SEARCH")+2 ; ++i )
		cout<<char(205);
	cout<<endl;		
	
	gotoxy ( 0 , 17 ) ;
	cout << "     >> CUSTOMER NAME    :       " ;
	cout<<endl;
	gotoxy ( 0 , 18 ) ;
	for ( j = 0 ; j < 168 ; ++j ) cout<<(char)220;
	cout<<endl;	
	
	i = 0 ;
	do
	{
		
		gotoxy( 34 , 17 );	

		while ( (int)ch!= 13 )
		{
			if ( !i )
			{
				strcpy ( msg , "!!...ENTER CUSTOMER NAME TO SEARCH...!!" ) ;
				msg_box( msg);
			}		
			
			else if ( i && !rslt ) 
			{
				strcpy ( msg , "!!...NO SEARCH RESULTS TO DISPLAY...!!" ) ;
				msg_box( msg );
			}
			
			else if ( i && rslt == 1 )
			{
				strcpy ( msg , "HIT >> ENTER << TO PROCEED WITH THIS CUSTOMER" ) ;
				msg_box( msg );
			}
			
			else
			{
				itoa ( rslt , temp , 10 ) ;
				strcpy ( msg , "" );
				strcpy(msg , "** DISPLAYING " ) ;
				strcat ( msg , temp ) ;
				strcat ( msg ," SEARCH RESULTS **") ;
				msg_box (msg) ;
			}
			
			gotoxy ( 34+strlen(cust_name) , 17 ) ;
			
			ch=getch();
						
			if ( cust_name[0]=='0' && i==1 && (int)ch == 13 )
			{
				*val = 0 ;
				return  ;
			}			
				
			if ( ( !rslt || rslt > 1 ) && !strcmp(c_found_same.name , "" ) && (int)ch == 13 ) 
			{	
				ch = '' ;
				continue ;
			}
			
			if ( ( !rslt || rslt > 1 ) && strcmp(c_found_same.name , "" ) && (int)ch == 13 ) 
			{	
				c_found = c_found_same ;
				flag = 2 ;
				break ;
			}			
			
			if ( rslt == 1 && (int)ch == 13 ) 
			{
				flag = 2 ;
				break ;
			}
			
			if ( (int)ch != 8 && (int)ch != 13 && (int)ch != 9 ) 
				if ( i !=47 )
				{
					cust_name[i++] = toupper(ch) ;
					cust_name[i] = '\0' ;
				}
				
			if ( (int)ch == 8 )
				if ( i != 0 )
				{
						--i ;
						cust_name[i] = '\0' ;
				}
				else
						i = 0 ;		
		
			
			
			if ( i>=0 ) 
			{
				gotoxy ( 34 , 17 ) ;
				printf("                                                           ") ;
				cout<<endl;
				if ( i == 1 || !rslt )
				{
					gotoxy ( 66 , 25 ) ; cout<<"                                                                 "<<endl;
				}
				gotoxy ( 34 , 17  ) ;
				for ( j=0 ; cust_name[j]!='\0' ; ++j)
					printf("%c" , cust_name[j]);
					
				mainfile.open("cust_list.bin",ios::in|ios::binary);
				
				if ( !i ) 
				{
					for ( int z = 21 ; z <= 21+(2*rslt) ; ++z )
					{
						for ( int k = 5 ; k < 151  ; ++k )
						{
							cout<<endl ;
							gotoxy( k , z ) ;
							cout<<" " ;
							cout<<endl ;
						}
					}
					rslt = 0 ;					
				}
				
				if( i > 0 )
				{
					for ( int z = 21 ; z <= 21+(2*rslt) ; ++z )
					{
						for ( int k = 5 ; k < 151  ; ++k )
						{
							cout<<endl ;
							gotoxy( k , z ) ;
							cout<<" " ;
							cout<<endl ;
						}
					}
					rslt = 0 ;
					strcpy(c_found_same.name , "" );
					while (mainfile.read((char*)&c , sizeof(customer)))
					{
						if ( strstr(c.name , cust_name ))
						{
							if ( rslt == 14 ) break ;
							c.show_data("ALL" , 21+(rslt*2) ) ;
							c_found = c ;
							if (!strcmp(c.name , cust_name)) c_found_same = c ;
							++rslt ; 
						}
					}
				}
				
				mainfile.close();
			}
			
		}
		
		if ( flag == 2 ) break ;

	}while ( !flag || flag ) ;
	
	if ( flag && !strcmpi ( purpose , "BILL" ) )
	{
		flag = c_found.credit_entry(val,inv_no);
		
		if ( !flag ) *val = 0 ;
		
		mainfile.open("cust_list.bin" , ios::in|ios::binary);
		newfile.open ("temp.bin" , ios::out|ios::binary);
		while(mainfile.read((char*)&c , sizeof(customer)))
		{
			if ( c.icode == c_found.icode )
				c = c_found ;
			newfile.write((char*)&c , sizeof(customer) );
		}
		newfile.close();
		mainfile.close();
		remove("cust_list.bin");
		rename("temp.bin" , "cust_list.bin");
		
		return ;
	}
	
	if ( flag && !strcmpi ( purpose , "CREDIT ENTRY" ) ) 
	{
		flag = c_found.credit_entry();
		
		mainfile.open ( "cust_list.bin" , ios::in|ios::binary ) ;
		newfile.open ("temp.bin" , ios::out|ios::binary);
		
		while( mainfile.read ((char*)&c , sizeof(customer) ) )
		{
			if ( c.icode == c_found.icode )
				c = c_found ;
			newfile.write((char*)&c , sizeof(customer) ) ;
		}
		
		newfile.close();
		mainfile.close();
		
		remove("cust_list.bin");
		rename("temp.bin" , "cust_list.bin");
		
	}
	
	if ( flag && !strcmpi ( purpose , "CREDIT PAY" ) ) 
	{
		flag = c_found.credit_pay();	
		mainfile.open ( "cust_list.bin" , ios::in|ios::binary ) ;
		newfile.open ("temp.bin" , ios::out|ios::binary);
		
		while( mainfile.read ((char*)&c , sizeof(customer) ) )
		{
			if ( c.icode == c_found.icode )
			{
				c = c_found ;
			}
			newfile.write((char*)&c , sizeof(customer) ) ;
		}
		
		newfile.close();
		mainfile.close();
		
		remove("cust_list.bin");
		rename("temp.bin"  , "cust_list.bin");
		
	}
	
	if ( flag && !strcmpi ( purpose , "SPECIFIC" ) )
	{
		header();
		gotoxy(0,0);cout<<endl;
		gotoxy(77 , 13) ;
		cout<<"CUSTOMER INFO"<<endl;
		gotoxy(76,14);
		for(i = 1 ; i <= strlen("CUSTOMER INFO")+2 ; ++i )
			cout<<char(205);
		cout<<endl;
		
		msg_box("|| ** HIT >> ENTER << TO CONTINUE ** ||");
	
		c_found.show_data("SINGLE");
	}
}

void search_product( char purpose [] )
{
	int i=0 , j=0 , flag = 0 , rslt = 0 ;
	char ch = '' , prod_name[50] = "" , prod_bc[20] = "" , temp[150] = "" , msg[150] = "" ;
	fstream mainfile , newfile ;
	product p , p_found , p_found_same ;

SEARCH_NAME:
	i=0 , j=0 , flag = 0 , rslt = 0 ;
	strcpy(prod_name,"");strcpy(temp,"");
	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(77 , 13) ;
	cout<<"PRODUCT SEARCH"<<endl;
	gotoxy(76,14);
	for(i = 1 ; i <= strlen("PRODUCT SEARCH")+2 ; ++i )
		cout<<char(205);
	cout<<endl;		
	
	gotoxy ( 0 , 17 ) ;
	cout << "     >> PRODUCT NAME    :       " ;
	cout<<endl;
	gotoxy ( 0 , 18 ) ;
	for ( j = 0 ; j < 168 ; ++j ) cout<<(char)220;
	cout<<endl;	
	
	i = 0 ;
	do
	{
		
		gotoxy( 34 , 17 );	

		while ( (int)ch!= 13 )
		{
			if ( !i )
			{
				strcpy ( msg , "!!...ENTER PRODUCT NAME TO SEARCH...!!...HIT >>TAB<< TO TOGGLE SEARCH...!!" ) ;
				msg_box( msg);
			}		
			
			else if ( i && !rslt ) 
			{
				strcpy ( msg , "!!...NO SEARCH RESULTS TO DISPLAY...!!" ) ;
				msg_box( msg );
			}
			
			else if ( i && rslt == 1 )
			{
				strcpy ( msg , "HIT >> ENTER << TO PROCEED WITH THIS PRODUCT" ) ;
				msg_box( msg );
			}
			
			else
			{
				itoa ( rslt , temp , 10 ) ;
				strcpy ( msg , "" );
				strcpy(msg , "** DISPLAYING " ) ;
				strcat ( msg , temp ) ;
				strcat ( msg ," SEARCH RESULTS **") ;
				msg_box (msg) ;
			}
			
			gotoxy ( 34+strlen(prod_name) , 17 ) ;
			
			ch=getch();
			
			if ( !i && (int)ch == 9 ) goto SEARCH_BC ;
						
			if ( prod_name[0]=='0' && i==1 && (int)ch == 13 )
				return  ;
				
			if ( ( !rslt || rslt > 1 ) && !strcmp(p_found_same.name , "" ) && (int)ch == 13 ) 
			{	
				ch = '' ;
				continue ;
			}
			
			if ( ( !rslt || rslt > 1 ) && strcmp(p_found_same.name , "" ) && (int)ch == 13 ) 
			{	
				p_found = p_found_same ;
				flag = 2 ;
				break ;
			}			
			
			if ( rslt == 1 && (int)ch == 13 ) 
			{
				flag = 2 ;
				break ;
			}
			
			if ( (int)ch != 8 && (int)ch != 13 && (int)ch != 9 ) 
				if ( i !=47 )
				{
					prod_name[i++] = toupper(ch) ;
					prod_name[i] = '\0' ;
				}
				
			if ( (int)ch == 8 )
				if ( i != 0 )
				{
						--i ;
						prod_name[i] = '\0' ;
				}
				else
						i = 0 ;		
		
			
			
			if ( i>=0 ) 
			{
				gotoxy ( 34 , 17 ) ;
				printf("                                                           ") ;
				cout<<endl;
				if ( i == 1 || !rslt )
				{
					gotoxy ( 66 , 25 ) ; cout<<"                                                                 "<<endl;
				}
				gotoxy ( 34 , 17  ) ;
				for ( j=0 ; prod_name[j]!='\0' ; ++j)
					printf("%c" , prod_name[j]);
					
				mainfile.open("prod_list.bin",ios::in|ios::binary);
				
				if ( !i ) 
				{
					for ( int z = 21 ; z <= 21+(2*rslt) ; ++z )
					{
						for ( int k = 5 ; k < 151  ; ++k )
						{
							cout<<endl ;
							gotoxy( k , z ) ;
							cout<<" " ;
							cout<<endl ;
						}
					}
					rslt = 0 ;					
				}
				
				if( i > 0 )
				{
					for ( int z = 21 ; z <= 21+(2*rslt) ; ++z )
					{
						for ( int k = 5 ; k < 151  ; ++k )
						{
							cout<<endl ;
							gotoxy( k , z ) ;
							cout<<" " ;
							cout<<endl ;
						}
					}
					rslt = 0 ;
					strcpy(p_found_same.name , "" );
					while (mainfile.read((char*)&p , sizeof(product)))
					{
						if ( strstr(p.name , prod_name ))
						{
							if ( rslt == 14 ) break ;
							p.show_data("ALL" , 21+(rslt*2) ) ;
							p_found = p ;
							if (!strcmp(p.name , prod_name)) p_found_same = p ;
							++rslt ; 
						}
					}
				}
				
				mainfile.close();
			}
			
		}
		
		if ( flag == 2 ) break ;

	}while ( !flag || flag ) ;
	goto PURPOSE;
	
	
SEARCH_BC:
	i=0 , j=0 , flag = 0 , rslt = 0 ;
	strcpy(prod_bc,"");strcpy(temp,"");	ch=''; 
	
	gotoxy ( 0 , 17 ) ;
	cout << "     >> PRODUCT BARCODE :       " ;
	cout<<endl;
	gotoxy ( 0 , 18 ) ;
	for ( j = 0 ; j < 168 ; ++j ) cout<<(char)220;
	cout<<endl;	
	
	i = 0 ;
	do
	{
		
		gotoxy( 34 , 17 );	

		while ( (int)ch!= 13 )
		{
			if ( !i )
			{
				strcpy ( msg , "!!...ENTER PRODUCT BARCODE TO SEARCH...!!...HIT >>TAB<< TO TOGGLE SEARCH...!!" ) ;
				msg_box( msg);
			}		
			
			else if ( i && !rslt ) 
			{
				strcpy ( msg , "!!...NO SEARCH RESULTS TO DISPLAY...!!" ) ;
				msg_box( msg );
			}
			
			else if ( i && rslt == 1 )
			{
				strcpy ( msg , "HIT >> ENTER << TO PROCEED WITH THIS PRODUCT" ) ;
				msg_box( msg );
			}
			
			else
			{
				itoa ( rslt , temp , 10 ) ;
				strcpy ( msg , "" );
				strcpy(msg , "** DISPLAYING " ) ;
				strcat ( msg , temp ) ;
				strcat ( msg ," SEARCH RESULTS **") ;
				msg_box (msg) ;
			}
			
			gotoxy ( 34+strlen(prod_bc) , 17 ) ;
			
			ch=getch();
			
			if ( !i && (int)ch == 9 ) goto SEARCH_NAME ;
						
			if ( prod_bc[0]=='0' && i==1 && (int)ch == 13 )
			{
				return  ;
			}			
				
			if ( ( !rslt || rslt > 1 ) && !strcmp(p_found_same.barcode , "" ) && (int)ch == 13 ) 
			{	
				ch = '' ;
				continue ;
			}
			
			if ( ( !rslt || rslt > 1 ) && strcmp(p_found_same.barcode , "" ) && (int)ch == 13 ) 
			{	
				p_found = p_found_same ;
				flag = 2 ;
				break ;
			}			
			
			if ( rslt == 1 && (int)ch == 13 ) 
			{
				flag = 2 ;
				break ;
			}
			
			if ( (int)ch != 8 && (int)ch != 13 && (int)ch != 9 ) 
				if ( i !=47 )
				{
					prod_bc[i++] = toupper(ch) ;
					prod_bc[i] = '\0' ;
				}
				
			if ( (int)ch == 8 )
				if ( i != 0 )
				{
						--i ;
						prod_bc[i] = '\0' ;
				}
				else
						i = 0 ;		
		
			
			
			if ( i>=0 ) 
			{
				gotoxy ( 34 , 17 ) ;
				printf("                                                           ") ;
				cout<<endl;
				if ( i == 1 || !rslt )
				{
					gotoxy ( 66 , 25 ) ; cout<<"                                                                 "<<endl;
				}
				gotoxy ( 34 , 17  ) ;
				for ( j=0 ; prod_bc[j]!='\0' ; ++j)
					printf("%c" , prod_bc[j]);
					
				mainfile.open("prod_list.bin",ios::in|ios::binary);
				
				if ( !i ) 
				{
					for ( int z = 21 ; z <= 21+(2*rslt) ; ++z )
					{
						for ( int k = 5 ; k < 151  ; ++k )
						{
							cout<<endl ;
							gotoxy( k , z ) ;
							cout<<" " ;
							cout<<endl ;
						}
					}
					rslt = 0 ;					
				}
				
				if( i > 0 )
				{
					for ( int z = 21 ; z <= 21+(2*rslt) ; ++z )
					{
						for ( int k = 5 ; k < 151  ; ++k )
						{
							cout<<endl ;
							gotoxy( k , z ) ;
							cout<<" " ;
							cout<<endl ;
						}
					}
					rslt = 0 ;
					strcpy(p_found_same.barcode , "" );
					while (mainfile.read((char*)&p , sizeof(product)))
					{
						if ( strstr(p.barcode , prod_bc ))
						{
							if ( rslt == 14 ) break ;
							p.show_data("ALL" , 21+(rslt*2) ) ;
							p_found = p ;
							if (!strcmp(p.barcode , prod_bc)) p_found_same = p ;
							++rslt ; 
						}
					}
				}
				
				mainfile.close();
			}
			
		}
		
		if ( flag == 2 ) break ;

	}while ( !flag || flag ) ;
	
PURPOSE:
	if ( flag && !strcmpi ( purpose , "EDIT" ) )
	{
		header();
		gotoxy(0,0);cout<<endl;
		gotoxy(77 , 13) ;
		cout<<"PRODUCT INFO"<<endl;
		gotoxy(76,14);
		for(i = 1 ; i <= strlen("PRODUCT INFO")+2 ; ++i )
			cout<<char(205);
		cout<<endl;
		
		mainfile. open ( "prod_list.bin" , ios::in|ios::binary );
		newfile. open ( "temp.bin" , ios::out|ios::binary );
		
		while ( mainfile.read((char*) &p , sizeof (product) ))
		{
			if ( strcmp(p.barcode , p_found.barcode) ) 
				newfile.write((char*) &p , sizeof (product)) ;
		}
		
		mainfile.close();
		newfile.close();
		
		p_found.edit_data();
		
		flag = 0 ;
		
		newfile. open ( "temp.bin" , ios::app|ios::binary );
		
				newfile.write((char*)&p_found , sizeof(product)) ;
		
		newfile.close();				
		
		remove ( "prod_list.bin" ) ;
		rename ( "temp.bin" , "prod_list.bin" );		
	
	}
	
	if ( flag && !strcmpi ( purpose , "STCK" ) )
	{
		header();
		gotoxy(0,0);cout<<endl;
		gotoxy(77 , 13) ;
		cout<<"STOCK UPDATE"<<endl;
		gotoxy(76,14);
		for(i = 1 ; i <= strlen("STOCK UPDATE")+2 ; ++i )
			cout<<char(205);
		cout<<endl;
		
		mainfile. open ( "prod_list.bin" , ios::in|ios::binary );
		newfile. open ( "temp.bin" , ios::out|ios::binary );
		
		while ( mainfile.read((char*) &p , sizeof (product) ))
		{
			if ( strcmp(p.barcode , p_found.barcode) ) 
				newfile.write((char*) &p , sizeof (product)) ;
		}
		
		mainfile.close();
		newfile.close();
		
		p_found.add_stock();
		
		flag = 0 ;
		
		newfile. open ( "temp.bin" , ios::app|ios::binary );
		
				newfile.write((char*)&p_found , sizeof(product)) ;
		
		newfile.close();				
		
		remove ( "prod_list.bin" ) ;
		rename ( "temp.bin" , "prod_list.bin" );				
	
	}	
	
}

void convert(char str[])
{
	int i = 0 ;
	for ( i = 0 ; str[i]!='\0' ; ++i )
		str[i] = toupper(str[i]);
}

int scan( char str[] , char to_scan[])
{
	int i = 0 ;
	fstream file ;
	product p ;
	customer c ;
	
	if (!strcmp(to_scan,"barcode"))
	{
		file.open("prod_list.bin",ios::in|ios::binary);
		
		while (file.read((char*)&p,sizeof(product)))
			if(!strcmp((str) , p.barcode))
			{	
				file.close();
				return 0 ;
			}
		
		file.close();
		return 1 ;
	}
	
	if (!strcmp(to_scan,"name"))
	{
		file.open("cust_list.bin",ios::in|ios::binary);
		
		while (file.read((char*)&c,sizeof(customer)))
			if(!strcmpi(str , c.name))
			{	
				file.close();
				return 0 ;
			}
		
		file.close();
		return 1 ;
	}
	
	return 0;
}

void sales_history()
{
	fstream file ;
	bill b ;
	
	header() ; 
	int i=0 , j = 0 ;
	char ch = '' ;

	file.open ( "bill_list.bin" , ios::in|ios::binary );

VIEW_F_F:
	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(78 , 13) ;
	cout<<"SALES HISTORY"<<endl;
	gotoxy(77,14);
	for(i = 1 ; i <= strlen("SALES HISTORY")+2 ; ++i )
		cout<<char(205);
		
	cout<<endl;	
	i = 0 ;
	while ( file.read((char*)&b , sizeof(bill)) )
	{
		b.show_data("HISTORY" , 18+5*i);
		cout<<endl<<endl;
		for ( j = 0 ; j < 168 ; ++j ) cout<<(char)220;
		cout<<endl; 
		++i ;
		if ( i == 6  )
		{
			msg_box("|| ** ENTER : VIEW MORE ** || ** TAB : TOGGLE SORT ** || ** 0 : GO BACK ** ||");	
			ch = '';
			while((int)ch!=13&&(int)ch!=48&&(int)ch!=9) ch = getch() ;
			if ( (int)ch == 13 ) goto VIEW_F_F ;
			if ( (int)ch == 9  ) { file.seekg(-1*sizeof(bill) , ios::end); goto VIEW_L_F ; }
			if ( (int)ch == 48 ) break ;
		}
		
	}

	if ( ch == '0' ) return ;
	
	msg_box("!!!===HIT >> ENTER << TO GO BACK===!!!===HIT >> TAB << TO TOGGLE SORT===!!!");
	ch = '' ;
	while((int)ch!=13&&(int)ch!=9)ch=getch() ;
	if ( (int)ch == 9 ) { file.seekg(-1*sizeof(bill) , ios::end); goto VIEW_L_F ; }
	file.close();
	return ;
	
	
VIEW_L_F:
	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(78 , 13) ;
	cout<<"SALES HISTORY"<<endl;
	gotoxy(77,14);
	for(i = 1 ; i <= strlen("SALES HISTORY")+2 ; ++i )
		cout<<char(205);
		
	cout<<endl;	
	i = 0 ;
	while ( file.read((char*)&b , sizeof(bill)) )
	{
		b.show_data("HISTORY" , 18+5*i);
		cout<<endl<<endl;
		for ( j = 0 ; j < 168 ; ++j ) cout<<(char)220;
		cout<<endl; 
		++i ;
		file.seekg(-2*sizeof(bill),ios::cur);
		if ( i == 6  )
		{
			msg_box("|| ** ENTER : VIEW MORE ** || ** TAB : TOGGLE SORT ** || ** 0 : GO BACK ** ||");	
			ch = '';
			while((int)ch!=13&&(int)ch!=48&&(int)ch!=9) ch = getch() ;
			if ( (int)ch == 13 ) goto VIEW_L_F ;
			if ( (int)ch == 9  ) { file.seekg(0 , ios::beg); goto VIEW_F_F ; }
			if ( (int)ch == 48 ) break ;
		}	
		
	}
	
	if ( ch == '0' ) return ;
	
	msg_box("!!!===HIT >> ENTER << TO GO BACK===!!!");
	ch = '' ;
	while((int)ch!=13&&(int)ch!=9)ch=getch() ;
	if ( (int)ch == 9 ) { file.seekg(0 , ios::beg); goto VIEW_F_F ; }
	
	file.close();
	
	return ;

}

void bill_show ( )
{
	int i = 0 , j = 0 , flag = 0;
	char ch = '' ;
	fstream file ;
	char bill_no[50]="";
	int rslt = 0 ;
	bill b , b_found;
	
	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(79 , 13) ;
	cout<<"BILL SEARCH"<<endl;
	gotoxy(78,14);
	for(i = 1 ; i <= strlen("BILL SEARCH")+2 ; ++i )
		cout<<char(205);
	cout<<endl;		
	
	gotoxy ( 0 , 17 ) ;
	cout << "     >> INVOICE NUMBER    :       " ;
	cout<<endl;
	gotoxy ( 0 , 18 ) ;
	for ( j = 0 ; j < 168 ; ++j ) cout<<(char)220;
	cout<<endl;	
	
	i = 0 ;
	
	do
	{
		
		gotoxy ( 34 , 17 ) ;
		while ( (int)ch != 13 )
		{
			if ( !i )
				msg_box( "!!...ENTER INVOICE NUMBER TO SEARCH...!!" ) ;
			if ( i && rslt )
				msg_box( "!!!===HIT >> ENTER << TO PROCEED WITH THIS INVOICE===!!!" );	
				
			if ( i && !rslt )
				msg_box( "*** SORRY *** NO INVOICE FOUND ***");
			
			gotoxy ( 34+strlen(bill_no) , 17);
			
			ch = getch();
			
			if ( ch=='0' && !i && !rslt ) return ;
			
			if ( !i && (int)ch==13 )
			{
				ch = '' ;
				continue ;
			}
			
			if ( i && rslt && (int)ch == 13 ) break ;
			
			if ( !rslt && (int)ch == 13 )
			{
				ch = '';
				continue ;
			}
			
			if ( bill_no[0]=='0' && i==1 && (int)ch == 13 )
				return  ;
				
			if ( (int)ch != 8 && (int)ch != 13 ) 
				if ( i !=47 && isdigit(ch))
				{
					bill_no[i++] = ch ;
					bill_no[i] = '\0' ;
				}
				
			if ( (int)ch == 8 )
				if ( i != 0 )
				{
						--i ;
						bill_no[i] = '\0' ;
				}
				else
						i = 0 ;	

			if ( i>=0 ) 
			{
				gotoxy ( 34 , 17 ) ;
				printf("                                                           ") ;
				cout<<endl;

				gotoxy ( 34 , 17  ) ;
				for ( j=0 ; bill_no[j]!='\0' ; ++j)
					printf("%c" , bill_no[j]);
					
				file.open("bill_list.bin",ios::in|ios::binary);
				
					for ( int z = 21 ; z <= 23 ; ++z )
					{
						for ( int k = 5 ; k <= 168  ; ++k )
						{
							cout<<endl ;
							gotoxy( k , z ) ;
							cout<<" " ;
							cout<<endl ;
						}
						
					}
					rslt = 0 ;				
				
				if( i > 0 )
				{

					while (file.read((char*)&b , sizeof(bill)))
					{
						if ( atoi(bill_no) == b.bill_no )
						{
							b.show_data("HISTORY" , 21+(rslt*2) ) ;
							b_found = b ;
							rslt = 1 ;
						}
					}
				}
				
				file.close();
			}
						
		}
		if ( i && rslt && (int)ch == 13 ) break ;
		
	}while( !flag || flag ) ;
	
	b_found.show_data("BILL_DISPLAY");
}



		//TIME & DATE DISPLAY
//<<!!============================!!>>
void showtime()
{
	time_t t1 = time(0);
	char date[15],time[15],t[5];
	strcpy(date,"");strcpy(time,"");
	struct tm * now = localtime( & t1 );
	cout<<"  ";
	if(now->tm_hour<10)cout<<"0";
	cout << now->tm_hour << ":";
	if(now->tm_min<10)cout<<"0";
	cout<< now->tm_min << ":";
	if(now->tm_sec<10)cout<<"0";
	cout<< now->tm_sec;
	cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    ";
	if(now->tm_mday<10)cout<<"0";
	cout <<  now->tm_mday << '-';
	if((now->tm_mon+1)<10)cout<<"0";
	cout << (now->tm_mon + 1) << '-'
		 << (now->tm_year + 1900) <<endl;
	cout<<"  ";

	//PREPARING THE DATE TO SAVE AS GLOBAL

	if(now->tm_mday<10)strcat(date,"0");
	strcat(date,itoa(now->tm_mday,t,10));
	strcat(date,"-");
	if((now->tm_mon+1)<10)strcat(date,"0");
	strcat(date,itoa(now->tm_mon + 1,t,10));
	strcat(date,"-");
	strcat(date,itoa(now->tm_year + 1900,t,10));

	strcpy(curr_date,date);							//MAKING DATE & TIME GLOBAL FOR

}

		//EXIT DISPLAY
//<<!!============================!!>>
void exit_screen()
{
	int i=0;
	system("cls");
	for(i=0;i<=18;++i)
		cout<<'\n';
	cout<<"\n\t\t\t\t\t\t\t\t";
	for(i=0;i<53;++i)
	cout<<(char)220;
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(219);cout<<"                                                   "<<char(219);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"            COMPUTERISED BILLING SYSTEM            "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"                                                   "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"              PROGRAMMED & DESIGNED BY             "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"            ";for(i=0;i<28;++i)cout<<char(205);cout<<"           "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"                                                   "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"             MOHAMMED AZHAR PADARIYAKAM            "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"                                                   "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"             COMPUTER SCIENCE DEPARTMENT           "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(186);cout<<"                azharakbar@gmail.com               "<<char(186);
	cout<<"\n\t\t\t\t\t\t\t\t"<<char(219);cout<<"                                                   "<<char(219);

	cout<<"\n\t\t\t\t\t\t\t\t";
	for(i=0;i<53;++i)
	cout<<(char)223;
	cout<<endl;
	getchar();
	system("cls");
	exit(0);
}

void gotoxy (int x, int y)
{
    COORD coord; // coordinates
    coord.X = x; coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}




int product::enter_data(int flag )
{
	int  i =0  , j = 0 ;
	char temp_barcode[20]="" , temp_prod_name[50]="" , temp_price[10]="" , temp='' ;
	fstream file ;
	
	do{
		
		header();
		gotoxy(0,0);cout<<endl;
		gotoxy(75 , 13) ;
		cout<<"NEW PRODUCT ENTRY"<<endl;
		gotoxy(74,14);
		for(i = 1 ; i <= strlen("NEW PRODUCT ENTRY")+2 ; ++i )
			cout<<char(205);
		cout<<endl;
		
		if ( flag == 0 ) msg_box("|| ** ENTER PRODUCT BARCODE ** || ** HIT '0' TO GO BACK ** ||");
		
		if ( flag == 1 ) msg_box("|| ** ENTER PRODUCT NAME ** || ** HIT '0' TO GO BACK ** ||");
		
		if ( flag == 2 ) msg_box("|| ** ENTER UNIT PRICE ** || ** HIT '0' TO GO BACK ** ||");
		
		if ( flag == 3 ) 
		{ 
			msg_box("|| ** DATA SAVED ** || ** HIT '0' TO GO BACK ** ||") ;
		}
		
		if ( flag == 4 ) msg_box("|| ** ITEM EXISTS ** || ** HIT 'S' TO VIEW DETAILS ** || ** HIT '0' TO GO BACK ** ||");
		
		temp = '' ;
		i=0;
		
		gotoxy(57,20);cout<<">> BARCODE                :            "<<endl;
		gotoxy(57,22);cout<<">> PRODUCT NAME           :            "<<endl;
		gotoxy(57,24);cout<<">> PRICE (INR)            :            "<<endl;
		
		if (!strcmp(temp_barcode,""))
		{
			strcpy(temp_prod_name,"");
			strcpy(temp_price,"");
			
			gotoxy(96,20);
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( temp_barcode[0]=='0' && i==1 && (int)temp == 13 )
					return 0 ;
					
				if ( (int)temp != 8 && (int)temp != 13 ) 
					if ( i !=19 && isalnum(temp) )
						temp_barcode[i++] = toupper(temp) ;
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 84 , 20 ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 96 , 20 ) ;
					for ( j=0 ; j<i ; ++j)
						printf("%c" , temp_barcode[j]);
				}
				
			}
			temp_barcode[i] = '\0';
			
			if ( !scan(temp_barcode,"barcode") )
			{
				strcpy ( temp_barcode , "" );
				flag = 4 ;
			}
			
			if ( strcmp (temp_barcode,"") ) flag = 1 ;
			
			continue ;
			
		}

		i = 0 ;
		
		if (strcmp(temp_barcode,"")&&!strcmp(temp_prod_name,""))
		{
			strcpy(temp_price,"");
			gotoxy(96,20);
				cout<<temp_barcode<<endl;
			gotoxy(96,22);
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( temp_prod_name[0]=='0' && i==1 && (int)temp == 13 )
				{
					strcpy(temp_barcode,"");
					flag = 0 ;
					continue ;
				}
				
				if ( (int)temp != 8 && (int)temp != 13 ) 
					if ( i !=47 )
						temp_prod_name[i++] = toupper(temp) ;
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 84 , 22 ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 96 , 22 ) ;
					for ( j=0 ; j<i ; ++j)
						printf("%c" , temp_prod_name[j]);
				}
				
			}
			temp_prod_name[i] = '\0';	

			if(strcmp(temp_barcode,"")) flag = 2 ;
			
			continue;
		}
		
		if (strcmp(temp_barcode,"")&&strcmp(temp_prod_name,"")&&!strcmp(temp_price,""))
		{
			gotoxy(96,20);
				cout<<temp_barcode<<endl;
			gotoxy(96,22);
				cout<<temp_prod_name<<endl;
	
			gotoxy(96,24);
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( temp_price[0]=='0' && i==1 && (int)temp == 13 )
				{
					strcpy(temp_prod_name,"");
					flag = 1 ;
					break ;
				}
				
				if ( (int)temp != 8 && (int)temp != 13 ) 
					if ( i != 10 && ( isdigit(temp) || temp=='.' ) )
					{
						if ( temp == '.' )
							for ( j = 0 ; j < i ; ++j )
								if ( temp_price[j] == '.' ) break ;
						
						if ( isdigit(temp) || j == i ) temp_price[i++] = temp ;
					}
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 84 , 24 ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 96 , 24 ) ;
					for ( j=0 ; j<i ; ++j)
						printf("%c" , temp_price[j]);
				}
				
			}
			temp_price[i] = '\0';
			
			if ( strcmp ( temp_prod_name , "" ) ) 
			{
				strcpy(barcode ,temp_barcode);
				strcpy(name,temp_prod_name);strcpy(temp_prod_name,"");
				price=atof(temp_price) ;strcpy(temp_price,"");
				stock = -1 ;
				flag = 0 ; 
				return 1 ;		
			}		
			
			continue ; 
			
		}
		
	}while( !flag || flag ) ;
	
	return 0 ;
}

void product::add_stock()
{
	int  i =0  , j = 0 , flag = 0 ;
	char temp_stk[10]="" , temp='' ;
 

	do{
		
		show_data("STOCK");
		
		if ( !flag ) msg_box("|| ** ENTER STOCK PURCHASED ** || ** HIT '0' TO GO BACK ** ||");
		
		temp = '' ;
		i=0;
		
		gotoxy(57,28);cout<<">> NEW STOCK              :            "<<endl;
		
		gotoxy(96,28);
		
		i = 0 ;
		temp = '' ;
		
		while ( (int)temp!= 13 )
		{
				
			temp=getch();
			
			if ( temp_stk[0]=='0' && i==1 && (int)temp == 13 )
			{
				return ;
			}
			
			if ( !i && (int)temp == 13 ) 
			{	
				temp = '' ;
				continue ;
			}
			
			if ( (int)temp != 8 && (int)temp != 13 ) 
				if ( i != 10 && isdigit(temp) )
				{
					if ( isdigit(temp) || j == i ) temp_stk[i++] = temp ;
				}
				
			if ( (int)temp == 8 )
				if ( i != 0 )
						--i ;
				else
						i = 0 ;		
		
			if ( i>=0 ) 
			{
				gotoxy ( 84 , 28 ) ;
				printf("                                                           ") ;
				cout<<endl;
				gotoxy ( 96 , 28 ) ;
				for ( j=0 ; j<i ; ++j)
					printf("%c" , temp_stk[j]);
			}
			
		}
		temp_stk[i] = '\0';
		
		if ( strcmp ( temp_stk , "" ) )
		{
			if ( stock == -1 ) stock = 0 ;
			stock+=atoi(temp_stk) ;

			flag = 0 ; 
			break;
		}
		
	}while( !flag || flag ) ;	
	
	gotoxy(57,28);
	for ( i = 0 ; i < 51 ; ++ i ) cout<<" ";
	cout<<endl;
	gotoxy(57,26);
	for ( i = 0 ; i < 81 ; ++ i ) cout<<" ";
	cout<<endl;
	gotoxy(57,24);
	cout<<">> UPDATED STOCK          :            "<<stock<<"                     "<<endl;
	msg_box("|| ** DATA SAVED ** || ** HIT >> ENTER << TO GO BACK ** ||") ;
	cout<<endl;
	gotoxy(0,0);
	temp = '';
	while((int)temp!=13) temp=getch() ;
	
}

void product::show_data(char type[] , int offset )
{
	int i = 0 ;
	if(!strcmpi(type,"ALL"))
	{
		cout<<endl;
		gotoxy ( 5 , offset ) ;  cout << barcode<<endl;
		gotoxy ( 35 , offset );  cout << name <<endl ;
		
		if((int)price == (float)price)
			{gotoxy ( 105 , offset ); cout << setw(11)<<float(price)<<".00" <<endl;}
		else if ((int)(price*2) == (float)(price*2))
			{gotoxy ( 105 , offset ); cout << setw(13)<<float(price) <<"0"<<endl;}		
		else
			{gotoxy ( 105 , offset ); cout << setw(14)<<float(price) <<endl;}
		
		if(stock)
			{gotoxy ( 140 , offset ); cout << stock <<endl;}		
		else
			{gotoxy ( 140 , offset ); cout << "!!==OUT OF STOCK==!!" <<endl;		}
	}
	
	if(!strcmpi(type,"SINGLE") || !strcmpi(type,"STOCK"))
	{
		gotoxy(57,18);cout<<">> BARCODE                :            "<<barcode<<endl;
		gotoxy(57,20);cout<<">> PRODUCT NAME           :            "<<name<<endl;
		gotoxy(57,22);
		if(!price)
			cout<<">> PRICE (INR)            :            "<<"0.00"<<endl;
		else if((int)price==(float)price)
			cout<<">> PRICE (INR)            :            "<<price<<".00"<<endl;
		else if((int)(price*2)==(float)(price*2))
			cout<<">> PRICE (INR)            :            "<<price<<"0"<<endl;
			
		if(!strcmpi(type,"STOCK"))
		{
			gotoxy(57,24);
			if ( stock <= 0 )
				cout<<">> STOCK IN HAND          :            "<<"!!===OUT OF STOCK===!!"<<endl;
			else
				cout<<">> STOCK IN HAND          :            "<<stock<<endl;
			
		}
		
		else {gotoxy(55,25);
		
		for ( i = 0 ; i < 50 ; ++i ) cout<<(char)220;}
		cout<<endl ;
	}
	
}


int customer::enter_data( int flag , int ccp = 0 )
{
	int  i =0  , j = 0 ;
	char temp_name[50]="" , temp_ctc[15]="" , temp_cr[10]="" , temp_ccp[10]="" , temp='' ;
	fstream mainfile,newfile ;
	customer c ; 
	customer t ; t.icode = ccp ; t.get_ccode(ccp);
	
	get_ccode ( ccp ) ;
	
	do{
		
		header();
		gotoxy(0,0);cout<<endl;
		gotoxy(74 , 13) ;
		cout<<"NEW CUSTOMER ENTRY"<<endl;
		gotoxy(73,14);
		for(i = 1 ; i <= strlen("NEW CUSTOMER ENTRY")+2 ; ++i )
			cout<<char(205);
		cout<<endl;
		
		if ( flag == 0 ) msg_box("|| ** ENTER CUSTOMER NAME ** || ** HIT '0' TO GO BACK ** ||");
		
		if ( flag == 1 ) msg_box("|| ** ENTER CONTACT NUMBER ** || ** HIT '0' TO GO BACK ** ||");
		
		if ( flag == 2 ) msg_box("|| ** ENTER INITIAL CREDIT ** || ** HIT '0' TO GO BACK ** ||");
		
		if ( flag == 3 ) 
		{ 
			msg_box("|| ** DATA SAVED ** || ** HIT '0' TO GO BACK ** ||") ;
		}
		
		if ( flag == 4 ) msg_box("|| ** CUSTOMER EXISTS ** || ** HIT 'S' TO VIEW DETAILS ** || ** HIT '0' TO GO BACK ** ||");
		
		temp = '' ;
		i=0;
		
		gotoxy(57,20);cout<<">> CUSTOMER CODE          :            "<<"-------"<<endl;
		gotoxy(57,22);cout<<">> CUSTOMER NAME          :            "<<endl;
		gotoxy(57,24);cout<<">> CONTACT NUMBER         :            "<<endl;
		gotoxy(57,26);cout<<">> CREDIT (INR)           :            "<<endl;
		
		if (!strcmp(temp_name,""))
		{
			strcpy(temp_ctc,"");
			strcpy(temp_cr,"");
			
			gotoxy(96,22);
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( temp_name[0]=='0' && i==1 && (int)temp == 13 )
					return 0 ;
				
				if ( (int)temp != 8 && (int)temp != 13 ) 
					if ( i !=47 )
						temp_name[i++] = toupper(temp) ;
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 84 , 22 ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 96 , 22 ) ;
					for ( j=0 ; j<i ; ++j)
						printf("%c" , temp_name[j]);
				}
				
			}
			temp_name[i] = '\0';
			
			if ( !scan(temp_name,"name") )
			{
				strcpy ( temp_name , "" );
				flag = 4 ;
			}
			
			if ( strcmp (temp_name,"") ) flag = 1 ;
			
			continue ;
			
		}

		i = 0 ;
		
		if (strcmp(temp_name,"")&&!strcmp(temp_ctc,""))
		{
			strcpy(temp_cr,"");
			gotoxy(96,22);
				cout<<temp_name<<endl;
			gotoxy(96,24);
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( temp_ctc[0]=='0' && i==1 && (int)temp == 13 )
				{
					strcpy(temp_name,"");
					flag = 0 ;
					continue ;
				}
				
				if ( (int)temp != 8 && (int)temp != 13 ) 
					if ( i !=13 && isdigit(temp) )
						temp_ctc[i++] = toupper(temp) ;
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 84 , 24 ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 96 , 24 ) ;
					for ( j=0 ; j<i ; ++j)
						printf("%c" , temp_ctc[j]);
				}
				
			}
			temp_ctc[i] = '\0';	

			if(strcmp(temp_name,"")) flag = 2 ;
			
			continue;
		}
		
		if (strcmp(temp_name,"")&&strcmp(temp_ctc,"")&&!strcmp(temp_cr,""))
		{
			gotoxy(96,22);
				cout<<temp_name<<endl;
			gotoxy(96,24);
				cout<<temp_ctc<<endl;
	
			gotoxy(96,26);
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( temp_cr[0]=='0' && i==1 && (int)temp == 13 )
				{
					strcpy(temp_ctc,"");
					flag = 1 ;
					break ;
				}
				
				if ( (int)temp != 8 && (int)temp != 13 ) 
					if ( i != 10 && ( isdigit(temp) || temp=='.' ) )
					{
						if ( temp == '.' )
							for ( j = 0 ; j < i ; ++j )
								if ( temp_cr[j] == '.' ) break ;
						
						if ( isdigit(temp) || j == i ) temp_cr[i++] = temp ;
					}
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 84 , 26 ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 96 , 26 ) ;
					for ( j=0 ; j<i ; ++j)
						printf("%c" , temp_cr[j]);
				}
				
			}
			temp_cr[i] = '\0';
			
			if ( strcmp ( temp_ctc , "" ) )
			{
				if ( ccp > 1 )
				{
						flag = 0 ;
						mainfile.open("cust_list.bin",ios::in|ios::binary);
						newfile.open ("temp.bin",ios::out|ios::binary);
						while(mainfile.read((char*)&c , sizeof(customer)))
						{
							if(strcmp(temp_name,c.name)<0 && !flag ) 
							{
								strcpy(t.name,"HERE");
								t.icode = c.icode ;
								t.get_ccode(t.icode);
								
								newfile.write((char*)&t,sizeof(customer));
								
								flag = 1 ; 
							}
							else if(!(strcmp(temp_name,c.name)<0) && !flag )
								newfile.write((char*)&c,sizeof(customer));
							if ( flag )
							{
								c.icode += 1 ;
								c.get_ccode(c.icode);
								newfile.write((char*)&c,sizeof(customer));
							}
						}
						mainfile.close();
						newfile.close();
						remove("cust_list.bin");
						rename("temp.bin","cust_list.bin");			
				}
				else
				{
					t.icode=icode = 1 ;
					strcpy(ccode,"SSP0001");
					strcpy(t.ccode,"SSP0001");
				}
				strcpy(name,temp_name);strcpy(temp_name,"");
				strcpy(ctc_no,(temp_ctc));
				tot_cr=atof(temp_cr) ;strcpy(temp_cr,"");
				icode = ccp ;
				
				if( tot_cr > 0 )
				{
					cr[0].cr_val = tot_cr;
					strcpy(cr[0].date , curr_date);
					cr_entries=1 ;
				}
				else cr_entries = 0 ;
				
				flag = 0 ; gotoxy(96,20);
				cout<<t.ccode<<endl;
				cin.get();
				return 1 ;
			}
			
			continue ; 
			
		}
		
	}while( !flag || flag ) ;
	
	return 0 ;
}


void customer::show_data(char type[] , int offset )
{
	int i = 0 ;
	if(!strcmpi(type,"ALL"))
	{
		cout<<endl;
		gotoxy ( 5 , offset ) ;  cout << ccode<<endl;
		gotoxy ( 25 , offset );  cout << name <<endl ;
		
		if(tot_cr)
		{
			if((int)tot_cr == (float)tot_cr)
				{gotoxy ( 105 , offset ); cout << setw(11)<<float(tot_cr)<<".00" <<endl;}
			else if ((int)(tot_cr*2) == (float)(tot_cr*2))
				{gotoxy ( 105 , offset ); cout << setw(13)<<float(tot_cr) <<"0"<<endl;}		
			else
				{gotoxy ( 105 , offset ); cout << setw(14)<<float(tot_cr) <<endl;}
		}
		
		else
			{gotoxy ( 105 , offset ); cout << setw(14)<<"!!==NO CREDIT==!!"<<endl;}
		
		gotoxy ( 140 , offset ); cout << ctc_no <<endl;
	
	}
	
	if(!strcmpi(type,"SINGLE"))
	{
		gotoxy(57,18);cout<<">> CUSTOMER CODE          :            "<<ccode<<endl;
		gotoxy(57,20);cout<<">> CUSTOMER NAME          :            "<<name<<endl;
		gotoxy(57,22);cout<<">> CONTACT NUMBER         :            "<<ctc_no<<endl;
		gotoxy(57,24);
		if(!tot_cr)
			cout<<">> NET CREDIT (INR)       :            "<<"!!==NO DUES==!!"<<endl;
		else if((int)tot_cr==(float)tot_cr)
			cout<<">> NET CREDIT (INR)       :            "<<tot_cr<<".00"<<endl;
		else if((int)(tot_cr*2)==(float)(tot_cr*2))
			cout<<">> NET CREDIT (INR)       :            "<<tot_cr<<"0"<<endl;
		
		gotoxy(55,25);
		for ( i = 0 ; i < 50 ; ++i ) cout<<(char)220;
		cout<<endl ;
		gotoxy ( 76 , 27 ) ; cout<<"RECENT ACTIVITIES"<<endl;
		gotoxy ( 75 , 28 ) ; for ( i = 1 ; i <= strlen ("RECENT ACTIVITIES") + 2 ; ++i ) cout<<(char)205 ;  
		cout<<endl; 
		
		if (cr_entries == 0)
		{
			gotoxy ( 71 , 34 ) ;
			cout << "** NO ACTIVITIES TILL NOW **" <<endl ;
		}
		else
		{
			for ( i = 0 ; i < cr_entries ; ++i )
			{
				gotoxy ( 57 , 30 + 2*i ) ;
				cout<<">> "<<cr[i].date<<endl;
				gotoxy ( 97 , 30 + 2*i ) ;
				if ( cr[i].cr_val > 0 )
				{
					cout<<"CR : "<<cr[i].cr_val;
					if ( cr[i].invoice_no ) cout<<"\t\t>> INVOICE NO.: "<<cr[i].invoice_no;
					cout<<endl;
				}
				else
				{
					cout<<"PD : "<<-cr[i].cr_val<<endl;
				}
				
			}
		}
		
		cin.get();
	}
	
}

int customer::credit_entry( float* val , int inv_no )
{
	int  i =0  , j = 0 , flag = 0 ;
	char temp_cr[10]="" , temp='' ;
 

	do{
		
		header();
		gotoxy(0,0);cout<<endl;
		gotoxy(76 , 13) ;
		cout<<"NEW CREDIT ENTRY"<<endl;
		gotoxy(75,14);
		for(i = 1 ; i <= strlen("NEW CREDIT ENTRY")+2 ; ++i )
			cout<<char(205);
		cout<<endl;
		
		if ( flag == 0 ) msg_box("|| ** ENTER NEW CREDIT AMOUNT ** || ** HIT '0' TO GO BACK ** ||");
		
		temp = '' ;
		i=0;
		
		gotoxy(57,20);cout<<">> CUSTOMER CODE          :            "<<ccode<<endl;
		gotoxy(57,22);cout<<">> CUSTOMER NAME          :            "<<name<<endl;
		gotoxy(57,24);cout<<">> CONTACT NUMBER         :            "<<ctc_no<<endl;
		gotoxy(57,26);
		if(!tot_cr)
			cout<<">> NET CREDIT (INR)       :            "<<"!!==NO DUES==!!"<<endl;
		else if((int)tot_cr==(float)tot_cr)
			cout<<">> NET CREDIT (INR)       :            "<<tot_cr<<".00"<<endl;
		else if((int)(tot_cr*2)==(float)(tot_cr*2))
			cout<<">> NET CREDIT (INR)       :            "<<tot_cr<<"0"<<endl;
			
		if ( val ) break ;
		
		gotoxy(57,28);cout<<">> NEW CREDIT AMOUNT      :            "<<endl;
		
		gotoxy(96,28);
		
		i = 0 ;
		
		while ( (int)temp!= 13 )
		{
				
			temp=getch();
			
			if ( temp_cr[0]=='0' && i==1 && (int)temp == 13 )
			{
				return 0 ;
			}
			
			if ( !i && (int)temp == 13 ) 
			{	
				temp = '' ;
				continue ;
			}
			
			if ( (int)temp != 8 && (int)temp != 13 ) 
				if ( i != 10 && ( isdigit(temp) || temp=='.' ) )
				{
					if ( temp == '.' )
						for ( j = 0 ; j < i ; ++j )
							if ( temp_cr[j] == '.' ) break ;
					
					if ( isdigit(temp) || j == i ) temp_cr[i++] = temp ;
				}
				
			if ( (int)temp == 8 )
				if ( i != 0 )
						--i ;
				else
						i = 0 ;		
		
			if ( i>=0 ) 
			{
				gotoxy ( 84 , 28 ) ;
				printf("                                                           ") ;
				cout<<endl;
				gotoxy ( 96 , 28 ) ;
				for ( j=0 ; j<i ; ++j)
					printf("%c" , temp_cr[j]);
			}
			
		}
		temp_cr[i] = '\0';
		
		if ( strcmp ( temp_cr , "" ) )
		{
			tot_cr+=atof(temp_cr) ;
			
			if ( cr_entries == 10 )
			{
				for ( i = 1 ; i <= 9 ; ++i )
				{
					cr[i-1] = cr[i] ;
				}
				--cr_entries ;
			}
			
			cr[cr_entries].cr_val = atof(temp_cr);
			strcpy(cr[cr_entries].date , curr_date);
			
			cr_entries++ ;

			flag = 0 ; 
			break;
		}
		
	}while( !flag || flag ) ;	
	
	if ( val )
	{
		char temp_val[25]="" , msg[250] = "" ;
		itoa(*val,temp_val,10);
		strcpy(msg,">> DO YOU WISH TO CREDIT INR ");
		strcat(msg,temp_val);
		strcat(msg," TO ");
		strcat(msg,name);
		strcat(msg, " ? ");
		int size = strlen(msg) ;
		size = size / 2 ;
		msg_box("!!!===>> ** Y : YES ** << OR >> ** N : NO ** <<===!!!");
		cout<<endl;
		gotoxy( mid - size , 28 ) ;
		cout<<msg<<"     "<<endl;
		temp = '';
		while( temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' ) temp = getch() ;
		
		if ( temp == 'N' || temp == 'n' ){ *val = 0 ; return 0 ;}
		
		if ( temp == 'Y' || temp == 'y' ) 
		{
			tot_cr+=(*val);
			
			if ( cr_entries == 10 )
			{
				for ( i = 1 ; i <= 9 ; ++i )
				{
					cr[i-1] = cr[i] ;
				}
				--cr_entries ;
			}
			
			cr[cr_entries].cr_val = *val;
			strcpy(cr[cr_entries].date , curr_date);
			cr[cr_entries].invoice_no = inv_no ;
			strcpy(::name,name);
			cr_entries++ ;
			
		}
		
		
	}
	
	gotoxy(10,28);
	for ( i = 0 ; i < 150 ; ++ i ) cout<<" ";
	cout<<endl;
	gotoxy(57,26);
	for ( i = 0 ; i < 81 ; ++ i ) cout<<" ";
	cout<<endl;
	gotoxy(57,26);
	if((int)tot_cr==(float)tot_cr)
		cout<<">> UPDATED CREDIT (INR)   :            "<<tot_cr<<".00"<<endl;
	else if((int)(tot_cr*2)==(float)(tot_cr*2))
		cout<<">> UPDATED CREDIT (INR)   :            "<<tot_cr<<"0"<<endl;
	msg_box("|| ** DATA SAVED ** || ** HIT >> ENTER << TO GO BACK ** ||") ;
	cout<<endl;
	gotoxy(0,0);
	temp = '';
	while((int)temp!=13) temp=getch() ;

	return 1 ;
}

int customer::credit_pay()
{
	int  i =0  , j = 0 , flag = 0 ;
	char temp_cr[10]="" , temp='' ;

	do{
		
		header();
		gotoxy(0,0);cout<<endl;
		gotoxy(77 , 13) ;
		cout<<"CREDIT PAYMENT"<<endl;
		gotoxy(76,14);
		for(i = 1 ; i <= strlen("CREDIT PAYMENT")+2 ; ++i )
			cout<<char(205);
		cout<<endl;
		
		if ( flag == 0 ) msg_box("|| ** ENTER NEW CREDIT AMOUNT ** || ** HIT '0' TO GO BACK ** ||");
		
		if ( flag == 1 ) msg_box("|| ** ERROR ** || ** AMOUNT PAYED IS GREATER THAN NET CREDIT ** ||");
		
		temp = '' ;
		i=0;
		
		gotoxy(57,20);cout<<">> CUSTOMER CODE          :            "<<ccode<<endl;
		gotoxy(57,22);cout<<">> CUSTOMER NAME          :            "<<name<<endl;
		gotoxy(57,24);cout<<">> CONTACT NUMBER         :            "<<ctc_no<<endl;
		gotoxy(57,26);
		if(!tot_cr)
			cout<<">> NET CREDIT (INR)       :            "<<"!!==NO DUES==!!"<<endl;
		else if((int)tot_cr==(float)tot_cr)
			cout<<">> NET CREDIT (INR)       :            "<<tot_cr<<".00"<<endl;
		else if((int)(tot_cr*2)==(float)(tot_cr*2))
			cout<<">> NET CREDIT (INR)       :            "<<tot_cr<<"0"<<endl;
			
	if ( ! tot_cr ) 
	{	
		gotoxy ( 66 , 28 ) ;
		cout << "** CUSTOMER HAS NO PENDING CREDIT **" << endl ;
		
		msg_box("!!...HIT >> ENTER << TO CONTINUE...!!");
		cout<<endl;gotoxy(0,0);
		temp = getch() ; while((int)temp!=13) temp = getch() ;
		return 0 ; 
	}
		gotoxy(57,28);cout<<">> AMOUNT PAYED           :            "<<endl;
		
		gotoxy(96,28);
		
		i = 0 ;
		
		while ( (int)temp!= 13 )
		{
				
			temp=getch();
			
			if ( temp_cr[0]=='0' && i==1 && (int)temp == 13 )
			{
				return 0 ;
			}
			
			if ( !i && (int)temp == 13 ) 
			{	
				temp = '' ;
				continue ;
			}
			
			if ( (int)temp != 8 && (int)temp != 13 ) 
				if ( i != 10 && ( isdigit(temp) || temp=='.' ) )
				{
					if ( temp == '.' )
						for ( j = 0 ; j < i ; ++j )
							if ( temp_cr[j] == '.' ) break ;
					
					if ( isdigit(temp) || j == i ) temp_cr[i++] = temp ;
				}
				
			if ( (int)temp == 8 )
				if ( i != 0 )
						--i ;
				else
						i = 0 ;		
		
			if ( i>=0 ) 
			{
				gotoxy ( 84 , 28 ) ;
				printf("                                                           ") ;
				cout<<endl;
				gotoxy ( 96 , 28 ) ;
				for ( j=0 ; j<i ; ++j)
					printf("%c" , temp_cr[j]);
			}
			
		}
		temp_cr[i] = '\0';
		
		if ( atof ( temp_cr ) > tot_cr )
		{
			flag = 1 ; 
			continue ;
		}
		
		
		
		if ( strcmp ( temp_cr , "" ) )
		{
			tot_cr-=atof(temp_cr) ;
			
			if ( cr_entries == 10 )
			{
				for ( i = 1 ; i <= 9 ; ++i )
				{
					cr[i-1] = cr[i] ;
				}
				--cr_entries ;
			}
			
			cr[cr_entries].cr_val = - atof(temp_cr);
			strcpy(cr[cr_entries].date , curr_date);
			cr_entries++ ;

			flag = 0 ; 
			break;
		}
		
	}while( !flag || flag ) ;	
	
	gotoxy(57,28);
	for ( i = 0 ; i < 51 ; ++ i ) cout<<" ";
	cout<<endl;
	gotoxy(57,26);
	if((int)tot_cr==(float)tot_cr)
		cout<<">> UPDATED CREDIT (INR)   :            "<<tot_cr<<".00"<<endl;
	else if((int)(tot_cr*2)==(float)(tot_cr*2) && tot_cr )
		cout<<">> UPDATED CREDIT (INR)   :            "<<tot_cr<<"0"<<endl;
	msg_box("|| ** DATA SAVED ** || ** HIT >> ENTER << TO GO BACK ** ||") ;
	cout<<endl;
	gotoxy(0,0);
	temp = '';
	while((int)temp!=13) temp=getch() ;

	return 1 ;
}


void customer::get_ccode(int ccp)
{
	char temp_ccp[10]="" , temp_cr[10]="" ;
	
	strcpy(temp_ccp,"SSP");
	if ( ccp < 10 )
		strcat ( temp_ccp , "000" );
	else if ( ccp < 100 )
		strcat ( temp_ccp , "00" );
	else if ( ccp < 1000 )
		strcat ( temp_ccp , "0" );
	else	
		strcat ( temp_ccp , "" ) ;
	
	itoa ( ccp , temp_cr , 10 ) ;
	
	strcat ( temp_ccp , temp_cr );
	strcpy(ccode , temp_ccp ); 
	icode = ccp ;
}


int product::edit_data()
{
	int flag = 0 , i = 0 , j = 0 ;
	char ch = '' , choice = '' , temp = '' , temp_barcode[50] = "" , temp_name[50] = "" , temp_price[10] = "" ;
	
	do
	{
		show_data("SINGLE");
		
		if (!flag)
			msg_box("** B : BARCODE ** N : PRODUCT NAME ** P : PRICE ** D : DELETE **");
		if ( flag == 1 )
			msg_box("!!===INVALID CHOICE===!!");
		if ( flag == 2 )
			msg_box("!!===PRODUCT EXISTS WITH THE SAME BARCODE===!!");

			
		flag = 0 ;
		ch = '' ;
		i = 0 ;
		choice = '' ;
		
		cout<<endl;
		gotoxy(61,35);	
		cout<<"===>>  YOUR CHOICE    :    "<<endl;
		gotoxy(97,35); cout<<"  "<<endl; 
		while ( (int)ch!= 13 )
		{
			
			gotoxy ( 97 , 35 );	
			 ch=getch();
			
			if ( !i && (int)ch == 13 ) 
			{	
				ch = '' ;
				msg_box("** B : BARCODE ** N : PRODUCT NAME ** P : PRICE ** D : DELETE **");
				continue ;
			}
			
			if ( (int)ch != 13 && (int)ch != 8 )
			{
				i = 1 ;
				choice = toupper(ch) ;
			}
			

			if ( i && (int)ch == 13 ) break ;

			if ( i && (int)ch == 8 )
			{
				i = 0 ;
				gotoxy(97,35);cout<<" ";
				ch='' ;choice = '' ;
			}
		
			if ( i>=0 ) 
			{
				gotoxy ( 97 , 35 ) ;
				printf("%c" , choice);
				cout<<endl;
			}

			
			
		}

		if ( choice == 'B' || choice == 'N' || choice == 'P' || choice == 'D' ) flag = 0 ;
		else if ( (int) choice == 13 || choice == '' ) flag = 0 ;
		else flag = 1 ;
		
		cout<<endl ;
		
		switch ( choice )
		{
			
			case 'B':
				gotoxy ( 96 , 18 );
				cout<<"                                                      "<<endl;
				gotoxy ( 96 , 18 ) ;	
				i = 0 ;
				temp = '' ;
				flag = 0 ;
				while ( (int)temp!= 13 )
				{
					temp=getch();
					
					if ( !i && (int)temp == 13 ) 
					{	
						temp = '' ;
						continue ;
					}
					
					if ( temp_barcode[0]=='0' && i==1 && (int)temp == 13 )
					{	
						flag = 1 ;
						break ;
					}
						
					if ( (int)temp != 8 && (int)temp != 13 ) 
						if ( i !=19 && isalnum(temp) )
							temp_barcode[i++] = toupper(temp) ;
						
					if ( (int)temp == 8 )
						if ( i != 0 )
								--i ;
						else
								i = 0 ;		
				
					if ( i>=0 ) 
					{
						gotoxy ( 96 , 18 ) ;
						printf("                                                           ") ;
						cout<<endl;
						gotoxy ( 96 , 18 ) ;
						for ( j=0 ; j<i ; ++j)
							printf("%c" , temp_barcode[j]);
					}
					
				}
				temp_barcode[i] = '\0';
				
				if ( flag == 1 ) 
				{
					flag = 0 ; 
					break ; 
				}
				
				flag = 0 ;
				
				if ( !scan(temp_barcode,"barcode") )
				{
					strcpy ( temp_barcode , "" );
					flag = 2 ;
					break ;
				}
				
				if ( strcmp (temp_barcode,"") ) flag = 5 ;
				
				break;
			case 'N':
				gotoxy ( 96 , 20 );
				cout<<"                                                      "<<endl;
				gotoxy ( 96 , 20 ) ;
				i = 0 ;
				temp = '' ;
				flag = 0 ;
				while ( (int)temp!= 13 )
				{
					temp=getch();
					
					if ( !i && (int)temp == 13 ) 
					{	
						temp = '' ;
						continue ;
					}
					
					if ( temp_name[0]=='0' && i==1 && (int)temp == 13 )
					{
						flag = 1 ;
						break ;
					}
						
					if ( (int)temp != 8 && (int)temp != 13 ) 
						if ( i !=47 )
							temp_name[i++] = toupper(temp) ;
						
					if ( (int)temp == 8 )
						if ( i != 0 )
								--i ;
						else
								i = 0 ;		
				
					if ( i>=0 ) 
					{
						gotoxy ( 96 , 20 ) ;
						printf("                                                           ") ;
						cout<<endl;
						gotoxy ( 96 , 20 ) ;
						for ( j=0 ; j<i ; ++j)
							printf("%c" , temp_name[j]);
					}
					
				}
				temp_name[i] = '\0';
				
				if ( flag == 1 ) 
				{
					flag = 0 ; 
					break ; 
				}				
				
				flag = 0 ;
				
				if ( strcmp (temp_name,"") ) flag = 6 ;
				
				break;
			case 'P':
				gotoxy ( 96 , 22 );
				cout<<"                                                      "<<endl;
				gotoxy ( 96 , 22 ) ;
				i = 0 ;
				flag = 0 ;
				temp = 0 ;
				while ( (int)temp!= 13 )
				{
						
					temp=getch();
					
					if ( !i && (int)temp == 13 ) 
					{	
						temp = '' ;
						continue ;
					}
					
					if ( temp_price[0]=='0' && i==1 && (int)temp == 13 )
					{
						flag = 1 ;
						break ;
					}
					
					if ( (int)temp != 8 && (int)temp != 13 ) 
						if ( i != 10 && ( isdigit(temp) || temp=='.' ) )
						{
							if ( temp == '.' )
								for ( j = 0 ; j < i ; ++j )
									if ( temp_price[j] == '.' ) break ;
							
							if ( isdigit(temp) || j == i ) temp_price[i++] = temp ;
						}
						
					if ( (int)temp == 8 )
						if ( i != 0 )
								--i ;
						else
								i = 0 ;		
				
					if ( i>=0 ) 
					{
						gotoxy ( 96 , 22 ) ;
						printf("                                                           ") ;
						cout<<endl;
						gotoxy ( 96 , 22 ) ;
						for ( j=0 ; j<i ; ++j)
							printf("%c" , temp_price[j]);
					}
					
				}
				temp_price[i] = '\0';				
				
				if ( flag == 1 ) 
				{
					flag = 0 ; 
					break ; 
				}	
				flag = 0 ;
				
				if ( strcmp (temp_price,"") ) flag = 7 ;				
				
				break;
				
			case 'D' :
				flag = 0 ;
				do
				{
					
					if (!flag)
						msg_box("** Y : YES ** N : NO **");
					if ( flag == 1 )
						msg_box("!!===INVALID CHOICE===!!");

					flag = 0 ;
					ch = '' ;
					i = 0 ;
					choice = '' ;
					
					cout<<endl;
					gotoxy ( 61 , 35 ) ;
					cout<<"ARE YOU SURE TO DELETE THIS ITEM ? "<<endl ;
					gotoxy(97,35); cout<<"  "<<endl; 
					while ( (int)ch!= 13 )
					{
						
						gotoxy ( 97 , 35 );	
						ch=getch();
						
						if ( !i && (int)ch == 13 ) 
						{	
							ch = '' ;
							continue ;
						}
						
						if ( (int)ch != 13 && (int)ch != 8 )
						{
							i = 1 ;
							choice = toupper(ch) ;
						}
						

						if ( i && (int)ch == 13 ) break ;

						if ( i && (int)ch == 8 )
						{
							i = 0 ;
							gotoxy(97,35);cout<<" ";
							ch='' ;choice = '' ;
						}
					
						if ( i>=0 ) 
						{
							gotoxy ( 97 , 35 ) ;
							printf("%c" , choice);
							cout<<endl;
						}

						
						
					}
					if ( choice == 'Y' || choice == 'N' ) { flag = 0 ; break ; }
					else if ( (int) choice == 13 || choice == '' ) flag = 0 ;
					else flag = 1 ;					
				}while( !flag || flag );

				if ( choice == 'Y' ) 
				{
					gotoxy(61 , 35);
					cout<<"              "<<endl;				
					strcpy(barcode , "-1") ; 
					gotoxy ( 65 , 35 ) ;
					cout<<"!!===PRODUCT DELETED SUCCESSFULLY===!!"<<endl;
					msg_box("!!=== HIT >> ENTER << TO CONTINUE ===!!");
					ch = '' ;
					while((int)ch!=13) ch = getch () ;
					return 0 ;
				}
				else return 0 ;
				break ;
				
			case '0':
				return 0 ;
				break ;
			default:
				break;
		}
		
		if ( flag == 5 || flag == 6 || flag == 7 )
		{
			gotoxy(61 , 35);
			cout<<"              "<<endl;
			if ( flag == 5 ) 
			{
				strcpy(barcode , (temp_barcode)) ;
				gotoxy ( 65 , 35 ) ;
				cout<<"**** BARCODE UPDATED SUCCESSFULLY ****"<<endl; 
			}
			if ( flag == 6 ) 
			{
				strcpy ( name , temp_name ) ;
				gotoxy ( 63 , 35 ) ;
				cout<<"**** PRODUCT NAME UPDATED SUCCESSFULLY ****"<<endl; 
			}
			if ( flag == 7 ) 
			{
				price = atof(temp_price) ;
				gotoxy ( 66 , 35 ) ;
				cout<<"**** PRICE UPDATED SUCCESSFULLY ****"<<endl; 
			}
			msg_box("!!=== HIT >> ENTER << TO CONTINUE ====!!") ;
			gotoxy ( 0 , 0 ) ;
			ch = ''; 
			while((int)ch!=13) ch=getch();
			return 1 ; 
		}
		
	}while(flag||!flag);
	cin.get();
	return 0 ;
}



int bill::new_bill ( int inv_no )
{
	bill_no = inv_no ;
	strcpy ( bill_date , curr_date ) ;
	total = 0.00 ;
	
	int i=0 , slno = 1 , flag = 0 , j = 0 , beg = 0 , last = 0 , rec = 0 , k = 0 , pos = 0 , a = 0 , b = 0 , found = 0 , tab = 0 ; 
	float tot = 0 ;
	char ch = '' , temp = '' , temp_barcode[20]="" , temp_name[50]="" , temp_qty[8]="" ; 
	fstream mainfile , newfile ;
	product p , p_found ;

START:
	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(77 , 10) ;
	cout<<"INVOICE BILLING"<<endl;
	gotoxy(76,11);
	for(i = 1 ; i <= strlen("INVOICE BILLING")+2 ; ++i )
		cout<<char(205);
	cout<<endl<<endl;
	
	cout<<"   >> INVOICE NO.: "<<bill_no <<endl;
	
	gotoxy ( 135 , 13 ) ;
	if((int)tot == (float)tot)
		cout << ">> NET TOTAL (INR) : "<<total<<".00   "<<endl ; 
	else if ((int)(tot*2) == (float)(tot*2))
		cout << ">> NET TOTAL (INR) : "<<total<<"0   "<<endl ;
	else
		cout << ">> NET TOTAL (INR) : "<<total<<"   "<<endl ;
	for ( i = 1 ; i<=168 ; ++i )
		cout<<(char)220 ;
	cout<<endl ;
	gotoxy ( 3 , 16 ) ;
	cout<<"SL#."<<endl;
	gotoxy ( 15 , 16 ) ;
	cout<<"BARCODE"<<endl ;
	gotoxy ( 40 , 16 );
	cout<<"DESCRIPTION"<<endl;
	gotoxy ( 100 , 16 );
	cout<<"RATE (INR)"<<endl ;
	gotoxy ( 135 , 16 ) ;
	cout<<"QTY"<<endl ;
	gotoxy ( 150 , 16 ) ;
	cout<<"TOTAL"<<endl;
	for ( i = 1 ; i<=168 ; ++i )
		cout<<(char)220 ;
	cout<<endl<<endl ;
	
	if ( flag == 3 )
	{
		for ( k = 0 ; k < slno ; ++k ) 
		{
			gotoxy ( 3 , 19+(2*k)); cout<<k+1<<endl;
			gotoxy ( 15 , 19+(2*k)); cout<<item[k].prd.barcode<<endl;
			gotoxy ( 40 , 19+(2*k)); cout<<item[k].prd.name<<endl;
			gotoxy ( 100 , 19+(2*k));
			
			if((int)(item[k].prd.price) == (float)(item[k].prd.price))
				{cout << setw(3)<<float(item[k].prd.price)<<".00" <<endl;}
			else if ((int)(p.price*2) == (float)(p.price*2))
				{cout << setw(5)<<float(item[k].prd.price)<<"0"<<endl;}		
			else
				{cout << setw(6)<<float(item[k].prd.price)<<endl;}				
			
			gotoxy ( 135 , 19+(2*k)); cout<<item[k].qty<<endl;
			gotoxy ( 150 , 19+(2*k)); 
			
			if((int)((item[k].prd.price)*item[k].qty) == (float)((item[k].prd.price)*item[k].qty))
				{cout << setw(3)<<float(((item[k].prd.price)*item[k].qty))<<".00" <<endl;}
			else if ((int)(((item[k].prd.price)*item[k].qty)*2) == (float)(((item[k].prd.price)*item[k].qty)*2))
				{cout << setw(5)<<float(((item[k].prd.price)*item[k].qty)) <<"0"<<endl;}		
			else
				{cout << setw(6)<<float(((item[k].prd.price)*item[k].qty)) <<endl;}			
		}
		gotoxy(150 , 19+2*(slno-1) );cout<<"             "<<endl;
		flag = 0 ;
	}
	
READ_BC:
	do
	{
		gotoxy ( 135 , 13 ) ;
		
				if((int)tot == (float)tot)
					cout << ">> NET TOTAL (INR) : "<<total<<".00   "<<endl ; 
				else if ((int)(tot*2) == (float)(tot*2))
					cout << ">> NET TOTAL (INR) : "<<total<<"0    "<<endl ;
				else
					cout << ">> NET TOTAL (INR) : "<<total<<"    "<<endl ;
		
		gotoxy ( 3 , 19+2*(slno-1) ) ;
		cout<<"                                                                                                                                     "<<endl;
		gotoxy ( 3 , 19+2*(slno-1) );
		cout << slno <<endl;
		do
		{
			gotoxy ( 15 , 19+2*(slno-1) ) ;
			cout<<"                                                                                                                                                                       "<<endl;
			gotoxy ( 15 , 19+2*(slno-1) );			
			temp = '' ;
			i = 0 ;
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && slno > 1 && (int)temp == 13 )
				{
					flag = bill_checkout () ;
					
					if ( flag == 2 )
					{
						item_count = slno - 1  ; 
						return 2 ; 
					}
					
					if ( flag == 3 )
					{
						goto START ;
					}
				}
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( !i && (int)temp == 9 )
				{
					flag = 0 ;
					found = 0 ;
					goto READ_NAME ;
				}
				
				if ( slno == 1 && temp_barcode[0]=='0' && i==1 && (int)temp == 13 )
					return -1 ;
					
				if ( temp_barcode[0]=='0' && i==1 && (int)temp == 13 && slno > 1)
				{
					gotoxy ( 15 , 19+2*(slno-1) ) ;
					cout<<"                                                                                                                                                               "<<endl;					
					pos = slno-2 ;
					goto MANUAL_ENTRY ;
				}
					
				if ( (int)temp != 8 && (int)temp != 13 && (int)temp != 9 ) 
					if ( i !=19 && isalnum(temp) )
						temp_barcode[i++] = toupper(temp) ;
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 15 , 19+2*(slno-1) ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 70 , 19+2*slno ) ;	
					cout<<"                                   ";					
					cout<<endl;
					gotoxy ( 15 , 19+2*(slno-1) ) ;
					for ( j=0 ; j<i ; ++j)
					{
						printf("%c" , temp_barcode[j]);
					}
					
					if ( found )
					{
						for ( a = 1 ; a <= found ; ++a ) 
						{
							for ( b = 15 ; b <= 110 ; ++b )
							{
								cout<<endl ;
								gotoxy ( b , (19+(a*2))+2*(slno-1) ) ;
								cout<<" "<<endl ;
							}
						}
					}
						found = 0 ;
						strcpy(p_found.barcode," ");
						mainfile.open("prod_list.bin" , ios::in | ios::binary ) ;
						while ( mainfile . read ( (char*) &p , sizeof ( product ) ) )
						{
							flag = 1 ; 
							for ( j = 0 ; j < i ; ++j )
							{
								if ( p.barcode[j] != temp_barcode[j] )
								{
									flag = 1 ; 
									break ;
								}
								else flag = 0 ;
							}
							
							if ( !flag ) 
							{
								if (!found) p_found = p ;
								++found ;
								cout<<endl ;
								gotoxy ( 15 , (19+(found*2))+2*(slno-1) ) ;
								
								
								cout<<p.barcode<<endl ;
								gotoxy ( 40 , (19+(found*2))+2*(slno-1) ) ;
								cout<<"                                                      "<<endl;
								gotoxy ( 40 , (19+(found*2))+2*(slno-1) );
								cout<<p.name<<endl;
								gotoxy ( 100 , (19+(found*2))+2*(slno-1) );
								cout<<"                                   "<<endl;
		
								if((int)p.price == (float)p.price)
									{gotoxy ( 100 , (19+(found*2))+2*(slno-1) ); cout << setw(3)<<float(p.price)<<".00" <<endl;}
								else if ((int)(p.price*2) == (float)(p.price*2))
									{gotoxy ( 100 , (19+(found*2))+2*(slno-1) ); cout << setw(5)<<float(p.price) <<"0"<<endl;}		
								else
									{gotoxy ( 100 , (19+(found*2))+2*(slno-1) ); cout << setw(6)<<float(p.price) <<endl;}								
								
							}
							
							if ( found ==  5 )
								break ;
						}
						mainfile.close() ;					
				}

			gotoxy ( 15+i , 19+2*(slno-1) );	
			}
			
			temp_barcode[i] = '\0';	

			if ( !strcmpi ( temp_barcode , "CNL" ) )	return -1 ;
			
			flag = 0 ;

			mainfile.open("prod_list.bin",ios::in|ios::binary);
			
			while ( mainfile.read((char*)&p , sizeof(product)) )
			{	
				if ( !strcmp(p.barcode , temp_barcode) ) 
				{
					flag = 1 ;
					break ;
				}	
			}
			
			mainfile.close();
			
			if ( !flag && strcmp ( p_found.barcode," ") )
			{
				p = p_found ;
				flag = 1 ;
			}
			
			
			if(flag)
				break ;
			else
			{
				cout<<endl;
				gotoxy ( 70 , 19+2*slno ) ;
				cout<<"!!!...PRODUCT NOT FOUND...!!!";
				cout<<endl;
				continue ;
			}
			
		}while(!flag||flag);
		
		if ( found )
		{
			for ( a = 1 ; a <= found ; ++a ) 
			{
				for ( b = 15 ; b <= 110 ; ++b )
				{
					cout<<endl ;
					gotoxy ( b , (19+(a*2))+2*(slno-1) ) ;
					cout<<" "<<endl ;
				}
			}
		} found = 0 ;
					
		cout<<endl ;
		gotoxy ( 15 , 19+2*(slno-1) ) ;
		cout<<p.barcode<<endl;
		gotoxy ( 40 , 19+2*(slno-1) ) ;
		cout<<"                                                      "<<endl;
		gotoxy ( 40 , 19+2*(slno-1) );
		cout<<p.name<<endl;
		gotoxy ( 100 , 19+2*(slno-1) );
		cout<<"                                   "<<endl;
		
		if((int)p.price == (float)p.price)
			{gotoxy ( 100 , 19+2*(slno-1) ); cout << setw(3)<<float(p.price)<<".00" <<endl;}
		else if ((int)(p.price*2) == (float)(p.price*2))
			{gotoxy ( 100 , 19+2*(slno-1) ); cout << setw(5)<<float(p.price) <<"0"<<endl;}		
		else
			{gotoxy ( 100 , 19+2*(slno-1) ); cout << setw(6)<<float(p.price) <<endl;}	
		goto READ_QTY ;

		
READ_NAME:

		do
		{
			gotoxy ( 40 , 19+2*(slno-1) ) ;
			cout<<"                                                                                                                                                                       "<<endl;
			gotoxy ( 40 , 19+2*(slno-1) );			
			temp = '' ;
			i = 0 ;
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && slno > 1 && (int)temp == 13 )
				{
					flag = bill_checkout () ;
					
					if ( flag == 2 )
					{
						item_count = slno - 1  ; 
						return 2 ; 
					}
					
					if ( flag == 3 )
					{
						goto START ;
					}
				}
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( !i && (int)temp == 9 )
				{
					flag = 0 ;
					found = 0 ;
					goto READ_BC ;
				}
				
				if ( slno == 1 && temp_name[0]=='0' && i==1 && (int)temp == 13 )
					return -1 ;
					
				if ( temp_name[0]=='0' && i==1 && (int)temp == 13 && slno > 1)
				{
					gotoxy ( 40 , 19+2*(slno-1) ) ;
					cout<<"                                                                                                                                                               "<<endl;					
					pos = slno-2 ;
					goto MANUAL_ENTRY ;
				}
					
				if ( (int)temp != 8 && (int)temp != 13 && (int)temp != 9 ) 
					if ( i !=19 && isalnum(temp) )
						temp_name[i++] = toupper(temp) ;
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 40 , 19+2*(slno-1) ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 70 , 19+2*slno ) ;	
					cout<<"                                   ";					
					cout<<endl;
					gotoxy ( 40 , 19+2*(slno-1) ) ;
					for ( j=0 ; j<i ; ++j)
					{
						printf("%c" , temp_name[j]);
					}
					
					if ( found )
					{
						for ( a = 1 ; a <= found ; ++a ) 
						{
							for ( b = 15 ; b <= 110 ; ++b )
							{
								cout<<endl ;
								gotoxy ( b , (19+(a*2))+2*(slno-1) ) ;
								cout<<" "<<endl ;
							}
						}
					}
						found = 0 ;
						strcpy(p_found.name," ");
						mainfile.open("prod_list.bin" , ios::in | ios::binary ) ;
						while ( mainfile . read ( (char*) &p , sizeof ( product ) ) )
						{
							flag = 1 ; 
							for ( j = 0 ; j < i ; ++j )
							{
								if ( p.name[j] != temp_name[j] )
								{
									flag = 1 ; 
									break ;
								}
								else flag = 0 ;
							}
							
							if ( !flag ) 
							{
								if (!found) p_found = p ;
								++found ;
								cout<<endl ;
								gotoxy ( 15 , (19+(found*2))+2*(slno-1) ) ;
								
								
								cout<<p.barcode<<endl ;
								gotoxy ( 40 , (19+(found*2))+2*(slno-1) ) ;
								cout<<"                                                      "<<endl;
								gotoxy ( 40 , (19+(found*2))+2*(slno-1) );
								cout<<p.name<<endl;
								gotoxy ( 100 , (19+(found*2))+2*(slno-1) );
								cout<<"                                   "<<endl;
		
								if((int)p.price == (float)p.price)
									{gotoxy ( 100 , (19+(found*2))+2*(slno-1) ); cout << setw(3)<<float(p.price)<<".00" <<endl;}
								else if ((int)(p.price*2) == (float)(p.price*2))
									{gotoxy ( 100 , (19+(found*2))+2*(slno-1) ); cout << setw(5)<<float(p.price) <<"0"<<endl;}		
								else
									{gotoxy ( 100 , (19+(found*2))+2*(slno-1) ); cout << setw(6)<<float(p.price) <<endl;}								
								
							}
							
							if ( found ==  5 )
								break ;
						}
						mainfile.close() ;					
				}

			gotoxy ( 40+i , 19+2*(slno-1) );	
			}
			
			temp_name[i] = '\0';	

			if ( !strcmpi ( temp_name , "CNL" ) )	return -1 ;
			
			flag = 0 ;

			mainfile.open("prod_list.bin",ios::in|ios::binary);
			
			while ( mainfile.read((char*)&p , sizeof(product)) )
			{	
				if ( !strcmp(p.name , temp_name) ) 
				{
					flag = 1 ;
					break ;
				}	
			}
			
			mainfile.close();
			
			if ( !flag && strcmp ( p_found.name," ") )
			{
				p = p_found ;
				flag = 1 ;
			}
			
			
			if(flag)
				break ;
			else
			{
				cout<<endl;
				gotoxy ( 70 , 19+2*slno ) ;
				cout<<"!!!...PRODUCT NOT FOUND...!!!";
				cout<<endl;
				continue ;
			}
			
		}while(!flag||flag);
		
		if ( found )
		{
			for ( a = 1 ; a <= found ; ++a ) 
			{
				for ( b = 15 ; b <= 110 ; ++b )
				{
					cout<<endl ;
					gotoxy ( b , (19+(a*2))+2*(slno-1) ) ;
					cout<<" "<<endl ;
				}
			}
		} found = 0 ;
					
		cout<<endl ;
		gotoxy ( 15 , 19+2*(slno-1) ) ;
		cout<<p.barcode<<endl;
		gotoxy ( 40 , 19+2*(slno-1) ) ;
		cout<<"                                                      "<<endl;
		gotoxy ( 40 , 19+2*(slno-1) );
		cout<<p.name<<endl;
		gotoxy ( 100 , 19+2*(slno-1) );
		cout<<"                                   "<<endl;
		
		if((int)p.price == (float)p.price)
			{gotoxy ( 100 , 19+2*(slno-1) ); cout << setw(3)<<float(p.price)<<".00" <<endl;}
		else if ((int)(p.price*2) == (float)(p.price*2))
			{gotoxy ( 100 , 19+2*(slno-1) ); cout << setw(5)<<float(p.price) <<"0"<<endl;}		
		else
			{gotoxy ( 100 , 19+2*(slno-1) ); cout << setw(6)<<float(p.price) <<endl;}	
		goto READ_QTY ;















			
		
READ_QTY:
		do
		{
			gotoxy ( 135 , 19+2*(slno-1) ) ;
			cout<<"                                   "<<endl;
			gotoxy ( 135 , 19+2*(slno-1) );			
			temp = '' ;
			i = 0 ;
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && (int)temp == 13 ) 
				{	
					temp = '' ;
					continue ;
				}
				
				if ( temp_qty[0]=='0' && i==1 && (int)temp == 13 )
					goto READ_BC ;
					
				if ( (int)temp != 8 && (int)temp != 13 ) 
					if ( i !=9 && isdigit(temp) )
						temp_qty[i++] = toupper(temp) ;
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 135 , 19+2*(slno-1) ) ;
					printf("                                                           ") ;
					cout<<endl;
					gotoxy ( 135 , 19+2*(slno-1) ) ;
					for ( j=0 ; j<i ; ++j)
						printf("%c" , temp_qty[j]);
				}
				
			}
			temp_qty[i] = '\0';	
			cout<<endl ;
			flag = 0 ;
			
			for ( i = 0 ; i < (slno-1) ; ++i )
			{
				if ( !strcmpi(item[i].prd.barcode , p.barcode) ) 
				{
					flag = 1 ;
					break ;
				}
			}
			
			if ( flag ) 
			{
				item[i].qty += atoi(temp_qty) ; 
				total = total + ( item[i].prd.price * atoi ( temp_qty ) ); 	
				tot = item[i].prd.price * item[i].qty ;
				cout<<endl ;
				gotoxy ( 135 , 19+2*(i));
				cout<<"                                         "<<endl;
				gotoxy ( 135 , 19+2*(i));
				cout<<item[i].qty<<endl ;
				gotoxy ( 150 , 19+2*(i));

				if((int)tot == (float)tot)
					{gotoxy ( 150 , 19+2*(i) ); cout << setw(3)<<float(tot)<<".00" <<endl;}
				else if ((int)(tot*2) == (float)(tot*2))
					{gotoxy ( 150 , 19+2*(i) ); cout << setw(5)<<float(tot) <<"0"<<endl;}		
				else
					{gotoxy ( 150 , 19+2*(i) ); cout << setw(6)<<float(tot) <<endl;}					
				--slno ;
			}
			
			else
			{
				tot = p.price * atoi ( temp_qty ) ;
				cout<<endl;

				if((int)tot == (float)tot)
					{gotoxy ( 150 , 19+2*(slno-1) ); cout << setw(3)<<float(tot)<<".00" <<endl;}
				else if ((int)(tot*2) == (float)(tot*2))
					{gotoxy ( 150 , 19+2*(slno-1) ); cout << setw(5)<<float(tot) <<"0"<<endl;}		
				else
					{gotoxy ( 150 , 19+2*(slno-1) ); cout << setw(6)<<float(tot) <<endl;}					
				item[slno-1].prd = p ;
				item[slno-1].qty=atoi(temp_qty);
				total += tot ;
			}
			
			++slno ;
			
			goto READ_BC ;
			
			flag = 0 ;
						
		}while(!flag||flag);

		
	}while ( !flag || flag ) ;
	
	
	cin.get () ;
	return 0 ;
	
MANUAL_ENTRY:
{
	gotoxy ( 135 , 19+2*(pos) ) ;
	cout<<"         "<<endl;
	gotoxy ( 135 , 19+2*(pos) ) ;
	temp = '' ;
	i = 0 ;
	while ( (int)temp!= 13 )
	{
			
		temp=getch();
		
		if ( !i && (int)temp == 13 ) 
		{	
			flag = 3;
			goto START ;
		}
		
		if ( !i && ( temp == 'D' || temp == 'd' ) )
		{
			cout<<"D"<<endl;
			gotoxy ( 135 , 19+2*(pos) ) ;
			temp = '';
			while((int)temp!=13 && (int)temp!=8)
			{
				temp = getch () ;
			}
			
			if ( (int)temp == 8 ) 
			{
				i = 0 ; 
				temp = '' ; 
				goto MANUAL_ENTRY ;
			}
			if ( (int)temp == 13 )
			{
				total = total - ( item[pos].prd.price * item[pos].qty ) ;
				for ( i = pos ; i <= slno-1 ; ++i )
				{
					item[i] = item[i+1];
				}
				--slno;
				flag = 3 ;
				goto START ;
			}
		}
		
		if ( temp_qty[0]=='0' && i==1 && (int)temp == 13 )
		{
			if (pos - 1 >= 0 ) 
			{
				gotoxy ( 135 , 19+2*(pos) ) ;
				cout<<"         "<<endl;			
				gotoxy ( 135 , 19+2*(pos) ) ;
				cout<<item[pos].qty<<endl;			
				--pos ;
			}
			goto MANUAL_ENTRY ;
		}
			
		if ( (int)temp != 8 && (int)temp != 13 ) 
			if ( i !=9 && isdigit(temp) )
				temp_qty[i++] = toupper(temp) ;
			
		if ( (int)temp == 8 )
			if ( i != 0 )
					--i ;
			else
					i = 0 ;		
	
		if ( i>=0 ) 
		{
			gotoxy ( 135 , 19+2*(pos) ) ;
			printf("         ") ;
			cout<<endl;
			gotoxy ( 135 , 19+2*(pos) ) ;
			for ( j=0 ; j<i ; ++j)
				printf("%c" , temp_qty[j]);
		}
		
	}
	temp_qty[i] = '\0';	
	
	total = total - (item[pos].prd.price*item[pos].qty) ;
	
	item[pos].qty = atoi(temp_qty);
	total = total + (item[pos].prd.price*item[pos].qty) ;
	cout<<endl ;
	flag = 3 ;
	goto START;
}
	
}

int bill::bill_checkout ( )
{
	int i = 0 , j = 0 , flag = 0 ;
	char temp_dis[10]="" , temp_cash[10]="" , temp = '' , choice ='' ;

START:
	i = 0 ; j = 0 ; flag = 0 ; temp = '' ; choice = '' ;
	header();
	gotoxy(0,0);cout<<endl;
	gotoxy(77 , 10) ;
	cout<<"INVOICE BILLING"<<endl;
	gotoxy(76,11);
	for(i = 1 ; i <= strlen("INVOICE BILLING")+2 ; ++i )
		cout<<char(205);
	cout<<endl<<endl;
	
	cout<<"   >> INVOICE NO.: "<<bill_no <<endl;
	
	gotoxy ( 135 , 13 ) ;
	cout << ">> NET TOTAL (INR) : "<<total<<".00"<<endl ; 
	for ( i = 1 ; i<=168 ; ++i )
		cout<<(char)220 ;
	cout<<endl ;
	gotoxy ( 66 , 16 ) ;
	cout<<"<<< *** >>> BILL CHECKOUT <<< *** >>>";
	cout<<endl ;
	for ( i = 1 ; i<=168 ; ++i )
		cout<<(char)220 ;
	cout<<endl<<endl ;
	
	gotoxy(57,21);cout<<">> INVOICE NUMBER         :            "<<bill_no<<endl;
	gotoxy(57,23);
	if((int)total==(float)total)
		cout<<">> TOTAL (INR)            :            "<<total<<".00"<<endl;
	else if((int)(total*2)==(float)(total*2))
		cout<<">> TOTAL (INR)            :            "<<total<<"0"<<endl;		
	gotoxy(57,25);cout<<">> DISCOUNT (INR)         :            "<<endl;
	gotoxy(57,27);cout<<">> NET TOTAL (INR)        :            "<<endl;
	gotoxy(57,29);cout<<">> CASH / CREDIT ?        :            "<<endl;
	
ENTER_DIS:
	do
	{
		if ( flag == 2 )
			msg_box("*** ERROR *** DISCOUNT MORE THAN TOTAL *** ");
		if ( flag == 0 ) 
			msg_box("!!!===ENTER DISCOUNT VALUE===!!!===HIT >> ENTER << FOR NO DISCOUNT===!!!");
		flag = 0 ;
		gotoxy ( 96 , 25 ) ;
		printf("                                                           ") ;
		gotoxy ( 96 , 25 ) ;
		
		temp = '' ;
		i = 0 ;
		
		while ( (int)temp!= 13 )
		{
				
			temp=getch();
			
			if ( !i && (int)temp == 13 ) 
			{	
				strcpy ( temp_dis , "" ) ;
				break ;
			}
			
			if ( temp_dis[0]=='0' && i==1 && (int)temp == 13 )
			{
				return 3 ;
			}
			
			if ( (int)temp != 8 && (int)temp != 13 ) 
				if ( i != 8 && ( isdigit(temp) || temp=='.' ) )
				{
					if ( temp == '.' )
						for ( j = 0 ; j < i ; ++j )
							if ( temp_dis[j] == '.' ) break ;
					
					if ( isdigit(temp) || j == i ) temp_dis[i++] = temp ;
				}
				
			if ( (int)temp == 8 )
				if ( i != 0 )
						--i ;
				else
						i = 0 ;		
		
			if ( i>=0 ) 
			{
				gotoxy ( 96 , 25 ) ;
				printf("                                                           ") ;
				cout<<endl;
				gotoxy ( 96 , 25 ) ;
				for ( j=0 ; j<i ; ++j)
					printf("%c" , temp_dis[j]);
			}
			
		}
		temp_dis[i] = '\0';		
		
		if ( !strcmp ( temp_dis , "" ) ) dis = 0.00 ;
		
		else 
			if ( atof(temp_dis) >= total  )
			{
				flag = 2 ;
				continue ;
			}
			else
			{			
				dis = atof(temp_dis) ;
				msg_box("!!!===>> ** C : CASH ** << OR >> ** R : CREDIT ** <<===!!!");
			}
		break ;
		
	}while( !flag || flag ) ;

	cout << endl ;
	
	gotoxy ( 96 , 25 ) ; 
	
	if((int)(dis)==(float)(dis))
		cout<<dis<<".00"<<endl;
	else if((int)((dis)*2)==(float)((dis)*2))
		cout<<dis<<"0"<<endl;		
	
	gotoxy ( 96 , 27 ) ; 
	
	if((int)(total-dis)==(float)(total-dis))
		cout<<total-dis<<".00"<<endl;
	else if((int)((total-dis)*2)==(float)((total-dis)*2))
		cout<<total-dis<<"0"<<endl;	
		
		net_total = total - dis ;
		
ENTER_CH:
	gotoxy(57,29);cout<<">> CASH / CREDIT ?        :            "<<endl;
	do
	{
		if ( flag == 1 )
			msg_box("*** ERROR *** INVALID CHOICE *** ");
		if ( flag == 0 ) 
			msg_box("!!!===>> ** C : CASH ** << OR >> ** R : CREDIT ** <<===!!!");
		flag = 0 ;
		gotoxy ( 96 , 29 ) ;
		printf("   ") ;
		gotoxy ( 96 , 29 ) ;
		
		temp = '' ;
		i = 0 ;
		
		while ( (int)temp!= 13 )
		{
			
			gotoxy ( 96 , 29 );	
			 temp=getch();
			 
			if ( choice=='0' && i==1 && (int)temp == 13 )
			{
				cout<<endl ;
				gotoxy ( 96 , 29 ) ; cout<<"   "<<endl ;
				gotoxy ( 96 , 27 ) ; cout<<"               "<<endl; 
				
				goto ENTER_DIS;
			}
			
			if ( !i && (int)temp == 13 ) 
			{	
				temp = '' ;
				msg_box("!!!===>> ** C : CASH ** << OR >> ** R : CREDIT ** <<===!!!");
				continue ;
			}
			
			if ( (int)temp != 13 && (int)temp != 8 )
			{
				i = 1 ;
				choice = toupper(temp) ;
			}
			

			if ( i && (int)temp == 13 ) break ;

			if ( i && (int)temp == 8 )
			{
				i = 0 ;
				gotoxy(96,29);cout<<" ";
				temp='' ;choice = '' ;
			}
		
			if ( i>=0 ) 
			{
				gotoxy ( 96 , 29 ) ;
				printf("%c" , choice);
				cout<<endl;
			}

			
			
		}

		if ( choice == 'C' || choice == 'R' ) { flag = 0 ; break ; }
		else if ( (int) choice == 13 || choice == '' ) flag = 0 ;
		else flag = 1 ;
		
		cout<<endl ;		
	} while ( !flag || flag ) ;
	
	cout<<endl ;
	flag = 0 ;
	
	if ( choice == 'C' )
	{
		cash = 1 ;
		credit = 0 ;
		
		gotoxy(57,29);cout<<">> CASH (INR)             :            "<<endl;
		gotoxy(57,31);cout<<">> CHANGE (INR)           :            "<<endl;
		
		do
		{
			if ( flag == 2 )
				msg_box("*** ERROR *** CASH LESS THAN NET TOTAL *** ");
			if ( flag == 0 ) 
				msg_box("!!!===ENTER CASH PAID===!!!");
			flag = 0 ;
			gotoxy ( 96 , 29 ) ;
			printf("            ") ;
			gotoxy ( 96 , 29 ) ;
			
			temp = '' ;
			i = 0 ;
			
			while ( (int)temp!= 13 )
			{
					
				temp=getch();
				
				if ( !i && (int)temp == 13 ) 
				{	
					msg_box("!!!===ENTER CASH PAID===!!!");
					temp = '';
					gotoxy(96 , 29 ) ;
					continue ;
				}
				
				if ( temp_cash[0]=='0' && i==1 && (int)temp == 13 )
				{
					gotoxy(57,31);cout<<"                                       "<<endl;				
					goto ENTER_CH ;
				}
				
				if ( (int)temp != 8 && (int)temp != 13 ) 
					if ( i != 8 && ( isdigit(temp) || temp=='.' ) )
					{
						if ( temp == '.' )
							for ( j = 0 ; j < i ; ++j )
								if ( temp_cash[j] == '.' ) break ;
						
						if ( isdigit(temp) || j == i ) temp_cash[i++] = temp ;
					}
					
				if ( (int)temp == 8 )
					if ( i != 0 )
							--i ;
					else
							i = 0 ;		
			
				if ( i>=0 ) 
				{
					gotoxy ( 96 , 29 ) ;
					printf("                ") ;
					cout<<endl;
					gotoxy ( 96 , 29 ) ;
					for ( j=0 ; j<i ; ++j)
						printf("%c" , temp_cash[j]);
				}
				
			}
			temp_cash[i] = '\0';		
		
				if ( atof(temp_cash) < net_total  )
				{
					flag = 2 ;
					continue ;
				}
				else
				{			
					cout<<endl ;
					gotoxy ( 96 , 31 ) ;
					
					if((int)(atof(temp_cash)-net_total)==(float)(atof(temp_cash)-net_total))
						cout<<atof(temp_cash)-net_total<<".00"<<endl;
					else if((int)((atof(temp_cash)-net_total)*2)==(float)((atof(temp_cash)-net_total)*2))
						cout<<atof(temp_cash)-net_total<<"0"<<endl;						
					
					msg_box("!!!!....|||| BILL SAVED ||||....!!!!");
					temp = '' ;
					while ( (int)temp != 13 ) temp = getch () ;
					return 2 ;
				}
			break ;			
		}while ( !flag || flag ) ;
		
	}
	
	if ( choice == 'R')
	{
		cash = 0 ;
		credit = 1 ;
		float net = net_total ;
		search_customer("BILL",&net,bill_no);
		
REQD_POS:
		if (!net) goto START ;
		
		else
		{
			strcpy ( name , ::name );
			
			i = 0 , j = 0 , flag = 0 ;
			header();
			gotoxy(0,0);cout<<endl;
			gotoxy(77 , 10) ;
			cout<<"INVOICE BILLING"<<endl;
			gotoxy(76,11);
			for(i = 1 ; i <= strlen("INVOICE BILLING")+2 ; ++i )
				cout<<char(205);
			cout<<endl<<endl;
			
			cout<<"   >> INVOICE NO.: "<<bill_no <<endl;
			
			gotoxy ( 135 , 13 ) ;
			cout << ">> NET TOTAL (INR) : "<<total<<".00"<<endl ; 
			for ( i = 1 ; i<=168 ; ++i )
				cout<<(char)220 ;
			cout<<endl ;
			gotoxy ( 66 , 16 ) ;
			cout<<"<<< *** >>> BILL CHECKOUT <<< *** >>>";
			cout<<endl ;
			for ( i = 1 ; i<=168 ; ++i )
				cout<<(char)220 ;
			cout<<endl<<endl ;
			
			gotoxy(57,21);cout<<">> INVOICE NUMBER         :            "<<bill_no<<endl;
			gotoxy(57,23);
			if((int)total==(float)total)
				cout<<">> TOTAL (INR)            :            "<<total<<".00"<<endl;
			else if((int)(total*2)==(float)(total*2))
				cout<<">> TOTAL (INR)            :            "<<total<<"0"<<endl;

			gotoxy(57,25);cout<<">> DISCOUNT (INR)         :            ";
			if((int)(dis)==(float)(dis))
				cout<<dis<<".00"<<endl;
			else if((int)((dis)*2)==(float)((dis)*2))
				cout<<dis<<"0"<<endl;				
			gotoxy(57,27);cout<<">> NET TOTAL (INR)        :            ";
			if((int)(net_total)==(float)(net_total))
				cout<<net_total<<".00"<<endl;
			else if((int)((net_total)*2)==(float)((net_total)*2))
				cout<<net_total<<"0"<<endl;			
			gotoxy(57,29);cout<<">> CREDITED TO            :            "<<name<<endl;
			
			msg_box("!!!!....|||| BILL SAVED ||||....!!!!");
			temp = '' ;
			while ( (int)temp != 13 ) temp = getch () ;
			
			return 2 ;
		}
	}
	
	cin.get();
	
	return 0;
}

void bill::show_data(char type[] , int offset )
{
	int i = 0 , j = 0 ;
	if (!strcmpi(type,"HISTORY"))
	{
		cout<<endl;
		gotoxy ( 5 , offset ) ;  cout << ">>  INVOICE NO.: "<< bill_no <<endl;
		gotoxy ( 140 , offset );  cout << bill_date <<" : BILL DATE << " <<endl ;
		
		gotoxy  ( 5 , offset+2) ; cout<< "<*> TOTAL :     "<<endl ;
		if((int)total == (float)total)
			{gotoxy ( 20 , offset+2 ); cout << setw(11)<<float(total)<<".00" <<endl;}
		else if ((int)(total*2) == (float)(total*2))
			{gotoxy ( 20 , offset+2 ); cout << setw(13)<<float(total) <<"0"<<endl;}		
		else
			{gotoxy ( 20 , offset+2 ); cout << setw(14)<<float(total) <<endl;}
			
		gotoxy  ( 75 , offset+2) ; cout<< "<*> DISCOUNT : "<<endl ;
		if((int)dis == (float)dis)
			{gotoxy ( 90 , offset+2 ); cout << setw(11)<<float(dis)<<".00" <<endl;}
		else if ((int)(dis*2) == (float)(dis*2))
			{gotoxy ( 90 , offset+2 ); cout << setw(13)<<float(dis) <<"0"<<endl;}		
		else
			{gotoxy ( 90 , offset+2 ); cout << setw(14)<<float(dis) <<endl;}
			
			
		gotoxy  ( 135 , offset+2) ; cout<< "<*> NET TOTAL : "<<endl ;
		if((int)net_total == (float)net_total)
			{gotoxy ( 150 , offset+2 ); cout << setw(11)<<float(net_total)<<".00" <<endl;}
		else if ((int)(net_total*2) == (float)(net_total*2))
			{gotoxy ( 150 , offset+2 ); cout << setw(13)<<float(net_total) <<"0"<<endl;}		
		else
			{gotoxy ( 150 , offset+2 ); cout << setw(14)<<float(net_total) <<endl;}
		
		if(cash)
			{gotoxy ( 75 , offset ); cout <<" ** CASH PAYMENT ** "<<endl;}		
		else
		{
			int size = 20 + strlen(name);
			size = size /2 ;
			gotoxy ( mid - size , offset ) ;cout << "** CREDITED TO : "<<name<<" **" <<endl;		
		}		
	}
	
	
	if ( !strcmpi(type,"BILL_DISPLAY"))
	{
		header();
		gotoxy(0,0);cout<<endl;
		gotoxy(76 , 10) ;
		cout<<"PAST BILL DISPLAY"<<endl;
		gotoxy(75,11);
		for(i = 1 ; i <= strlen("PAST BILL DISPLAY")+2 ; ++i )
			cout<<char(205);
		cout<<endl<<endl;
		
		cout<<"   >> INVOICE NO.: "<<bill_no <<endl;
		
		for ( i = 1 ; i<=168 ; ++i )
			cout<<(char)220 ;
		cout<<endl ;
		gotoxy ( 3 , 16 ) ;
		cout<<"SL#."<<endl;
		gotoxy ( 15 , 16 ) ;
		cout<<"BARCODE"<<endl ;
		gotoxy ( 40 , 16 );
		cout<<"DESCRIPTION"<<endl;
		gotoxy ( 100 , 16 );
		cout<<"RATE (INR)"<<endl ;
		gotoxy ( 135 , 16 ) ;
		cout<<"QTY"<<endl ;
		gotoxy ( 150 , 16 ) ;
		cout<<"TOTAL"<<endl;
		for ( i = 1 ; i<=168 ; ++i )
			cout<<(char)220 ;
		cout<<endl<<endl ;		
		i = 0 ;
		
		for ( i = 0 ; i < item_count ; ++i ) 
		{
			gotoxy ( 3 , 19+(2*i)); cout<<i+1<<endl;
			gotoxy ( 15 , 19+(2*i)); cout<<item[i].prd.barcode<<endl;
			gotoxy ( 40 , 19+(2*i)); cout<<item[i].prd.name<<endl;
			gotoxy ( 100 , 19+(2*i)); cout<<item[i].prd.price<<endl;
			gotoxy ( 135 , 19+(2*i)); cout<<item[i].qty<<endl;
			gotoxy ( 150 , 19+(2*i)); cout<<(item[i].prd.price)*item[i].qty<<endl;
		}
		for ( j = 1 ; j<=168 ; ++j )
			cout<<(char)205 ;
		cout<<endl<<endl ;		
		++i ;
		gotoxy ( 135 , 19+(2*i)) ; cout<<" >> TOTAL (INR)     :  ";
		if((int)total == (float)total)
			{cout << setw(3)<<float(total)<<".00" <<endl;}
		else if ((int)(total*2) == (float)(total*2))
			{cout << setw(5)<<float(total) <<"0"<<endl;}		
		else
			{cout << setw(6)<<float(total) <<endl;}	
			
		gotoxy ( 135 , 21+(2*i)) ; cout<<" >> DISCOUNT (INR)  :  ";
		if((int)dis == (float)dis)
			{cout << setw(3)<<float(dis)<<".00" <<endl;}
		else if ((int)(dis*2) == (float)(dis*2))
			{cout << setw(5)<<float(dis) <<"0"<<endl;}		
		else
			{cout << setw(6)<<float(dis) <<endl;}	
			
		gotoxy ( 135 , 23+(2*i)) ; cout<<" >> NET TOTAL (INR) :  ";
		if((int)net_total == (float)net_total)
			{cout << setw(3)<<float(net_total)<<".00" <<endl;}
		else if ((int)(net_total*2) == (float)(net_total*2))
			{cout << setw(5)<<float(net_total) <<"0"<<endl;}		
		else
			{cout << setw(6)<<float(net_total) <<endl;}			
		
		gotoxy ( 135 , 25+(2*i)) ; cout<<" >> PAYMENT         :  ";
		if(cash)cout<<"CASH"<<endl;
		else
			{	cout<<"CREDIT"<<endl;
				gotoxy( 25 , 21+(2*i)) ; cout<<"*** CREDITED TO : "<<name<<" ***"<<endl;
			}
		msg_box("!!!===HIT >> ENTER << TO CONTINUE===!!!");
		char ch = '' ;
		while ( (int)ch != 13 ) ch = getch() ;
		
	}

}

