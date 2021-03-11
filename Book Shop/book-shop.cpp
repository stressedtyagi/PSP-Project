#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <vector>
using namespace std;

#define MAX_LENGTH 100

class BookShop {
	public :
		static void updateBookShop(double rev, int bS) {
			BookShop::revenue += rev;
			BookShop::bookSold += bS;
		}
		static double getRevenue(){return revenue;}
		static int getBookSold(){return bookSold;}
	private :
		static double revenue;
		static int bookSold;
};

double BookShop::revenue;
int BookShop::bookSold;

class Admin : public BookShop {
	public :
		Admin(char name[MAX_LENGTH],int pin) : name{name}, pin{pin}{}
		void AdminMenu();
		static void viewBookShopAccount();

		int getPin() const {return pin;};
		void setPin(int pin) {this->pin = pin;}
	private : 
		int pin;
		char* name;
};

class Book : public BookShop {
	public:	
		Book() : author{new char[MAX_LENGTH]}, title{new char[MAX_LENGTH]}, publisher{new char[MAX_LENGTH]}{}
		Book(char* title, char* author, char* publisher, double price, int stock) : title{title}, author{author}, publisher{publisher}, price{price}, stock{stock}{}
		
		void feedData();
		void editData();
		void buyBook();
		void showData() const;
		static void printBooks(const vector<Book>&);
		static int search(const vector<Book>&,char*,char*);
		static bool deleteBook(vector<Book>&,int);

		friend ostream& operator << (ostream&,const Book&);
		friend istream& operator >> (istream&,Book&);

		char* getTitle() {return title;}
		char* getAuthor() {return author;}
		char* getPublisher() {return publisher;}
		double getPrice() {return price;}
		int getStock() {return stock;}
	private:
		char *author,*title,*publisher;
		double price;
		int stock;
};

ostream& operator << (ostream& out, const Book& book) {
	out << "-----------------------------------------" << endl;
	out << "Title : " << book.title << endl;
	out << "Author : " << book.author << endl;
	out << "Publisher : " << book.publisher << endl;
	out << "Price : Rs." << book.price << endl;
	out << "Stock : " << book.stock << endl;
	out << "-----------------------------------------" << endl;
	return out;
}

istream& operator >> (istream& in, Book& book) {
	in.ignore();
	cout<<"Enter Title Name: ";       
	in.getline(book.title,MAX_LENGTH);
	cout<<"Enter Author Name: ";      
	in.getline(book.author,MAX_LENGTH);
	cout<<"Enter Publisher Name: ";   
	in.getline(book.publisher,MAX_LENGTH);
	cout<<"Enter Price: ";            
	in>>book.price;
	cout<<"Enter Stock Position: ";   
	in>>book.stock;   
	return in;
}

int Book::search( const vector<Book>& books, char* tbuy,char* abuy)	{
	for(int i = 0; i < books.size(); i++) {
		if(strcmp(books[i].title,tbuy)==0 && strcmp(books[i].author,abuy)==0)
			return i;
	}
	return -1;	
}

void Book::feedData()	{
	cin.ignore();
	cout<<"Enter Title Name: ";       
	cin.getline(this->title,MAX_LENGTH);
	cout<<"Enter Author Name: ";      
	cin.getline(this->author,MAX_LENGTH);
	cout<<"Enter Publisher Name: ";   
	cin.getline(this->publisher,MAX_LENGTH);
	cout<<"Enter Price: ";            
	cin>>this->price;
	cout<<"Enter Stock Position: ";   
	cin>>this->stock;   
}

void Book::editData()	{
	int choice;
	cout << "\n--------------------------------------------------------\n";
	cout << "Which Field you want to edit :- "
		<< "\n1. Author Name"
		<< "\n2. Tile of book"
		<< "\n3. Publisher Name"
		<< "\n4. Price of Book"
		<< "\n5. Stock Position of Book";
	cout << "\n--------------------------------------------------------\n";
	cout << "Enter your choice --> ";
	cin >> choice;
	cin.ignore();
	switch (choice) {
		case 1:{
			char* str = new char[MAX_LENGTH];
			cout<<"\nEnter Vaild NEW Author Name: ";      
			cin.getline(str,MAX_LENGTH);
			author = str;
			break;
		}
		case 2: {
			char *str = new char[MAX_LENGTH];
			cout<<"\nEnter NEW Title: ";       
			cin.getline(str,MAX_LENGTH);
			title = str;
			break;
		}
		case 3: {
			char *str = new char[MAX_LENGTH];
			cout<<"\nEnter NEW Publisher Name: ";   
			cin.getline(str,MAX_LENGTH);
			publisher = str;
			break;
		}
		case 4: {
			cout << "\nEnter NEW Price of the book: ";            
			cin >> this->price;
			break;
		}
		case 5: {
			cout<<"\nEnter NEW Stock Position: ";   
			cin>>this->stock;   
		}
		default:
			break;
	}
	cout << "\n\n\t\t BOOK RECORD AFTER UPDATION ..." << endl;
	this->showData();
}

void Book::showData() const{
	cout << "-----------------------------------------" << endl;
	cout << "Title : " << this->title << endl;
	cout << "Author : " << this->author << endl;
	cout << "Publisher : " << this->publisher << endl;
	cout << "Price : Rs." << this->price << endl;
	cout << "Stock : " << this->stock << endl;
	cout << "-----------------------------------------" << endl;
}

void Book::buyBook()	{
	int count;
	cout<<"\nEnter Number Of Books to buy: ";
	cin>>count;
	if(count <= this->stock)	{
		this->stock -= count;
		double total_price = (this->price)*count;
		cout<<"\nBooks Bought Sucessfully";
		cout<<"\nAmount: Rs. "<< total_price;
		updateBookShop(total_price,count);
	}else	cout<<"\n!! Required Copies not in Stock !!" << endl;
}

bool Book::deleteBook(vector<Book> &books, int index) {
	if(index == books.size()-1) {
		books.pop_back();
	}else if (index >= 0 && index < books.size()){
		for(int i = index; i < books.size(); i++) {
			books[i] = books[i+1];
		}	
		books.pop_back();
	}else {
		return false;
	}
	return true;
}

void Book::printBooks(const vector<Book> &books) {
	if(books.size() > 0) {
		cout << "**************************************************************************************************" << endl;
		for(int i = 0; i < books.size(); i++) {
			cout << "-----------------------------------------" << endl;
			cout << "SNO. : " << i+1 << endl;
			// cout << "Title : " << books[i].title << endl;
			// cout << "Author : " << books[i].author << endl;
			// cout << "Publisher : " << books[i].publisher << endl;
			// cout << "Price : Rs." << books[i].price << endl;
			// cout << "Stock : " << books[i].stock << endl;
			// cout << "-----------------------------------------" << endl;
			cout << books[i];
		}
		cout << "**************************************************************************************************" << endl;
	}else {
		cout << "!! No Record Found !! " << endl;
	}
}

void Admin::AdminMenu() {
	int choice{0};
	bool inLoop{true};
	while(inLoop) {
		cout << "\n--------------------------------------------------------\n";
		cout << "\t     !!!! [" << name << "] !!!!" << endl; 
		cout << "\n\t\t!!!! ADMIN MENU !!!!\n" << endl
			 << "1. Show Book Shop Account Details" << endl
			 << "2. Change Admin Password" << endl
			 << "0. Exit from Admin Menu" << endl;
		cout << "\n--------------------------------------------------------\n";
		cout <<"Enter your Choice --> ";
		cin >> choice;

		switch(choice) {
			case 1:
				Admin::viewBookShopAccount();
				break;
			case 2: {
				int x;
				cout << "Enter new password : ";
				cin >> x;
				this->setPin(x);
			}
				break;
			case 0:
				inLoop = false;
				break;
			default:
				cout << "\n\n\t\t !!! WRONG CHOICE !!! \n\n";
				break;
		}
	}
}

void Admin::viewBookShopAccount() {
	cout << "\n--------------------------------------------------------\n";
	cout << "\nTotal Revenue of Book Shop : Rs." << getRevenue();
	cout << "\nTotal number of copies sold : " << getBookSold() << endl;
	cout << "\n--------------------------------------------------------\n";
}

int main()	{
	Admin A((char*)"Divyanshu Tyagi", 123);
	vector<Book> B {
		Book((char*)"Eloquent JavaScript, Second Edition", (char*)"Marijn Haverbeke", (char*)"No Starch Press", 45.91, 3),
        Book((char*)"Anna Karenina", (char*)"Tolstoy", (char*)"Harcourt Brace", 13.5, 4),
        Book((char*)"Bleak House", (char*)"Dickens, Charles", (char*)"Random House", 5.75, 8),
        Book((char*)"Harry Potter", (char*)"Rowling, J.K",(char*) "Harcourt Brace", 19.95, 4),
        Book((char*)"Lord of the Rings",(char*) "Tolkien, J.R.",(char*) "Penguin", 27.45, 1),
        Book((char*)"Tom Sawyer",(char*) "Twain, Mark",(char*) "Random House", 7.75, 3),
        Book((char*)"One Hundred Years of Solitude",(char*) "Marquez",(char*) "Harper  Perennial", 14.00, 4),
        Book((char*)"Speaking JavaScript",(char*) "Axel Rauschmayer", (char*)"O'Reilly Media", 35.22, 5),
        Book((char*)"The Hours", (char*)"Cunnningham",(char*) "Harcourt Brace", 12.35, 2),
        Book((char*)"Huckleberry Finn", (char*)"Twain",(char*) "Penguin", 5.76, 6)
	};
    // vector<Book> B;
	char titlebuy[MAX_LENGTH],authorbuy[MAX_LENGTH];
	while(1)	{
		char choice;
		cout << "\n--------------------------------------------------------\n";
		cout<<"\t\t|||| MENU ||||\t\t\t[[[[ [A]-ADMIN ]]]]"
		    <<"\n1. Entry of New Book"
		    <<"\n2. Buy Book"
		    <<"\n3. Search For Book"
		    <<"\n4. Edit Details Of Book"
            <<"\n5. Delete Book"
			<<"\n6. Print All Books Details"
		    <<"\n0. Exit";
		cout << "\n--------------------------------------------------------\n";
		cout <<"Enter your Choice --> ";
		cin>>choice;
		
		switch(choice)	{
			case 'A': {
				int pin;
				cout << "Enter admin pin : ";
				cin >> pin;
				if(pin == A.getPin()) {
					cout << "\n\t    !!!! LOGIN SUCCCESSFUL !!!!" << endl;
					A.AdminMenu();
				}else {
					cout << "\n\t\t!!!! INVAILD PASSWORD !!!!" << endl;
				}
				break;
			}
			case '1': {
				Book temp;
				cin >> temp;
                B.push_back(temp);
				break;
			}	
			case '2': {
				cin.ignore();
				cout<<"\nEnter Title Of Book: "; 
                cin.getline(titlebuy,MAX_LENGTH);
				cout<<"Enter Author Of Book: ";  
                cin.getline(authorbuy,MAX_LENGTH);
				int BookIndex = Book::search(B,titlebuy,authorbuy);
				if(BookIndex != -1) {
					if(B[BookIndex].getStock() > 0)
						B[BookIndex].buyBook();
					else 
						cout<<"\n!! Required Copies not in Stock !!" << endl;
				}
				else
					cout<<"\n!! This Book is Not in our RECORD !!";	
				break;
			}
			case '3': {
				cin.ignore();
				cout<<"\nEnter Title Of Book: "; 
                cin.getline(titlebuy,MAX_LENGTH);
				cout<<"Enter Author Of Book: ";  
                cin.getline(authorbuy,MAX_LENGTH);
				int BookIndex = Book::search(B,titlebuy,authorbuy);
				if(BookIndex != -1)
					B[BookIndex].showData();
				else
					cout<<"\n!! This Book is Not in our RECORD !!";	
				break;
			} 
			case '4': {
				cin.ignore();
				cout<<"\nEnter Title Of Book: "; 
                cin.getline(titlebuy,MAX_LENGTH);
				cout<<"Enter Author Of Book: ";  
                cin.getline(authorbuy,MAX_LENGTH);
				int BookIndex = Book::search(B,titlebuy,authorbuy);
				if(BookIndex != -1) 
					B[BookIndex].editData();
				else 
					cout<<"\n!! This Book is Not in our RECORD !!";	
				break;
			} 
			case '5': {
            	cin.ignore();
				cout<<"\nEnter Title Of Book: "; 
                cin.getline(titlebuy,MAX_LENGTH);
				cout<<"Enter Author Of Book: ";  
                cin.getline(authorbuy,MAX_LENGTH);
				int BookIndex = Book::search(B,titlebuy,authorbuy);
				if(BookIndex != -1)  {
					if(Book::deleteBook(B, BookIndex)) {
						cout << "\n\n\t\tBook Successfully Deleted!!\n" << endl;
					}else {
						cout << "\n\n\t\t!! ERROR WHILE DELETING BOOK !!\n" << endl;
					}
				}else 	cout<<"\n!! This Book is Not in our RECORD !!";	
				break;
			}
			case '6': {
				Book::printBooks(B);
				break;
			}
			case '0': 
				exit(0);
			default: 
				cout<<"\nInvalid Choice Entered";
		}
	}	
	return 0;
}