#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int getPairSumCount(int[], int, int);
int getMostCommonTarget(int[], int);

int main() {
    int task;
    cout << "Would you like to perform task 2 or task 3 (enter 2 or 3): ";
    cin >> task;
    
    string input;
    cout << "Enter file name to read from: ";
    cin >> input;
    
    ifstream inFile(input);
    // read input
    if (inFile.is_open()) {
        int n;
        int target;
        inFile >> n;
        
        if (task == 2)
            inFile >> target;

        int *input = new int[n];
        
        int i = 0;
        while (inFile >> input[i])
            i++;

        if (task == 2)
            cout << "\nanswer = " << getPairSumCount(input, n, target) << endl;
        else if (task == 3)
            cout << "\nanswer = " << getMostCommonTarget(input, n) << endl;
        else
            cout << "Invalid task '" << task << "' Please try again." << endl;
        
        delete [] input;
    } else {
        cout << "Error opening file..." << endl;
    }

    return 0;
}

// Counts the number of pairs that add up to target
// O(nlogn) time | O(1) space
int getPairSumCount(int arr[], int n, int target) {
    sort(arr, arr + n); // O(nlogn) time

    int numPairs = 0; // number of pairs that add up to target
    int left = 0, right = n - 1; // left and right indexes

    // start left and right indexes at the oustide (both ends of the sorted array), and move them inside towards each other
    // increment numPairs whenever a correct pair is found
    while (left < right) { // O(n) time
        int sum = arr[left] + arr[right]; // current sum

        if (sum < target) // sum is too small -> increase left index to increase sum
            left++;
        else if (sum > target) // sum is too large -> decrease right index to decrease sum
            right--;
        else { // sum equals target
            int leftCount = 1, rightCount = 1; // number of duplicates on left and right side

            while (left < right && arr[left + 1] == arr[left]) { // count duplicates on left side
                leftCount++;
                left++;
            }
            left++;

            while (left < right && arr[right - 1] == arr[right]) { // count duplicates on right side
                rightCount++;
                right--;
            }
            right--;

            numPairs += leftCount * rightCount; // add number of correct pairs
        }
    }

    return numPairs;
}

// Finds the most common target among all pairs of numbers
// O(n^2*logn) time | O(n^2) space
int getMostCommonTarget(int arr[], int n) {
    vector<int> sums; // O(n^2) space

    // store all possible sums - O(n^2) time | O(n^2) space
    int i = 0;
    while (i < n) {
        int j = i + 1;
        while (j < n) {
            int currentSum = arr[i] + arr[j];
            sums.push_back(currentSum);

            while (j < (n - 1) && arr[j + 1] == arr[j]) // skip duplicates
                j++;
            j++;
        }

        while (i < (n - 1) && arr[i + 1] == arr[i]) // skip duplicates
            i++;
        i++;
    }

    int mostCommonTarget;
    int maxCount = 0;
    // O(n^2*logn) time | O(1) space
    for (int i = 0; i<sums.size(); i++) { // O(n) time | O(1) space
        int currentSum = sums[i];
        int currentCount = getPairSumCount(arr, n, currentSum); // O(nlogn) time | O(1) space

        if (currentCount >= maxCount) {
            if (currentCount == maxCount) {
                mostCommonTarget = min(currentSum, mostCommonTarget);
            } else {
                mostCommonTarget = currentSum;
                maxCount = currentCount;
            }
        }
    }

    return mostCommonTarget;
}