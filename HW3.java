import java.util.Arrays;

public class HW3 {
    public static void main(String[] args) {
        int[] x = { 2, 7, 2, 3, 1, 5, 6 };
        System.out.println(twoSumCount(x, 7));
    }

    // O(nlogn) time | O(1) space
    public static int twoSumCount(int[] arr, int target) {
        Arrays.sort(arr); // O(nlogn) time

        int numPairs = 0;
        int left = 0, right = arr.length - 1;
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
}