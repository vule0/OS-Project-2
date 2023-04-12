Operating Systems Project 2 - Vu Le (U43500182)
This program reads in memory traces and performs a specified page replacement algorithm. 

To run this algorithm, type "make" in console. (If this doesn't work, try "g++ *.cpp -Wall -std=c++11")
Then, follow the format: "./memsim (trace file) (numberframes) (fifo/lru/vms) (debug/quiet)"

The first argument (trace file) determines which trace file to use. In this case, we use either bzip.trace or sixpack.trace
The second argument (numberframes) determines how many frames are in memory.
The third argument (fifo/lru/vms) determines which algorithm to run.
The fourth argument (debug/quiet) specifies which mode to run the program in. The debug option will output Page Hit or Page Fault at each memory trace. The quiet option will run silently
and output the results at the end.

If the third argument is vms, then the program requires another input. 
The format for vms should follow: "./memsim (trace file) (numberframes) (fifo/lru/vms) (percentage) (debug/quiet)"
The (percentage) argument specifies the percentage of the total program memory to be used in the secondary buffer.

