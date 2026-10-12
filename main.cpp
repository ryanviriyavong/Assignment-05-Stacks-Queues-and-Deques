/*
 * ============================================================================
 * Academic Integrity & AI Use Declaration
 * Course: CS 210 - Data Structures / Algorithms
 * Assignment: Assignment 05 - Stacks, Queues, and Deques
 * File Name: Viriyavong_Ryan_Assignment05.cpp
 * Author: Ryan Viriyavong
 * Date: 10/11/2026
 * 
 * AI Tool Used: Gemini
 * Nature of AI Assistance:
 *    - Assisted with implementing array-based and linked-list representations for stacks, queues, and deques in C++17.
 *    - Helped structure the custom master class design and operation demonstrations.
 * 
 * ============================================================================
 */

#include <vector>
#include <stdexcept>
#include <iostream>

class mystructures {
public:
    // array stack
    class astack {
    private:
        std::vector<int> v;
    public:
        void push(int x) { v.push_back(x); }
        void pop() {
            if (v.empty()) throw std::underflow_error("empty stack");
            v.pop_back();
        }
        int peek() const {
            if (v.empty()) throw std::underflow_error("empty stack");
            return v.back();
        }
        bool empty() const { return v.empty(); }
        size_t size() const { return v.size(); }
    };

    // linked stack
    class lstack {
    private:
        struct node {
            int data;
            node* next;
            node(int val) : data(val), next(nullptr) {}
        };
        node* top_node = nullptr;
        size_t sz = 0;
    public:
        ~lstack() { while(!empty()) pop(); }
        void push(int x) {
            node* n = new node(x);
            n->next = top_node;
            top_node = n;
            sz++;
        }
        void pop() {
            if (empty()) throw std::underflow_error("empty stack");
            node* temp = top_node;
            top_node = top_node->next;
            delete temp;
            sz--;
        }
        int peek() const {
            if (empty()) throw std::underflow_error("empty stack");
            return top_node->data;
        }
        bool empty() const { return top_node == nullptr; }
        size_t size() const { return sz; }
    };

    // array queue
    class aqueue {
    private:
        std::vector<int> v;
        size_t head = 0, tail = 0, count = 0, cap = 4;
        void grow() {
            std::vector<int> nv(cap * 2);
            for(size_t i = 0; i < count; ++i) nv[i] = v[(head + i) % cap];
            v = std::move(nv);
            head = 0; tail = count; cap *= 2;
        }
    public:
        aqueue() { v.resize(cap); }
        void enqueue(int x) {
            if (count == cap) grow();
            v[tail] = x;
            tail = (tail + 1) % cap;
            count++;
        }
        void dequeue() {
            if (empty()) throw std::underflow_error("empty queue");
            head = (head + 1) % cap;
            count--;
        }
        int front() const {
            if (empty()) throw std::underflow_error("empty queue");
            return v[head];
        }
        bool empty() const { return count == 0; }
        size_t size() const { return count; }
    };

    // linked queue
    class lqueue {
    private:
        struct node {
            int data;
            node* next;
            node(int val) : data(val), next(nullptr) {}
        };
        node* head = nullptr;
        node* tail = nullptr;
        size_t sz = 0;
    public:
        ~lqueue() { while(!empty()) dequeue(); }
        void enqueue(int x) {
            node* n = new node(x);
            if (empty()) head = tail = n;
            else { tail->next = n; tail = n; }
            sz++;
        }
        void dequeue() {
            if (empty()) throw std::underflow_error("empty queue");
            node* temp = head;
            head = head->next;
            if (!head) tail = nullptr;
            delete temp;
            sz--;
        }
        int front() const {
            if (empty()) throw std::underflow_error("empty queue");
            return head->data;
        }
        bool empty() const { return head == nullptr; }
        size_t size() const { return sz; }
    };

    // array deque
    class adeque {
    private:
        std::vector<int> v;
        size_t head = 0, tail = 0, count = 0, cap = 4;
        void grow() {
            std::vector<int> nv(cap * 2);
            for(size_t i = 0; i < count; ++i) nv[i] = v[(head + i) % cap];
            v = std::move(nv);
            head = 0; tail = count; cap *= 2;
        }
    public:
        adeque() { v.resize(cap); }
        void push_back(int x) {
            if (count == cap) grow();
            v[tail] = x;
            tail = (tail + 1) % cap;
            count++;
        }
        void push_front(int x) {
            if (count == cap) grow();
            head = (head == 0) ? cap - 1 : head - 1;
            v[head] = x;
            count++;
        }
        void pop_back() {
            if (empty()) throw std::underflow_error("empty deque");
            tail = (tail == 0) ? cap - 1 : tail - 1;
            count--;
        }
        void pop_front() {
            if (empty()) throw std::underflow_error("empty deque");
            head = (head + 1) % cap;
            count--;
        }
        int get_front() const {
            if (empty()) throw std::underflow_error("empty deque");
            return v[head];
        }
        int get_back() const {
            if (empty()) throw std::underflow_error("empty deque");
            size_t idx = (tail == 0) ? cap - 1 : tail - 1;
            return v[idx];
        }
        bool empty() const { return count == 0; }
        size_t size() const { return count; }
    };

    // linked deque
    class ldeque {
    private:
        struct node {
            int data;
            node* prev;
            node* next;
            node(int val) : data(val), prev(nullptr), next(nullptr) {}
        };
        node* head = nullptr;
        node* tail = nullptr;
        size_t sz = 0;
    public:
        ~ldeque() { while(!empty()) pop_front(); }
        void push_front(int x) {
            node* n = new node(x);
            if (empty()) head = tail = n;
            else { n->next = head; head->prev = n; head = n; }
            sz++;
        }
        void push_back(int x) {
            node* n = new node(x);
            if (empty()) head = tail = n;
            else { tail->next = n; n->prev = tail; tail = n; }
            sz++;
        }
        void pop_front() {
            if (empty()) throw std::underflow_error("empty deque");
            node* temp = head;
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
            delete temp;
            sz--;
        }
        void pop_back() {
            if (empty()) throw std::underflow_error("empty deque");
            node* temp = tail;
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            else head = nullptr;
            delete temp;
            sz--;
        }
        int get_front() const {
            if (empty()) throw std::underflow_error("empty deque");
            return head->data;
        }
        int get_back() const {
            if (empty()) throw std::underflow_error("empty deque");
            return tail->data;
        }
        bool empty() const { return head == nullptr; }
        size_t size() const { return sz; }
    };

    // testing everything out
    static void run() {
        std::cout << "running my tests...\n";

        // test empty handling error catch
        try {
            astack s;
            s.pop();
        } catch(const std::exception& e) {
            std::cout << "caught empty error fine: " << e.what() << "\n";
        }

        // array stack demo with 10+ ops
        astack s1;
        for(int i = 0; i < 12; ++i) s1.push(i);
        s1.pop(); s1.pop();
        std::cout << "astack size after ops: " << s1.size() << "\n";

        // linked stack demo with 10+ ops
        lstack s2;
        for(int i = 0; i < 15; ++i) s2.push(i);
        s2.pop();
        std::cout << "lstack size after ops: " << s2.size() << "\n";

        // array queue demo with 10+ ops
        aqueue q1;
        for(int i = 0; i < 12; ++i) q1.enqueue(i);
        q1.dequeue(); q1.dequeue();
        std::cout << "aqueue size after ops: " << q1.size() << "\n";

        // linked queue demo with 10+ ops
        lqueue q2;
        for(int i = 0; i < 11; ++i) q2.enqueue(i);
        q2.dequeue();
        std::cout << "lqueue size after ops: " << q2.size() << "\n";

        // array deque demo with 10+ ops
        adeque d1;
        for(int i = 0; i < 6; ++i) d1.push_back(i);
        for(int i = 6; i < 12; ++i) d1.push_front(i);
        d1.pop_back(); d1.pop_front();
        std::cout << "adeque size after ops: " << d1.size() << "\n";

        // linked deque demo with 10+ ops
        ldeque d2;
        for(int i = 0; i < 10; ++i) d2.push_back(i);
        d2.pop_front(); d2.pop_back();
        std::cout << "ldeque size after ops: " << d2.size() << "\n";
        
        std::cout << "\nnotes on o(1) vs o(n):\n";
        std::cout << "for all the array ones (astack, aqueue, adeque), pushing or enqueuing is o(1) amortized, but once they run out of space they grow and copy everything over which turns into o(n). for the linked list ones (lstack, lqueue, ldeque), adding and removing is always strict o(1) because we just play with pointers and never have to resize or shift elements around.\n";
    }
};

int main() {
    mystructures::run();
    return 0;
}