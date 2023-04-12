#ifndef FIFO_H
#define FIFO_H
#include "dataStructures.hpp"

void fifo(FILE* fp, int nframes, int debug){
    //inputs address and read/write bits and counters
    unsigned int addr;
    char rw;
    int reads = 0, writes = 0, traces = 0;
    std::deque<Page*> pageTable;
    while (!feof(fp)){
        fscanf(fp, "%x %c", &addr, &rw);
        traces++;

        int read_write = 0;
        //determine read_write bit by conversion into 1/0
        if (toupper(rw) == 'W'){
            read_write = 1;
        }
        else if (toupper(rw) == 'R'){
            read_write = 0;
        }
        else{
            if (debug){
                std::cout << "Read/Write not found " << rw << std::endl;
            }
        }
        //get pageNum from address and search pageTable
        unsigned int pageNum = convertAddress(addr);
        int found = searchPageTable(pageTable, pageNum);

        if (found && debug){
            std::cout << "Page Hit for: " << pageNum << std::endl;

        }
        // Page Hit: update W bit if necessary
        if (found){
            if (read_write){
                for (unsigned int i = 0; i < pageTable.size(); i++){
                    if (pageTable[i]->FrameNum == pageNum){
                        pageTable[i]->DirtyBit = 1;
                        break;
                    }
                }
            }
        }
        else{
            // Page fault
            if (debug){
                std::cout << "Page Fault for: " << pageNum << std::endl;
            }
            Page* newPage = new Page(pageNum);
            reads++;
            if (read_write){
                newPage->DirtyBit = 1;
            }

            // create newPage and insert into table
            // if pageTable is full, pop front and insert newPage into back. else, insert newPage into back
            if (pageTable.size() >= unsigned(nframes)){
                if(pageTable.front()->DirtyBit){
                    writes++;
                }
                pageTable.pop_front();
            }
            pageTable.push_back(newPage);
        }
    }

    std::cout << "Memory Frames: " << nframes << std::endl;
    std::cout << "Trace Count: " << --traces << std::endl;
    std::cout << "Read Count: " << reads << std::endl;
    std::cout << "Write Count: " << writes << std::endl;
}

#endif