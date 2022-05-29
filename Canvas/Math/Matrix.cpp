#include "Matrix.h"

#include "Utils.h"

namespace cc
{
	namespace detail
	{
		template<typename Matrix, size_t dim>
		inline constexpr void _cc_mat_fill(Matrix& m, Float val)
		{
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					m[i][j] = val;
				}
			}
		}

		template<typename Matrix, size_t dim>
		inline constexpr void _cc_mat_fill_diag(Matrix& m, Float val)
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
		inline constexpr void _cc_mat_tpose(Matrix& m)
		{
			for (size_t i = 0; i < dim; ++i)
			{
				for (size_t j = i + 1; j < dim; ++j)
				{
					std::swap(m[j][i], m[i][j]);
				}
			}
		}

		template<typename Matrix, size_t dim>
		inline constexpr Matrix _cc_mat_cofactor(const Matrix& m, size_t row, size_t col)
		{
			size_t ci = 0, cj = 0;
			Matrix cofactor;
			for (size_t i = 0; i < dim; ++i)
			{
				if (i == row) continue;

				for (size_t j = 0; j < dim; ++j)
				{
					if (j == col) continue;

					cofactor[ci][cj++] = m[i][j];
					if (cj - 1 == dim) { cj = 0; ci++; }
				}
			}

			return cofactor;
		}

		/*template<typename Matrix, size_t dim>
		inline constexpr Float _cc_mat_det(const Matrix& m)
		{
			if constexpr (dim == 1) return m[0][0];

			Float det(0);
			Matrix cofactor;
			int sign = 1;
			for (size_t i = 0; i < dim; i++)
			{
				cofactor = _cc_mat_cofactor<Matrix, dim>(m, 0, i);
				det += sign * m[0][i] * _cc_mat_det<Matrix, dim - 1>(cofactor);

				sign = -sign;
			}

			return det;
		}*/

		template<typename Matrix, size_t dim>
		inline constexpr void _cc_mat_inv(Matrix& m)
		{
			size_t pivotRow = 0;
			size_t pivotCol = 0;

			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					m[pivotRow][pivotCol] = 0;
				}
			}
		}
	}

	Matrix3::Matrix3()
		: m()
	{}

	Matrix3::Matrix3(Float val)
		: m()
	{
		detail::_cc_mat_fill_diag<Matrix3, 3>(*this, val);
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
		detail::_cc_mat_tpose<Matrix3, 3>(*this);
		return *this;
	}

	Matrix3 Matrix3::Transposed() const
	{
		return Matrix3(*this).Transpose();
	}

	Matrix3& Matrix3::Invert()
	{
		detail::_cc_mat_inv<Matrix3, 3>(*this);
		return *this;
	}

	Matrix3 Matrix3::Inverse() const
	{
		Matrix3 inverse = *this;
		detail::_cc_mat_inv<Matrix3, 3>(inverse);
		return inverse;
	}

	Float Matrix3::Det() const
	{
		//return detail::_cc_mat_det<Matrix3, 3>(*this);
		return Float(0);
	}

	Matrix4::Matrix4()
		: m()
	{}

	Matrix4::Matrix4(Float val)
		: m()
	{
		detail::_cc_mat_fill_diag<Matrix4, 4>(*this, val);
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
		detail::_cc_mat_tpose<Matrix4, 4>(*this);
		return *this;
	}

	Matrix4 Matrix4::Transposed() const
	{
		return Matrix4(*this).Transpose();
	}

	Matrix4& Matrix4::Invert()
	{
		detail::_cc_mat_inv<Matrix4, 4>(*this);
		return *this;
	}

	Matrix4 Matrix4::Inverse() const
	{
		Matrix4 inverse = *this;
		detail::_cc_mat_inv<Matrix4, 4>(inverse);
		return inverse;
	}

	Float Matrix4::Det() const
	{
		//return detail::_cc_mat_det<Matrix4, 3>(*this);
		return Float(0);
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
		return detail::_cc_mat_mult<Matrix3, 3>(m, n);
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
		return detail::_cc_mat_mult<Matrix4, 4>(m, n);
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


	Vector2 operator*(const Vector2& u, const Matrix3& m)
	{
		Vector3 temp(u.x, u.y, 1.0);
		return { Vector3::Dot(m[1], temp), Vector3::Dot(m[0], temp) };
	}

	Vector3 operator*(const Vector3& u, const Matrix3& m)
	{
		return { Vector3::Dot(m[2], u), Vector3::Dot(m[1], u), Vector3::Dot(m[0], u) };
	}

	Vector3 operator*(const Vector3& u, const Matrix4& m)
	{
		Vector4 temp(u.x, u.y, u.z, 1.0);
		return { Vector4::Dot(m[2], temp), Vector4::Dot(m[1], temp), Vector4::Dot(m[0], temp) };
	}

	Vector4 operator*(const Vector4& u, const Matrix4& m)
	{
		return { Vector4::Dot(m[3], u), Vector4::Dot(m[2], u), Vector4::Dot(m[1], u), Vector4::Dot(m[0], u) };
	}
}
