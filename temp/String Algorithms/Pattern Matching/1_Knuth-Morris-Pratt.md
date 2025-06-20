#include <iostream>
#include <vector>

using namespace std;

// Function to compute the LPS array
void computeLPSArray(const string &pattern, vector<int> &lps) {
    int m = pattern.length();
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // First element is always 0
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // Reduce length
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Pattern Matching Algorithm
void KMPSearch(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> lps(m, 0); // LPS array

    // Compute LPS array
    computeLPSArray(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) { // Found a match
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1]; // Move j using LPS
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1]; // Shift pattern using LPS
            } else {
                i++;
            }
        }
    }
}

// Driver Code
int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    KMPSearch(text, pattern);

    return 0;
}
