namespace cc
{
    namespace detail
	{
		template<typename Matrix, size_t dim, typename T>
		inline constexpr void _cc_mat_fill(Matrix& m, T val)
		{
			for (size_t i = 0; i < dim; i++)
			{
				for (size_t j = 0; j < dim; j++)
				{
					m[i][j] = val;
				}
			}
		}

		template<typename Matrix, size_t dim, typename T>
		inline constexpr void _cc_mat_fill_diag(Matrix& m, T val)
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

    template <typename T>
    inline Matrix3T<T>::Matrix3T()
		: m()
	{}

	template <typename T>
    inline Matrix3T<T>::Matrix3T(T val)
		: m()
	{
		detail::_cc_mat_fill_diag<Matrix3T<T>, 3>(*this, val);
	}

	template <typename T>
    inline Matrix3T<T>::Matrix3T(const Vector3T<T>& row0, const Vector3T<T>& row1, const Vector3T<T>& row2)
	{
		m[0] = row0;
		m[1] = row1;
		m[2] = row2;
	}

	template <typename T>
    inline Vector3T<T>& Matrix3T<T>::operator[](size_t index)
	{
		return m[index];
	}

	template <typename T>
    inline const Vector3T<T>& Matrix3T<T>::operator[](size_t index) const
	{
		return m[index];
	}

	template <typename T>
    inline Matrix3T<T>& Matrix3T<T>::Transpose()
	{
		detail::_cc_mat_tpose<Matrix3T, 3>(*this);
		return *this;
	}

	template <typename T>
    inline Matrix3T<T> Matrix3T<T>::Transposed() const
	{
		return Matrix3T(*this).Transpose();
	}

	template <typename T>
    inline Matrix3T<T>& Matrix3T<T>::Invert()
	{
		detail::_cc_mat_inv<Matrix3T, 3>(*this);
		return *this;
	}

	template <typename T>
    inline Matrix3T<T> Matrix3T<T>::Inverse() const
	{
		Matrix3T inverse = *this;
		detail::_cc_mat_inv<Matrix3T, 3>(inverse);
		return inverse;
	}

	template <typename T>
    inline T Matrix3T<T>::Det() const
	{
		//return detail::_cc_mat_det<Matrix3T, 3>(*this);
		return T(0);
	}

	template <typename T>
    inline Matrix4T<T>::Matrix4T()
		: m()
	{}

	template <typename T>
    inline Matrix4T<T>::Matrix4T(T val)
		: m()
	{
		detail::_cc_mat_fill_diag<Matrix4T, 4>(*this, val);
	}

	template <typename T>
    inline Matrix4T<T>::Matrix4T(const Vector4T<T>& row0, const Vector4T<T>& row1, const Vector4T<T>& row2, const Vector4T<T>& row3)
	{
		m[0] = row0;
		m[1] = row1;
		m[2] = row2;
		m[3] = row3;
	}

	template <typename T>
    inline Vector4T<T>& Matrix4T<T>::operator[](size_t index)
	{
		return m[index];
	}

	template <typename T>
    inline const Vector4T<T>& Matrix4T<T>::operator[](size_t index) const
	{
		return m[index];
	}

	template <typename T>
    inline Matrix4T<T>& Matrix4T<T>::Transpose()
	{
		detail::_cc_mat_tpose<Matrix4T, 4>(*this);
		return *this;
	}

	template <typename T>
    inline Matrix4T<T> Matrix4T<T>::Transposed() const
	{
		return Matrix4T(*this).Transpose();
	}

	template <typename T>
    inline Matrix4T<T>& Matrix4T<T>::Invert()
	{
		detail::_cc_mat_inv<Matrix4T, 4>(*this);
		return *this;
	}

	template <typename T>
    inline Matrix4T<T> Matrix4T<T>::Inverse() const
	{
		Matrix4T inverse = *this;
		detail::_cc_mat_inv<Matrix4T, 4>(inverse);
		return inverse;
	}

	template <typename T>
    inline T Matrix4T<T>::Det() const
	{
		//return detail::_cc_mat_det<Matrix4T, 3>(*this);
		return T(0);
	}

	template <typename T>
    inline Matrix3T<T> operator+(const Matrix3T<T>& m, const Matrix3T<T>& n)
	{
		return Matrix3T( m[0] + n[0], m[1] + n[1], m[2] + n[2] );
	}

	template <typename T>
    inline Matrix3T<T> operator-(const Matrix3T<T>& m, const Matrix3T<T>& n)
	{
		return Matrix3T( m[0] - n[0], m[1] - n[1], m[2] - n[2] );
	}

	template <typename T>
    inline Matrix3T<T> operator*(const Matrix3T<T>& m, const Matrix3T<T>& n)
	{
		return detail::_cc_mat_mult<Matrix3T, 3>(m, n);
	}


	template <typename T>
    inline Matrix3T<T>& operator+=(Matrix3T<T>& m, const Matrix3T<T>& n)
	{
		m = m + n;
		return m;
	}

	template <typename T>
    inline Matrix3T<T>& operator-=(Matrix3T<T>& m, const Matrix3T<T>& n)
	{
		m = m - n;
		return m;
	}

	template <typename T>
    inline Matrix3T<T>& operator*=(Matrix3T<T>& m, const Matrix3T<T>& n)
	{
		m = m * n;
		return m;
	}


	template <typename T>
    inline Matrix4T<T> operator+(const Matrix4T<T>& m, const Matrix4T<T>& n)
	{
		return Matrix4T( m[0] + n[0], m[1] + n[1], m[2] + n[2], m[3] + n[3] );
	}

	template <typename T>
    inline Matrix4T<T> operator-(const Matrix4T<T>& m, const Matrix4T<T>& n)
	{
		return Matrix4T( m[0] - n[0], m[1] - n[1], m[2] - n[2], m[3] - n[3] );
	}

	template <typename T>
    inline Matrix4T<T> operator*(const Matrix4T<T>& m, const Matrix4T<T>& n)
	{
		return detail::_cc_mat_mult<Matrix4T, 4>(m, n);
	}


	template <typename T>
    inline Matrix4T<T>& operator+=(Matrix4T<T>& m, const Matrix4T<T>& n)
	{
		m = m + n;
		return m;
	}

	template <typename T>
    inline Matrix4T<T>& operator-=(Matrix4T<T>& m, const Matrix4T<T>& n)
	{
		m = m - n;
		return m;
	}

	template <typename T>
    inline Matrix4T<T>& operator*=(Matrix4T<T>& m, const Matrix4T<T>& n)
	{
		m = m * n;
		return m;
	}



	template <typename T>
    inline Vector2T<T> operator*(const Matrix3T<T>& m, const Vector2T<T>& u)
	{
		Vector3T<T> temp(u.x, u.y, 1.0);
		return { Vector3T<T>::Dot(m[0], temp), Vector3T<T>::Dot(m[1], temp) };
	}

	template <typename T>
    inline Vector3T<T> operator*(const Matrix3T<T>& m, const Vector3T<T>& u)
	{
		return { Vector3T<T>::Dot(m[0], u), Vector3T<T>::Dot(m[1], u), Vector3T<T>::Dot(m[2], u) };
	}

	template <typename T>
    inline Vector3T<T> operator*(const Matrix4T<T>& m, const Vector3T<T>& u)
	{
		Vector4T<T> temp(u.x, u.y, u.z, 1.0);
		return { Vector4T<T>::Dot(m[0], temp), Vector4T<T>::Dot(m[1], temp), Vector4T<T>::Dot(m[2], temp) };
	}

	template <typename T>
    inline Vector4T<T> operator*(const Matrix4T<T>& m, const Vector4T<T>& u)
	{
		return { Vector4T<T>::Dot(m[0], u), Vector4T<T>::Dot(m[1], u), Vector4T<T>::Dot(m[2], u), Vector4T<T>::Dot(m[3], u) };
	}


	template <typename T>
    inline Vector2T<T> operator*(const Vector2T<T>& u, const Matrix3T<T>& m)
	{
		Vector3T<T> temp(u.x, u.y, 1.0);
		return { Vector3T<T>::Dot(m[1], temp), Vector3T<T>::Dot(m[0], temp) };
	}

	template <typename T>
    inline Vector3T<T> operator*(const Vector3T<T>& u, const Matrix3T<T>& m)
	{
		return { Vector3T<T>::Dot(m[2], u), Vector3T<T>::Dot(m[1], u), Vector3T<T>::Dot(m[0], u) };
	}

	template <typename T>
    inline Vector3T<T> operator*(const Vector3T<T>& u, const Matrix4T<T>& m)
	{
		Vector4T<T> temp(u.x, u.y, u.z, 1.0);
		return { Vector4T<T>::Dot(m[2], temp), Vector4T<T>::Dot(m[1], temp), Vector4T<T>::Dot(m[0], temp) };
	}

	template <typename T>
    inline Vector4T<T> operator*(const Vector4T<T>& u, const Matrix4T<T>& m)
	{
		return { Vector4T<T>::Dot(m[3], u), Vector4T<T>::Dot(m[2], u), Vector4T<T>::Dot(m[1], u), Vector4T<T>::Dot(m[0], u) };
	}
}