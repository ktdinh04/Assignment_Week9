#include <iostream>
using namespace std;

// Định nghĩa cấu trúc Node để biểu diễn các hạng tử của đa thức
struct Node {
    int heso;    // Hệ số của hạng tử
    int bac;     // Bậc của hạng tử
    Node* next;  // Con trỏ trỏ tới hạng tử kế tiếp
};

// Hàm tạo node mới với hệ số và bậc cho trước (chỉ tạo nếu heso != 0)
Node* createNode(int heso, int bac) {
    if (heso == 0) return nullptr; // Không tạo node nếu hệ số bằng 0
    Node* newNode = new Node;
    newNode->heso = heso;
    newNode->bac = bac;
    newNode->next = nullptr;
    return newNode;
}

// Hàm thêm một hạng tử vào danh sách, duy trì thứ tự theo bậc giảm dần
void them_so_hang(Node** head, int heso, int bac) {
    if (heso == 0) return; // Bỏ qua nếu hệ số bằng 0

    Node* newNode = createNode(heso, bac); // Tạo hạng tử mới
    if (!newNode) return; // Kiểm tra nullptr từ createNode

    if (*head == nullptr || (*head)->bac < newNode->bac) {
        newNode->next = *head; // Đặt newNode ở đầu danh sách nếu bậc của nó lớn hơn
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != nullptr && current->next->bac > newNode->bac) {
            current = current->next;
        }
        if (current->bac == bac) {
            current->heso += heso;
            delete newNode; // Giải phóng node không cần thiết nếu cộng hệ số
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

// Hàm hiển thị đa thức
void Display(Node* head) {
    if (head == nullptr) {
        printf("Empty\n");
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        if (current->heso != 0) {
            if (current->bac != 0) {
                printf("%dx^%d", current->heso, current->bac);
            } else {
                printf("%d", current->heso);
            }
            if (current->next != nullptr && current->next->heso > 0) {
                printf(" + ");
            }
        }
        current = current->next;
    }
    printf("\n");
}

// Hàm tính tổng hai đa thức f(x) và g(x) tại chỗ
Node* Sum_of_funct(Node* f, Node* g) {
    Node* result = nullptr;
    while (f != nullptr || g != nullptr) {
        if (f && (!g || f->bac > g->bac)) {
            them_so_hang(&result, f->heso, f->bac);
            f = f->next;
        } else if (g && (!f || f->bac < g->bac)) {
            them_so_hang(&result, g->heso, g->bac);
            g = g->next;
        } else {
            int sum = f->heso + g->heso;
            if (sum != 0) { // Chỉ thêm nếu hệ số khác 0
                them_so_hang(&result, sum, f->bac);
            }
            f = f->next;
            g = g->next;
        }
    }
    return result;
}

// Hàm nhập đa thức từ người dùng
Node* input() {
    Node* head = nullptr;
    int n;
    printf("Nhap so so hang: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int heso, bac;
        printf("Nhap he so: ");
        scanf("%d", &heso);
        printf("Nhap bac: ");
        scanf("%d", &bac);
        them_so_hang(&head, heso, bac);
    }
    return head;
}

// Hàm giải phóng bộ nhớ cho danh sách
void freeList(Node* head) {
    Node* current;
    while (head != nullptr) {
        current = head;
        head = head->next;
        delete current;
    }
}

int main() {
    printf("Nhap da thuc f(x): \n");
    Node* f = input();
    printf("f(x) = ");
    Display(f);
    
    printf("Nhap da thuc g(x): \n");
    Node* g = input();
    printf("g(x) = ");
    Display(g);
    
    Node* sum = Sum_of_funct(f, g);
    printf("h(x) = f(x) + g(x) = ");
    Display(sum);
    
    freeList(f);
    freeList(g);
    freeList(sum);
    
    return 0;
}
