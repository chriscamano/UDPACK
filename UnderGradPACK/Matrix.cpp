#include "Matrix.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
/*
Default Constructor: Accepts matrix dimension and initial value for each cell
*/
Matrix::Matrix(unsigned rowSize, unsigned colSize, double initial) {

	m_rowSize = rowSize;
	m_colSize = colSize;
	m_matrix.resize(rowSize);

	for (unsigned i = 0; i < m_matrix.size(); i++)
	{
		m_matrix[i].resize(colSize, initial);
	}
}

/*
File based matrix constructor, reads file data and generates matrix
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

//Copy Constructor 
Matrix::Matrix(const Matrix& right) {
	this->m_colSize = right.getCols();
	this->m_rowSize = right.getRows();
	this->m_matrix = right.m_matrix;
}
//Deconstructor 
Matrix::~Matrix() {
}

Matrix Matrix::operator=(const Matrix& right) {
	this->m_colSize = right.getCols();
	this->m_rowSize = right.getRows();
	this->m_matrix = right.m_matrix;
	return  *this;
}
//Overloaded addition operator for matrix addition
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
//Overloaded subtraction operator for matrix addition
Matrix Matrix::operator-(Matrix &right) {



	if (m_colSize == right.getCols()&&m_rowSize==right.getRows()) {
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
//Overloaded multiplication operator for matrix multiplication 
Matrix Matrix::operator*(Matrix &right) {
	Matrix product(m_rowSize, right.getCols(), 0.0);
	if (m_colSize == right.getRows()){
		double temp = 0.0;
		for (unsigned i = 0; i < m_rowSize; i++){
			for (unsigned j = 0; j < right.getCols(); j++){
				temp = 0.0;
				for (unsigned k = 0; k < m_colSize; k++){
					temp += m_matrix[i][k] * right(k, j);
				}
				product(i, j) = temp;
			}
		}
		return product;
	}
	else{
		cout<< "Dimension Mis-Match error"<<endl;
		return *this;
	}
}

double& Matrix::operator()(const unsigned& row, const unsigned& col)
{
	return this->m_matrix[row][col];
}

Matrix Matrix::transpose() {
	return 0();
}

unsigned Matrix::getRows() const {
	return m_rowSize;
}

unsigned Matrix::getCols() const {
	return m_colSize;
}

void Matrix::print() {
	cout << "\n Printing Matrix... \n";
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
	precisionVal=maxValLength;
	//This are is a little sloppy, room for improvement
	//add 1 for the left space between border and first column then add 1 to the precision value for the right space. Scale by column space
	matrixSize = 1 + (precisionVal+1) * m_colSize;

	//print top row with corners
	cout << '\xc9';
	for (int i = 0; i < matrixSize; i++) {
		cout << " ";
	}
	cout << '\xBB' << endl;

	//print rows of matrix
	for (int i = 0; i < m_rowSize; i++) {
		cout << '\xBA' << " ";
		for (int j = 0; j < m_colSize; j++) {
			cout << left << setfill('0')  << setprecision(precisionVal) << m_matrix[i][j] << " ";
		}
		cout << '\xBA' << endl;
	}

	//print bottom with corners
	cout << '\xC8';
	for (int i = 0; i < matrixSize; i++) {
		cout << " ";
	}
	cout << '\xBC' << endl;


}
