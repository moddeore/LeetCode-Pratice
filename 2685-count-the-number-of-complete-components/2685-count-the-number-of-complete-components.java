class Solution {
    public int countCompleteComponents(int n, int[][] edges) {
        // Build adjacency list
        List<Integer>[] graph = new ArrayList[n];

        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }

        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];

            graph[u].add(v);
            graph[v].add(u);
        }

        boolean[] visited = new boolean[n];
        int answer = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int vertices = 0;
                int edgeCount = 0;

                // DFS
                Stack<Integer> stack = new Stack<>();
                stack.push(i);
                visited[i] = true;

                while (!stack.isEmpty()) {
                    int node = stack.pop();
                    vertices++;

                    // Count edges
                    edgeCount += graph[node].size();

                    for (int next : graph[node]) {
                        if (!visited[next]) {
                            visited[next] = true;
                            stack.push(next);
                        }
                    }
                }

                // Every edge is counted twice
                edgeCount /= 2;

                // Check if component is complete
                int requiredEdges = vertices * (vertices - 1) / 2;

                if (edgeCount == requiredEdges) {
                    answer++;
                }
            }
        }

        return answer;
    }
}