// Link to question: https://www.hackerrank.com/contests/cmpe250-codingparty-v1/challenges/merge-two-sorted-linked-lists
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    SinglyLinkedList newList;
    while (head1 && head2) {
        int data1 = head1->data;
        int data2 = head2->data;
        if (data1 < data2) {
            newList.insert_node(data1);
            head1 = head1->next;
        } else {
            newList.insert_node(data2);
            head2 = head2->next;
        }
    }

    while(head1) {
        newList.insert_node(head1->data);
        head1 = head1->next;
    }
    
    while(head2) {
        newList.insert_node(head2->data);
        head2 = head2->next;
    }

    return newList.head;
}