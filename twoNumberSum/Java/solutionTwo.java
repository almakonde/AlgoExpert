import java.util.*;

class solutionTwo {
    public static int[] twoNumberSum(int[] array, int targetSum) {
        Set<Integer> nums = new HashSet<>();
        for(int num: array) {
            int potentialMatch = targetSum - num;
            if(nums.contains(potentialMatch)) {
                return new int[] {num, potentialMatch};
            }
            else {
                nums.add(num);
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