/* \todo[inline]{Lab2 Select Function}
*/
/*
\begin{alltt}
\textcolor{red}{ The select function was also developed in class amongst
all other students and the professor.
This function calls the previously mentioned partition function and uses
it to provide the desired results.}
\end{alltt}
\color{black} \rule{\linewidth}{0.5mm}
*/
#include <chrono>
#include <ctime>
#include <iostream>  /*\textcolor{red}{required libraries}*/
#include <algorithm>
#ifdef UNIT_TEST
#include "catch.hpp"
#endif
using namespace std::chrono;


/*
Function declaration for partition.
*/
int partition(int a[], int lower, int upper, int pivot_idx);


/*
\begin{alltt}
\textcolor{red}{In the previous lab, documentation for select was not as
good as it should be. So, before moving on to the function itself i would
like to share some visual aid that could help understand the select function
better.In the previous lab, our select was not working due to having extra 
variables that were just not being used. After getting rid of them, we are 
only left with p, k and b.
\includegraphics[scale=0.6]{gdb1}
At the begining, these are the current values of p, k and b.
K < P = true so, it should call select again recursively.
\includegraphics[scale=0.6]{gdb2}
K < P = true so, it should call select again recursively.
\includegraphics[scale=0.6]{gdb3}
K < P = false, so it should go to the next line which is 
else if(k > p) select(arr, k, p+1, b);
\includegraphics[scale=0.6]{gdb4}
It keeps on looping through those lines until it reaches base case,
when it reaches base case, its eventually going to return arr[p].
I did not demonstrate all the screenshots for all the operations as that
would be too much. This screen shot is that when it reaches base case. After
it keeps reaching base from every call made the previous stack, eventually it
will return the median.
}
\end{alltt}
*/
int select(int arr[], int k, int a, int b)
{
	int p = partition(arr,a,b,k);
	int n1 = p - a;    
	int n2 = 1;        
	int n3 = b - (n1 + n2);    
	if(k < p) select(arr, k, 0, p);  /*\textcolor{red}{recursive step}*/
	else if(k > p) select(arr, k, p+1, b);
	else return arr[p]; //base case
}

/*\newpage
\textcolor{red}{Following is the code that the quicksort algorithm uses. For this lab,
no documentation is required for the quicksort function.}*/
	int quick_partition(int a[], int from, int to)
{
    int pivot = a[from];
    int i = from - 1;    int j = to + 1;
    while (i < j)
    {
        i++; while (a[i] < pivot) { i++; }
        j--; while (a[j] > pivot) { j--; }
        if (i < j) { std::swap(a[i], a[j]); }
    }
    return j;
}


void quicksort(int a[], int from, int to)
{
    if (from >= to) { return; }
    int p = quick_partition(a, from, to);
    quicksort(a, from, p);
    quicksort(a, p + 1, to);
}

/*\pagebreak*/
#ifdef UNIT_TEST
/*\textcolor{red}{Test case "Select." This test case calls the selet function and checks
if the values are accurate and if select actually calculated the median.}*/
TEST_CASE("Select")
{
	const int n = 1000000;
	int a[n];
	for(int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	std::random_shuffle(a, a+n);
	
	
	REQUIRE(select(a,n/2,0,n)==n/2);
}
#endif
/*\pagebreak*/
/*\textcolor{red}{Test case "quick." This test case calls the quicksort
function given to us by the instructor.}*/

TEST_CASE("quick")
{
	const int f = 1000000;
	int a[f];
	for(int i = 0; i < f; i++)
	{
		a[i] = i;
	}
	std::random_shuffle(a, a+f);
	
	
	quicksort(a,0,f-1);
	REQUIRE(a[f/2]==f/2);

}
/*\pagebreak*/
/*\textcolor{red}{Test case "sort." This test case calls the built in sort 
function.}*/

TEST_CASE("sort")
{
	const int h = 1000000;
	int c[h];
	for(int i = 0; i < h; i++)
	{
		c[i] = i;
	}
	std::random_shuffle(c, c+h);
	
	
	std::sort(c, c+h);
	REQUIRE(c[h/2]==h/2);
	
}



/*\newpage
*/


/*
\begin{alltt}\textcolor{red}{This is the main and last part of our program. Our main
goal in this program was to test the speed of the three algorithms. The following
pictures show how the built-in sort() is s lower than the quicksort algorithm. But
the fastest one is still select. Even though select is the fastest algorith in here
I am still not sure if it is a good comparison because the other two algorithms
are sorting a list while select is just finding the median of a list, so I am not
sure if this is a valid comparison.}

QUICKSORT TIME
\includegraphics[scale=0.6]{quick}
BUILT-IN SORT FUNCTION TIME
\includegraphics[scale=0.6]{sort}
\pagebreak
SELECT TIME
\includegraphics[scale=0.6]{select}

Also, I have a request for the next lab. I personally feel that the next
lab should not be based upon this lab at all. I feel that is a better way
for students to comprehend the code better. We are moving onto new topics
and that should reflect in our codes.
\end{alltt}
*/
