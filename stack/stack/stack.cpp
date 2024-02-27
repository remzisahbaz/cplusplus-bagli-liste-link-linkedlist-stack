#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <windows.h> // Sleep() fonksiyonu için

// Yýðýt veri yapýsý
class Stack {
public:
    int* data;
    int size;
    int capacity;
    int count;
public:
    Stack() : size(0), count(0),capacity(10) {
        data = (int*)malloc(capacity * sizeof(int));
    }

    ~Stack() {
        free(data);
    }

    void push(int value) {
        if (size >= capacity) {
            capacity *= 2;
            int* newData = (int*)malloc(capacity * sizeof(int));
            memcpy(newData, data, size * sizeof(int)); // Mevcut veriyi yeni alana kopyalama
            free(data); // Eski veriyi serbest býrakma
            data = newData; // Yeni veri alanýný göster
        }
        data[size++] = value;
        count++;
    }

    void init(int s,int c) {
        count = 0;
        size = s;
        capacity = c;
        data = (int*)malloc(capacity * sizeof(int));
    }

    int pop() {
        if (size <= 0) {
            std::cerr << "Yigit bos!" << std::endl;
            return -1; // Varsayýlan hata deðeri, uygun deðer belirlenebilir.
        }
        return data[--size];
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isLastElementEven(int value) const {
            return value % 2 == 0;
    }
};

// Ýkili Arama Aðacý düðüm veri yapýsý
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Ýkili Arama Aðacý veri yapýsý
class BinarySearchTree {
private:
    Node* root;

    // Ýkili Arama Aðacý düðümlerini postorder gezisi ile silen yardýmcý fonksiyon
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        free(node);
    }

    // Ýkili Arama Aðacýna düðüm ekleme yardýmcý fonksiyonu
    Node* insertNode(Node* root, int value) {
        if (root == nullptr) {
            return new Node(value);
        }

        if (value < root->data) {
            root->left = insertNode(root->left, value);
        }
        else if (value > root->data) {
            root->right = insertNode(root->right, value);
        }

        return root;
    }

    // Ýkili Arama Aðacýnýn yüksekliðini hesaplayan yardýmcý fonksiyon
    int getHeight(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + max(getHeight(root->left), getHeight(root->right));
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        deleteTree(root);
    }

    // Ýkili Arama Aðacýna düðüm ekleme iþlevi
    void insert(int value) {
        root = insertNode(root, value);
    }

    // Ýkili Arama Aðacýndaki en yüksek yüksekliðe sahip düðümü seçen iþlev
    Node* getMaxHeightNode(Node* node1, Node* node2) {
        // Ýlk aðaçýn yüksekliði daha büyükse, ilk aðacý seç
        if (getHeight(node1) > getHeight(node2)) {
            return node1;
        }
        // Ýkinci aðacýn yüksekliði daha büyükse, ikinci aðacý seç
        else if (getHeight(node1) < getHeight(node2)) {
            return node2;
        }
        // Yükseklikler eþitse, düðümlerinin toplam deðeri daha büyük olaný seç
        else {
            int sum1 = sumNodeValues(node1);
            int sum2 = sumNodeValues(node2);
            return (sum1 >= sum2) ? node1 : node2;
        }
    }

    // Ýkili Arama Aðacýný postorder gezerek ASCII karakterlerini ekrana yazdýran iþlev
    void postorderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        postorderTraversal(root->left);
        postorderTraversal(root->right);
        std::cout << static_cast<char>(root->data);
    }

    // Ýkili Arama Aðacýnýn düðüm deðerlerinin toplamýný hesaplayan yardýmcý fonksiyon
    int sumNodeValues(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        return root->data + sumNodeValues(root->left) + sumNodeValues(root->right);
    }

    Node* getRoot() const {
        return root;
    }
};

BinarySearchTree processLine( const std::string & line) {

    int number;
   const  int MAX_STACKS = 5;
    Stack stacks[MAX_STACKS];
   // stacks = (Stack*)malloc(MAX_STACKS * sizeof(Stack));
    int stackCount = 0;
    int treesCount = 0;
    int treesCapacity = 5;
   // stacks[stackCount].init(0, 10);
    const  int bstCount = 5;
    BinarySearchTree trees[bstCount];
   
    BinarySearchTree bst[bstCount];
    BinarySearchTree result;
   
    int lineNo = 0;
 /*   std::string line;
    while (std::getline(file, line))
    {
        lineNo++;
        std::cout << lineNo<<". Satir Okundu" << std::endl << std::endl;
        stackCount++;
        if (stackCount >= MAX_STACKS) {
            MAX_STACKS++;
            stacks = (Stack*)realloc(stacks, MAX_STACKS * sizeof(Stack));
            stacks[stackCount].init(0, 10);
            std::cout << "stack sayisi artirildi!" << std::endl;
        }
        */
        std::istringstream iss(line);
        while (iss >> number) {
            if (!stacks[stackCount].isEmpty()) {

                int top = stacks[stackCount].pop();
                if (number > top && number%2==0)
                {
                   
                    stackCount++;
                  //  bst.~BinarySearchTree();
                    if (stackCount >= MAX_STACKS) {
                     //   MAX_STACKS++;
                     //   stacks = (Stack*)realloc(stacks, MAX_STACKS * sizeof(Stack));

                        stacks[stackCount].init(0, 10);
                       
                    } std::cout << "stack sayisi artirildi!" << std::endl;
                }
            }

           stacks[stackCount].push(number);
           bst[stackCount].insert(number);
           
            std::cout << stackCount << ".stack   yeni eleman : " << number << std::endl;
        }
        int i = stackCount;
        while(i>=0){
            trees[i] = bst[i--];
        }

       
        treesCount = stackCount;
            Node* maxNode = trees[0].getMaxHeightNode(trees[0].getRoot(), trees[0].getRoot());
            for (int i = 0; i <= treesCount; ++i) {
                maxNode = trees[i].getMaxHeightNode(maxNode, trees[i].getRoot());
            }



            result.insert(maxNode->data);
            result.getRoot()->left = maxNode->left;
            result.getRoot()->right = maxNode->right;

                if (result.getRoot() != nullptr) {
                std::cout << "ASCII Karakterleri: ";
                result.postorderTraversal(result.getRoot());
                std::cout << std::endl;
            }

    free(stacks); // Dinamik olarak ayrýlan belleði serbest býrak
    return result;
}

int main() {
    std::ifstream file("Sayilar.txt");
    if (!file) {
        std::cerr << "Dosya acilamadi!" << std::endl;
        return 1;
    }
    int    lineNo=0;
    std::string line;
    while (std::getline(file, line))
    {
       std::cout << ++lineNo << ". Satir Okundu" << std::endl << std::endl;

        BinarySearchTree bst = processLine(line);
        if (bst.getRoot() != nullptr) {
            std::cout << "ASCII Karakterleri: ";
            bst.postorderTraversal(bst.getRoot());
            std::cout << std::endl;
        }

    }
    file.close();
    return 0;
}
