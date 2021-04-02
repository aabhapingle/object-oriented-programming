#include<iostream>
#include<string.h>
#include<iomanip>

using namespace std;

class Student{

public:
	// student details

	string fullname;
	int rollno;
	string year;
	int division;
	string dob;
	string blood_grp;
	string address;
	string phone;
	int license_number;

	static int total_no;

	static void total_count(){
		cout<<"Total number of students:"<<total_no<<endl;
	}

	// default constructor

	Student(){
		fullname = "Student Name";
		rollno = 000000;
		year = 1;
		division = 1;
		dob = "01/01/2020";
		blood_grp = "O+";
		address = "Pune";
		phone = "0000000000";
		license_number = 0;

		//total_no++;
		}

	// parameterized constructor

	Student(Student *obj){
		this ->fullname = obj->fullname;
		this ->rollno = obj->rollno;
		this ->year = obj->year;
		this ->division = obj->division;
		this -> dob = obj->dob;
		this -> blood_grp = obj->blood_grp;
		this -> address = obj->address;
		this -> phone = obj->phone;
		this -> license_number = obj->license_number;

		total_no++;
	}

	// copy constructor

	Student(const Student &obj){
		fullname = obj.fullname;
		rollno = obj.rollno;
		year = obj.year;
		division = obj.division;
		dob = obj.dob;
		blood_grp = obj.blood_grp;
		address = obj.address;
		phone = obj.phone;
		license_number = obj.license_number;

		total_no++;
	}

	// for fullname validation
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

	// get_details will store all the details of the student

	void get_details(){
		cout<<"-----Enter Student details-----"<<endl;
		cout<<"Name:"<<endl;

		cin.ignore(50, '\n');
		getline(cin, fullname);
		while (!validName(fullname))
		{
			cout << "Invalid ! Press enter to proceed.";
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"Name:"<<endl;
			getline(cin, fullname);
		}

		// integer part will be ignored
		cout<<"Roll Number:"<<endl;
		int roll;
		while(!(cin>>roll)){
			cin.clear();
			cin.ignore(50, '\n');
			cout<<"Please enter valid roll number!"<<endl;
			cout<<"Roll Number:"<<endl;
			cin>>roll;
		}
		rollno = roll;

		cin.ignore(50, '\n');
		cout<<"Year:"<<endl;
		cin>>year;

		cout<<"Division:"<<endl;
		cin >> division;

		cout<<"Date Of Birth:"<<endl;
		cin>>dob;

		cout<<"Blood Group:"<<endl;
		cin>>blood_grp;

		cout<<"Address:"<<endl;
		cin.ignore(50, '\n');
		getline(cin, address);

		cout<<"Phone Number:"<<endl;
		cin>>phone;
	}

	// put_details will display the details of the students

	friend class Class2;

	// destructor

	~Student(){
		cout<<"Inside Destructor"<<endl;
	}
};

int Student::total_no = 0;

// friend class

class Class2{
public:
	inline void put_details(Student obj){
	cout<<"-----Student Details-----"<<endl;
	cout<<"Name: "<<obj.fullname<<endl;
	cout<<"Roll Number: "<<obj.rollno<<endl;
	cout<<"Year:"<<obj.year<<endl;
	cout<<"Division:"<<obj.division<<endl;
	cout<<"DOB:"<<obj.dob<<endl;
	cout<<"Blood Group:"<<obj.blood_grp<<endl;
	cout<<"Address:"<<obj.address<<endl;
	cout<<"Phone:"<<obj.phone<<endl;
	}
};

// error check for choice
//int getchoice(){
//	int choice = 0;
//
//	cout<<"Enter a choice:";
//	cin>>setw(1)>>choice;
//
//	// error check for choice
//	while(!cin.good())
//	{
//		cout<<"Please enter correct input!"<<endl;
//
//		cin.clear();
//		cin.ignore(10000, '\n'); // single quote n
//
//		cout<<"Enter a choice:";
//		cin>>setw(1)>>choice;
//	}
//
//	//clear stream
//	cin.clear();
//	cin.ignore(10000, '\n'); // single quote n
//
//	return choice;
//}


int main(){


	Class2 obj2;

	int c = 0;
//	c = getchoice();

	Student *ptr[10], obj;
	while(c != 7){
		cout<<"*************** MENU ****************"<<endl;
		cout<<"Enter choice:"<<endl;
		cout<<"1. Create new students."<<endl;
		cout<<"2. Display all students."<<endl;
		cout<<"3. Update Student details."<<endl;
		cout<<"4. Delete student details."<<endl;
		cout<<"5. Total number of students created in the lifetime."<<endl;
		cout<<"6. Make a copy of an object."<<endl;
		cout<<"7. Exit."<<endl;

		cin>>c;
		//c = getchoice();
		switch(c){
		case 1:
			int n;
			cout<<"How many students do you want to enter:"<<endl;
			cin>>n;

			for(int i=0;i<n;i++){
				ptr[i] = new Student();
				ptr[i]->get_details();
				}
			break;

		case 2:
			for(int j=0;j<n;j++){
			obj2.put_details(ptr[j]);
			}
			break;

		case 3:
			cout<<"Enter the index of the student that you want to update:"<<endl;
			int ch;
			cin>>ch;
			obj = new Student(*ptr[ch]);
			obj.get_details();
			cout<<"----New details:----"<<endl;
			obj2.put_details(obj);
			*ptr[ch] = obj;
			cout<<"\n"<<endl;

			// will display the total number of students

			break;

		case 4:
			cout<<"Delete which student?(Enter index)"<<endl;
			int ch1;
			cin>>ch1;
			delete(ptr[ch1]);
			cout<<"Object Destroyed !"<<endl;
			break;

		case 5:
			Student::total_count();
			break;

		case 6:
		{
			cout<<"Make a copy of which student?(Enter index)";
			int no;
			cin>>no;
			Student copy_obj = ptr[no];
			Class2 object;
			object.put_details(copy_obj);
			cout<<"Copy Made!"<<endl;
			break;
		}

		default:
		{
			cout<<"Invalid Choice!"<<endl;
			break;
		}
		}
	}
	cout<<"Bye Bye"<<endl;
	return 0;
}
