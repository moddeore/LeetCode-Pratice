
import java.util.*;

class Solution {
    public int assignEdgeWeights(int[][] edges) {
        int n = edges.length + 1;
        List<Integer>[] graph = new ArrayList[n + 1];

        for (int i = 1; i <= n; i++) {
            graph[i] = new ArrayList<>();
        }

        for (int[] edge : edges) {
            graph[edge[0]].add(edge[1]);
            graph[edge[1]].add(edge[0]);
        }

        int[] depth = new int[n + 1];
        Arrays.fill(depth, -1);

        Queue<Integer> queue = new LinkedList<>();
        queue.offer(1);
        depth[1] = 0;

        int maxDepth = 0;

        while (!queue.isEmpty()) {
            int node = queue.poll();

            for (int next : graph[node]) {
                if (depth[next] == -1) {
                    depth[next] = depth[node] + 1;
                    maxDepth = Math.max(maxDepth, depth[next]);
                    queue.offer(next);
                }
            }
        }

        long mod = 1_000_000_007L;
        long ans = 1;

        for (int i = 1; i < maxDepth; i++) {
            ans = (ans * 2) % mod;
        }

        return (int) ans;
    }
}
