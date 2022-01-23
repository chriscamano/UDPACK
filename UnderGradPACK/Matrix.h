#pragma once
#include <stdio.h>
#include <fstream> // for file access
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

using std::vector;
using std::tuple;

class Matrix {
public:
	//Matrix constructors 
	Matrix(unsigned, unsigned, double);
	Matrix(const char*);
	Matrix(const Matrix&);
	~Matrix();

	Matrix operator=(const Matrix& right);
	double& operator()(const unsigned&, const unsigned&);
	//Matrix Operations 
	Matrix operator*(Matrix&);
	//Scalar Operations
	Matrix operator*(double&);
	Matrix operator/(double&);
	//Utility Functions
	Matrix transpose();

	double trace();
	vector<Matrix> LUFactor();
	Matrix eye(int&);
	//Matrix syntax functions 
	unsigned getRows() const;
	unsigned getCols() const;
	void print();

private:
	unsigned m_rowSize;
	unsigned m_colSize;
	vector<vector<double> > m_matrix;
	void printSpaces(const int&);
};
