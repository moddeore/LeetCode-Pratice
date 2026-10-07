class Solution {
public:

    bool isValid(string s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(') {
                balance++;
            }
            else if (c == ')') {
                balance--;

                // More ')' than '('
                if (balance < 0)
                    return false;
            }
        }

        // All '(' must be matched
        return balance == 0;
    }

    vector<string> removeInvalidParentheses(string s) {

        vector<string> ans;

        // BFS queue
        queue<string> q;

        // Avoid duplicate strings
        unordered_set<string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {

            string current = q.front();
            q.pop();

            // If current string is valid,
            // this is the minimum-removal level.
            if (isValid(current)) {
                ans.push_back(current);
                found = true;
            }

            // If we already found valid strings,
            // don't generate strings with more removals.
            if (found)
                continue;

            // Remove one parenthesis at every position
            for (int i = 0; i < current.length(); i++) {

                // We only remove parentheses.
                if (current[i] != '(' && current[i] != ')')
                    continue;

                string next = current.substr(0, i) +
                              current.substr(i + 1);

                // If this string is not visited
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};