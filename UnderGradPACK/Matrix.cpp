﻿#include "Matrix.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
/*
Default Constructor: Accepts matrix dimension and initial value for each cell
Author: Chris Camano
*/
Matrix::Matrix(unsigned rowSize, unsigned colSize, double initial) {

	m_rowSize = rowSize;
	m_colSize = colSize;
	m_matrix.resize(rowSize);

	for (unsigned i = 0; i < m_matrix.size(); i++) {
		m_matrix[i].resize(colSize, initial);
	}
}

/*
File based matrix constructor, reads file data and generates matrix
Author: Chris Camano
*/
Matrix::Matrix(const char* file) {
	ifstream file_A(file); // input file stream to open the file A.txt

	// Task 1
	// Keeps track of the Column and row sizes
	int colSize = 0;
	int rowSize = 0;

	// read it as a vector
	string line_A;
	int index = 0;
	double element_A;
	double* vector_A = nullptr;

	//Check that file can be opened 
	if (file_A.is_open() && file_A.good()) {
		//while there are more lines remaining in the file 
		while (getline(file_A, line_A)) {
			rowSize++;
			stringstream stream_A(line_A);
			colSize = 0;
			while (1) {
				stream_A >> element_A;
				//if there are no remaining elements in the line break the loop
				if (!stream_A)
					break;
				colSize++;

				double* tempArr = new double[index + 1];
				copy(vector_A, vector_A + index, tempArr);
				tempArr[index] = element_A;
				vector_A = tempArr;
				index++;
			}
		}
	}

	else {
		cout << "Matrix import failed";
	}

	//update Matrix object dimensions
	m_colSize = colSize;
	m_rowSize = rowSize;
	m_matrix.resize(rowSize);

	//reset tracking index
	index = 0;
	//resize each row vector to appropriate column size
	for (unsigned i = 0; i < m_matrix.size(); i++) {
		m_matrix[i].resize(colSize);
	}
	//populate indicies of matrix with data stored in vector_A
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			this->m_matrix[i][j] = vector_A[index];
			index++;
		}
	}

	// Free memory 
	delete[] vector_A;
}

/*
Copy Constructor
Author: Chris Camano
*/
Matrix::Matrix(const Matrix& right) {
	this->m_colSize = right.getCols();
	this->m_rowSize = right.getRows();
	this->m_matrix = right.m_matrix;
}
//Deconstructor 
Matrix::~Matrix() {
}

//-----------------------------------------------------------------------------------------------Operator Overloading--------------------------------------------------------------

/*
Overloaded = operator for matrix assignnment
Author: Chris Camano
*/
Matrix Matrix::operator=(const Matrix& right) {
	this->m_colSize = right.getCols();
	this->m_rowSize = right.getRows();
	this->m_matrix = right.m_matrix;
	return  *this;
}

/*
Overloaded addition operator for matrix addition
Author: Chris Camano
*/
Matrix Matrix::operator+(Matrix& right) {
	if (m_colSize == right.getCols() && m_rowSize == right.getRows()) {
		//create new Matrix representing sum
		Matrix sum(m_rowSize, m_colSize, 0.0);
		//For each element pair add sum to relative index and return sum matrix
		for (unsigned i = 0; i < m_rowSize; i++) {
			for (unsigned j = 0; j < m_colSize; j++) {
				sum(i, j) = this->m_matrix[i][j] + right(i, j);
			}
		}
		return sum;
	}
	else {
		cout << "Dimension Mis-Match error" << endl;
		return *this;
	}
}
/*
Overloaded subtraction operator for matrix subtraction
Author: Chris Camano
*/

Matrix Matrix::operator-(Matrix& right) {
	if (m_colSize == right.getCols() && m_rowSize == right.getRows()) {
		//create new Matrix representing sum
		Matrix sum(m_rowSize, m_colSize, 0.0);
		//For each element pair add sum to relative index and return sum matrix
		for (unsigned i = 0; i < m_rowSize; i++) {
			for (unsigned j = 0; j < m_colSize; j++) {
				sum(i, j) = this->m_matrix[i][j] - right(i, j);
			}
		}
		return sum;
	}
	else {
		cout << "Dimension Mis-Match error" << endl;
		return *this;
	}

}
/*
Overloaded multiplication operator for matrix multiplication
Author: Chris Camano
*/
Matrix Matrix::operator*(Matrix& right) {
	Matrix product(m_rowSize, right.getCols(), 0.0);
	if (m_colSize == right.getRows()) {
		double temp = 0.0;
		for (unsigned i = 0; i < m_rowSize; i++) {
			for (unsigned j = 0; j < right.getCols(); j++) {
				temp = 0.0;
				for (unsigned k = 0; k < m_colSize; k++) {
					temp += m_matrix[i][k] * right(k, j);
				}
				product(i, j) = temp;
			}
		}
		return product;
	}
	else {
		cout << "Dimension Mis-Match error" << endl;
		return *this;
	}
}

/*
Overloaded () operator for matrix index referncing
Author: Chris Camano
*/
double& Matrix::operator()(const unsigned& row, const unsigned& col)
{
	return this->m_matrix[row][col];
}


// Scalar Multiplication
//Author: Chris Camano
Matrix Matrix::operator*(double& scalar) {
	Matrix result(m_rowSize, m_colSize, 0.0);
	for (unsigned i = 0; i < m_rowSize; i++) {
		for (unsigned j = 0; j < m_colSize; j++) {
			result(i, j) = this->m_matrix[i][j] * scalar;
		}
	}
	return result;
}

// Scalar Division
//Author: Chris Camano
Matrix Matrix::operator/(double& scalar) {
	Matrix result(m_rowSize, m_colSize, 0.0);
	for (unsigned i = 0; i < m_rowSize; i++) {
		for (unsigned j = 0; j < m_colSize; j++) {
			result(i, j) = this->m_matrix[i][j] / scalar;
		}
	}
	return result;
}


//-----------------------------------------------------------------------------------------------Utility--------------------------------------------------------------

/*
Transpose Function
Author: Juvenal Barajas
*/
Matrix Matrix::transpose() {

	Matrix temp(m_colSize, m_rowSize, 1.00);

	// Double for loop to access each individual
	// element from matrix.
	for (int i = 0; i < m_rowSize; i++) {
		for (int j = 0; j < m_colSize; j++) {
			// moving row elements from original
			// matrix to column elements from new
			// matrix.
			temp(j, i) = this->m_matrix[i][j];
		}
	}


	return temp;
}

vector<Matrix> Matrix::LUFactor() {
	if (this->getCols() != this->getRows()) {
		cout << "Matrix is not square LU factorization undefined" << endl;
	}
	int n = this->getCols();
	unsigned partialSum = 0;
	vector<Matrix> LUFactors;
	
	Matrix L = eye(n);
	Matrix U(m_colSize, m_rowSize, 0);
	
	//LU Decomposition algorithm with column pivoting 
	//shorturl.at/fjxF7
	for (int k = 0; k < n; k++) {
		//Copy diagonal element of A to U 
		U(k, k) = this->m_matrix[k][k];

		//Pivot Column Calculations
		//For each row set elements of L to the element of A divided by the diagonal of U 
		//For each column set elements of U to corresponding element of A
		for (int i = k+1; i < n; i++) {
			L(i, k) = this->m_matrix[i][k] / U(k, k);
			U(k, i) = this->m_matrix[k][i];
		}

		//Matrix update calculations set each element of A to the difference of the upper and 
		//Lower matricies
		for (int i = k + 1; i < n; i++) {
			for (int j = k + 1; j < n; j++) {
				this->m_matrix[i][j] = this->m_matrix[i][j] - (L(i, k) * U(k, j));
			}
		}
	}

	LUFactors.push_back(L);
	LUFactors.push_back(U);
	return LUFactors;
}

Matrix Matrix::eye(int& n) {
	Matrix I(n, n, 0);
	for (int i = 0; i < n; i++) {
		I(i, i) = 1.0;
	}
	return I;
}



/*
Adaptive printing function
Author: Chris Camano
*/
void Matrix::print() {
	char borders[5] = { '\xc9' ,'\xBB','\xBA','\xC8','\xBC' };
	string s;
	int matrixSize, precisionVal;
	int maxValLength = 0;
	int roundOffVal = 3;


	for (int i = 0; i < m_rowSize; i++) {
		for (int j = 0; j < m_colSize; j++) {
			//for each element of the matrix convert it to a string then trim the floating point round off error to 3 places.
			s = to_string(m_matrix[i][j]).substr(0, to_string(m_matrix[i][j]).find(".") + roundOffVal + 1);
			//If the string is larger than the previously tracked largest entry in the matrix change the max length
			if (s.size() > maxValLength) {
				maxValLength = s.size();
			}
			s = "";
		}
	}
	//update the precision value for printing table in accordance to the max entry length found during search
	//add +1 to max length to account for '.' 

	precisionVal = maxValLength + 1;

	//This is a little sloppy, room for improvement
	//add 1 for the left space between border and first column then add 1 to the precision value for the right space after each index. Scale by column space

	matrixSize = 1 + (precisionVal + 1) * m_colSize;

	//print top row with corners

	cout << borders[0];
	printSpaces(matrixSize);
	cout << borders[1] << endl;

	//print rows of matrix
	for (int i = 0; i < m_rowSize; i++) {
		cout << borders[2] << " ";
		for (int j = 0; j < m_colSize; j++) {
			//For each row print 0s until precision requirement is fufilled 
			cout << left << setfill('0') << setw(precisionVal) << setprecision(precisionVal) << m_matrix[i][j] << " ";
		}
		cout << borders[2] << endl;
	}

	//print bottom with corners
	cout << borders[3];
	printSpaces(matrixSize);
	cout << borders[4] << endl;

}
//-----------------------------------------------------------------------------------------------Helper Functions--------------------------------------------------------------

void Matrix::printSpaces(const int& size)
{
	for (int i = 0; i < size; i++) {
		cout << " ";
	}
}

unsigned Matrix::getRows() const {
	return m_rowSize;
}

unsigned Matrix::getCols() const {
	return m_colSize;
}