/* \todo[inline]{Lab2 Select Function}
\includegraphics[scale=0.6]{select.png}
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

*/
int select(int arr[], int k, int a, int b)
{
	int p = partition(arr,a,b,k);
	int n1 = p - a;    
	int n2 = 1;        
	int n3 = b - (n1 + n2);    
	CHECK(n1+n2+n3 == b);
	if(k < n1) select(arr, k, 0, n1);  /*\textcolor{red}{recursive step}*/
	else if(k > n1 + n2) select(arr, k, n1+n2, b);
	else return arr[p]; //base case
}
#ifdef UNIT_TEST

TEST_CASE("Select")
{
	const int n = 10;
	int a[n] = {2, 87, 21, 3, 12, 78, 97, 16, 89, 20};
	/* \textcolor{red}{{2, 12, 3, 16, 78, 97, 21, 89, 87, 21} == 21}*/
	REQUIRE(select(a,n/2,0,n)==20);
	const int m = 14; int b[m];
	for(int i = 0;i<m;i++) b[i] = i;
	std::random_shuffle(b, b+m);
	REQUIRE(select(a,m/2,0,m)==m/2);
}


TEST_CASE("time")
{
	const int size = 10;
	int pivot_index = size / 2;
	/* \textcolor{red}{int array[size], brray[size];} */
	int c[size] = {2, 87, 21, 3, 12, 78, 97, 16, 89, 21};
	int d[size] = {2, 12, 3, 16, 78, 97, 21, 89, 87, 21};
	/* \textcolor{red}{median of {2, 3, 12, 16, 21, 78, 89, 97} == 21} */
	int N = sizeof(c)/sizeof(int); 
	int lower = 0;
	int upper = N;
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	REQUIRE(select(c, N/2, 0, N) == 21); /*\textcolor{red}{return the median}*/
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	

	duration<double> selectTimeSpan = duration_cast<duration<double>>(t2 - t1);

	std::cout << "select() took " << selectTimeSpan.count() << " seconds.";
	std::cout << std::endl;
	
	
	/* \textcolor{red}{use sort()}*/
	high_resolution_clock::time_point t3 = high_resolution_clock::now();

	std::sort(d,d+N); /* \textcolor{red}{range [0,n]} */
	REQUIRE(d[N/2] == 21);
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	duration<double> sortTimeSpan = duration_cast<duration<double>>(t4 - t3);

	std::cout << "sort() took " << sortTimeSpan.count() << " seconds.";
	std::cout << std::endl;
	
	std::cout << "selectTimeSpan - sortTimeSpan = " 
			<< (selectTimeSpan.count() - sortTimeSpan.count()) << " seconds.";
	std::cout << std::endl;
	
}

/* 
\newpage
\textcolor{red}{This the Catch2 for our comparison. The catch test cases
make sure that the values resulting are right before they get passed onto
the next lines.}
\VerbatimInput{finalres}
\newpage
*/
#endif

/*
\begin{alltt}\textcolor{red}{This is the main and last part of our program. Our main
goal in this program was to test the speed of two algorithms. The following
picture shows how the built-in sort() is faster than the algorithm our
class came up with. Hence, the lab is complete.}

\includegraphics[scale=0.5]{comparison}
\end{alltt}
*/
