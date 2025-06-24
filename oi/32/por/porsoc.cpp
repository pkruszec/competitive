#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
using namespace std;

using permutation_t = vector<int>;
using counter_t = long long;

// Function to calculate the number of inversions in a permutation
counter_t calculate_inversions(const permutation_t& perm) {
    counter_t inversions = 0;
    for (size_t i = 0; i < perm.size(); ++i) {
        for (size_t j = i + 1; j < perm.size(); ++j) {
            if (perm[i] > perm[j]) {
                ++inversions;
            }
        }
    }
    return inversions;
}

int main() {
    cerr << "[DEBUG] STARTING!" << endl;
    
    // Open the input file.
    ifstream input("input.in");
    if (!input) {
        cerr << "Error: Cannot open input file!" << endl;
        return 1;
    }

    // Read n, m, and the initial permutation.
    int n, m;
    input >> n >> m;
    permutation_t books(n);
    for (int i = 0; i < n; ++i) {
        input >> books[i];
    }

    // Close the input file.
    input.close();

    // Track remaining operations.
    int remaining_operations = m;

    // Output the size of the permutation.
    cout << n << endl;

    cerr << "[DEBUG] Books: ";
    for (auto x : books) {
        cerr << x << " ";
    }
    cerr << endl << endl;

    // Interactive loop.
    while (true) {
        // Read the positions of the pairs to be swapped.
        int x, y;
        cin >> x >> y;
        cerr << "[DEBUG] Swapping positions: " << x << ' ' << y << endl;

        // Check if we have remaining operations.
        if (remaining_operations <= 0) {
            cerr << "Error: No operations remaining!" << endl;
            return 1;
        }

        // Swap the books at indices x-1 and y-1 (convert to 0-based index).
        swap(books[x - 1], books[y - 1]);
        --remaining_operations;

        // Calculate the number of inversions.
        counter_t inversions = calculate_inversions(books);

        cerr << "[DEBUG] Books: ";
        for (auto x : books) {
            cerr << x << " ";
        }
        cerr << endl << "[DEBUG] LIBRARY RETURNS: " << inversions << endl << endl;
        
        // Output the number of inversions.
        cout << inversions << endl;
        if (inversions == 0) {
            cerr << "[DEBUG] SOLVED, remaining_operations: " << remaining_operations << endl;
            return 0;
        }
    }

    return 0;
}
