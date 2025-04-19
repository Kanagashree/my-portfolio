#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store book information
struct Book {
    int id;
    char title[50];
    char author[50];
    int isIssued; // 0 for available, 1 for issued
};

// Function to add a new book to the library
void addBook(FILE *file) {
    struct Book newBook;
    printf("Enter book ID: ");
    scanf("%d", &newBook.id);
    getchar();  // To consume the newline character left by scanf

    printf("Enter book title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;  // Remove the newline character

    printf("Enter book author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;  // Remove the newline character

    newBook.isIssued = 0; // Initially, book is not issued

    fwrite(&newBook, sizeof(struct Book), 1, file);  // Write book to file
    printf("Book added successfully!\n");
}

// Function to view all available books
void viewBooks(FILE *file) {
    struct Book book;
    printf("Available books:\n");
    rewind(file);  // Move file pointer to the beginning

    while(fread(&book, sizeof(struct Book), 1, file)) {
        if(book.isIssued == 0) {
            printf("ID: %d, Title: %s, Author: %s\n", book.id, book.title, book.author);
        }
    }
}

// Function to issue a book
void issueBook(FILE *file) {
    int id;
    struct Book book;
    printf("Enter book ID to issue: ");
    scanf("%d", &id);

    rewind(file);  // Move file pointer to the beginning

    while(fread(&book, sizeof(struct Book), 1, file)) {
        if(book.id == id && book.isIssued == 0) {
            book.isIssued = 1;
            fseek(file, -(long)sizeof(struct Book), SEEK_CUR);
            // Move back to the correct position
            fwrite(&book, sizeof(struct Book), 1, file);  // Update book status to issued
            printf("Book issued successfully!\n");
            return;
        }
    }

    printf("Book not available or already issued.\n");
}

// Function to return a book
void returnBook(FILE *file) {
    int id;
    struct Book book;
    printf("Enter book ID to return: ");
    scanf("%d", &id);

    rewind(file);  // Move file pointer to the beginning

    while(fread(&book, sizeof(struct Book), 1, file)) {
        if(book.id == id && book.isIssued == 1) {
            book.isIssued = 0;
            fseek(file, -(long)sizeof(struct Book), SEEK_CUR);
            // Move back to the correct position
            fwrite(&book, sizeof(struct Book), 1, file);  // Update book status to available
            printf("Book returned successfully!\n");
            return;
        }
    }

    printf("Invalid book ID or the book is not issued.\n");
}

// Main menu function
void menu() {
    FILE *file = fopen("book_data.txt", "rb+");  // Open the file in read-write binary mode
    if (file == NULL) {
        file = fopen("book_data.txt", "wb+");  // If file doesn't exist, create it
    }

    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook(file);
                break;
            case 2:
                viewBooks(file);
                break;
            case 3:
                issueBook(file);
                break;
            case 4:
                returnBook(file);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);

    fclose(file);  // Close the file
}

int main() {
    menu();  // Call the menu function
    return 0;
}






















