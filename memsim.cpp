#include "dataStructures.hpp"
#include "fifo.hpp"
#include "lru.hpp"
#include "vms.hpp"

int main(int argc, char* argv[]){
    // opening trace file
    FILE *fp = fopen(argv[1], "r");
    if (!fp){
        std::cout << "Error opening file!\n";
        return -1;
    }
    // reading variables from command line such as number of frames, specified algorithm, and debug input
    int numframes = atoi(argv[2]);
    char* algorithm = argv[3];
    for (int i = 0; algorithm[i] != '\0'; i++){
        algorithm[i] = tolower(algorithm[i]);
    }

    int debug = 0;
    //selection for fifo
    if (strcmp(algorithm, "fifo") == 0){
        char* debug_input = argv[4];
        if (strcmp(debug_input, "debug") == 0){
            debug = 1;
        }
        fifo(fp, numframes, debug);
        fclose(fp);
    }
    //selection for lru
    if (strcmp(algorithm, "lru") == 0){
        char* debug_input = argv[4];
        if (strcmp(debug_input, "debug") == 0){
            debug = 1;
        }
        lru(fp, numframes, debug);
        fclose(fp);
    }
    //selection for vms (requires percentage input)
    if (strcmp(algorithm, "vms") == 0){
        int percentage = atoi(argv[4]);
        char* debug_input = argv[5];
        if (strcmp(debug_input, "debug") == 0){
            debug = 1;
        }
        segmented_fifo(fp, numframes, debug, percentage);
        fclose(fp);
    }
    return 1;
}