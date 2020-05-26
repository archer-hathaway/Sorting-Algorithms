/* This program compares the following five sort algorithms:
 *  mergesort, quick sort, select sort, and insert sort
 
 * Date: 2/15/2020
 */

#include <algorithm>   // Provides swap
#include <cstdlib>     // Provides EXIT_SUCCESS, size_t
#include <iostream>    // Provides cout
#include <ctime>       // provide clock function.
using namespace std;
const size_t ARRAY_SIZE = 10000;

// PROTOTYPES of the sorting functions used in this test program:
// Each of these functions has the same precondition and postcondition:
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].
//void heapsort(int data[], size_t n);
void mergesort(int data[], size_t n);
void quicksort(int data[], size_t n);
void selectionsort(int data[], size_t n);
void insertionsort(int data[], size_t n);
void quickSortRecursive(int data[], int begin, int end);
size_t partition(int data[], int lowerBound, int upperBound);



// PROTOTYPE of a function that will test one of the sorting functions:
void testsort(void sorter(int data[], size_t n), const char* name);


int main()
{
    cout << "This program will generate arrays with ARRAY_SIZE elements" << endl;
    cout << "Then it sorts the arrays by using different sort function and " << endl;
    cout << "displays the needed time for each sorting\n" << endl;
    cout << "Press Enter key to start test ";
    getchar();
    cout << endl;

    /*
    testsort(heapsort, "heapsort");
    cout << "Press Enter key to continue ";
    getchar();
    cout << endl;
    */

    testsort(mergesort, "mergesort");
    cout << "Press Enter key to continue ";
    getchar();
    cout << endl;

    testsort(quicksort, "quicksort");
    cout << "Press Enter key to continue ";
    getchar();
    cout << endl;

    testsort(selectionsort, "selectionsort");
    cout << "Press Enter key to continue ";
    getchar();
    cout << endl;


    testsort(insertionsort, "insertionsort");

    cout << "Press Enter key to exit ";
    getchar();

    return EXIT_SUCCESS;
}



void testsort(void sorter(int data[], size_t n), const char* name)
{
    const int    LIMIT = 10000;    // Biggest number to put in the array
    int data[ARRAY_SIZE];              // Array of integers to be sorted
    size_t count[LIMIT];               // Count of how many times each
                                       // number appears in data array
    size_t i;                          // Index for the data array.

    clock_t beginning, ending;          // the beginning and ending time to call sorter function

    cout << "Testing the " << name << endl;

    // Initialize the count array to zeros:
    fill_n(count, LIMIT, (size_t)0);

    // Fill the data array with random numbers:
    srand(0);
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        data[i] = rand() % (LIMIT);
        ++count[data[i]];
    }

    // Sort the numbers
    beginning = clock();
    sorter(data, ARRAY_SIZE);
    ending = clock();

    // Check that the data array is sorted and that it has the right
    // number of copies of each number:
    --count[data[0]];
    for (i = 1; i < ARRAY_SIZE; ++i)
    {
        if (data[i - 1] > data[i])
        {
            cout << "Incorrect sort at index " << i << endl;
            return;
        }
        --count[data[i]];
    }

    for (i = 0; i < (size_t)LIMIT; ++i)
    {
        if (count[i] != 0)
        {
            cout << "Incorrect numbers in the data array after sorting."
                << endl;
            return;
        }
    }


    cout << "Sorting completed correctly ";
    cout << "in " << (ending - beginning) / 1000.0 << " seconds\n" << endl;
}



//*************************************************************************
// HEAPSORT IMPLEMENTATION:
/* Assume that the heap data stored in array. i.e. we view the array as heap
size_t parent(size_t k)
{

}

size_t left_child(size_t k)
{

}

size_t right_child(size_t k)
{

}

// make a heap based on given data array
void make_heap(int data[], size_t n)
{

}

void reheapify_down(int data[], size_t n)
{

}

void heapsort(int data[], size_t n)
{

}
//*************************************************************************
*/


//*************************************************************************
// MERGESORT IMPLEMENTATION:
//
void merge(int data[], size_t n1, size_t n2)
// Precondition: data is an array (or subarray) with at least n1 + n2 elements.
// The first n1 elements (from data[0] to data[n1 - 1]) are sorted from
// smallest to largest, and the last n2 (from data[n1] to data[n1 + n2 - 1])
// also are sorted from smallest to largest.
// Postcondition: The first n1 + n2 elements of data have been rearranged to be
// sorted from smallest to largest.
// NOTE: If there is insufficient dynamic memory, then bad_alloc is thrown.
// Library facilities used: cstdlib
{
    int* temp;//temp that would be pointing to the dynamic array where the elements would be kept
    size_t moved = 0;//this would hold the amount of element that is moved from the data array to the temp
    size_t moved1 = 0;// with the two halves, this would hold the number moved from the first portion of the data
    size_t moved2 = 0;//allocated for the next portion of the data
    size_t i;// declared index that moves from the temp to the data array

    temp = new int[n1 + n2];//using new to create dynamic array and store in temp

    //if conditions are satisfied in the while loop, then elements are merged
    // and moved to the temp array
    while ((moved1 < n1) && (moved2 < n2))
    {
        if (data[moved1] < (data + n1)[moved2])
            temp[moved++] = data[moved1++]; //here we copy from the first portion
        else
            temp[moved++] = (data + n1)[moved2++];//copying from the second portion
    }

    //the left over elements are moved to the rightside and leftside creating subarrays
    while (moved1 < n1)
        temp[moved++] = data[moved1++];
    while (moved2 < n2)
        temp[moved++] = (data + n1)[moved2++];

    //this loop uses the index, to move from temp into the data array, freeing up the temp
    for (i = 0; i < n1 + n2; i++)
        data[i] = temp[i];
    delete[] temp;

}

void mergesort(int data[], size_t n)
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].
// NOTE: If there is insufficient dynamic memory, thenbad_alloc is thrown.
// Library facilities used: cstdlib
{
    size_t n1;//size depicting first subarray
    size_t n2;//size depicting second subarray
    if (n > 1)//as long as n is greater than 1
    {
        //get breakdown of the subarrays n1,n2
        n1 = n / 2;
        n2 = n - n1;

        mergesort(data, n1);//this sorts from the beginning index 0 to the first subarray -1
        mergesort((data + n1), n2);//this sorts from the position of n1 to the end position

        merge(data, n1, n2); //paramaters passed into function to merge both halves that have been sorted
    }
}
//*************************************************************************



//*************************************************************************
// QUICKSORT IMPLEMENTATION:
//
//*************************************************************************
/*
size_t partition(int data[], size_t n)
{

}
*/

size_t partition(int data[], int lowerBound,int upperBound)
{
    int begin, end, pivot; // declaring variables
    pivot = data[lowerBound]; //first set the element with the lower bound as the pivot
    begin = lowerBound; // store the lowerbound as in the variable > begin
    end = upperBound; // store the upperbound in the variable end
    while(begin < end)     //outer loop enters only if the begin is less than end
    {
         while(data[begin] <= pivot)//as long as the array element> begin is less than or equal to teh set pivot
         {
                 begin++; //increment begin
          }

         while (data[end] > pivot) // as long as data array holding element end is greater than pivot
         {
            end--;  //decrement the end
         }
        if(begin < end) // here begin is less than end condition
        {
            swap(data[begin] , data[end] ); // end is swapped with begin
        }

    }

    swap(data[lowerBound] , data[end] ); // if it did not enter the while loop swap end with lowerbound
    return end; // then return end

}

void	quickSortRecursive(int data[], int lowerBound, int upperBound)//recursive function passing data array,lowerbound and upperbound
{


    if (lowerBound < upperBound)//this happens when lowerbound is less than upperbound
    {
        int location; // declaring variable called location
        location = partition(data, lowerBound, upperBound);//location hold the value called by the partition function
        quickSortRecursive(data, lowerBound, location-1);//parameters inserted in recursive function calling itself
        quickSortRecursive(data, location+ 1,  upperBound);// recursive with end + 1
    }
}

void quicksort(int data[], size_t n)
{
    quickSortRecursive(data,0,n-1); // pass the parameters to the function recursively as it is called
}



//*************************************************************************
// SELECTIONSORT IMPLEMENTATION:
//
void selectionsort(int data[], size_t n)
// Library facilities used: algorithm, cstdlib
{
    int i,j;//counter
    for (i = 0; i < n - 1;i++)//outer loop to follow through with the n-1 amount of passes for the iteration
    {
        //setting minimum element by taking first element as min element.
        int min = i;   // initialized to the i value
        for (j = i + 1;j < n; j++) //inner loop increment as we compare each element in the array
        {
            //comparing preceding element with min and updating min
            if (data[j] < data[min]) //as long as it is less than the min
            {
                min = j;
            }
        }
        //check to see if the min is not equal to i then we swap the elements
        if (min != i)
            {
            swap(data[i], data[min]);
            }
    }
}
//*************************************************************************

//*************************************************************************
// INSERTION SORT IMPLEMENTATION
//
void insertionsort(int data[], size_t n)
//
{
    int i,j, temp; //declaring variables i,j and temp
    for (i=1;i<n;i++) //outer loop incrementing as the unsorted sublist exist
    {
        temp = data[i]; // temp used to store the value to compare with the sorted list in the array
        j = i - 1;   // when i = 1, j =1-1 = 0, which is the element to the left of index 1
        while (j >= 0 && data[j] > temp)//to enter inner loop both conditions have to be true
        {
            data[j + 1] = data[j];
                j--; //decrement counter to focus on sorted sublist
        }
        data[j + 1] = temp;
    }
}

/*
OUTPUT OF THE MAIN FUNCTION ;

This program will generate arrays with ARRAY_SIZE elements
Then it sorts the arrays by using different sort function and
displays the needed time for each sorting

Press Enter key to start test

Testing the mergesort
Sorting completed correctly in 0.005 seconds

Press Enter key to continue

Testing the quicksort
Sorting completed correctly in 0.004 seconds

Press Enter key to continue

Testing the selectionsort
Sorting completed correctly in 0.132 seconds

Press Enter key to continue

Testing the insertionsort
Sorting completed correctly in 0.065 seconds

Press Enter key to exit



*/
