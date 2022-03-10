#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int twoSumCount(int[], int, int);
int mostCommonTarget(int[], int);

int main() {
  ifstream inFile("input-2.1.txt");
  int n;
  int target;
  inFile >> n;
  inFile >> target;
  int input[n];

  int i = 0;
  while (inFile >> input[i])
    i++;

  cout << mostCommonTarget(input, n) << endl;

  return 0;
}

// Counts the number of pairs that add up to target
// O(nlogn) time | O(1) space
int twoSumCount(int arr[], int n, int target) {
    sort(arr, arr + n); // O(nlogn) time

    int numPairs = 0;
    int left = 0, right = n - 1;
    while (left < right) { // O(n) time
        int sum = arr[left] + arr[right];

        if (sum < target) {
            while (left < right && arr[left + 1] == arr[left]) // skip duplicates
                left++;
            left++;
        }
        else if (sum > target) {
            while (left < right && arr[right - 1] == arr[right]) // skip duplicates
                right--;
            right--;
        }
        else { // sum equals target
            int leftCount = 1, rightCount = 1;

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

            numPairs += leftCount * rightCount;
        }
    }

    return numPairs;
}

// Finds the most common target among all pairs of numbers
// O(n^2*logn) time | O(n^2) space
int mostCommonTarget(int arr[], int n) {
    vector<int> sums; // O(n^2) space
    int idx = 0;

    // store all possible sums - O(n^2) time | O(n^2) space
    int i = 0;
    while (i < n) {
        int j = i + 1;
        while (j < n) {
            int currentSum = arr[i] + arr[j];

            while (arr[j + 1] == arr[j]) // move past duplicates
                j++;
            j++;
        }

        while (arr[i + 1] == arr[i]) // move past duplicates
            i++;
        i++;
    }

    int target;
    int maxCount = 0;
    // O(n^2*logn) time | O(1) space
    for (int i = 0; i<sums.size(); i++) { // O(n) time | O(1) space
        int currentSum = sums[i];
        int currentCount = twoSumCount(arr, n, currentSum); // O(nlogn) time | O(1) space

        if (currentCount >= maxCount) {
            if (currentCount == maxCount) {
                target = min(currentSum, target);
            } else {
                target = currentSum;
                maxCount = currentCount;
            }
        }
    }

    return target;
}