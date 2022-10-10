// C++ program to implement
// external sorting using
// merge sort
#include <bits/stdc++.h>
// #include <execution>

using namespace std;

class SuffixArray{
public:
    int *sa; //store size(int)  sa[0]: size sa[-2]: docid sa[-1]: pos
    SuffixArray() {}
    SuffixArray(int max_value){
        sa = new int [5];
        sa[0] = 4;
        for (int i = 1; i < 5; i++){
            sa[i] = max_value;
        }
    }
    /*
    ~SuffixArray() {
        delete []sa ;
    }
    */
    void loadData(ifstream &ifs){
        int size = 0;
        ifs.read((char*)&size, sizeof(int));
        cout << "current size is: " << size << endl;
        sa = new int [size + 1];
        sa[0] = size;
        ifs.read((char*)&sa[1], size * sizeof(int));
    }
    bool operator <(const SuffixArray& suff)const{
        int min_len = min(sa[0], suff.sa[0]);
        for (int i = 1; i < min_len + 1 - 2; i++){
            if (sa[i] < suff.sa[i]){
                return true;
            } else if (sa[i] > suff.sa[i]){
                return false;
            }
        }
        return sa[0] < suff.sa[0];
    }
};


class ExternalSort {
public:
    SuffixArray SA_MAX;
    ExternalSort() {
    }
    ExternalSort(SuffixArray _SAMAX) {
        SA_MAX = _SAMAX;
    }
    /*
    T T_MAX;
    ExternalSort() {
    }
    ExternalSort(T _TMAX) {
        T_MAX = _TMAX;
    }
    */

public:
    struct MinHeapNode {
        // The element to be stored
        SuffixArray element;

        // index of the array from which
        // the element is taken
        int i;
    };

    // A class for Min Heap
    class MinHeap {
        // pointer to array of elements in heap
        MinHeapNode *harr;

        // size of min heap
        int heap_size;

    public:
        // Constructor: creates a min
        // heap of given size
        // Constructor: Builds a heap from
        // a given array a[] of given size
        MinHeap(MinHeapNode a[], int size) {
            heap_size = size;
            harr = a; // store address of array
            int i = (heap_size - 1) / 2;
            while (i >= 0) {
                MinHeapify(i);
                i--;
            }
        }

        // Prototype of a utility function
        // to swap two min heap nodes
        void swap(MinHeapNode *x, MinHeapNode *y) {
            MinHeapNode temp = *x;
            *x = *y;
            *y = temp;
        }

        // to heapify a subtree with
        // root at given index
        // A recursive method to heapify
        // a subtree with root
        // at given index. This method
        // assumes that the
        // subtrees are already heapified
        void MinHeapify(int i) {
            int l = left(i);
            int r = right(i);
            int smallest = i;

            if (l < heap_size && harr[l].element < harr[i].element)
                smallest = l;

            if (r < heap_size
                && harr[r].element < harr[smallest].element)
                smallest = r;

            if (smallest != i) {
                swap(&harr[i], &harr[smallest]);
                MinHeapify(smallest);
            }
        }

        // to get index of left child
        // of node at index i
        int left(int i) {
            return (2 * i + 1);
        }

        // to get index of right child
        // of node at index i
        int right(int i) {
            return (2 * i + 2);
        }

        // to get the root
        MinHeapNode getMin() {
            return harr[0];
        }

        // to replace root with new node
        // x and heapify() new root
        void replaceMin(MinHeapNode x) {
            harr[0] = x;
            MinHeapify(0);
        }
    };
    /*
    // Merges two subarrays of arr[].
    // First subarray is arr[l..m]
    // Second subarray is arr[m+1..r]
    void merge(SuffixArray arr[], int l, int m, int r) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;

        // create temp arrays 
        SuffixArray L[n1];
        SuffixArray R[n2];

        // Copy data to temp arrays L[] and R[] 
        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        // Merge the temp arrays back into arr[l..r]
        // Initial index of first subarray
        i = 0;

        // Initial index of second subarray
        j = 0;

        // Initial index of merged subarray
        k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j])
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }

        // Copy the remaining elements of L[], if there are any

        while (i < n1)
            arr[k++] = L[i++];

        // Copy the remaining elements of R[], if there are any
        while (j < n2)
            arr[k++] = R[j++];
    }
    */

    /* l is for left index and r is right index of the
       sub-array of arr to be sorted */
    
    /*
    void mergeSort(SuffixArray arr[], int l, int r) {
        if (l < r) {
            // Same as (l+r)/2, but avoids overflow for
            // large l and h
            int m = l + (r - l) / 2;

            // Sort first and second halves
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);

            merge(arr, l, m, r);
        }
    }
    */
    // Merges k sorted files. Names of files are assumed
    // to be 1, 2, 3, ... k
    void mergeFiles(char *output_file, int n, int k) {
        ifstream in[k];
        for (int i = 0; i < k; i++) {
            string fileName = "./temp/" + to_string(i);

            // convert i to string
            //snprintf(fileName, sizeof(fileName), "./template/%d", i);

            // Open output files in read mode.

            in[i] = ifstream(fileName, ios::in | ios::binary);
        }

        // FINAL OUTPUT FILE
        ofstream out(output_file, ios::out | ios::binary);

        // Create a min heap with k heap
        // nodes. Every heap node
        // has first element of scratch
        // output file
        MinHeapNode *harr = new MinHeapNode[k];
        int i;
        for (i = 0; i < k; i++) {
            // break if no output file is empty and
            // index i will be no. of input files
            if (in[i].eof()) {
                break;
            }
            harr[i].element.loadData(in[i]);
            //in[i].read((char *)&harr[i].element, sizeof(T));

            // Index of scratch output file
            harr[i].i = i;
        }
        // Create the heap
        MinHeap hp(harr, i);

        int count = 0;

        // Now one by one get the
        // minimum element from min
        // heap and replace it with
        // next element.
        // run till all filled input
        // files reach EOF
        while (count != i) {
            // Get the minimum element
            // and store it in output file
            MinHeapNode root = hp.getMin();
            int size = root.element.sa[0] + 1;
            out.write((char *)&root.element.sa[0], size * sizeof(int));
            //out.write((char *)&root.element, sizeof(T));

            // Find the next element that
            // will replace current
            // root of heap. The next element
            // belongs to same
            // input file as the current min element.
            if (in[root.i].peek() == EOF) {
                root.element = SA_MAX;
                count++;
            } else {
                cout << "current root i is: " << root.i << endl;
                root.element.loadData(in[root.i]);
                //in[root.i].read((char *)&root.element, sizeof(T));
            }

            // Replace root with next
            // element of input file
            hp.replaceMin(root);
        }

        // close input and output files
        for (int i = 0; i < k; i++)
            in[i].close();

        out.close();
    }
    //suffix array structure: size(uint16_t) suffix array(vector<uint16_t>) , docid(uint16_t) 
    /*
    void loadSuffixArray(ifstream &ifs, int run_size, T *arr){
        for (int i = 0; i < run_size){
            uint16_t size;
            //load size
            ifs.read(&size, sizeof(uint16_t));
            arr[i].sa = new uint16_t [size + 1];
            arr[i].sa[0] = size;
            cout << "current suffix array size is: " << size << endl;
            //load array
            ifs.read(&arr[i][0], size * sizeof(uint16_t));
            for (int j = 0; j < arr[j].size(); j++){
                cout << arr[i][j] << ", ";
            }
        }
    }
    */
    // Using a merge-sort algorithm,
    // create the initial runs
    // and divide them evenly among
    // the output files
    void createInitialRuns(char *input_file, int run_size, int num_ways) {
        ifstream inFile(input_file, ios::in | ios::binary); //二进制读方式打开


        ofstream out[num_ways];

        for (int i = 0; i < num_ways; i++) {
            string fileName = "./temp/" + to_string(i);

            out[i] = ofstream(fileName, ios::out | ios::binary);
        }

        
        SuffixArray *arr = new SuffixArray[run_size];

        bool eof = false;
        int next_output_file = 0;

        int i;
        while (!eof) {
            // write run_size elements
            // into arr from input file
            for (i = 0; i < run_size; i++) {
                // judge if coming eof
                eof = (inFile.peek() == EOF);
                if (eof == true) {
                    cout << "out" << endl;
                    break;
                }
                arr[i].loadData(inFile);
                //inFile.read((char *)&arr[i], sizeof(T));
            }

            printf("sort part: ");
            cout << "sort " << endl;
            cout << i << endl;
            assert(i == run_size);
            // sort array using merge sort
            // mergeSort(arr, 0, i - 1);
            sort(arr,arr+i);
            // sort(std::execution::par_unseq, arr, arr + i);

            // write the records to the
            // appropriate scratch output file
            // can't assume that the loop
            // runs to run_size
            // since the last run's length
            // may be less than run_size
            for (int j = 0; j < i; j++) {
                out[next_output_file].write((char *)&(arr[j].sa[0]), (arr[j].sa[0] + 1) * sizeof(int));
            }
            eof = (inFile.peek() == EOF);
            if (eof == true) {
                cout << "out" << endl;
                break;
            }

            cout << next_output_file << endl;
            next_output_file++;
        }

        // close input and output files
        for (int i = 0; i < num_ways; i++)
            out[i].close();

        inFile.close();
    }

    // For sorting data stored on disk 
    //modify here
    void externalSort(char *input_file, char *output_file, int num_ways, int run_size) {
        // read the input file,
        // create the initial runs,
        // and assign the runs to
        // the scratch output files
        printf("------------------creating InitialRuns------------------\n");

        createInitialRuns(input_file, run_size, num_ways);
        printf("------------------merging Files------------------\n");
        // Merge the runs using
        // the K-way merging
        mergeFiles(output_file, run_size, num_ways);
    }
};