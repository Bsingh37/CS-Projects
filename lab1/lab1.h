/* \obeylines \obeyspaces

\todo[inline]{Lab Goal} 
\textcolor{Fuchsia}{The following program is supposed to give the students 
a review on the basic concepts of C++ and get them warmed up before 
starting to work more on data structure related topics. In order to do 
this, the lab requires the students to use structures and arrays which 
are the fundamentals of studying data structures.}
*/

/* 
\newpage
\textcolor{red}{Following are the libraries and namespace used by the program.}
*/


#include <iostream>
#include <cmath>

using namespace std;

/*\obeylines \obeyspaces
\textcolor{red}{Here, we intialize the required structures in order to 
get the desired results.
Point --> has two double values: x and y;
Triangle1 --> has 3 points: A, B and C
Triangle2 --> has two arrays with three elements each: x and y.}
*/

double distance();
double perimeter();
double perimeter2();

struct Point{
	public:
		double x;
		double y;
};

struct Triangle1{
	public:
		Point a;
		Point b;
		Point c;
};


/*\obeylines \obeyspaces
\textcolor{red}{Triangle2 is a speciality in this program, the logic works the same way
as traingle1, but the difference being triangle2 uses arrays instead of 
Points. 
In the next file: main.cpp, we will see the specific function 
that was made for this structure.}
*/

struct Triangle2{
	public:
		double x[3];
		double y[3];
		Triangle2(double x1,double y1,double x2,double y2,double x3,double y3);
};
