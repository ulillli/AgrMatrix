#include "Matrix.h"
#include <string.h>

int main() {
	try{
		Matrix<int> I(3, 3);
		Matrix<double> D(3, 3);
		std::cout << "Matrix<int>     I:\n";
		I.printMatrix();
		std::cout << "Matrix<double>  D:\n";
		D.printMatrix();
		std::cout << "(D+I):\n";
		(D + I).printMatrix();
		std::cout << "(D*I):\n";
		(D * I).printMatrix();
		std::cout<<"Calculating the determinant  (D*I): \n" << (D * I).Det() << endl;
		Matrix<string> S(4, 4);
		std::cout << "Matrix<string>  S:\n";
		S.printMatrix();
		std::cout << "S.Trensposition  :\n";
		S.Transposition();
		S.printMatrix();
	}
	catch (const char * str) {
		std::cout << str;
	}
}
