#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include "BOOK.h"
#include "User.h"
#include"ColorUtils.h"
using namespace std;

// Function declarations
void showMainMenu();
void bookOperationsMenu(BOOK& Lib);
void userOperationsMenu(User& Users);
void borrowReturnMenu(User& Users, BOOK& Lib);
void reportsMenu(User& Users, BOOK& Lib);
void demoData(BOOK& Lib, User& Users);

// Utility functions
void clearScreen() {
    system("cls");  // Windows - use "clear" for Linux/Mac
}

void pressAnyKey() {
    cout << "\n";
    ColorUtils::printInfo("Press any key to continue...");
    cin.ignore();
    cin.get();
}

int getIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');  // Using a large fixed number instead of max()
            ColorUtils::printError("Invalid input! Please enter a number.");
        }
        else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int main() {
    BOOK Lib;
    User Users;

    // Load demo data
    demoData(Lib, Users);

    int choice;
    do {
        showMainMenu();
        choice = getIntegerInput("Enter your choice (1-5): ");

        switch (choice) {
        case 1:
            bookOperationsMenu(Lib);
            break;
        case 2:
            userOperationsMenu(Users);
            break;
        case 3:
            borrowReturnMenu(Users, Lib);
            break;
        case 4:
            reportsMenu(Users, Lib);
            break;
        case 5:
            ColorUtils::printSuccess("Thank you for using Library Management System!");
            break;
        default:
            ColorUtils::printError("Invalid choice! Please select 1-5.");
            pressAnyKey();
        }
    } while (choice != 5);

    return 0;
}

void showMainMenu() {
    clearScreen();
    ColorUtils::printHeader("LIBRARY MANAGEMENT SYSTEM");

    cout << setw(5) << "1." << " Book Operations" << endl;
    cout << setw(5) << "2." << " User Operations" << endl;
    cout << setw(5) << "3." << " Borrow/Return Books" << endl;
    cout << setw(5) << "4." << " Reports & Analytics" << endl;
    cout << setw(5) << "5." << " Exit" << endl;

    cout << endl;
    ColorUtils::printInfo("Select an option (1-5): ");
}

void bookOperationsMenu(BOOK& Lib) {
    int choice;
    do {
        clearScreen();
        ColorUtils::printHeader("BOOK OPERATIONS");

        cout << setw(5) << "1." << " Add New Book" << endl;
        cout << setw(5) << "2." << " Remove Book" << endl;
        cout << setw(5) << "3." << " Update Book" << endl;
        cout << setw(5) << "4." << " Find Book" << endl;
        cout << setw(5) << "5." << " Show All Books" << endl;
        cout << setw(5) << "6." << " Most Demanded Book" << endl;
        cout << setw(5) << "7." << " Back to Main Menu" << endl;

        cout << endl;
        choice = getIntegerInput("Enter your choice (1-7): ");
        BSTNode* found;
        switch (choice) {
        case 1:
            clearScreen();
            ColorUtils::printTitle("ADD NEW BOOK");
            Lib.insert();
            pressAnyKey();
            break;
        case 2:
            clearScreen();
            ColorUtils::printTitle("REMOVE BOOK");
            if (Lib.findBook()) {
                char confirm;
                cout << "Are you sure you want to remove this book? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    Lib.remove();
                    ColorUtils::printSuccess("Book removed successfully!");
                }
                else {
                    ColorUtils::printInfo("Book removal cancelled.");
                }
            }
            pressAnyKey();
            break;
        case 3:
            clearScreen();
            ColorUtils::printTitle("UPDATE BOOK");
            Lib.update();
            ColorUtils::printSuccess("Book updated successfully!");
            pressAnyKey();
            break;
        case 4:
            clearScreen();
            ColorUtils::printTitle("FIND BOOK");
            found = Lib.findBook();
            found->printBook();
            pressAnyKey();
            break;
        case 5:
            clearScreen();
            ColorUtils::printTitle("ALL BOOKS IN LIBRARY");
            Lib.printAllBooks();
            pressAnyKey();
            break;
        case 6:
            clearScreen();
            ColorUtils::printTitle("MOST DEMANDED BOOK");
            Lib.findMostDemandedBook();
            pressAnyKey();
            break;
        case 7:
            ColorUtils::printInfo("Returning to Main Menu...");
            break;
        default:
            ColorUtils::printError("Invalid choice! Please select 1-7.");
            pressAnyKey();
        }
    } while (choice != 7);
}

void userOperationsMenu(User& Users) {
    int choice;
    do {
        clearScreen();
        ColorUtils::printHeader("USER OPERATIONS");

        cout << setw(5) << "1." << " Add New User" << endl;
        cout << setw(5) << "2." << " Remove User" << endl;
        cout << setw(5) << "3." << " Find User" << endl;
        cout << setw(5) << "4." << " Show All Users" << endl;
        cout << setw(5) << "5." << " Back to Main Menu" << endl;

        cout << endl;
        choice = getIntegerInput("Enter your choice (1-5): ");

        switch (choice) {
        case 1:
            clearScreen();
            ColorUtils::printTitle("ADD NEW USER");
            Users.insertUser();
            ColorUtils::printSuccess("User added successfully!");
            pressAnyKey();
            break;
        case 2:
            clearScreen();
            ColorUtils::printTitle("REMOVE USER");
            Users.deleteUser();
            ColorUtils::printSuccess("User removed successfully!");
            pressAnyKey();
            break;
        case 3:
            clearScreen();
            ColorUtils::printTitle("FIND USER");
            Users.printUser();
            pressAnyKey();
            break;
        case 4:
            clearScreen();
            ColorUtils::printTitle("ALL USERS");
            Users.printAllUsers();
            pressAnyKey();
            break;
        case 5:
            ColorUtils::printInfo("Returning to Main Menu...");
            break;
        default:
            ColorUtils::printError("Invalid choice! Please select 1-5.");
            pressAnyKey();
        }
    } while (choice != 5);
}

void borrowReturnMenu(User& Users, BOOK& Lib) {
    int choice;
    do {
        clearScreen();
        ColorUtils::printHeader("BORROW & RETURN OPERATIONS");

        cout << setw(5) << "1." << " Borrow Book" << endl;
        cout << setw(5) << "2." << " Return Book" << endl;
        cout << setw(5) << "3." << " Back to Main Menu" << endl;

        cout << endl;
        choice = getIntegerInput("Enter your choice (1-3): ");

        switch (choice) {
        case 1: {
            clearScreen();
            ColorUtils::printTitle("BORROW BOOK");
            int userId = getIntegerInput("Enter User ID: ");
            int issn = getIntegerInput("Enter Book ISSN: ");

            // Check if user exists
            if (Users.search(userId)) {
                Users.BorrowBook(userId, issn, Lib);
                ColorUtils::printSuccess("Book borrowing process completed!");
            }
            else {
                ColorUtils::printError("User not found!");
            }
            pressAnyKey();
            break;
        }
        case 2: {
            clearScreen();
            ColorUtils::printTitle("RETURN BOOK");
            int userId = getIntegerInput("Enter User ID: ");
            int issn = getIntegerInput("Enter Book ISSN: ");

            // Check if user exists
            if (Users.search(userId)) {
                Users.ReturnBook(userId, issn, Lib);
                ColorUtils::printSuccess("Book return process completed!");
            }
            else {
                ColorUtils::printError("User not found!");
            }
            pressAnyKey();
            break;
        }
        case 3:
            ColorUtils::printInfo("Returning to Main Menu...");
            break;
        default:
            ColorUtils::printError("Invalid choice! Please select 1-3.");
            pressAnyKey();
        }
    } while (choice != 3);
}

void reportsMenu(User& Users, BOOK& Lib) {
    int choice;
    do {
        clearScreen();
        ColorUtils::printHeader("REPORTS & ANALYTICS");

        cout << setw(5) << "1." << " Calculate Fines" << endl;
        cout << setw(5) << "2." << " Most Demanded Book" << endl;
        cout << setw(5) << "3." << " Display All Users with Balances" << endl;
        cout << setw(5) << "4." << " Display All Books" << endl;
        cout << setw(5) << "5." << " Check AVL Balance" << endl;
        cout << setw(5) << "6." << " Back to Main Menu" << endl;

        cout << endl;
        choice = getIntegerInput("Enter your choice (1-6): ");

        switch (choice) {
        case 1:
            clearScreen();
            ColorUtils::printTitle("OUTSTANDING FINES REPORT");
            Users.calcFines();
            pressAnyKey();
            break;
        case 2:
            clearScreen();
            ColorUtils::printTitle("MOST DEMANDED BOOK REPORT");
            Lib.findMostDemandedBook();
            pressAnyKey();
            break;
        case 3:
            clearScreen();
            ColorUtils::printTitle("USERS WITH BALANCE FACTORS");
            Users.InOrderBalance();
            pressAnyKey();
            break;
        case 4:
            clearScreen();
            ColorUtils::printTitle("COMPLETE BOOK CATALOG");
            Lib.printAllBooks();
            pressAnyKey();
            break;
        case 5:
            clearScreen();
            ColorUtils::printTitle("AVL TREE BALANCE CHECK");
            if (Users.isAVL()) {
                ColorUtils::printSuccess("User AVL tree is perfectly balanced!");
            }
            else {
                ColorUtils::printError("User AVL tree is unbalanced!");
            }
            pressAnyKey();
            break;
        case 6:
            ColorUtils::printInfo("Returning to Main Menu...");
            break;
        default:
            ColorUtils::printError("Invalid choice! Please select 1-6.");
            pressAnyKey();
        }
    } while (choice != 6);
}

void demoData(BOOK& Lib, User& Users) {
    // Add sample books
    ColorUtils::printInfo("Loading demo data...");

    Lib.insert(101, "The Great Gatsby", { "F. Scott Fitzgerald" }, 5, 3);
    Lib.insert(102, "To Kill a Mockingbird", { "Harper Lee" }, 4, 2);
    Lib.insert(103, "1984", { "George Orwell" }, 6, 4);
    Lib.insert(104, "Pride and Prejudice", { "Jane Austen" }, 3, 2);
    Lib.insert(105, "The Catcher in the Rye", { "J.D. Salinger" }, 5, 3);

    // Add sample users
    Users.insertUser(1001, "Alice Johnson");
    Users.insertUser(1002, "Bob Smith");
    Users.insertUser(1003, "Carol Davis");
    Users.insertUser(1004, "David Wilson");
    Users.insertUser(1005, "Eva Brown");

    ColorUtils::printSuccess("Demo data loaded successfully!");
    pressAnyKey();
}