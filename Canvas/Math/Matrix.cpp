#include "Matrix.h"


template<typename T, size_t dim>
inline constexpr void _cc_fill_mat(std::array<T, dim>& m, cc::Float val)
{
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			m[i][j] = val;
		}
	}
}

template<typename T, size_t dim>
inline constexpr void _cc_fill_mat_diag(std::array<T, dim>& m, cc::Float val)
{
	for (size_t i = 0; i < dim; i++)
	{
		m[i][i] = val;
	}
}

template<typename Matrix, size_t dim>
inline constexpr Matrix _cc_mat_mult(const Matrix& m, const Matrix& n)
{
	Matrix result;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			result[i][j] = m[i][j] * n[j][i];
		}
	}
	return result;
}

template<typename Matrix, size_t dim>
inline constexpr Matrix _cc_mat_transpose(const Matrix& m)
{
	Matrix result;
	for (size_t i = 0; i < dim; ++i)
	{
		for(size_t j = 0; j < dim; ++j)
		{
			result[j][i] = m[i][j];
		}
	}

	return result;
}

namespace cc
{
	Matrix3::Matrix3()
		: m()
	{}

	Matrix3::Matrix3(Float val)
		: m()
	{
		_cc_fill_mat_diag<Vector3, 3>(m, val);
	}

	Matrix3::Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2)
	{
		m[0] = row0;
		m[1] = row1;
		m[2] = row2;
	}

	Vector3& Matrix3::operator[](size_t index)
	{
		return m[index];
	}

	const Vector3& Matrix3::operator[](size_t index) const
	{
		return m[index];
	}

	Matrix3& Matrix3::Transpose()
	{
		m = _cc_mat_transpose<std::array<Vector3, 3>, 3>(m);
		return *this;
	}

	Matrix3 Matrix3::Transposed() const
	{
		return Matrix3(*this).Transpose();
	}


	Matrix4::Matrix4()
		: m()
	{}

	Matrix4::Matrix4(Float val)
		: m()
	{
		_cc_fill_mat_diag<Vector4, 4>(m, val);
	}

	Matrix4::Matrix4(const Vector4& row0, const Vector4& row1, const Vector4& row2, const Vector4& row3)
	{
		m[0] = row0;
		m[1] = row1;
		m[2] = row2;
		m[3] = row3;
	}

	Vector4& Matrix4::operator[](size_t index)
	{
		return m[index];
	}

	const Vector4& Matrix4::operator[](size_t index) const
	{
		return m[index];
	}

	Matrix4& Matrix4::Transpose()
	{
		m = _cc_mat_transpose<std::array<Vector4, 4>, 4>(m);
		return *this;
	}

	Matrix4 Matrix4::Transposed() const
	{
		return Matrix4(*this).Transpose();
	}


	Matrix3 operator+(const Matrix3& m, const Matrix3& n)
	{
		return Matrix3( m[0] + n[0], m[1] + n[1], m[2] + n[2] );
	}

	Matrix3 operator-(const Matrix3& m, const Matrix3& n)
	{
		return Matrix3( m[0] - n[0], m[1] - n[1], m[2] - n[2] );
	}

	Matrix3 operator*(const Matrix3& m, const Matrix3& n)
	{
		return _cc_mat_mult<Matrix3, 3>(m, n);
	}


	Matrix3& operator+=(Matrix3& m, const Matrix3& n)
	{
		m = m + n;
		return m;
	}

	Matrix3& operator-=(Matrix3& m, const Matrix3& n)
	{
		m = m - n;
		return m;
	}

	Matrix3& operator*=(Matrix3& m, const Matrix3& n)
	{
		m = m * n;
		return m;
	}


	Matrix4 operator+(const Matrix4& m, const Matrix4& n)
	{
		return Matrix4( m[0] + n[0], m[1] + n[1], m[2] + n[2], m[3] + n[3] );
	}

	Matrix4 operator-(const Matrix4& m, const Matrix4& n)
	{
		return Matrix4( m[0] - n[0], m[1] - n[1], m[2] - n[2], m[3] - n[3] );
	}

	Matrix4 operator*(const Matrix4& m, const Matrix4& n)
	{
		return _cc_mat_mult<Matrix4, 4>(m, n);
	}


	Matrix4& operator+=(Matrix4& m, const Matrix4& n)
	{
		m = m + n;
		return m;
	}

	Matrix4& operator-=(Matrix4& m, const Matrix4& n)
	{
		m = m - n;
		return m;
	}

	Matrix4& operator*=(Matrix4& m, const Matrix4& n)
	{
		m = m * n;
		return m;
	}


	Vector2 operator*(const Matrix3& m, const Vector2& u)
	{
		Vector3 temp(u.x, u.y, 1.0);
		return { Vector3::Dot(m[0], temp), Vector3::Dot(m[1], temp) };
	}

	Vector3 operator*(const Matrix3& m, const Vector3& u)
	{
		return { Vector3::Dot(m[0], u), Vector3::Dot(m[1], u), Vector3::Dot(m[2], u) };
	}

	Vector3 operator*(const Matrix4& m, const Vector3& u)
	{
		Vector4 temp(u.x, u.y, u.z, 1.0);
		return { Vector4::Dot(m[0], temp), Vector4::Dot(m[1], temp), Vector4::Dot(m[2], temp) };
	}

	Vector4 operator*(const Matrix4& m, const Vector4& u)
	{
		return { Vector4::Dot(m[0], u), Vector4::Dot(m[1], u), Vector4::Dot(m[2], u), Vector4::Dot(m[3], u) };
	}


	/*
	Vector2 operator*(const Vector2& u, const Matrix3& m)
	{
		Vector3 temp(u.x, u.y, 1.0);
		return { Dot(m[1], temp), Dot(m[0], temp) };
	}

	Vector3 operator*(const Vector3& u, const Matrix3& m)
	{
		return { Dot(m[2], u), Dot(m[1], u), Dot(m[0], u) };
	}

	Vector3 operator*(const Vector3& u, const Matrix4& m)
	{
		Vector4 temp(u.x, u.y, u.z, 1.0);
		return { Dot(m[2], temp), Dot(m[1], temp), Dot(m[0], temp) };
	}

	Vector4 operator*(const Vector4& u, const Matrix4& m)
	{
		return { Dot(m[3], u), Dot(m[2], u), Dot(m[1], u), Dot(m[0], u) };
	}
	*/
}
