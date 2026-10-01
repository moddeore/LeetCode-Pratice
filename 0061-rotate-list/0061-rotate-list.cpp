class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL)
            return head;

        // Find length
        int n = 0;
        ListNode* temp = head;

        while (temp != NULL) {
            n++;
            temp = temp->next;
        }

        // Extra rotations are unnecessary
        k = k % n;

        while (k > 0) {
            ListNode* prev = NULL;
            temp = head;

            // Find last node
            while (temp->next != NULL) {
                prev = temp;
                temp = temp->next;
            }

            // Move last node to front
            prev->next = NULL;
            temp->next = head;
            head = temp;

            k--;
        }

        return head;
    }
};