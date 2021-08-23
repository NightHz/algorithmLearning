#pragma once
struct Matrix // AxBµÄ¾ØÕó
{
private:
	double* m;
	int write_i;
public:
	const int rows;
	const int columns;
	const int size;
	Matrix(int _A, int _B) : rows(_A), columns(_B), size(_A* _B), m(new double[_A * _B]{ 0 }), write_i(0) {}
	Matrix(const Matrix& mat) : Matrix(mat.rows, mat.columns) { (*this) = mat; write_i = size; }
	~Matrix() { if (m != nullptr) delete[] m; }
	Matrix& operator<<(double v) { m[write_i++] = v; return *this; }
	double& operator[](int i) { return m[i]; }
	double operator[](int i) const { return m[i]; }
	double& operator()(int r, int c) { return m[r * columns + c]; }
	double operator()(int r, int c) const { return m[r * columns + c]; }
	Matrix& operator=(const Matrix& mat)
	{
		if (rows != mat.rows || columns != mat.columns)
			return (*this);
		for (int i = 0; i < size; i++)
			m[i] = mat.m[i];
		return *this;
	}
};

bool matrix_size_match(const Matrix& m1, const Matrix& m2)
{
	return m1.rows == m2.rows && m1.columns == m2.columns;
}
Matrix operator+(const Matrix& m1, const Matrix& m2)
{
	if (!matrix_size_match(m1, m2))
		return Matrix(1, 1);
	Matrix m(m1.rows, m1.columns);
	for (int i = 0; i < m.size; i++)
		m[i] = m1[i] + m2[i];
	return m;
}
Matrix operator-(const Matrix& m1, const Matrix& m2)
{
	if (!matrix_size_match(m1, m2))
		return Matrix(1, 1);
	Matrix m(m1.rows, m1.columns);
	for (int i = 0; i < m.size; i++)
		m[i] = m1[i] - m2[i];
	return m;
}
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	if (m1.columns != m2.rows)
		return Matrix(1, 1);
	Matrix m(m1.rows, m2.columns);
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.columns; j++)
			for (int k = 0; k < m1.columns; k++)
				m(i, j) += m1(i, k) * m2(k, j);
	return m;
}
Matrix matrix_transpose(const Matrix& m1)
{
	Matrix m(m1.columns, m1.rows);
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.columns; j++)
			m(i, j) = m1(j, i);
	return m;
}
int vector_dot(const Matrix& m1, const Matrix& m2)
{
	if (m1.rows != m2.rows || m1.columns != 1 || m2.columns != 1)
		return -1;
	return (int)(matrix_transpose(m1) * m2)[0];
}