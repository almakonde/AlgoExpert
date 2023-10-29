//Two Number Sum
//Write a function that takes in a non-empty array of distinct integers and an integer representing 
//a target sum. If any of two numbers in the input array sum up to the target sum, the function should return them in an array
//in any order
//note that the target sum has to be obtained by summing two different integers in the array
//you can't add a single integer to itself in order to obtain the target sum
//you can assume that there will be at most one pair of numbers summing up to the target sum

import java.util.*;
import java.util.Scanner;


class solutionOne {
    public static int[] twoNumberSum(int[] array, int targetSum) {
        for (int i = 0; i < array.length - 1; i ++) {
            int firstNum = array[i];
            for (int j = i +1; j < array.length; j ++) {
                int secondNum = array[j];
                if(firstNum + secondNum == targetSum) {
                    return new int[] {firstNum, secondNum};
                }
            }
        }
        //empty array if no answer
        return new int[0];



    }

    public static void main(String[] args)
    {
        Scanner value = new Scanner(System.in);
        System.out.println("Enter a targetSum number, please");
        int targetSum = value.nextInt();
        System.out.printf("Entered targetSum value is: %d \n", targetSum);
        value.close();

        int[] array = new int[] { 3, 5, -4, 8, 11, 1, -1, 6};
        System.out.printf("Array's element for search: \n");
        for (int i : array) {

            System.out.printf("%d ", i); 

        }
        int[] result = twoNumberSum(array, targetSum);

        if(result.length == 2) {
            System.out.printf("Numbers found: %d and %d%n", result[0], result[1]);
        }
        else {
            System.out.println("No numbers found");
        }

    }
}