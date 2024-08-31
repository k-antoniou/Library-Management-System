#ifndef WRITES_H
#define WRITES_H

typedef struct {
    char* title;
    int writer_id;
} writes;

writes* read_writes(const char* filename, int* num_writes);
void swap_writes(writes *writes1, writes *writes2);
int writes_search_id(writes* writes_arr, int writes_entries, int in_writer_id);
void bubble_sort_writes(writes *writes_arr, int writes_entries);
int save_writes(int writes_entries, writes* writes_arr);
void free_writes(writes* writes_arr, int num_writes);

#endif
