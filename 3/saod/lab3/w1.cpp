#include <climits>
#include <cmath>
#include <iostream>

struct FibHeapNode {
    int key;
    char* value;
    int degree;
    bool mark;
    FibHeapNode* parent;
    FibHeapNode* child;
    FibHeapNode* left;
    FibHeapNode* right;

    FibHeapNode(int k, char* val)
        : key(k),
          value(val),
          degree(0),
          mark(false),
          parent(nullptr),
          child(nullptr),
          left(this),
          right(this) {}
};

struct FibHeap {
    FibHeapNode* min;
    int nnodes;

    FibHeap() : min(nullptr), nnodes(0) {}

    FibHeapNode* fibheap_insert(int key, char* value) {
        FibHeapNode* node = new FibHeapNode(key, value);
        if (min == nullptr) {
            min = node;
        } else {
            FibHeapNode* oldMin = min;
            node->left = oldMin;
            node->right = oldMin->right;
            oldMin->right = node;
            node->right->left = node;
            if (key < min->key) {
                min = node;
            }
        }
        nnodes++;
        return node;
    }

    FibHeapNode* fibheap_min() { return min; }

    void fibheap_link(FibHeapNode* y, FibHeapNode* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->left = y;
            y->right = y;
        } else {
            FibHeapNode* firstChild = x->child;
            FibHeapNode* lastChild = firstChild->left;
            firstChild->left = y;
            lastChild->right = y;
            y->left = lastChild;
            y->right = firstChild;
        }
        x->degree++;
        y->mark = false;
    }

    void fibheap_consolidate() {
        int maxDegree = static_cast<int>(log2(nnodes)) + 1;
        FibHeapNode* A[maxDegree];
        for (int i = 0; i < maxDegree; i++) {
            A[i] = nullptr;
        }

        FibHeapNode* x = min;
        int numRoots = 0;
        if (x != nullptr) {
            numRoots++;
            x = x->right;
            while (x != min) {
                numRoots++;
                x = x->right;
            }
        }

        while (numRoots > 0) {
            int d = x->degree;
            FibHeapNode* next = x->right;
            while (A[d] != nullptr) {
                FibHeapNode* y = A[d];
                if (x->key > y->key) {
                    FibHeapNode* temp = x;
                    x = y;
                    y = temp;
                }
                fibheap_link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
            x = next;
            numRoots--;
        }

        min = nullptr;
        for (int i = 0; i < maxDegree; i++) {
            if (A[i] != nullptr) {
                if (min == nullptr || A[i]->key < min->key) {
                    min = A[i];
                }
            }
        }
    }

  FibHeapNode* fibheap_delete_min() {
    FibHeapNode* z = min;
    if (z != nullptr) {
        FibHeapNode* child = z->child;
        if (child != nullptr) {
            FibHeapNode* currentChild = child;
            do {
                FibHeapNode* nextChild = currentChild->right;
            
                currentChild->parent = nullptr;
                currentChild->left = min;
                currentChild->right = min->right;
                min->right->left = currentChild;
                min->right = currentChild;
                currentChild = nextChild;
            } while (currentChild != child);
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            min = nullptr;
        } else {
            min = z->right;
            fibheap_consolidate(); 
        }
        nnodes--;
    }
    return z;
}


    void fibheap_decrease_key(FibHeapNode* x, int newkey) {
        if (newkey > x->key) {
            return;
        }
        x->key = newkey;
        FibHeapNode* y = x->parent;
        if (y != nullptr && x->key < y->key) {
            fibheap_cut(x, y);
            fibheap_cascading_cut(y);
        }
        if (x->key < min->key) {
            min = x;
        }
    }

    void fibheap_cut(FibHeapNode* x, FibHeapNode* y) {
        if (x == x->right) {
            y->child = nullptr;
        } else {
            if (y->child == x) {
                y->child = x->right;
            }
            x->left->right = x->right;
            x->right->left = x->left;
        }
        y->degree--;
        x->left = min;
        x->right = min->right;
        min->right->left = x;
        min->right = x;
        x->parent = nullptr;
        x->mark = false;
    }

    void fibheap_cascading_cut(FibHeapNode* y) {
        FibHeapNode* z = y->parent;
        if (z != nullptr) {
            if (!y->mark) {
                y->mark = true;
            } else {
                fibheap_cut(y, z);
                fibheap_cascading_cut(z);
            }
        }
    }

    void fibheap_delete(FibHeapNode* x) {
        fibheap_decrease_key(x, INT_MIN);
        fibheap_delete_min();
    }
};

FibHeapNode* findNodeByKey(FibHeap& heap, int key) {
    if (heap.min == nullptr) return nullptr;

    FibHeapNode* startNode = heap.min;
    FibHeapNode* currentNode = startNode;

    do {
        if (currentNode->key == key) {
            return currentNode;
        }
        currentNode = currentNode->right;
    } while (currentNode != startNode);

    return nullptr;
}

FibHeap* fibheap_union(FibHeap* heap1, FibHeap* heap2) {
    FibHeap* newHeap = new FibHeap();

    if (heap1->min == nullptr) {
        return heap2;
    }
    if (heap2->min == nullptr) {
        return heap1;
    }

    newHeap->min = heap1->min;
    FibHeapNode* heap1MinRight = heap1->min->right;
    FibHeapNode* heap2MinLeft = heap2->min->left;

    heap1->min->right = heap2->min;
    heap2->min->left = heap1->min;
    heap1MinRight->left = heap2MinLeft;
    heap2MinLeft->right = heap1MinRight;

    if (heap2->min->key < heap1->min->key) {
        newHeap->min = heap2->min;
    }

    newHeap->nnodes = heap1->nnodes + heap2->nnodes;

    return newHeap;
}

int main() {
    FibHeap heap1, heap2;

    heap1.fibheap_insert(10, "Heap1_Node1");
    heap1.fibheap_insert(3, "Heap1_Node2");
    heap1.fibheap_insert(15, "Heap1_Node3");

    heap2.fibheap_insert(7, "Heap2_Node1");
    heap2.fibheap_insert(1, "Heap2_Node2");
    heap2.fibheap_insert(20, "Heap2_Node3");

    std::cout << "Minimum in heap1: " << heap1.fibheap_min()->key << std::endl;
    std::cout << "Minimum in heap2: " << heap2.fibheap_min()->key << std::endl;

    FibHeap* unionHeap = fibheap_union(&heap1, &heap2);

    std::cout << "Minimum in union heap: " << unionHeap->fibheap_min()->key << std::endl;

    FibHeapNode* deletedNode = unionHeap->fibheap_delete_min();
    if (deletedNode != nullptr) {
        std::cout << "Deleted minimum node: Key = " << deletedNode->key << ", Value = " << deletedNode->value << std::endl;
    }

    FibHeapNode* minNode = unionHeap->fibheap_min();
    if (minNode != nullptr) {
        std::cout << "Minimum node after deletion: Key = " << minNode->key << ", Value = " << minNode->value << std::endl;
    }

    return 0;
}
