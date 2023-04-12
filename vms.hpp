#ifndef VMS_H
#define VMS_H
#include "dataStructures.hpp"


void segmented_fifo(FILE* fp, int nframes, int debug, int percentage){
    //inputs address and read/write bits and counters
    unsigned int addr;
    char rw;
    int reads = 0, writes = 0, traces = 0;

    // calculating size of primaryCache and secondaryCache depending on input percentage
    unsigned int secondarySize = ((nframes * percentage) / 100);
    unsigned int primarySize = nframes - secondarySize;

    //Edge Cases: if FIFO cache = 0 -> run LRU
                //if LRU cache = 0 -> run FIFO
    if (primarySize == 0){
        lru(fp, nframes, debug);
        return;
    }
    if (secondarySize == 0){
        fifo(fp, nframes, debug);
        return;
    }

    std::vector<Page*> primaryCache;
    std::vector<Page*> secondaryCache;

    while (!feof(fp)){
        fscanf(fp, "%x %c", &addr, &rw);
        traces++;

        int read_write = 0;
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
        //get pageNum from address and search both pageTables
        unsigned int pageNum = convertAddress(addr);
        int foundPrimary = searchPageTable(primaryCache, pageNum);
        int foundSecondary = searchPageTable(secondaryCache, pageNum);
        if (debug && foundPrimary){
            std::cout << "Page hit in Primary Cache for: " << pageNum << std::endl;
        }
        if (debug && foundSecondary){
            std::cout << "Page hit in Secondary Cache for: " << pageNum << std::endl;
        }   


        // Page Hit in FIFO: update W bit
        if (foundPrimary){
            if (read_write){
                for (unsigned int i = 0; i < primaryCache.size(); i++){
                    if (primaryCache[i]->FrameNum == pageNum){
                        primaryCache[i]->DirtyBit = 1;
                        break;
                    }
                }
            }
        }
        // Page Hit in LRU (FIFO is FULL): update W bit, move LRU page to back of FIFO, and move front of FIFO into LRU
        else if (foundSecondary){
                for (unsigned int i = 0; i < secondaryCache.size(); i++){
                    if (secondaryCache[i]->FrameNum == pageNum){
                        Page* LRUPage = secondaryCache[i];
                        if (read_write){
                            LRUPage->DirtyBit = 1;
                        }
                        secondaryCache.erase(secondaryCache.begin() + i);
                        primaryCache.push_back(LRUPage);
                        Page* frontFIFO = primaryCache.front();
                        primaryCache.erase(primaryCache.begin());
                        secondaryCache.push_back(frontFIFO);
                    break;
                    }
                }
        }
        //Page Faults
        else{
            if (debug){
                std::cout << "Page Fault for: " << pageNum << std::endl;
            }
            // create newPage and update dirtybit
            Page* newPage = new Page(pageNum);
            if (read_write){
                newPage->DirtyBit = 1;
            }
            reads++;
            // not in FIFO, and FIFO is NOT full: push into FIFO
            if (primaryCache.size() < primarySize){
                primaryCache.push_back(newPage);
            }
            // not in FIFO, and FIFO IS full + LRU is NOT full: move front of FIFO into LRU and insert newPage into FIFO
            else if (secondaryCache.size() < secondarySize){
                Page* frontFIFO = primaryCache.front();
                primaryCache.erase(primaryCache.begin());
                primaryCache.push_back(newPage);
                secondaryCache.push_back(frontFIFO);
            }
            // both caches are full: remove front of LRU, move front of FIFO into LRU, add newPage into FIFO
            else if (primaryCache.size() >= primarySize && secondaryCache.size() >= secondarySize){
                Page* oldestLRU = secondaryCache.front();
                Page* frontFIFO = primaryCache.front();
                primaryCache.erase(primaryCache.begin());
                primaryCache.push_back(newPage);
                if (oldestLRU->DirtyBit){
                    writes++;
                }
                secondaryCache.erase(secondaryCache.begin());
                secondaryCache.push_back(frontFIFO);
            }
            else{
                std::cout << " Error finding page\n";
            }
        }
    }
    std::cout << "Memory Frames: " << nframes << std::endl;
    std::cout << "Trace Count: " << --traces << std::endl;
    std::cout << "Read Count: " << reads << std::endl;
    std::cout << "Write Count: " << writes << std::endl;
}

#endif