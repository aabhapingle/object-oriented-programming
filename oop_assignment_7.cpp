/* Write a program in C++ to use map associative container.
The keys will be the names of states and the values will be the
populations of the states.
When the program runs, the user is prompted to type the name of a state.
The program then looks in the map, using the state name as an index and
returns the population of the state. */

#include<iostream>
#include<iterator>
#include<map>
#include<string>
using namespace std;

int main(){
	// empty map
	map<string, int> india;

	india.insert(pair<string, int>("maharashtra", 100000));
	india.insert(pair<string, int>("assam", 10000));
	india.insert(pair<string, int>("bihar", 3000));
	india.insert(pair<string, int>("karnataka", 40000));
	india.insert(pair<string, int>("rajasthan", 50000));
	india.insert(pair<string, int>("west bengal", 80000));
	india.insert(pair<string, int>("telangana", 90000));
	india.insert(pair<string, int>("goa", 8000));
	india.insert(pair<string, int>("gujrat", 700000));
	india.insert(pair<string, int>("nagaland", 50000));

	// time complexity for searching items from a map is O(log(n))
	string s;

	while(1){
		cout<<"\n";
		cout<<"-----POPULATION-----"<<endl;
		cout<<"Please enter a state:";
		getline(cin, s);
		auto itr = india.find(s);
		if(itr != india.end()){
			cout<<"Population:";
			cout<<itr->second;
		}
		else{
			cout<<"No such state exists!";
		}
		cout<<"\n";
	}

	return 0;
}
