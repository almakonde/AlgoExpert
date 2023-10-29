import java.util.*;

class validateSubsequence {
    public static bool isValidSubsequence(List<Integer> array, List<Integer> sequence) {
        int arrIndx = 0;
        int seqIndx = 0;
        while(arrIndx < array.size() && seqIndx < sequence.size() ) {
            if (array.get(arrIndx).equals(sequence.get(seqIndx))) {
                seqIndx++;

            }
            arrIndx++;
        }
        return seqIndx == sequence.size();

    }

    
}