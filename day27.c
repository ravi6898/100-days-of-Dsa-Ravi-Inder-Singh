class Solution {
public:
    void removeLoop(Node* head) {
        if (!head || !head->next) return;
        
        Node* slow = head;
        Node* fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        
        if (slow != fast) return;
        
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        Node* start = slow;
        Node* temp = start;
        while (temp->next != start) {
            temp = temp->next;
        }
        temp->next = nullptr;
    }
};