#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int twoSumCount(int[], int, int);

int main() {
  ifstream inFile("input-2.3.txt");
  int n;
  int target;
  inFile >> n;
  inFile >> target;
  int input[n];

  int i = 0;
  while (inFile >> input[i])
    i++;

  cout << twoSumCount(input, n, target) << endl;

  return 0;
}

// O(nlogn) time | O(1) space
int twoSumCount(int arr[], int n, int target) {
    sort(arr, arr + n); // O(nlogn) time

    int numPairs = 0;
    int left = 0, right = n - 1;
    while (left < right) { // O(n) time
        int sum = arr[left] + arr[right];

        if (sum < target)
            left++;
        else if (sum > target)
            right--;
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