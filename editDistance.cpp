#include <iostream>
#include <string>

using namespace std;

int editDistance(string x, string y) {
    int xLength = x.length();
    int yLength = y.length();
    if (xLength == 0 && yLength == 0)
        return 0; // empty strings are the same

    int dp[xLength + 1][yLength + 1];  // x is the row, y is the column

    for (int i = 0; i <= xLength; i++)  // if y is an empty string
        dp[i][0] = i;
    for (int j = 0; j <= yLength; j++)  // if x is an empty string
        dp[0][j] = j;

    for (int i = 1; i <= xLength; i++) {
        for (int j = 1; j <= yLength; j++) {
            if (x[i - 1] == y[j - 1])
                dp[i][j] = dp[i - 1][j - 1];  // base case
            else
                dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + 1);  // min of delete, insert, substitute
        }
    }


    //display steps
    int xL = xLength;
    int yL = yLength;
    while (xL > 0 && yL > 0) {
        if (x[xL - 1] != y[yL - 1]) {
            if (dp[xL][yL] == 1 + dp[xL][yL - 1]) {
                cout << "Insert \"" << y[yL - 1] << "\"" << endl;
                yL--;
            }
            else if (dp[xL][yL] == 1 + dp[xL - 1][yL]) {
                cout << "Delete \"" << x[xL - 1] << "\"" << endl;
                xL--;
            }
            else if (dp[xL][yL] == 1 + dp[xL - 1][yL - 1]) {
                cout << "Substitute \"" << x[xL - 1] << "\" into \"" << y[yL - 1] << "\"" << endl;
                xL--;
                yL--;
            }
        } else {
            xL--;
            yL--;
        }
    }

    // if xLength > yLength and every letter in y is in x then we delete the remaining letters
    while (xL > 0) {
        cout << "Delete \"" << x[xL - 1] << "\"" << endl;
        xL--;
    }

    return dp[xLength][yLength];
}

int main() {
    string x, y;
    cout << "Enter word 1: ";
    getline(cin, x);
    cout << "Enter word 2: ";
    getline(cin, y);

    int answer = editDistance(x, y);
    cout << "The minimum steps are: " << answer << endl;

    return 0;
}


