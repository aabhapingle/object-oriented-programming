/* Write a function template for selection sort that inputs,
sorts and outputs an integer array and a float array. */

// if we are overloading a function just because the datatype is different
// coding is same
// number of arguements is also same

// complexity of selection sort is O(n^2)

#include<iostream>
#include<iomanip>

using namespace std;

// X is a placeholder

template <class X>
// no bound checking for formal parameters arr[]
// length of array does not matter

void sort(X arr[], int n){
	// n is the number of elements in the array

	for(int j = 0; j<n; j++){
		X min = arr[j];
		int position = j;  // position where the min element is found

		// find minimum
		for(int k = j; k<n ;k++){
			if(min > arr[k]){
				min = arr[k];
				position = k;
			}
		}

		// shift all the elements which are left to the position
		for(int i = position; i > j; i-- ){
			arr[i] = arr[i-1];
		}
		arr[j] = min;
	}

	cout<<"------This is the sorted array !-----"<<endl;
	// print the sorted array
	for(int a=0; a<n ; a++){
		cout<<arr[a]<<", ";
	}
	cout<<endl;
}

// error check for choice entered
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

		cout<<"Choose an option:";
		cin>>setw(1)>>choice;
	}

	//clear stream
	cin.clear();
	cin.ignore(10000, '\n'); // single quote n

	return choice;
}

// checking whether we are getting float/int inputs
template <class Y>
// parameter list should be nonempty
Y validate(Y number){
	// Y number = 0;
	cin >> number;

	while(!cin.good()){
		cout << "Please enter value of correct data type!"<<endl;

		cin.clear();
		cin.ignore(10000, '\n');

		cout<<"Enter again: ";
		cin >> number;
	}
	//clear stream
	cin.clear();
	cin.ignore(10000, '\n'); // single quote n

	return number;
}

int main(){
	// menu
	cout<<"------------------------------------------------"<<endl;
	cout<<"Choose an option:\n 1.Sort floating point numbers\n 2.Sort integers\n 3.Exit"<<endl;
	int choice = 0;
	choice = getchoice();

	while(choice != 3){
		switch(choice){
		case 1:
		{
			int n = 0;
			cout<<"How many numbers do you want to enter?";
			n = validate(n);
			cout<<endl;

			float arr_f[n];
			cout<<"----Enter floating point numbers.----"<<endl;

			// get array of float nos
			for(int f = 0; f < n; f++){
				float no;
				cout<<"Enter number "<<f<<" : ";
				no = validate(no);
				arr_f[f] = no;
			}

			// call function
			sort(arr_f, n);
			break;
		}

		case 2:
		{
			int n = 0;
			cout<<"How many numbers do you want to enter?";
			n = validate(n);
			cout<<endl;

			int arr_i[n];
			cout<<"------Enter integers------"<<endl;

			// get integer array
			for(int e=0; e < n; e++){
				int number;
				cout<<"Enter number "<<e<<" : ";
				number = validate(number);
				arr_i[e] = number;
			}

			// call function
			sort(arr_i, n);
			break;
		}

		default:
		{
			cout<<"Enter a valid option!"<<endl;
			break;
		}
		}
		cout<<"------------------------------------------------"<<endl;
		cout<<"Choose one option:\n 1.Sort floating point numbers\n 2.Sort integers\n 3.Exit"<<endl;
		choice = getchoice();
	}
    cout<<"Bye Bye!";
	return 0;
}
