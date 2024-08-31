#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "author.h"
#include "book.h"

int menu() {
    int choice;
	
    printf("\n1.Insert new writer record\n");
    printf("2.Insert new book record\n");
    printf("3.Search a writer record\n");
    printf("4.Search a book record\n");
    printf("5.Delete a writer record\n");
    printf("6.Delete a book record\n");
    printf("7.Exit\n\n");
    
	printf("Enter your choice: ");
    
	scanf("%d", &choice);
    
	return choice;
}

