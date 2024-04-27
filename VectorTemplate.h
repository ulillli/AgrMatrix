#pragma once
#include <iostream>

template<class T>
class VectorTemplate{
public:
	T * coords = nullptr;
	int size = 0;
public:
	friend std::istream& operator >>(std::istream & istr, VectorTemplate& a) {
		for (int i = 0; i < a.size; i++) {
			istr >> a.coords[i];
		}
		return istr;
	}
	friend std::ostream& operator <<(std::ostream & ostr, const VectorTemplate& a) {
		ostr << "(";
		for (int i = 0; i < a.size-1; i++) {
			ostr  <<a.coords[i] << ", ";
		}
		ostr << a.coords[a.size-1];
		ostr << ")" << std::endl;
		return ostr;
	}
	VectorTemplate(int n = 0) : size(n) {
		coords = new T[n];
		for (int i = 0; i < this->size; i++) this->coords[i] = (1.123123+i);
	}
	VectorTemplate(T * a,int n) : size(n) {
		//if (n <= 0) throw "Incorrect size when initializing a class object with array";
		coords = new T[this->size];
		for (int i = 0; i < this->size; i++) this->coords[i] = a[i];
	}
	VectorTemplate(const VectorTemplate & b) : size(b.size) {
		//if (size <= 0) throw "Incorrect size when initializing a class object with another object";
		coords = new T[this->size];
		for (int i = 0; i < this->size; i++) {
			this->coords[i] = b.coords[i];
		}
	}
	template<class T2>
	VectorTemplate(const VectorTemplate<T2> & v) : size(v.size) {
		coords = new T[size];
		for (int i = 0; i < size; i++) {
			coords[i] = static_cast<T>(v.coords[i]);
		}
	}

	T & operator[](int index) const {
		if ((0 <= index) && (index < size)) return coords[index];
		else throw "Incorecct index\n";
	}
	VectorTemplate & operator=(const VectorTemplate& b) {
		if (&b != this) {
			this->size = b.size;
			delete[] coords;
			coords = new T[size];
			for (int i = 0; i < size; i++) coords[i] = b.coords[i];
			return *this;
		}
		return *this;
	}
	VectorTemplate & operator+=(const VectorTemplate & b) {
		if (this->size == b.size) {
			for (int i = 0; i < size; i++) {
				this->coords[i] += b.coords[i];
			}
			return *this;
		}
		else throw "Incorect operator +";
	}
	VectorTemplate& operator-=(const VectorTemplate& b) {
		if (this->size == b.size) {
			for (int i = 0; i < size; i++) this->coords[i] -= b.coords[i];
			return *this;
		}
		else throw "Incorect operator -";
	}
	VectorTemplate& operator*=(T b) {
		if (b != 0) {
			for (int i = 0; i < size; i++) this->coords[i] = b * this->coords[i];
			return *this;
		}
		else throw "Multiplication by 0";
	}
	VectorTemplate& operator/=(T b) {
		if (b != 0) {
			for (int i = 0; i < size; i++) this->coords[i] = this->coords[i] / b;
			return *this;
		}
		else throw "Division by 0";
	}
	bool operator==(const VectorTemplate& b) const {
		if (this->size == b.size) {
			int i = 0;
			while (this->coords[i] == b.coords[i]) i++;
			if (i == this->size) return 1;
			else return 0;
		}
		else throw "Incorect operator == ";
	}
	bool operator!=(const VectorTemplate& b) const {
		if (this->size == b.size) {
			int i = 0;
			while (this->coords[i] == b.coords[i]) i++;
			if (i == this->size) return 0;
			else return 1;
		}
		else throw "Incorect operator != ";
	}
	VectorTemplate operator+(const VectorTemplate& b) const {
		VectorTemplate c(*this);	 
		c += b;
		return c;
	}
	VectorTemplate operator-(const VectorTemplate& b) const {
		VectorTemplate c=*this;
		c -= b;
		return c;
	}
	VectorTemplate operator-() const {
		VectorTemplate res(*this);
		for (int i = 0; i < size; i++) {
			res[i] = (-res[i]);
		}
		return res;
	}
	VectorTemplate operator*(double b) const {
		VectorTemplate c(*this);
		c *= b;
		return c;
	}
	double operator*(const VectorTemplate& b) const {
		double P = this->For(b);
		return P;
	}
	VectorTemplate operator/(T b) const {
		VectorTemplate c(this->size);
		c /= b;
		return c;
	}

	double distance(const VectorTemplate& b) {
		if (this->size == b.size) {
			VectorTemplate res(size);
			for (int i = 0; i < size; i++) res.coords[i] = (this->coords[i] - b.coords[i]);
			return sqrt(res.For(res));
		}
		else throw "Incorrect size for culculate distance";
	}
	double culculateNorma() {
		return sqrt(For(*this));
	}
	double For(const VectorTemplate& res) const {
		double tmp = 0;
		for (int i = 0; i < size; i++) tmp += (this->coords[i] * res.coords[i]);
		return tmp;
	}
	void printV() {
		std::cout << "(";
		for (int i = 0; i < this->size - 1; i++) std::cout << this->coords[i] << ",";
		std::cout << this->coords[this->size - 1] << ")" << std::endl;
	}
	~VectorTemplate() {
		delete[] coords;
		
	}

};

