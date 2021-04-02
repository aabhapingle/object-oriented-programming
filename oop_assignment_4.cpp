/* Write a C++ program that creates an output file, writes information to it, closes the file, open
it again as an input file and read the information from the file.
*/

#include<iostream>
#include<iomanip>
#include<fstream>
// for setw

using namespace std;

// base class
class publication{
protected:
	float price;
	string title;
public:
	// default constructor
	publication(){
		title = "0";
		price = 0.0;
	}

	// for string validation
	bool validName(string name)
		{
		    if(name.length() == 0)
		        return false;

		    for(int i = 0; i < name.length(); i++)
		    {
		    	if(name[i] >= '0' && name[i] <= '9')
		        return false;
		    }
		    return true;
		}

	void get_main_details(){
		cout<<"Enter the title:";
		getline(cin, title);
		while (!validName(title))
		    {
				cout << "Invalid ! Press enter to proceed.";
				cin.clear();
				cin.ignore(1000, '\n');
				cout<<"Enter the title:";
		        getline(cin, title);
		    }
		cout<<"Enter the price:";
		cin>>price;
	}
};

class book:public publication{
private:
	int page_count;
public:
	book(){
		page_count = 0;
	}
	void get_page(){
		cout<<"Enter the page count of the book:";
		cin>>page_count;
	}
	void display_book(){
		cout<<"*****BOOK DETAILS*****"<<endl;
		cout<<"Title: "<<title<<endl;
		cout<<"Price: Rs."<<price<<endl;
		cout<<"Page count: "<<page_count<<endl;
		cout<<"\n";
	}
	// int storebook();

	int storebook(){
		ofstream fout;
		// fout.open("test_file.dat", ios::app|ios::binary);

		fout.open("test_file_2.txt", ios::app);

		// address of caller object, use 'this'

		fout.write((char*)this, sizeof(*this));  // size of book object
		fout.close();
		cout<<"Contents written and file closed successfully!"<<endl;
		return 1;
	}

	void viewAllBooks(){
		ifstream fin;
		fin.open("test_file_2.txt", ios::in);
		if(!fin){
			cout<<"File not found!"<<endl;
		}
		else{
			fin.read((char*)this, sizeof(*this));
			while(!fin.eof()){
				display_book();
				fin.read((char*)this, sizeof(*this));
			}
			fin.close();
		}
	}

};

class tape:public book{
private:
	float playing_time;
public:
	tape(){
		playing_time = 0.0;
	}
	void get_time(){
		cout<<"Enter playing time(in min):";
		cin>>playing_time;
	}
	void display_tape(tape obj2){
		cout<<"*****TAPE DETAILS*****"<<endl;
		cout<<"Title: "<<obj2.title<<endl;
		cout<<"Price: Rs."<<obj2.price<<endl;
		cout<<"Playing time in minutes: "<<obj2.playing_time<<endl;
		cout<<"\n";
	}
};

// error check
int getchoice(){
	int choice = 0;

	cout<<"Enter a choice:";
	cin>>setw(1)>>choice;

	// error check for choice
	while(!cin.good())
	{
		cout<<"Please enter correct input!"<<endl;

		cin.clear();
		cin.ignore(10000, '\n'); // single quote n

		cout<<"Enter a choice:";
		cin>>setw(1)>>choice;
	}

	//clear stream
	cin.clear();
	cin.ignore(10000, '\n'); // single quote n

	return choice;
}


int main(){
//	book obj3;
//	obj3.display_book(obj3);

//	tape obj4;
//	obj4.display_tape(obj4);

	cout<<"---Choose an option---\n 1.Book\n 2.Tape\n 3.View all books\n 4.Exit"<<endl;

	int choice = 0;
	choice = getchoice();

	while(choice != 4)
	{
		switch(choice)
		{
		case 1:
			// object dies after the block
		{
			cout<<"---BOOK---"<<endl;
			book obj;
			obj.get_main_details();
			obj.get_page();
			// obj.display_book(obj);
			obj.storebook();
			break;
		}

		case 2:
		{
			cout<<"---TAPE---"<<endl;
			tape obj1;
			obj1.get_main_details();
			obj1.get_time();
			obj1.display_tape(obj1);
			break;
		}

		case 3:
		{
			book b1;
			b1.viewAllBooks();
			break;
		}

		default:
		{
			cout<<"Enter a valid option !"<<endl;
			break;
		}
		}
		cout<<"---Choose an option---\n 1.Book\n 2.Tape\n 3.View all books\n 4.Exit"<<endl;
		choice = getchoice();
	}
	cout<<"Bye"<<endl;
	return 0;
}
