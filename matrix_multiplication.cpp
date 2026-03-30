#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

const int N = 100;
int kay[N][N] = {0};
int r[N] = {0};
int q;  //number of matrises q

int c(int i, int j) { 
	if (i == j) return 0;
	if (i == j - 1) {
		kay[i][i+1] = i;
		return r[i]*r[i+1]*r[i+2];
	}
	
	int u = c(i,i)+c(i+1,j)+r[i]*r[i+1]*r[j+1];
	kay[i][j] = i;
	
	for (int k=i+1; k<j; k++) {
		int t = c(i,k)+c(k+1,j)+r[i]*r[k+1]*r[j+1];
		if (t < u) {
			u = t;
			kay[i][j] = k;
		}
	}
	return u;
}

int theC[N][N] = {0};
int c1(int i, int j) {
	if (theC[i][j] > 0) return theC[i][j];
	if (i == j) return 0;
	if (i == j - 1) {
		kay[i][i+1] = i;
		theC[i][j] = r[i]*r[i+1]*r[i+2];
		return theC[i][j];
	}
	
	int u = c1(i,i)+c1(i+1,j)+r[i]*r[i+1]*r[j+1];
	kay[i][j] = i;
	
	for (int k=i+1; k<j; k++) {
		int t = c1(i,k)+c1(k+1,j)+r[i]*r[k+1]*r[j+1];
		if (t < u) {
			u = t;
			kay[i][j] = k;
		}
	}
	
	theC[i][j]=u;
	return theC[i][j];
}

void traceback(int i, int j) { //»ØËÝÇó½â³Ë·¨Ë³Ðò
	if (i == j) return;
	traceback(i, kay[i][j]);
	traceback(kay[i][j]+1, j);
	cout << "Multiply M(" << i << ", " << kay[i][j] << 
			") and M(" << (kay[i][j]+1) << ", " << j << ")" << endl;
}

int main() { 
	cin >> q;  //Input q

	int col[N]={0};
	for (int i = 0; i < q; i++) { //Input data of matrix1~q
		cin >> r[i];
		cin >> col[i];
	}
	r[q] = col[q-1];
	
	clock_t start, end;
	start=clock();
	
	cout << c1(0,q-1) << endl; //Output the solution: best mult-times
	traceback(0,q-1);
	
	end=clock();
	float endtime=(float)(end-start)/CLOCKS_PER_SEC;
	cout << "Total time: " << endtime * 1000 << "ms" << endl;
	
	return 0;
}
