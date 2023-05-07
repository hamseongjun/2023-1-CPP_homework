#include<iostream>
using namespace std;

class AAA{
private : 
	int num;
public :
    AAA(const int num){
        this->num = num;
    }
	AAA& add1(int n){
	 	num += n;
	 	return *this;
	}
	AAA add2(int n){
	 	num += n;
	 	return *this;
	}
	AAA& ShowNum(){
	 	cout<<num<<endl;
	 	return *this;
	}
};

int main(void){
	AAA a(3);
	a.add1(1).add1(1).ShowNum();
	a.add2(1).add2(1);
	a.ShowNum();
	return 0;
}
