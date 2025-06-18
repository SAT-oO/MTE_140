/**
 * @brief classic n-queens problem
 *
 * @param n number of queens
 * @callgraph checkSafe
 * @return all possible cases with the given n
 */

#include <iostream>
#include <vector>
using namespace std;

int arr[10][10] = {0};

int size_max = 0;
int counter = 0;

bool checkSafe(int row, int col) {
	// check each col and diagnonal
	// note: do not need to check row due to nature of dfs, need to unmark the row after dfs call

	// rows and cols
	for (int i = 0; i < size_max; i++) {
		if (arr[i][col] == 1 || arr[row][i] == 1) {
			return false;
		}
	}

	// check left diag
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		if (arr[i][j] == 1) {
			return false;
		}
	}

	// check right diag
	for (int i = row, j = col; i >= 0 && j < size_max; i--, j++) {
		if (arr[i][j] == 1) {
			return false;
		}
	}

	return true;
}

void dfs(int n) {
	// base case
	if (n <= 0) {
		for (int j = 0; j < size_max; j++) {
			for (int k = 0; k < size_max; k++) {
				cout << arr[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
		counter++;
		return;
	}

	for (int col = 0; col < size_max; col++) {
		// check if step
		if (!checkSafe(size_max-n, col)) {
			continue;
		}

		// place queen and step to next row
		arr[size_max - n][col] = 1;
		dfs(n - 1);
		arr[size_max - n][col] = 0; // unmark the row after dfs call
	}
}

int main() {
	int n;
	cout << "Enter the number of queens: ";
	cin >> n;
	size_max = n;
	dfs(n);
	cout<< "Total solutions: " << counter << endl;
	return 0;
}
