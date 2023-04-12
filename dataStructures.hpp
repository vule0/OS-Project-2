#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <deque>

// sets up Page structure for pageTable (vector of Page*)
struct Page{
    unsigned FrameNum;
    int DirtyBit;
    Page(unsigned FrameNum){
        this->FrameNum = FrameNum;
        this->DirtyBit = 0;
    }

};

//function to search for pages in PageTable (for FIFO, which uses deque pageTable)
int searchPageTable(std::deque<Page*> PageTable, unsigned int pageNum){
    for (unsigned int i = 0; i < PageTable.size(); i++){
        if (PageTable[i]->FrameNum == pageNum){
            return 1;
        }
    }
    return 0;
}

//function to search for pages in PageTable (for LRU and VMS, which uses vector pageTable)
int searchPageTable(std::vector<Page*> PageTable, unsigned int pageNum){
    for (unsigned int i = 0; i < PageTable.size(); i++){
        if (PageTable[i]->FrameNum == pageNum){
            return 1;
        }
    }
    return 0;
}

//obtains page number by shifting address bits
unsigned int convertAddress(unsigned addr){
    return (addr >> 12);
}

#endif