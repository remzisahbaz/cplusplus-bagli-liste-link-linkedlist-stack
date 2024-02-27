#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <windows.h> // Sleep() fonksiyonu i�in

// Y���t veri yap�s�
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
            free(data); // Eski veriyi serbest b�rakma
            data = newData; // Yeni veri alan�n� g�ster
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
            return -1; // Varsay�lan hata de�eri, uygun de�er belirlenebilir.
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

// �kili Arama A�ac� d���m veri yap�s�
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// �kili Arama A�ac� veri yap�s�
class BinarySearchTree {
private:
    Node* root;

    // �kili Arama A�ac� d���mlerini postorder gezisi ile silen yard�mc� fonksiyon
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        free(node);
    }

    // �kili Arama A�ac�na d���m ekleme yard�mc� fonksiyonu
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

    // �kili Arama A�ac�n�n y�ksekli�ini hesaplayan yard�mc� fonksiyon
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

    // �kili Arama A�ac�na d���m ekleme i�levi
    void insert(int value) {
        root = insertNode(root, value);
    }

    // �kili Arama A�ac�ndaki en y�ksek y�ksekli�e sahip d���m� se�en i�lev
    Node* getMaxHeightNode(Node* node1, Node* node2) {
        // �lk a�a��n y�ksekli�i daha b�y�kse, ilk a�ac� se�
        if (getHeight(node1) > getHeight(node2)) {
            return node1;
        }
        // �kinci a�ac�n y�ksekli�i daha b�y�kse, ikinci a�ac� se�
        else if (getHeight(node1) < getHeight(node2)) {
            return node2;
        }
        // Y�kseklikler e�itse, d���mlerinin toplam de�eri daha b�y�k olan� se�
        else {
            int sum1 = sumNodeValues(node1);
            int sum2 = sumNodeValues(node2);
            return (sum1 >= sum2) ? node1 : node2;
        }
    }

    // �kili Arama A�ac�n� postorder gezerek ASCII karakterlerini ekrana yazd�ran i�lev
    void postorderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        postorderTraversal(root->left);
        postorderTraversal(root->right);
        std::cout << static_cast<char>(root->data);
    }

    // �kili Arama A�ac�n�n d���m de�erlerinin toplam�n� hesaplayan yard�mc� fonksiyon
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

    free(stacks); // Dinamik olarak ayr�lan belle�i serbest b�rak
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
