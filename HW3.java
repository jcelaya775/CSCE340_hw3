import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

public class HW3 {
    public static void main(String[] args) {
        Scanner s = null;
        try {
            s = new Scanner(new File("input-2.4.txt"));
        } catch (IOException ioe) {
            System.out.println("Error: " + ioe);
        }

        int n = s.nextInt();
        int target = s.nextInt();
        int[] input = new int[n];

        int i = 0;
        while (s.hasNextInt()) {
            input[i] = s.nextInt();
            i++;
        }

        s.close();

        System.out.println(twoSumCount(input, target));
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