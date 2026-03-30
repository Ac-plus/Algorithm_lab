#include <bits/stdc++.h>
using namespace std;

const int N=1000;
int weight[N]={0}, profit[N]={0};
int numberOfObjects;

//f(i,y) = profit of putting i to n with capacity y
int f(int i, int theCapacity) {
	if (i==numberOfObjects) 
		return (theCapacity < weight[numberOfObjects] 
				? 0:profit[numberOfObjects]);
				
	if (theCapacity < weight[i]) return f(i+1, theCapacity);
	
	return max(f(i+1,theCapacity), 
				f(i+1,theCapacity-weight[i])+profit[i]);
}

//减少了重复计算次数的递归函数
int fArray[N][N]={0};
int f1(int i, int theCapacity) {
	//检查是否已经计算过
	if (fArray[i][theCapacity]>=0) return fArray[i][theCapacity];
	
	//尚未计算过
	if (i==numberOfObjects){
		fArray[i][theCapacity]=(theCapacity < weight[numberOfObjects]
								? 0:profit[numberOfObjects]);
		return fArray[i][theCapacity];
	} 
	
	//使用formula 19-2 
	if (theCapacity < weight[i]) {
		fArray[i][theCapacity] = f1(i+1, theCapacity);
	}
	else {
		fArray[i][theCapacity] = max(f1(i+1,theCapacity), 
				f1(i+1,theCapacity-weight[i])+profit[i]);
	}
	return fArray[i][theCapacity];
} 

void traceback(int *weight, int numberOfObjects, 
				int knapsackCapacity, int *x) 
{
	for	(int i=1; i<numberOfObjects; i++) 
		if (f(i,knapsackCapacity)==f(i+1,knapsackCapacity))
			x[i]=0;
		else {
			x[i]=1;
			knapsackCapacity-=weight[i];
		}
	x[numberOfObjects]=(f(numberOfObjects,knapsackCapacity)>0)? 1:0;
	
	cout << "The best x[] is: ";
	for (int i=1; i<=numberOfObjects; i++)
		cout << x[i] << " ";
	cout << endl;
}

int main() {
	
	cout << "Input c: ";
	int c;
	cin >> c;
	cout << "Input n: ";
	cin >> numberOfObjects;
	cout << "Input w[]: ";
	for (int i = 1; i <= numberOfObjects; i++) 
		cin >> weight[i];
	cout << "Input p[]: ";
	for (int i = 1; i <= numberOfObjects; i++) 
		cin >> profit[i];
	
	//f1 init
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) fArray[i][j] = -1;
	
	clock_t start, end;
	start=clock();
	
	cout << "The best profit is: " << " " << f(1,c)<< endl;
	int x[N]={0};
	traceback(weight, numberOfObjects, c, x);
	
	end=clock();
	double endtime=(double)(end-start)/CLOCKS_PER_SEC;
	cout << "Total time: " << endtime * 1000 << "ms" << endl;
	return 0;
}
