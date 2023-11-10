#include <iostream> 
#include <queue>

using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::endl;

class GameObject {
private:
    int mID;

public:
    GameObject() = default;
    GameObject(int id) : mID(id) {}

    inline int ID() { return mID; }
};

template <typename T>
struct Node
{
    T mObject;
    unique_ptr<Node> mLeft;
    unique_ptr<Node> mRight;

    Node(T& object) : mObject(object) {}
};

template <typename T>
class BinaryTree final {
private:
  unique_ptr<Node<T>> mRoot;
  int mDepth;

public:
    BinaryTree() : mDepth(0) {}

    void Add(const T& object) {
        Add(mRoot, object);
    }

    bool Search(const T& object) {
        return Search(mRoot, object);
    }

/*
    // DFS
    void Preorder() { // PLR이라 공간분할에 사용

    }
    void Inorder() { // LPR

    }
    void Postorder() { // LRP

    }
    // BFS
    void Levelorder(Node<T>* node) {
        std::queue<Node<T>*> q;

        if (node == nullptr) return;
        cout << node->mObject << endl;
        if (node->mLeft) q.push(node->mLeft);
        if (node->mRight) q.push(node->mRight);
        if (!q.empty()) {
            Node<T>* node = q.front(); // 제일 처음 것 (빼는 것x)
            q.pop();
            Levelorder(node);
        }
    }
*/

private:
    void Add(Node<T>*& node, T& object) {
        if (node == nullptr) {
            unique_ptr<Node<T>> node = make_unique<Node<T>>(object);
        }
        else if (object < node->mObject) {
            Add(node->mLeft, object);
        }
        else {
            Add(node->mRight, object);  
        }
    }

    bool Search(Node<T>*& node, T& object) {
        if (node == nullptr) {
            return false;                   // 끝내 못찾은 경우
        } else if (object == node->mObject) {
            return true;                    // 찾은 경우
        } else if (object < node->mObject) {
            Search(node->mLeft, object);
        } else {
            Search(node->mRight, object);
        }
    }

    void SetChild(Node<T>*& parent, Node<T>*& child) {
        if (parent->mObject > child->mObject) {
            parent->mLeft = child;
        } else {
            parent->mRight = child;
        }
    }
};