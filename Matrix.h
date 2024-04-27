#pragma 
#include "VectorTemplate.h"
#include "VectorD.h"

template<class T>
class Matrix {
private:
	VectorTemplate<VectorTemplate<T>> coords;
	int n, m;
public:
	int getN() const { return n; };
	int getM() const { return m; };
	Matrix(int n = 0, int m = 0) : n(n), m(m) {
		coords = VectorTemplate<VectorTemplate<T>>(n);
		for (int i = 0; i < n; i++) this->coords[i] = VectorTemplate<T>(m);
	}
	Matrix(const Matrix & a) : n(a.n), m(a.m) {
		coords = VectorTemplate<VectorTemplate<T>>(n);
		for (int i = 0; i < n; i++) this->coords[i] = a.coords[i];
	}
	template<class T2>
	Matrix(const Matrix<T2> & M) : n(M.getN()), m(M.getM()) {
		coords = VectorTemplate<VectorTemplate<T>>(n);
		for (int i = 0; i < n; i++) {
			this->coords[i] = static_cast<VectorTemplate<T>>(M[i]);
		}
	}
	VectorTemplate<T>& operator[](int index) const {
		if ((0 <= index) && (index < n)) return coords[index];
		else throw "Incorecct index\n";
	}
	
	Matrix & operator=(const Matrix & a) {
		this->n = a.n;
		this->m = a.m;
		coords = VectorTemplate<VectorTemplate<T>>(n);
		for (int i = 0; i < n; i++) this->coords[i] = a.coords[i];
		return *this;
	}
	Matrix operator-() const {
		Matrix res(*this);
		for (int i = 0; i < n; i++) res[i] = -(res[i]);
		return res;
	}
	Matrix& operator+=(const Matrix& a) {
		if ((this->n == a.n) && (this->m == a.m)) {
			for (int i = 0; i < n; i++) this->coords[i] += a[i];
			return *this;
		}
		else throw "Inccorect operator+=\n";
	}
	Matrix& operator*=(const Matrix& a) {
		if (this->n == a.m) {
			Matrix tmp(a), res(n, n);
			tmp.Transposition();
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					res[i][j] = (coords[i] * tmp[j]);
				}
			}
			*this = res;
			return *this;
		}
		else throw "Inccorect operator*=\n";
	}
	Matrix operator+(const Matrix& a) {
		if ((this->n == a.n) && (this->m == a.m)) {
			Matrix res(*this);
			res += a;
			return res;
		}
		else throw "Inccorect operator+=\n";
	}
	Matrix& operator*=(const double& a) {
		for (int i = 0; i < n; i++) this->coords[i] *= a;
		return *this;
	}
	Matrix operator*(const double & a) {
		Matrix res(*this);
		res *= a;
		return res;
	}
	Matrix operator*(const Matrix & M) {
		Matrix res(*this);
		res *= M;
		return res;
	}
	Matrix& operator/=(const double& a) {
		if (a != 0) {
			for (int i = 0; i < n; i++) this->coords[i] /= a;
			return *this;
		}
		else throw "Division by 0\n";
	}
	Matrix operator/(const double& a) {
		Matrix res(*this);
		res /= a;
		return res;
	}
	void Transposition() {
		Matrix tmp(*this);
		coords = VectorTemplate<VectorTemplate<T>>(n);;
		for (int i = 0; i < n; i++) coords[i] = VectorTemplate<T>(m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) coords[i][j] = tmp[j][i];
		}
	}
	double Det() {
		double D = 1;
		if (n == m) {
			for (int i = 0; i < n; i++) {
				double Ved;
				int indexm;
				bool flag = true;
				if (coords[i][i] != 0) {
					Ved = coords[i][i];
					//cout << "VED " << Ved << endl;
					indexm = i;
				}
				else {
					int j = 0;
					while ((coords[i][j] == 0) && (j < m))
					{
						if (j != m - 1) j++;
						else {
							flag = false;
							break;
						}

					}
					if (flag != false) {
						Ved = coords[i][j];
						//cout << "VED " << Ved << endl;
						indexm = j;
					}
					else break;
				}
				for (int j = 0; j < n; j++) {
					if ((j != i) && (coords[j][indexm] != 0)) {
						double tmp = coords[j][indexm] / Ved;
						//cout << Ved << " " << tmp << endl;
						for (int k = 0; k < m; k++) {
							coords[j][k] -= coords[i][k] * tmp;
						}
						this->printMatrix();
					}
				}
			}
			for (int i = 0; i < n; i++) {
				bool flag = false;
				for (int j = 0; j < n; j++) {
					if (coords[i][j] != 0) {
						flag = true;
						D *= coords[i][j] * pow(1, i < j);
						break;
					}
				}
				if (flag == false) D = 0;
			}
			return D;
		}
		else throw "n!=m\n";
	}
	
	void printMatrix() {
		for (int i = 0; i < n; i++) std::cout << coords[i];
		cout << endl;
	}
	~Matrix() {

	}
	
};
