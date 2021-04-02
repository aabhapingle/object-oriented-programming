#include<iostream>
#include<iomanip>
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

		// validation of title
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
	void display_book(book obj){
		cout<<"\n";
		cout<<"*****BOOK DETAILS*****"<<endl;
		cout<<"Title: "<<obj.title<<endl;
		cout<<"Price: Rs."<<obj.price<<endl;
		cout<<"Page count: "<<obj.page_count<<endl;
		cout<<"----------------------";
		cout<<"\n";
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
		cout<<"\n";
		cout<<"*****TAPE DETAILS*****"<<endl;
		cout<<"Title: "<<obj2.title<<endl;
		cout<<"Price: Rs."<<obj2.price<<endl;
		cout<<"Playing time in minutes: "<<obj2.playing_time<<endl;
		cout<<"----------------------";
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
	cout<<"---Choose an option---\n 1.Enter a Book\n 2.Enter a Tape\n 3.Find a book \n 4.Find a tape\n 5.Show all books\n 6.Show all tapes\n 7.Exit"<<endl;

	int choice = 0;
	choice = getchoice();

	// arrays for storing objects of book and tape

	book book_arr[50];
	int i = 0;

	tape tape_arr[50];
	int j = 0;

	while(choice != 7)
	{
		switch(choice)
		{
		case 1:
			// object dies after the block
		{
			cout<<"\n";
			cout<<"---BOOK---"<<endl;

			book_arr[i].get_main_details();
			book_arr[i].get_page();

			i++;
			break;
		}

		case 2:
		{
			cout<<"\n";
			cout<<"---TAPE---"<<endl;

			tape_arr[j].get_main_details();
			tape_arr[j].get_time();

			j++;
			break;
		}

		case 3:
		{
			cout<<"\n";
			int b=0;
			cout<<"Enter the index of the book from 0 to "<<i<<endl;
			cin>>b;
			book_arr[b].display_book(book_arr[b]);

			break;
		}

		case 4:
		{
			cout<<"\n";
			int t=0;
			cout<<"Enter the index of the book from 0 to "<<j<<endl;
			cin>>t;
			tape_arr[t].display_tape(tape_arr[t]);

			break;
		}

		case 5:
		{
			cout<<"\n";
			cout<<"---All Books---"<<endl;

			for(int k=0; k<i;k++){
				book_arr[k].display_book(book_arr[k]);
			}

			break;
		}

		case 6:
		{
			cout<<"\n";
			cout<<"---All Tapes---"<<endl;
			for(int l=0;l<j;l++){
				tape_arr[l].display_tape(tape_arr[l]);
			}


			break;
		}

		default:
		{
			cout<<"Enter a valid option !"<<endl;
			break;
		}
		}
		cout<<"---Choose an option---\n 1.Enter a Book\n 2.Enter a Tape\n 3.Find a book \n 4.Find a tape\n 5.Show all books\n 6.Show all tapes\n 7.Exit"<<endl;
		choice = getchoice();
	}
	cout<<"Bye"<<endl;
	return 0;
}
