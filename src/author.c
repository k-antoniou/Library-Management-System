#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "author.h"

author* read_authors(const char* filename, int* num_authors) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open author file");
        return NULL;
    }

    // Read the number of authors
    if (fscanf(file, "%d\n", num_authors) != 1) {
        perror("Failed to read number of authors");
        fclose(file);
        return NULL;
    }

    // Allocate memory for authors array
    author* authors = malloc(sizeof(author) * (*num_authors));
    if (!authors) {
        perror("Failed to allocate memory for authors");
        fclose(file);
        return NULL;
    }

    // Read each author's data
    for (int i = 0; i < *num_authors; i++) {
        authors[i].surname = malloc(sizeof(char) * 150);
        authors[i].name = malloc(sizeof(char) * 150);

        if (!authors[i].surname || !authors[i].name) {
            perror("Failed to allocate memory for author names");
            fclose(file);
            for (int j = 0; j < i; j++) {
                free(authors[j].surname);
                free(authors[j].name);
            }
            free(authors);
            return NULL;
        }

        if (fscanf(file, "%d\n%149s\n%149s\n%d\n", &authors[i].writer_id, authors[i].surname, authors[i].name, &authors[i].num_of_books) != 4) {
            perror("Failed to read author data");
            fclose(file);
            for (int j = 0; j <= i; j++) {
                free(authors[j].surname);
                free(authors[j].name);
            }
            free(authors);
            return NULL;
        }
    }

    fclose(file);
    return authors;
}

void swap_author(author *author1, author *author2)
{
    author tmp;

    tmp = *author1;
    *author1 = *author2;
    *author2 = tmp;
}

void bubble_sort_author(author *author_arr, int author_entries)
{
    int i,j;
    for(i=0;i<author_entries-1;i++){
        for (j=0;j<author_entries-i-1;j++){
            if(author_arr[j].writer_id > author_arr[j+1].writer_id){
                swap_author(&author_arr[j], &author_arr[j+1]);
            }
        }
    }
}

int author_search(author* author_arr, int author_entries, int in_id)
{
    int lb, mid, ub, pos = 0;
    //init bounds
    lb = 0;                            
    ub = author_entries;                            
    do
    {
        //compare id with the middle of array
        mid = (int)(lb + ub) / 2;      
        if(in_id < author_arr[mid].writer_id)     
            ub = mid - 1;                       
        else if(in_id > author_arr[mid].writer_id)
            lb = mid + 1;        
    //repeat the process till lb doesn't becomes ub and string is found   
    }while((in_id != author_arr[mid].writer_id) && lb <= ub);
    //if id is found
    if(in_id == author_arr[mid].writer_id){
        pos=mid;
        return pos;
    //if id is not found
    }else if(in_id != author_arr[mid].writer_id) {                                        //if not found
        printf("Author not found \n");
        return -1;
    }
}

int save_author(int author_entries, author* author_arr){
	int i;
	FILE *author_file;
	if ((author_file = fopen("author2.txt", "w")) == NULL ){
        fprintf(stderr, "File not found.\n");
        return -1;
    }
    fprintf(author_file, "%d\n", author_entries);
    for (i=0;i<author_entries; i++){
        fprintf(author_file, "%d\n%s\n%s\n%d\n", author_arr[i].writer_id, author_arr[i].surname, author_arr[i].name, author_arr[i].num_of_books);
    }
    fclose(author_file);

}

void free_authors(author* authors, int num_authors) {
    if (authors) {
        for (int i = 0; i < num_authors; i++) {
            free(authors[i].surname);
            free(authors[i].name);
        }
        free(authors);
    }
}
