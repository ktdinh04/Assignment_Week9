#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

struct CircularLinkedList {
    Node* head;

    CircularLinkedList() {
        head = nullptr;
    }

    void append(int data) {
        Node* new_node = new Node(data);
        if (!head) {
            head = new_node;
            new_node->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->next = head;
        }
    }

    int get_winner(int M) {
        Node* current = head;
        while (current->next != current) { // Only one person left in the circle
            // Move M-1 steps
            for (int i = 1; i < M; i++) {
                current = current->next;
            }
            // Remove the node at the current position
            cout << "Removing player " << current->next->data << endl;
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            current = current->next; // Move to the next player
        }
        int winner = current->data;
        delete current;
        return winner; // Last person remaining is the winner
    }
};

int josephus_winner(int N, int M) {
    CircularLinkedList circle;
    for (int i = 1; i <= N; i++) {
        circle.append(i);
    }
    return circle.get_winner(M);
}

int main() {
    int N, M;
    cout << "Enter number of players (N): ";
    cin >> N;
    cout << "Enter step count (M): ";
    cin >> M;
    int winner = josephus_winner(N, M);
    cout << "The winner is player " << winner << endl;
    return 0;
}
