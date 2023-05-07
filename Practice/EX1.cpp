 #include <iostream>
  using namespace std;
  
  struct AAA{
  int n;
 public:
  AAA():n(0){};
  AAA(int num = 0):n(num){
  }
};
 
 int main(void){
 AAA s1();
 AAA s2(10);

 cout<<"NoNo"<<endl;
 
  try{
 if(s2.n == 10)
 throw s2.n;
}
cout<<"NoNo"<<endl;
catch(int error){
 cout<<error<<endl;
}
return 0;
}