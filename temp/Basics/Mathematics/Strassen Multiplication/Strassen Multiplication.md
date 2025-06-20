# Strassen Matrix Multiplication Algorithm

## Introduction
Strassen's algorithm is a divide-and-conquer algorithm for matrix multiplication that is more efficient than the standard matrix multiplication algorithm. It was developed by Volker Strassen in 1969.

## The Problem
The standard matrix multiplication algorithm has a time complexity of O(n³), which becomes inefficient for large matrices. Strassen's algorithm improves this to approximately O(n^2.81).

## How the Algorithm Works

### Standard Matrix Multiplication
For two matrices A and B of size n×n, the standard multiplication requires n³ scalar multiplications:
- Each element C[i,j] in the resulting matrix is calculated as the dot product of the ith row of A and the jth column of B
- Requires n scalar multiplications and n-1 additions per element
- Total: n³ multiplications and n²(n-1) additions

### Strassen's Approach
Strassen discovered that for 2×2 matrices, you can compute the product using 7 multiplications instead of 8, with additional additions.

### Algorithm Steps:

1. **Divide** each matrix into four equal-sized submatrices:

   ```
   A = | A11 A12 |    B = | B11 B12 |
       | A21 A22 |        | B21 B22 |
   ```

2. **Calculate** seven products M1 to M7:
   - M1 = (A11 + A22) × (B11 + B22)
   - M2 = (A21 + A22) × B11
   - M3 = A11 × (B12 - B22)
   - M4 = A22 × (B21 - B11)
   - M5 = (A11 + A12) × B22
   - M6 = (A21 - A11) × (B11 + B12)
   - M7 = (A12 - A22) × (B21 + B22)

3. **Compute** the result submatrices:
   - C11 = M1 + M4 - M5 + M7
   - C12 = M3 + M5
   - C21 = M2 + M4
   - C22 = M1 - M2 + M3 + M6

4. **Combine** these submatrices to get the final product.

This process is applied recursively for larger matrices until we reach a small enough size where standard multiplication becomes more efficient.

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to add two matrices
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Function to subtract two matrices
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Function to get a submatrix
vector<vector<int>> getSubmatrix(const vector<vector<int>>& A, int row, int col, int size) {
    vector<vector<int>> submatrix(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            submatrix[i][j] = A[i + row][j + col];
        }
    }
    return submatrix;
}

// Function to combine submatrices
void combineSubmatrices(vector<vector<int>>& C, 
                      const vector<vector<int>>& C11, const vector<vector<int>>& C12,
                      const vector<vector<int>>& C21, const vector<vector<int>>& C22) {
    int n = C11.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = C11[i][j];
            C[i][j + n] = C12[i][j];
            C[i + n][j] = C21[i][j];
            C[i + n][j + n] = C22[i][j];
        }
    }
}

// Function for standard matrix multiplication
vector<vector<int>> standardMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Strassen's matrix multiplication algorithm
vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    
    // Base case: if matrix size is small, use standard multiplication
    if (n <= 64) {  // Threshold can be tuned for optimal performance
        return standardMultiply(A, B);
    }
    
    int mid = n / 2;
    
    // Divide matrices into submatrices
    vector<vector<int>> A11 = getSubmatrix(A, 0, 0, mid);
    vector<vector<int>> A12 = getSubmatrix(A, 0, mid, mid);
    vector<vector<int>> A21 = getSubmatrix(A, mid, 0, mid);
    vector<vector<int>> A22 = getSubmatrix(A, mid, mid, mid);
    
    vector<vector<int>> B11 = getSubmatrix(B, 0, 0, mid);
    vector<vector<int>> B12 = getSubmatrix(B, 0, mid, mid);
    vector<vector<int>> B21 = getSubmatrix(B, mid, 0, mid);
    vector<vector<int>> B22 = getSubmatrix(B, mid, mid, mid);
    
    // Calculate 7 products recursively
    vector<vector<int>> M1 = strassenMultiply(add(A11, A22), add(B11, B22));
    vector<vector<int>> M2 = strassenMultiply(add(A21, A22), B11);
    vector<vector<int>> M3 = strassenMultiply(A11, subtract(B12, B22));
    vector<vector<int>> M4 = strassenMultiply(A22, subtract(B21, B11));
    vector<vector<int>> M5 = strassenMultiply(add(A11, A12), B22);
    vector<vector<int>> M6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
    vector<vector<int>> M7 = strassenMultiply(subtract(A12, A22), add(B21, B22));
    
    // Calculate result submatrices
    vector<vector<int>> C11 = add(subtract(add(M1, M4), M5), M7);
    vector<vector<int>> C12 = add(M3, M5);
    vector<vector<int>> C21 = add(M2, M4);
    vector<vector<int>> C22 = add(add(subtract(M1, M2), M3), M6);
    
    // Combine result submatrices
    vector<vector<int>> C(n, vector<int>(n, 0));
    combineSubmatrices(C, C11, C12, C21, C22);
    
    return C;
}

// Pad matrix to the nearest power of 2 size
vector<vector<int>> padMatrix(const vector<vector<int>>& A) {
    int n = A.size();
    int m = A[0].size();
    int maxSize = max(n, m);
    
    // Find the next power of 2
    int paddedSize = 1;
    while (paddedSize < maxSize) {
        paddedSize *= 2;
    }
    
    // Create a padded matrix filled with zeros
    vector<vector<int>> padded(paddedSize, vector<int>(paddedSize, 0));
    
    // Copy the original matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            padded[i][j] = A[i][j];
        }
    }
    
    return padded;
}

// Main function to handle matrix multiplication
vector<vector<int>> multiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    int m = A[0].size();
    int p = B.size();
    int q = B[0].size();
    
    // Check if matrices can be multiplied
    if (m != p) {
        cerr << "Error: Incompatible matrix dimensions" << endl;
        return vector<vector<int>>();
    }
    
    // Pad matrices to the nearest power of 2 size
    vector<vector<int>> paddedA = padMatrix(A);
    vector<vector<int>> paddedB = padMatrix(B);
    
    // Multiply using Strassen's algorithm
    vector<vector<int>> paddedResult = strassenMultiply(paddedA, paddedB);
    
    // Extract the actual result
    vector<vector<int>> result(n, vector<int>(q, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            result[i][j] = paddedResult[i][j];
        }
    }
    
    return result;
}

// Print a matrix
void printMatrix(const vector<vector<int>>& A) {
    for (const auto& row : A) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Main function with example
int main() {
    // Example matrices
    vector<vector<int>> A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    vector<vector<int>> B = {
        {17, 18, 19, 20},
        {21, 22, 23, 24},
        {25, 26, 27, 28},
        {29, 30, 31, 32}
    };
    
    cout << "Matrix A:" << endl;
    printMatrix(A);
    
    cout << "\nMatrix B:" << endl;
    printMatrix(B);
    
    cout << "\nResult of A * B using Strassen's algorithm:" << endl;
    vector<vector<int>> C = multiply(A, B);
    printMatrix(C);
    
    return 0;
}
```

## Time Complexity Analysis

1. **Standard Algorithm**: O(n³)
2. **Strassen's Algorithm**: O(n^log₂7) ≈ O(n^2.81)

The time complexity can be derived from the master theorem:
- We have 7 recursive calls on matrices of size n/2
- This gives T(n) = 7T(n/2) + O(n²)
- By the master theorem, this gives T(n) = O(n^log₂7)

## Space Complexity

The space complexity is O(n²) for both algorithms, as we need to store the input and output matrices.

## Practical Considerations

1. **Threshold**: For small matrices, the standard algorithm is faster due to lower constant factors. In practice, we use a hybrid approach with a threshold.

2. **Matrix Size**: Strassen's algorithm requires that the matrices be square with dimensions that are powers of 2. For other matrices, padding is needed.

3. **Numerical Stability**: Strassen's algorithm may be less numerically stable than the standard algorithm due to more additions and subtractions.

4. **Parallelization**: Strassen's algorithm can be effectively parallelized, which makes it even more efficient on multi-core systems.
