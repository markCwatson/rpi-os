#include "mm.h"

// ARM GNU defines unsigned short as 16 bits
static unsigned short mem_map[PAGING_PAGES] = {0,};

// ARM GNU defines unsigned long as 32 bits
unsigned long mm_get_free_page(void) {
    for (int i = 0; i < PAGING_PAGES; i++){
        if (mem_map[i] == 0){
            mem_map[i] = 1;
            return LOW_MEMORY + i * PAGE_SIZE;
        }
    }

    return 0;
}

void mm_free_page(unsigned long p) {
    mem_map[(p - LOW_MEMORY) / PAGE_SIZE] = 0;
}
