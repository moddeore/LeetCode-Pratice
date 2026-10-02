
class Solution {
public:
    vector<string> result;

    void generate(string s, int open, int close, int n) {
        // If we used all n pairs
        if (s.length() == 2 * n) {
            result.push_back(s);
            return;
        }

        // We can add '(' if we still have some left
        if (open < n) {
            generate(s + "(", open + 1, close, n);
        }

        // We can add ')' only if there is an unmatched '('
        if (close < open) {
            generate(s + ")", open, close + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        generate("", 0, 0, n);
        return result;
    }
};

