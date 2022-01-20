#include <iostream>
#include <stdlib.h>
#include "matrix.h" // Matrix Class
using namespace std;
void printBanner();
void printBreak();
void promptUser();
void matrixTest();
void scalarTest();
void transposeTest();

string versionNum = "v0.1";

int main() {
	/*
	Project Description :
	Undergraduate linear algebra pack or UDPACK is a tool made to assist in early linear algebra calculations expected in the undergraduate cirriculum
	The project is scalable and will eventually be open to other for contribution
	Starting Date 1/14/22

	Current goals include:
	//-Matrix addition DONE
	//-Matrix subtraction DONE
	//-Matrix multiplication DONE
	//-Scalar addition DONE
	//-Scalar multiplication DONE
	//- Scalar Subraction DONE
	//-Scalar division DONE
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
	system("Color E");
	printBanner();
	promptUser();
	

	
	
	
}

void printBanner() {
	char borders[5] = { '\xc9' ,'\xBB','\xBA','\xC8','\xBC' };




	cout << borders[0];
	for (int i = 0; i < 70; i++) {
		cout << '\xCD';
	}
	cout<< borders[1] << endl;
	cout << borders[2]<<" "<<" __  __                    ____    ______  ____     __  __" <<"           "<<borders[2]<< endl;
	cout << borders[2] << " " << "/\\ \\/\\ \\                  /\\  _`\\ /\\  _  \\/\\  _`\\  /\\ \\/\\ \\  " << "        " << borders[2] << endl;
	cout << borders[2] << " " << "\\ \\ \\ \\ \\     __          \\ \\ \\L\\ \\ \\ \\L\\ \\ \\ \\/\\_\\\ \\ \\/'/'   " << "       " << borders[2] << endl;
	cout << borders[2] << " " << " \\ \\ \\ \\ \\  /'_ `\\  _______\\ \\ ,__/\\ \\  __ \\ \\ \\/_/_\\ \\ , <    " << "      " << borders[2] << endl;
	cout << borders[2] << " " << "  \\ \\ \\_\\ \\/\\ \\L\\ \\/\\______\\\\ \\ \\/  \\ \\ \\/\\ \\ \\ \\L\\ \\\\ \\ \\\\`\\  " << "      " << borders[2] << endl;
	cout << borders[2] << " " << "   \\ \\_____\\ \\____ \\/______/ \\ \\_\\   \\ \\_\\ \\_\\ \\____/ \\ \\_\\ \\_\\" << "      " << borders[2] << endl;
	cout << borders[2] << " " << "    \\/_____/\\/___L\\ \\         \\/_/    \\/_/\\/_/\\/___/   \\/_/\\/_/ "<< versionNum<< " " << borders[2] << endl;
	cout << borders[2] << " " << "              /\\____/                                        " << "        " << borders[2] << endl;
	cout << borders[2] << " " << "              \\_/__/                                          " << "       " << borders[2] << endl;
	cout << borders[3];
	for (int i = 0; i < 70; i++) {
		cout << '\xCD';
	}
	cout << borders[4] << endl<<endl << endl;
	
	cout << "Welcome to Under Grad PACK " << versionNum << "A Linear Algebra Toolbox" << endl << endl;
}
void printBreak() {
	cout << "---------------------------------------" << endl;
}
void promptUser() {
	int choice;
	char repeat = 'Y';
	do {
		cout << endl;
		cout << "-----------Which Test would you like to run?-----------" << endl << endl;
		cout << "      1.Scalar properties" << endl;
		cout << "      2.Matrix properties" << endl;
		cout << "      3.Transpose" << endl;
		cout << endl;
		cout << "Test Choice:";
		cin >> choice;

		switch (choice) {
		case 1:
			scalarTest();
		case 2:

			matrixTest();
		case 3:
			transposeTest();
		
			
		}
		
		cout<<endl << endl;
		cout<< "Would you like to run another Test  (Y / N): ";
		cin >> repeat;
	} while(repeat == 'Y' || repeat == 'y');
	
	


}
void matrixTest() {
	printBreak();
	
	Matrix A = Matrix("MatrixA.txt");
	cout << "            Matrix A" << endl;
	A.print();
	//--------------------------------------
	cout << "            Matrix B" << endl;
	Matrix B = Matrix("MatrixB.txt");
	A.print();
	printBreak();
	//Matrix Addition Test----------------
	cout << "      Matrix Addition Test: A+B" << endl;
	A = A + B;
	A.print();
	printBreak();
	//Matrix Subtraction Test

	cout << "      Matrix Subtraction Test: B-B" << endl;
	B = B - B;
	B.print();
	printBreak();
	//Matrix Multiplication Test
	Matrix C = Matrix(A);
	cout << "            Matrix C" << endl;
	C.print();
	printBreak();
	cout << "      Matrix Multiplication Test: C*A" << endl;
	C = C * A;
	C.print();
	printBreak();
}
void scalarTest() {

}
void transposeTest() {

}
