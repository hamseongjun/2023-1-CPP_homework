#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void divide(const int &num1, const int &num2, int &quotient, int &remainder);

int main(void)
{
	int num1, num2;
	cout<<"피연산자 두 개를 입력하세요: ";
	cin>>num1>>num2;
	

	int quotient, remainder;
	try
	{
		divide(num1, num2, quotient, remainder);
		cout<<"몫은 "<<quotient<<", 나머지는 "<<remainder<<"입니다."<<endl;
	}
	catch(int expn)
	{
		cout<<"잘못된 입력 값입니다."<<endl;
	}
	return 0;
}

void divide(const int &val1, const int &val2, int &quotient, int &remainder)
{
	if(val2==0)
		throw val2;
	quotient = val1/val2;
	remainder = val1%val2;
}