#include<iostream>
using namespace std;

class complex
{
private:
	float real, imaginary;
public:
	// default constructor

	complex()
	{
		real = 0;
		imaginary = 0;
	}

	// parameterized constructor

	complex(float r, float i)
	{
		real = r;
		imaginary = i;
	}

	// operator overloading for '+'
	// what the compiler sees here is answer = c1.add(c2)

	// here complex is the return data type, operator is a keyword and the argument taken is a complex number.

	complex operator +(complex c)
	{
		complex answer;
		answer.real = real + c.real;
		answer.imaginary = imaginary + c.imaginary;
		return answer;
	}

	// operator overloading for '*'

	complex operator *(complex c)
	{
		complex answer;
		answer.real = real*c.real - imaginary*c.imaginary;
		answer.imaginary = real*c.imaginary + c.real*imaginary;
		return answer;
	}

	// here, friend functions are defined because 'cin' and 'cout' are objects of istream and ostream
	// but we want complex class also to access these functions

	// operator overloading for << (insertion operator)

	friend ostream & operator << (ostream& out, const complex& c);

	// operator overloading for >> (extraction operator)

	friend istream & operator >> (istream& in,  complex& c);

};

// for directly taking input as a complex object

istream & operator >> (istream& in,  complex& c)
{
    cout << "Enter the Real Part of number: ";
    in >> c.real;
    cout << "Enter the Imaginary Part of number: ";
    in >> c.imaginary;
    return in;
}

// here operator overloading is done for directly displaying output as a complex object

// 'const' keyword is used because we don't want the value to be altered

// here 'out' is the object of 'ostream'

ostream & operator << (ostream& out, const complex& c)
{
	if(c.imaginary<0){
		out << c.real;
		out << c.imaginary<< "i" << endl;
		return out;
	}
	else{
		out << c.real;
		out <<"+"<< c.imaginary<< "i" << endl;
		return out;

	}
}

int main(){
	complex c1;
	cout<<"--FIRST NUMBER--"<<endl;
	cin >> c1;
	cout << "The first number is: " << c1;
	cout<< "\n";

	complex c2;
	cout<<"--SECOND NUMBER--"<<endl;
	cin >> c2;
	cout << "The second number is: " << c2;
	cout<< "\n";

	// choose an operation multiplication or addition

	int x;

	do{
		cout<<"Choose an option: \n 1.Multiplication \n 2.Addition \n 3.Exit "<< endl;
		cin>>x;

		switch(x){
		case 1:
			cout<<"The product is: "<<(c1*c2)<<endl;
			break;

		case 2:
			cout<<"The addition is: "<<(c1+c2)<<endl;
			break;

		case 3:
			cout<<"Byeee"<<endl;
			break;

		}
	}while(x!=3);

}
