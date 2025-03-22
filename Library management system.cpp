#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    std::string status;
    std::string issuedTo; 

    
    Book() : id(0), title(""), author(""), status("available"), issuedTo("") {}
    Book(int id, const std::string &title, const std::string &author)
        : id(id), title(title), author(author), status("available"), issuedTo("") {}
};

class Library {
private:
    std::vector<Book> books;

    void merge(std::vector<Book> &books, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<Book> leftArray(n1);
        std::vector<Book> rightArray(n2);

        for (int i = 0; i < n1; i++)
            leftArray[i] = books[left + i];
        for (int i = 0; i < n2; i++)
            rightArray[i] = books[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArray[i].id <= rightArray[j].id) {
                books[k] = leftArray[i];
                i++;
            } else {
                books[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            books[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < n2) {
            books[k] = rightArray[j];
            j++;
            k++;
        }
    }

    void mergeSort(std::vector<Book> &books, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(books, left, mid);
            mergeSort(books, mid + 1, right);

            merge(books, left, mid, right);
        }
    }

public:
    void addBook(int id, const std::string &title, const std::string &author) {
        Book newBook(id, title, author);
        books.push_back(newBook);
    }

    Book* searchBookById(int id) {
        for (std::vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                return &(*it);
            }
        }
        return NULL;
    }

    Book* searchBookByTitle(const std::string &title) {
        for (std::vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                return &(*it);
            }
        }
        return NULL;
    }

    void issueBook(int id, const std::string &studentName) {
        Book* book = searchBookById(id);
        if (book != NULL && book->status == "available") {
            book->status = "issued";
            book->issuedTo = studentName;
        } else {
            std::cout << "Book not available.\n";
        }
    }

    void returnBook(int id) {
        Book* book = searchBookById(id);
        if (book != NULL && book->status == "issued") {
            book->status = "available";
            book->issuedTo = "";
        } else {
            std::cout << "Book not issued.\n";
        }
    }

    void listBooks() {
        mergeSort(books, 0, books.size() - 1);
        for (std::vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            std::cout << "ID: " << it->id << ", Title: " << it->title << ", Author: " << it->author << ", Status: " << it->status << "\n";
        }
    }

    void deleteBook(int id) {
        for (std::vector<Book>::iterator it = books.begin(); it != books.end(); ) {
            if (it->id == id) {
                it = books.erase(it);
            } else {
                ++it;
            }
        }
    }
};

int main() {
    Library library;
    int choice;

    do {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Search Book by ID\n";
        std::cout << "3. Search Book by Title\n";
        std::cout << "4. Issue Book\n";
        std::cout << "5. Return Book\n";
        std::cout << "6. List Books\n";
        std::cout << "7. Delete Book\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                std::string title, author;
                std::cout << "Enter book ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                std::cout << "Enter book author: ";
                std::getline(std::cin, author);
                library.addBook(id, title, author);
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter book ID: ";
                std::cin >> id;
                Book* book = library.searchBookById(id);
                if (book != NULL) {
                    std::cout << "Book found: " << book->title << "\n";
                } else {
                    std::cout << "Book not found.\n";
                }
                break;
            }
            case 3: {
                std::string title;
                std::cout << "Enter book title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                Book* book = library.searchBookByTitle(title);
                if (book != NULL) {
                    std::cout << "Book found: " << book->title << "\n";
                } else {
                    std::cout << "Book not found.\n";
                }
                break;
            }
            case 4: {
                int id;
                std::string studentName;
                std::cout << "Enter book ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter student name: ";
                std::getline(std::cin, studentName);
                library.issueBook(id, studentName);
                break;
            }
            case 5: {
                int id;
                std::cout << "Enter book ID: ";
                std::cin >> id;
                library.returnBook(id);
                break;
            }
            case 6: {
                library.listBooks();
                break;
            }
            case 7: {
                int id;
                std::cout << "Enter book ID: ";
                std::cin >> id;
                library.deleteBook(id);
                break;
            }
            case 8: {
                std::cout << "Exiting...\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 8);

    return 0;
}
