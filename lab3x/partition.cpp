/*
\begin{alltt} 
\textcolor{red}{Purpose - The purpose of this lab is to use the previous
lab and improve upon the documentation. In order to increase the quality
of the documentation the students are advised t ouse some sort of visual
aid, for my visual aid, I chose to use the "gdb" debugger.Lab 2 dove  
into the topic of data structures and algorithms by introducing concepts
revolving around how much time an algorithm takes compareed to another.
After making changes to Lab2 and improving it, we will now compare the 
time taken by select, quicksort and the built in sort function. 

The students were provided the logic by the professor. Students and the
professor followed the directions giiven by the author regarding the
partition and select function.

After fixing both the functions, the student is expected to compare
the algorithm by a built in sorting function in the algorithm library and
the quicksort algorithm provided in the book.

The comparision should demonstrate which algorithm took the most time.}
\end{alltt}
\color{black} \rule{\linewidth}{0.5mm} 
\pagebreak
*/


/* \todo[inline]{Lab2 Partition } */
/* \begin{alltt}
\textcolor{red}{Partition Function 
This is the begining of partition function. The logic followed by the 
function is the one provided to us by the instructor.

The function takes in four parameters.
@param --> array on integers
@param --> lower value [left most value in the begining.]
@param --> upper value [right most value in the begining.]
@param --> pivotidx [the position of our pivot.]}

\color{black} \rule{\linewidth}{0.5mm} 
\end{alltt}
*/

#include <iostream>
#include "catch.hpp"
#include <algorithm>


int partition(int a[], int lower, int upper, int pivot_idx)
{
	int left = lower; int right = upper-2;
	
	int pivot = a[pivot_idx];
	/*\textcolor{red}{we want the pivot o be 16, so we set the pivot to a[7]}*/
	std::swap(a[pivot_idx], a[upper-1]);
	/*\textcolor{red}{swap the pivot value and the end of the array to make it easier 
	for comparsion}*/
	
	while(left <= right)
	{
		if(a[left] <= pivot) left++;
		else {std::swap(a[left], a[right]); right--;}
		/*\textcolor{red}{putting all the values less than the pivot to the left of the 
		array and the higher values to the right.}*/
	}
	std::swap(a[left], a[upper-1]);
	/*\textcolor{red}{now we know where to put the pivot value so we swap it with the
	value at "left" index.}*/
	return left;
}

