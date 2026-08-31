class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int prevCritical = -1;
        int minDistance = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            // Check local maximum or local minimum
            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {

                // First critical point
                if (first == -1) {
                    first = index;
                }

                // Distance from previous critical point
                if (prevCritical != -1) {
                    minDistance = min(minDistance, index - prevCritical);
                }

                prevCritical = index;
            }

            prev = curr;
            curr = next;
            index++;
        }

        // Fewer than 2 critical points
        if (first == -1 || first == prevCritical) {
            return {-1, -1};
        }

        // Distance between first and last critical points
        int maxDistance = prevCritical - first;

        return {minDistance, maxDistance};
    }
};