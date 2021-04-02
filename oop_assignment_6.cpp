/*Write C++ program using STL for sorting and searching user defined
records such as Item records (Item code, name, cost, quantity etc)
using vector container */

// sort using cost
// search using item code
// display function
// enter an item

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Item{
public:
	int itemcode;
	string name;
	float cost;

	Item(){
		itemcode = 0;
		name = "no name given";
		cost = 0;
	}

	void get_data(){
		cout << "-----Enter details of the item:----- "<<endl;
		cout << "Name: ";
		cin >>name;
		cout<<"Item code: ";
		cin>>itemcode;
		cout<<"Cost: ";
		cin>>cost;
	}

	void diplay(){
		cout<<"-----Item details-----"<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Item Code: "<<itemcode<<endl;
		cout<<"Cost: "<<cost<<endl;
	}
};

bool iscorrect(Item &obj, int code){
	if(obj.itemcode == code){
		return true;
	}
	return false;
}

bool checkprice(Item& obj1, Item& obj2){
	return obj1.cost < obj2.cost;
}

int main(){
	vector<Item> ivector; // vector for all the items

	/* Menu driven program */
	int choice = 0;
	while(choice != 5){
		cout<<"\n";
		cout<<"-----Menu-----"<<endl;
		cout<<"1. Enter an item.\n2. Display all\n3. Search using itemcode\n4. Sort using price\n5. Exit\n";
		cout<<"Enter an option:"<<endl;
		cin>>choice;
		switch(choice){
		case 1:{
			Item obj1;
			obj1.get_data();
			ivector.push_back(obj1);
			break;
				}
		case 2:{
			cout<<"-------Item List-------"<<endl;
			for(int v=0; v<ivector.size();v++){
				ivector[v].diplay();
			}
			break;
		}
		case 3:{
			cout<< "Enter the code of the item to be searched:"<<endl;
			int code;
			cin>>code;
			auto f = find_if(ivector.begin(), ivector.end(),[&code](const Item& obj){return obj.itemcode == code;});
			if(f==ivector.end()){
				cout<<"Item not found !"<<endl;
			}
			else{
				cout<<"Search results:"<<endl;
				auto i = std::distance(ivector.begin(), f);
				ivector[i].diplay();
			}
			break;
		}
		case 4:{
			sort(ivector.begin(), ivector.end(),checkprice);
			cout<<"Items have been sorted a/c to the prices!"<<endl;
			break;
		}
		default:{
			cout<<"please enter correct option !!!"<<endl;
			break;
		}

		}
	}
	cout<<"bye";
	return 0;
}
