// C++ code to implement 4-queen

#include <bits/stdc++.h>
using namespace std;

int a[30], cnt;

// Function to check whether queen can be
// placed in current position or not.
int place(int pos)
{
	int i;
	for (i = 1; i < pos; i++) {
		if ((a[i] == a[pos])
			|| ((abs(a[i] - a[pos]) == abs(i - pos))))
			return 0;
	}
	return 1;
}

// Function to print out the chess board
void print_sol(int N)
{
	int i, j;
	cnt++;
	cout << "\n\nSolution " << cnt << ":\n";
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (a[i] == j)
				cout << "Q\t";
			else
				cout << "*\t";
		}
		cout << endl;
	}
}

// Function to plave N queens on
// a N*N chess borad such that
// no queen attacks each other
void queen(int n)
{
	cnt = 0;
	int k = 1;
	a[k] = 0;
	while (k != 0) {
		a[k] = a[k] + 1;
		while ((a[k] <= n) && !place(k))
			a[k]++;
		if (a[k] <= n) {
			if (k == n)
				print_sol(n);
			else {
				k++;
				a[k] = 0;
			}
		}
		else
			k--;
	}
}

// Driver Code
int main()
{
	int N = 4;

	// Function call
	queen(N);
	cout << "\nTotal solutions=" << cnt;
	return 0;
}
