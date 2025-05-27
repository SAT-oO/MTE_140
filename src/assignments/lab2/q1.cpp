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

int arr[100000][100000] = { 0 };

int size_max = 0;

bool checkSafe( int row, int col )
{
    // check each col and diagnonal
    // note: do not need to check row due to nature of dfs, need to unmark the row after dfs call

    // rows and cols
    for( int i = 0; i < size_max; i++ )
    {
        if( arr[i][col] == 1 || arr[row][i] == 1 )
        {
            return false;
        }
    }

    // check left diag
    for( int i = row, j = col; i >= 0 && j >= 0; i--, j-- )
    {
        if( arr[i][j] == 1 )
        {
            return false;
        }
    }

    // check right diag
    for( int i = row, j = col; i >= 0 && j < size_max; i--, j++ )
    {
        if( arr[i][j] == 1 )
        {
            return false;
        }
    }

    return true;
}

void dfs( int n )
{
    // iterate through each row, current point is [n][col]
    for( int col = 0; col < n; col++ )
    {
        // if finished, print the board and return
        if( n == 0 )
        {
            for( int j = 0; j < n; j++ )
            {
                for( int k = 0; k < n; k++ )
                {
                    cout << arr[j][k] << " ";
                }
                cout << endl;
            }
            cout << endl;
            return;
        }

        // if not safe, continue
        if( !checkSafe(n, col) )
            continue;

        // safe
        arr[n][col] = 1;
        dfs( n - 1 );
        arr[n][col] = 0;
    }
}

int main()
{   
    int n;
    cin>>n;
    size_max = n;
    
    dfs(n);
    return 0;
}
