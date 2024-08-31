#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

book* read_books(const char* filename, int* num_books) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open book file");
        return NULL;
    }

    if (fscanf(file, "%d\n", num_books) != 1) {
        perror("Failed to read number of book entries");
        fclose(file);
        return NULL;
    }

    book* books = malloc(sizeof(book) * (*num_books));
    if (!books) {
        perror("Failed to allocate memory for books");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < *num_books; i++) {
        books[i].title = malloc(sizeof(char) * 150);
        if (!books[i].title) {
            perror("Failed to allocate memory for book title");
            fclose(file);
            free(books);
            return NULL;
        }
        if (fscanf(file, "%[^\n]\n%d\n%f\n", books[i].title, &books[i].release_date, &books[i].price) != 3) {
            perror("Failed to read book data");
            fclose(file);
            free(books);
            return NULL;
        }
    }

    fclose(file);
    return books;
}

void swap_book(book *b1, book *b2)
{
    book tmp;

    tmp = *b1;
    *b1 = *b2;
    *b2 = tmp;
}

void bubble_sort_book(book *book_arr, int book_entries)
{
    int i,j;
    for(i=0;i<book_entries-1;i++){
        for (j=0;j<book_entries-i-1;j++){
            if(strcmp(book_arr[j].title, book_arr[j+1].title)>0){
                swap_book(&book_arr[j], &book_arr[j+1]);
            }
        }
    }
}

int book_search(book* book_arr, int book_entries, char* in_title)
{
    int lb, mid, ub, pos = 0;
    //init bounds
    lb = 0;                             
    ub = book_entries;                            
    do
    {
        //compare title with the middle of the array
        mid = (int)(lb + ub) / 2;             
        if((strcmp(in_title, book_arr[mid].title))<0)      
            ub = mid - 1;                          
        else if((strcmp(in_title, book_arr[mid].title))>0)
            lb = mid + 1;                      
    }while((strcmp(in_title, book_arr[mid].title)!=0) && lb <= ub);
    //if title is found
    if((strcmp(in_title, book_arr[mid].title))==0){
        pos=mid;
        return pos;
        
    //if title is not found
    }else{                                        
        printf("Book not found \n");
        return -1;
    }
}

int save_book(int book_entries, book* book_arr){
	int i;
	FILE *book_file;
	if ((book_file = fopen("book2.txt", "w")) == NULL ){
        fprintf(stderr, "File not found.\n");
        return -1;
    }
    fprintf(book_file, "%d\n", book_entries);
    for (i=0;i<book_entries; i++){
        fprintf(book_file, "%s\n%d\n%f\n", book_arr[i].title,book_arr[i].release_date,book_arr[i].price);
	}
    fclose(book_file);
}

void free_books(book* books, int num_books) {
    if (books) {
        for (int i = 0; i < num_books; i++) {
            free(books[i].title);
        }
        free(books);
    }
}
