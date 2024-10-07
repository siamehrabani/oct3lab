// Mehrabani, Siavash
// CS136 - Lab5 Linked List

#include <iostream>
using namespace std;

// ---------------------------------------------------------
template <typename T>
class Node {
private:
    T data;
    Node* next;
public:
    Node(T val) : data(val), next(nullptr) {}
    T getData() const { return data; }
    void setData(T val) { data = val; }
    Node* getNext() const { return next; }
    void setNext(Node* node) { next = node; }
};
// ---------------------------------------------------------
template <typename T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList() : head(nullptr) {}

    void insertAtStart(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->setNext(head);
        head = newNode;
    }

    void insertAtEnd(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
    }

    void deleteByValue(T val) {
        if (head != nullptr) {
            if (head->getData() == val) {
                Node<T>* temp = head;
                head = head->getNext();
                delete temp;
            } else {
                Node<T>* current = head;
                while (current->getNext() != nullptr &&
                       current->getNext()->getData() != val) {
                    current = current->getNext();
                }
                if (current->getNext() != nullptr) {
                    Node<T>* temp = current->getNext();
                    current->setNext(current->getNext()->getNext());
                    delete temp;
                }
            }
        }
    }

    void print() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->getData() << " ";
            current = current->getNext();
        }
        cout << endl;
    }

    bool search(T val) {
        bool found = false;
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->getData() == val) {
                found = true;
                break;
            }
            current = current->getNext();
        }
        return found;
    }

    void mergeSortedLists(LinkedList& other) {
        Node<T>* dummy = new Node<T>(0);
        Node<T>* tail = dummy;
        Node<T>* current1 = head;
        Node<T>* current2 = other.head;

        while (current1 != nullptr && current2 != nullptr) {
            if (current1->getData() <= current2->getData()) {
                tail->setNext(current1);
                current1 = current1->getNext();
            } else {
                tail->setNext(current2);
                current2 = current2->getNext();
            }
            tail = tail->getNext();
        }

        if (current1 != nullptr) {
            tail->setNext(current1);
        } else if (current2 != nullptr) {
            tail->setNext(current2);
        }

        head = dummy->getNext();
        delete dummy;
        other.head = nullptr;
    }


    void splitInTwoHalves(LinkedList& firstHalf, LinkedList& secondHalf) {
        if (head == nullptr) {
            return; 
        }

        int count = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            count++;
            current = current->getNext();
        }

        int mid = count / 2;
        current = head;

        for (int i = 0; i < mid; ++i) {
            firstHalf.insertAtEnd(current->getData());
            current = current->getNext();
        }

        while (current != nullptr) {
            secondHalf.insertAtEnd(current->getData());
            current = current->getNext();
        }
    }
};

int main() {
    LinkedList<int> list1;
    list1.insertAtEnd(1);
    list1.insertAtEnd(3);
    list1.insertAtEnd(5);

    LinkedList<int> list2;
    list2.insertAtEnd(2);
    list2.insertAtEnd(4);
    list2.insertAtEnd(6);

    cout << "List 1: ";
    list1.print();
    cout << "List 2: ";
    list2.print();

    list1.mergeSortedLists(list2);
    cout << "Sorted Merged List: ";
    list1.print();

    LinkedList<int> firstHalf, secondHalf;
    list1.splitInTwoHalves(firstHalf, secondHalf);

    cout << "First Half: ";
    firstHalf.print();

    cout << "Second Half: ";
    secondHalf.print();

    return 0;
}