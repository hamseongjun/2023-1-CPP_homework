#include<iostream>
using namespace std;

void Swap(int &i, int &j){
    int temp = i;
    i = j;
    j = temp;
}

void SelectionSort(int *arr, const int n){
	int a, i, j, k;
	for(i=0; i<n; i++){
		a = i;
		for(j = i+1; j < n; j++)
	 		if (arr[j]<arr[a])
	 			a = j;
	 	swap(arr[i], arr[a]);
	 	for(int b = 0; b < n; b++)
	 		cout<<arr[b]<<" ";
	 	cout<<endl;
	}
}
int main(void){
	 int arr[5] = {9, 4, 7, 3, 2};
	SelectionSort(arr,5);
	return 0;
}
