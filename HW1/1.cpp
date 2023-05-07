#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void divide(const int &num1, const int &num2, int &quotient, int &remainder);

int main(void)
{
	int num1, num2;
	cout<<"�ǿ����� �� ���� �Է��ϼ���: ";
	cin>>num1>>num2;
	

	int quotient, remainder;
	try
	{
		divide(num1, num2, quotient, remainder);
		cout<<"���� "<<quotient<<", �������� "<<remainder<<"�Դϴ�."<<endl;
	}
	catch(int expn)
	{
		cout<<"�߸��� �Է� ���Դϴ�."<<endl;
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