/*
\begin{alltt} 
\textcolor{red}{Purpose - The purpose of this lab is to get the studenta familiar
with some more advanced concepts regarding data structures. Lab 1 
introduced them to the tools that they wer going to be using throughout
this course, this lab however, dives into the topic of data structures
and algorithms by introducing concepts revolving around how much time
an algorithm takes compareed to another. 

The students were provided the logic by the professor. Students and the
professor followed the directions giiven by the author regarding the
partition and select function.

After making both the functions, the student is expected to compare
the algorithm by a built in sorting function in the algorithm library.

The comparision should demonstrate which algorithm sorted the array faster.}
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
	int pivot = a[pivot_idx]; int left = lower; int right = upper-2;
	std::swap(a[pivot_idx], a[upper-1]);
	
	while(left <= right)
	{
		if(a[left] <= pivot) left++;
		else {std::swap(a[left], a[right]); right--;}
	}
	std::swap(a[left], a[upper-1]);
	return left;
}

