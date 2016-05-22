#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

struct Node {
    Node *next;
    Node *prev;
    int value;
    int key;

    Node(Node *p, Node *n, int k, int val) : prev(p), next(n), key(k), value(val) { };

    Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val) { };
};

class Cache {

protected:
    map<int, Node *> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node *tail; // double linked list tail pointer
    Node *head; // double linked list head pointer
    virtual void set(int &, int &) = 0; //set function
    virtual int get(int &) = 0; //get function

};

class LRUCache : public Cache {
public:

    LRUCache(int& capacity) { cp = capacity; }

    LRUCache(int&& capacity) { cp = capacity; }

    void set(int& k, int &v) {
        Node* node;
        map<int, Node*>::iterator it = mp.find(k);
        if (it != mp.end()) {
            remove(k);
        }
        else {
            remove_last();
        }
        node = new Node(NULL, NULL, k, v);
        mp[k] = node;
        push(node);
    }

    int get(int &k) {
        map<int, Node *>::iterator it = mp.find(k);
        if (it != mp.end())
            return mp[k]->value;
        else
            return -1;
    }

private:

    void remove(int& k) {
        if (mp[k]->prev)
            mp[k]->prev->next = mp[k]->next;
        if (mp[k]->next)
            mp[k]->next->prev = mp[k]->prev;
        mp[k]->next = NULL;
        mp[k]->prev = NULL;
        mp.erase(k);
        ++cp;
    }

    void push(Node *node) {
        if (cp <= 0)
            return;
        if (head)
            node->next = head;
        head = node;
        --cp;
    }


    void remove_last() {
        if (tail) {
            tail = tail->prev;
            tail->next = NULL;
        }
    }
};

int main() {
    string line;
    ifstream myfile("/Users/samistart/projects/LRUCache/data.txt");
    if (myfile.is_open()) {
        int n, capacity, i;
        myfile >> n >> capacity;
        LRUCache l(capacity);
        for (i = 0; i < n; i++) {
            string command;
            myfile >> command;
            if (command == "get") {
                cout << "GET!" << endl;
                int key;
                myfile >> key;
                cout << l.get(key) << endl;
            }
            else if (command == "set") {
                cout << "SET!" << endl;
                int key, value;
                myfile >> key >> value;
                l.set(key, value);
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}



