#include <iostream>
#include "matrix.h" // Matrix Class
using namespace std;

int main() {
	/*
	Project Description :
	Undergraduate linear algebra pack or UDPACK is a tool made to assist in early linear algebra calculations expected in the undergraduate cirriculum
	The project is scalable and will eventually be open to other for contribution
	Starting Date 1/14/22

	Current goals include:
	-Matrix addition
	-Matrix subtraction
	-Matrix multiplication
	-Scalar addition
	-Scalar multiplication
	- Scalar Subraction
	-Scalar division
	-SVD decompositionn
	-QR factorization
	-Hessenberg form calcualtions
	-Househoulder reflections QR 
	-QR method for eigenpairs
	-Lanczos method
	-Arnoldi method
	-Inverse

	-power iteration
	-numerical deflation
	-LU linear solver
	-Characteristic polynomial generator
	-Linear interpolation from solved systems
	-Eigencomputations
	-Complex eigenvalue computations
	-Determinant calculuations through cofactor expansion
	-Determinant calculuations through other means
	-LaTeX matrix generation exporting
	-Transpose
	-Matrix classification tools

	Constraints:
	-No tensor calculations
	-Matrices will start out at max of 20x20 and should have scalable output
	*/


	Matrix A = Matrix("MatrixA.txt");
	//cout << "            Matrix A" << endl;
	//A.print();

	//cout << "            Matrix B" << endl;
	//Matrix B = Matrix("MatrixB.txt");
	//A.print();

	//cout << "            A+B" << endl;

	//A = A + B;
	//A.print();


	//cout << "            B-B" << endl;

	//B = B - B;
	//B.print();

	Matrix C = Matrix(A);
	cout << "            Matrix C" << endl;
	C.print();
	cout << "            C*A" << endl;
	C = C * A;
	C.print();
}