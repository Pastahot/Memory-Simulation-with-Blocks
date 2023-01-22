#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ONEBLOCK 10 // size of one block
#define MAX_BLOCKS 10

struct block {
    int size;
    int index;
    char* memory;
    struct block* next;
};

struct block blocks[MAX_BLOCKS];
int block_count = 0;

void* my_alloc(int size) {
    if (block_count >= MAX_BLOCKS) {
        printf("Error: Maximum number of blocks reached\n");
        return NULL;
    }
    blocks[block_count].size = size;
    blocks[block_count].index = 1;
    blocks[block_count].memory = (char*)malloc(size);
    if (block_count > 0) {
        blocks[block_count - 1].next = &blocks[block_count];
    }
    block_count++;
    printf("Allocated block of size %d at memory address: %p\n", size, blocks[block_count - 1].memory);
    return blocks[block_count - 1].memory;
}

void my_free(void* ptr) {
    int i;
    for (i = 0; i < block_count; i++) {
        if (blocks[i].memory == ptr) {
            printf("Freed block at memory address: %p\n", ptr);
            blocks[i].index = -1;
            break;
        }
    }
}

void printRegionContents() {
    int i;
    for (i = 0; i < block_count; i++) {
        printf("block %d: ", i);
        int j;
        for (j = 0; j < blocks[i].size; j++) {
            if (blocks[i].index == 1) {
                printf("%c", blocks[i].memory[j]);
            }
            else {
                printf("-");
            }
        }
        printf(" status: %d\n", blocks[i].index);
    }
}

int main() {
    // Allocate some memory
    char* ptr1 = (char*)my_alloc(ONEBLOCK * 2);
    memset(ptr1, 'A', ONEBLOCK * 2);
    char* ptr2 = (char*)my_alloc(ONEBLOCK * 3);
    memset(ptr2, 'G', ONEBLOCK * 3);
    char* ptr3 = (char*)my_alloc(ONEBLOCK * 2);
    memset(ptr3, 'O', ONEBLOCK * 2);
    // Free some memory
    my_free(ptr1);
    // Print region contents
    printRegionContents();
    return 0;
}
