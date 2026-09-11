import java.util.*;

class Solution {
    public int[] arrayRankTransform(int[] arr) {
        int n = arr.length;
        
        // Copy and sort
        int[] sorted = arr.clone();
        Arrays.sort(sorted);
        
        // Assign ranks
        HashMap<Integer, Integer> rank = new HashMap<>();
        int r = 1;
        
        for (int num : sorted) {
            if (!rank.containsKey(num)) {
                rank.put(num, r);
                r++;
            }
        }
        
        // Replace elements with their rank
        for (int i = 0; i < n; i++) {
            arr[i] = rank.get(arr[i]);
        }
        
        return arr;
    }
}