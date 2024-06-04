#include <iostream>
using namespace std;

class Node {
public:
    int row;
    int column;
    int value;
    Node* next;
    Node* down;

    Node(int row, int col, int data) 
    : row(row), column(col), value(data), next(nullptr), down(nullptr) 
    {}
};

class SparseMatrix {
private:
    int rows;
    int cols;
    Node** rowHeaders;
    Node** colHeaders;

public:
    SparseMatrix(int rows, int cols) 
    : rows(rows), cols(cols) 
    {
        rowHeaders = new Node*[rows];
        colHeaders = new Node*[cols];

        for (int i = 0; i < rows; i++) {
            rowHeaders[i] = nullptr;
        }
        for (int i = 0; i < cols; i++) {
            colHeaders[i] = nullptr;
        }
    }

    void insert(int row, int col, int data) {
        Node* newNode = new Node(row, col, data);

        if (rowHeaders[row] == nullptr || rowHeaders[row]->column > col) {
            newNode->next = rowHeaders[row];
            rowHeaders[row] = newNode;
        } else {
            Node* temp = rowHeaders[row];
            while (temp->next && temp->next->column < col) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }

        if (colHeaders[col] == nullptr || colHeaders[col]->row > row) {
            newNode->down = colHeaders[col];
            colHeaders[col] = newNode;
        } else {
            Node* temp = colHeaders[col];
            while (temp->down && temp->down->row < row) {
                temp = temp->down;
            }
            newNode->down = temp->down;
            temp->down = newNode;
        }
    }

    void constMultiply(double constant) {
        for (int i = 0; i < rows; i++) {
            Node* temp = rowHeaders[i];
            while (temp != nullptr) {
                temp->value = (double)(temp->value) * constant;
                temp = temp->next;
            }
        }
    }

    void display() {
        for (int i = 0; i < rows; i++) {
            Node* temp = rowHeaders[i];
            for (int j = 0; j < cols; j++) {
                if (temp != nullptr && temp->column == j) {
                    cout << temp->value << " ";
                    temp = temp->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    SparseMatrix matrix(rows, cols);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert an element\n";
        cout << "2. Multiply by a constant\n";
        cout << "3. Display matrix\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int row, col, data;
                cout << "Enter row: ";
                cin >> row;
                cout << "Enter column: ";
                cin >> col;
                cout << "Enter value: ";
                cin >> data;
                matrix.insert(row, col, data);
                break;
            }
            case 2: {
                double constant;
                cout << "Enter constant to multiply: ";
                cin >> constant;
                matrix.constMultiply(constant);
                break;
            }
            case 3: {
                cout << "Matrix:\n";
                matrix.display();
                break;
            }
            case 4: {
                cout << "Exiting program.\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 4);

    return 0;
}
