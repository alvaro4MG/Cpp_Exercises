/*Álvaro Martínez García, 48150407E
ADA. 2021-22
Práctica 2:"Empirical analysis by means of program-steps account of two sorting algorithms: Middle-Quicksort and Heapsort."
*/
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <iomanip>

double pasos=0;

using namespace std;

void checkVector(int *v,size_t size){
    for (size_t i = 1; i < size; i++)
        if (v[i] < v[i-1]){ 
            cerr << "Panic, array not sorted! " << i << endl;
            exit(EXIT_FAILURE);            
        }
}

//--------------------------------------------------------------
// Middle Quick Sort
void 
middle_QuickSort(int * v, long left, long right){
    long i,j;
    int pivot; 

    
	if (left<right){
        
		i=left; j=right;
		pivot=v[(i+j)/2];
		do{
			while (v[i]<pivot){ i++; pasos++;}             //Contar estos
			while (v[j]>pivot){ j--; pasos++;}
			if (i<=j){ 
				swap(v[i], v[j]);
				i++; j--;                           //Contar estos también, solo como un paso
                pasos++;
			}
		}while (i<=j);
		if (left < j)  middle_QuickSort(v,left,j);
		if (i < right) middle_QuickSort(v,i,right);
	}
}

//--------------------------------------------------------------                
//HEAPSORT
// Procedure sink used by Heapsort algorith
// Sink an element (indexed by i) in a tree to keep the heap property. n is the size of the heap. 

void sink(int *v, size_t n, size_t i)
{
size_t largest;
size_t l, r; //left and right child
pasos++;

do{
    largest = i;  // Initialize largest as root
    l = 2*i + 1;  // left = 2*i + 1
    r = 2*i + 2;  // right = 2*i + 2
 
    // Is left child larger than root?
    if (l < n && v[l] > v[largest])
        largest = l;
 
    // Is right child larger than largest so far
    if (r < n && v[r] > v[largest])
        largest = r;
 
    // If largest is still root then the process is done
    if (largest == i) break;
    
	// If not, swap new largest with current node i and repeat the process with childs. 
    swap(v[i], v[largest]);
    i=largest;  
    pasos++;
   } while (true);
}
 
//--------------------------------------------------------------                
// Heapsort algorithm (ascending sorting)
void heapSort(int *v, size_t n)
{
    // Build a MAX-HEAP with the input array
    for (size_t i = n / 2 - 1; true; i--){            //quitamos i>=0 y ponemos true, ya sale del bucle cuando if(i==0) y así no da error
        sink(v, n, i);
        pasos++;
        if (i==0) break; //as size_t is unsigned type
	}	

  	// A this point we have a HEAP on the input array, let's take advantage of this to sort the array:
    // One by swap the first element, which is the largest (max-heap), with the last element of the vector and rebuild heap by sinking the new placed element on the begin of vector.  
    for (size_t i=n-1; i>0; i--)
    {
        
		// Move current root to the end.
        swap(v[0], v[i]);
 		// Now largest element is at the end but do not know if the element just moved to the beginning is well placed, so a sink process is required.
		// Note that, at the same time, the HEAP size is reduced one element by one.
        sink(v, i, 0);
        pasos++;
		// The procedure ends when HEAP has only one element, the lower of the input array
    }
}

//------------------------------------------------------------------------------------
int
main(void){

    srand(getpid());
    float promedioQuick=0,promedioHeap=0;
    
    cout << "# QUICKSORT VERSUS HEAPSORT"
        << endl
        << "# Average processing Msteps (millions of program steps)"
        << endl
        << "# Number of samples (arrays of integer): 30"
        << endl
        << endl
        << "# \t\t RANDOM ARRAYS \t\t\t SORTED ARRAYS \t\t\t REVERSE SORTED ARRAYS"
        << endl
        << "# \t\t -------------------------- \t -------------------------- \t ------------------------"
        << endl
        << "# Size \t\t Quicksort \t Heapsort \t Quicksort \t Heapsort \t Quicksort \t Heapsort"
        << endl
        << "# ======================================================================================================="
        << endl;

    for (int exp = 15; exp <= 20; exp++){           //tamaños cambiados para potencias de 2 entre 15 y 20
        size_t size = size_t( pow(2,exp) );
        int* v = new int [size];
        int* w = new int [size];

        cout << size << "\t\t" << flush;
        
        if (!v){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }


        for(int k=0;k<30;k++){

            for (size_t j = 0; j < size; j++){
                v[j] = rand();
                w[j] = v[j];
            }

            //hacer auxiliar de v antes de ordenarlo
            pasos=0;
            middle_QuickSort(v, 0, size-1);
            checkVector(v,size);
            promedioQuick+= pasos / 1000000;
            pasos=0;


            heapSort(w, size);
            checkVector(w,size);
            promedioHeap+= pasos / 1000000;
            pasos=0;

        }
        
        cout << setprecision(3)<<promedioQuick/30 << "\t\t" << promedioHeap/30<<"\t\t";
        promedioQuick=0;
        promedioHeap=0;

        //ahora con vector ordenado
        checkVector(v,size);
        middle_QuickSort(v, 0, size);    
        checkVector(v,size);
        promedioQuick+= pasos / 1000000;
        pasos=0;

        heapSort(v, size);
        checkVector(v,size);
        promedioHeap+= pasos / 1000000;
        pasos=0;

        cout << promedioQuick << "\t\t" << promedioHeap<<" \t\t";
        promedioQuick=0;
        promedioHeap=0;

        //ahora con vector del revés
        for(unsigned int i=0;i<size/2;i++){
            swap(v[i],v[(size-1)-i]);
            swap(w[i],w[(size-1)-i]);
        }

        middle_QuickSort(v, 0, size);
        checkVector(v,size);
        promedioQuick+= pasos / 1000000;
        pasos=0;

        heapSort(w, size);
        checkVector(w,size);
        promedioHeap+= pasos / 1000000;
        pasos=0;

        cout << promedioQuick << "\t\t" << promedioHeap<<endl;
        promedioQuick=0;
        promedioHeap=0;

        delete[] v;
        delete[] w;

    }

}