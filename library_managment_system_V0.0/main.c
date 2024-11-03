#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BOOK 100

struct Book{
    int id;
    char title[50];
    char author[50];
    bool is_borrowed;
    int student_id;
};

struct Library{
    struct Book books[MAX_BOOK];    //Capacity of library.
    int book_count;                 //Number of current books.
};

void addBook(struct Library *library,int id,const char *title,const char *author){

    if(library->book_count<MAX_BOOK){
        if(strlen(title) == 0 || strlen(author) == 0){
            printf("Invalid input. Please check book's informations.");
            return;
        }else{
            struct Book newBooks;
            newBooks.id=id;
            strcpy(newBooks.title,title);
            strcpy(newBooks.author,author);
            newBooks.is_borrowed=0;
            newBooks.student_id=-1;
            library->books[library->book_count++]=newBooks;
            printf("%s successfully registered.",newBooks.title);
        }

    }else{
        printf("Library is full!!!\n");
    }

}

void listBooks(struct Library *library){

    if(library->book_count == 0 ){
        printf("There aren't any books at your library.\n");
        return;
    }else{
        printf("%-5s %-20s %-20s %-10s\n","ID","Title","Author","Status");
        printf("-------------------------------------------------------------\n");
        int i=0;
        for(;i<library->book_count;i++){
            printf("%-5d %-20s %-20s %-10s\n",library->books[i].id,library->books[i].title,library->books[i].author,
                   library->books[i].is_borrowed ? "Borrowed" : "Available" );
        }
    }
}

void searchBook(struct Library *library,int id){

    for(int i=0;i<library->book_count;i++){
        if(library->books[i].id == id){
            printf("Book found.\n");
            printf("ID: %d\n",library->books[i].id);
            printf("Title: %s\n",library->books[i].title);
            printf("Author: %s\n",library->books[i].author);
            printf("Barrowed: %s\n",library->books[i].is_borrowed ? "Borrowed" : "Available");
            return;
        }
    }
     printf("Book is not availbale!!!\n");
}

void borrowBook(struct Library *library,int id,int student_id){

    for(int i=0;i<library->book_count;i++){
        if(library->books[i].id==id){
            if(library->books[i].is_borrowed){
                printf("This book already borrowed.\n");
            }else{
                library->books[i].student_id=student_id;
                library->books[i].is_borrowed=1;
                printf("Book borrowed.\n");
            }
            return;
        }
    }
    printf("Book id is not found.\n");

}

void returnBook(struct Library *library,int id){

    for(int i=0;i<library->book_count;i++){
        if(library->books[i].id==id){
            if(library->books[i].is_borrowed){
                library->books[i].is_borrowed=0;
                library->books[i].student_id=-1;
                printf("Book returned.\n");
            }else{
                printf("Book is already here.\n");
            }
            return;
        }
    }
    printf("Book id not found.\n");
}




int main()
{
    struct Library library;
    library.book_count=0;
    int student_id,id;
    char title[50],author[50];
    int choice;

    do{
        printf("\nWelcome Library Management System\n");
        printf("1.Add book.\n");
        printf("2.List all books.\n");
        printf("3.Search book by ID.\n");
        printf("4.Rent book.\n");
        printf("5.Return book.\n");
        printf("0.Exit.\n");
        printf("Please enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 0:
                printf("Exit!!!!");
                break;
            case 1:
                printf("ID: ");
                scanf("%d",&id);
                printf("Title: ");
                getchar();
                gets(title);
                printf("Author: ");
                gets(author);
                addBook(&library,id,title,author);
                break;
            case 2:
                listBooks(&library);
                break;
            case 3:
                printf("Enter book Id to search:");
                scanf("%d",&id);
                searchBook(&library,id);
                break;
            case 4:
                printf("Enter book ID to borrow: ");
                scanf("%d",&id);
                printf("Enter student ID: ");
                scanf("%d",&student_id);
                borrowBook(&library,id,student_id);
                break;
            case 5:
                printf("Enter book ID to return: ");
                scanf("%d",&id);
                returnBook(&library,id);
                break;
            default:
                printf("Invalide choice. Please try again.\n");

        }


    }while(choice!=0);


    return 0;
}
