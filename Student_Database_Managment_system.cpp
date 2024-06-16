#include <bits/stdc++.h>
using namespace std;

struct Student
{
    string id;
    string name;
    Student *next; // Pointer to the next student in the list
};

struct TreeNode
{
    Student *student;
    TreeNode *left;
    TreeNode *right;
};

Student *head = nullptr; // Head pointer of the linked list
TreeNode *root = nullptr; // Root pointer of the BST

// Function prototypes
void addStudent();
void searchStudent();
void updateStudent();
void deleteStudent();
void displayAllStudents();
void insertIntoBST(TreeNode *&root, Student *student);
Student *searchInBST(TreeNode *root, const string &id);
void buildBST();

int main()
{
    int choice;

    do
    {
        cout << "\n--- Student Database Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            buildBST();
            break;
        case 2:
            searchStudent();
            break;
        case 3:
            updateStudent();
            buildBST();
            break;
        case 4:
            deleteStudent();
            buildBST();
            break;
        case 5:
            displayAllStudents();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    // Free dynamically allocated memory before exiting
    Student *current = head;
    while (current != nullptr)
    {
        Student *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}

void addStudent()
{
    Student *newStudent = new Student;

    cout << "Enter student ID: ";
    cin >> newStudent->id;
    cin.ignore(); // Clear input buffer

    cout << "Enter student name: ";
    getline(cin, newStudent->name);

    newStudent->next = head; // Set the new node's next pointer to the current head
    head = newStudent;       // Update head to point to the new node

    cout << "Student added successfully!\n";
}

void searchStudent()
{
    string searchID;

    cout << "Enter student ID to search: ";
    cin >> searchID;

    Student *student = searchInBST(root, searchID);
    if (student)
    {
        cout << "\nFound student:\n";
        cout << "ID: " << student->id << endl;
        cout << "Name: " << student->name << endl;
    }
    else
    {
        cout << "Student not found!\n";
    }
}

void updateStudent()
{
    string updateID;
    Student *current = head;

    cout << "Enter student ID to update: ";
    cin >> updateID;
    cin.ignore(); // Clear input buffer

    while (current != nullptr)
    {
        if (current->id == updateID)
        {
            cout << "Enter new student ID: ";
            getline(cin, current->id);

            cout << "Enter new student name: ";
            getline(cin, current->name);

            cout << "Student updated successfully!\n";
            return;
        }
        current = current->next;
    }

    cout << "Student not found!\n";
}

void deleteStudent()
{
    string deleteID;
    Student *current = head;
    Student *previous = nullptr;

    cout << "Enter student ID to delete: ";
    cin >> deleteID;

    if (head != nullptr && head->id == deleteID)
    { // Delete head node
        head = head->next;
        delete current;
        cout << "Student deleted successfully!\n";
        return;
    }

    while (current != nullptr && current->id != deleteID)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "Student not found!\n";
        return;
    }

    previous->next = current->next; // Remove node from the list
    delete current;
    cout << "Student deleted successfully!\n";
}

void displayAllStudents()
{
    Student *current = head;

    if (head == nullptr)
    {
        cout << "No students in the database!\n";
        return;
    }

    cout << "\n--- Student List ---\n";
    while (current != nullptr)
    {
        cout << "ID: " << current->id << endl;
        cout << "Name: " << current->name << endl;
        current = current->next;
    }
}

void insertIntoBST(TreeNode *&root, Student *student)
{
    if (root == nullptr)
    {
        root = new TreeNode{student, nullptr, nullptr};
    }
    else if (student->id < root->student->id)
    {
        insertIntoBST(root->left, student);
    }
    else
    {
        insertIntoBST(root->right, student);
    }
}

Student *searchInBST(TreeNode *root, const string &id)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root->student->id == id)
    {
        return root->student;
    }
    if (id < root->student->id)
    {
        return searchInBST(root->left, id);
    }
    return searchInBST(root->right, id);
}

void buildBST()
{
    root = nullptr;
    Student *current = head;
    while (current != nullptr)
    {
        insertIntoBST(root, current);
        current = current->next;
    }
}
