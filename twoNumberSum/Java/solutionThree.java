import java.util.*;

class solutionThree {
    public static int[] twoNumberSum(int[] array, int targetSum) {
        Arrays.sort(array);
        int left = 0;
        int right = array.length;
        int currentSum = 0;

        while(left < right) {
            currentSum = array[left] + array[right - 1];
            if(currentSum == targetSum) {
                return new int[] {array[left], array[right - 1]};
            }
            else if(currentSum < targetSum) {
                left ++;
            }
            else if(currentSum > targetSum) {
                right --;
            }
        }
        return new int[0];
    }

    public static void printArray(int[] array) {
        for(int i : array) {
            System.out.printf("%d ", i);

        }
         System.out.println();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a target Sum value, please: ");
        int targetSum = scanner.nextInt();
        scanner.close();

        System.out.printf("Entered target Sum value is: %d%n", targetSum);

        int[] array = {3, 5, -4, 8, 11, 1, -1, 6};

        printArray(array);

        int[] result = twoNumberSum(array,  targetSum);

        if(result.length != 0) {
            System.out.printf("Numbers found: %d and %d %n", result[0], result[1]);
        }
        else {
            System.out.println("No such numbers found.");
        }
    }
}