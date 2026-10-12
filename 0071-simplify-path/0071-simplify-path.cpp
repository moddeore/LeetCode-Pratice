class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        string dir = "";

        for (int i = 0; i <= path.size(); i++) {
            if (i == path.size() || path[i] == '/') {
                if (dir == "..") {
                    if (!st.empty()) {
                        st.pop_back();
                    }
                }
                else if (dir != "" && dir != ".") {
                    st.push_back(dir);
                }

                dir = "";
            }
            else {
                dir += path[i];
            }
        }

        string result = "";

        for (string folder : st) {
            result += "/" + folder;
        }

        if (result == "") {
            return "/";
        }

        return result;
    }
};