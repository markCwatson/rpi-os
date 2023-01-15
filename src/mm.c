#include "mm.h"

static uint16_t mem_map[PAGING_PAGES] = {0,};

void* mm_get_free_page(void) {
    for (uint64_t i = 0; i < PAGING_PAGES; i++){
        if (mem_map[i] == 0){
            mem_map[i] = 1;
            return (void *)(LOW_MEMORY + (i * PAGE_SIZE));
        }
    }

    return 0;
}

void mm_free_page(void *p) {
    uint64_t page_num = (((uint64_t)p) - LOW_MEMORY) / PAGE_SIZE; 
    mem_map[page_num] = 0;
}
