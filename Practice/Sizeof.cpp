#include <iostream>
using namespace std;

class aaa{
	int n1;
	public:
	aaa(int n) : n1(n) {}
	~aaa() {
		cout << "de" << endl;
	}

	void show(const aaa a) {cout << a.n1 << endl;}
};

int main(int argc, char const *argv[])
{
	aaa a1(10);
	aaa a2(20);
	a2.show(a1);
	
	return 0;
}
