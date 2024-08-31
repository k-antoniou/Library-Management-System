#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writes.h"

writes* read_writes(const char* filename, int* num_writes) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open writes file");
        return NULL;
    }

    if (fscanf(file, "%d\n", num_writes) != 1) {
        perror("Failed to read number of writes entries");
        fclose(file);
        return NULL;
    }

    writes* writes_arr = malloc(sizeof(writes) * (*num_writes));
    if (!writes_arr) {
        perror("Failed to allocate memory for writes");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < *num_writes; i++) {
        writes_arr[i].title = malloc(sizeof(char) * 150);
        if (!writes_arr[i].title) {
            perror("Failed to allocate memory for write title");
            fclose(file);
            free(writes_arr);
            return NULL;
        }
        if (fscanf(file, "%[^\n]\n%d\n", writes_arr[i].title, &writes_arr[i].writer_id) != 2) {
            perror("Failed to read writes data");
            fclose(file);
            free(writes_arr);
            return NULL;
        }
    }

    fclose(file);
    return writes_arr;
}

void swap_writes(writes *writes1, writes *writes2)
{
	writes tmp;

    tmp = *writes1;
    *writes1 = *writes2;
    *writes2 = tmp;	
}

void bubble_sort_writes(writes *writes_arr, int writes_entries)
{
    int i,j;
    for(i=0;i<writes_entries-1;i++){
        for (j=0;j<writes_entries-i-1;j++){
            if(writes_arr[j].writer_id>writes_arr[j+1].writer_id){
                swap_writes(&writes_arr[j], &writes_arr[j+1]);
            }else if(writes_arr[j].writer_id==writes_arr[j+1].writer_id){
			    if(strcmp(writes_arr[j].title, writes_arr[j+1].title)>0){
                    swap_writes(&writes_arr[j], &writes_arr[j+1]);  
                }
            }
        }
    }
}

int writes_search_id(writes* writes_arr, int writes_entries, int in_writer_id)
{
    int lb, mid, ub, pos=0;
    lb = 0;
    ub = writes_entries; 
    do
    {
        //compare id with the middle of the array 
        mid = (int)(lb + ub) / 2;
        if(in_writer_id < writes_arr[mid].writer_id)
            ub = mid - 1;
        else if(in_writer_id > writes_arr[mid].writer_id)
            lb = mid + 1;
    }while((in_writer_id != writes_arr[mid].writer_id) && lb <= ub);
    //if id is found
    if(in_writer_id == writes_arr[mid].writer_id){
            pos=mid;
            return pos;
    //if id is not found
    }else{
        printf("Write not found \n");
        return -1;
    }
}

int save_writes(int writes_entries, writes* writes_arr){
	int i;
	FILE *writes_file;
	//save writes array to file
	if ((writes_file = fopen("writes2.txt", "w")) == NULL ){
        fprintf(stderr, "File not found.\n");
        return -1;
    }
    fprintf(writes_file, "%d\n", writes_entries);
    for (i=0;i<writes_entries; i++){
        fprintf(writes_file, "%s\n%d\n", writes_arr[i].title,writes_arr[i].writer_id);
            
    }
    fclose(writes_file);
}

void free_writes(writes* writes_arr, int num_writes) {
    if (writes_arr) {
        for (int i = 0; i < num_writes; i++) {
            free(writes_arr[i].title);
        }
        free(writes_arr);
    }
}
