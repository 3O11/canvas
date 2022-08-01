namespace cc
{
    template <typename T>
    inline Matrix3T<T>::Matrix3T()
		: m()
	{}

	template <typename T>
    inline Matrix3T<T>::Matrix3T(T val)
		: m()
	{
		for (size_t i = 0; i < 3; i++)
        {
            m[i][i] = val;
        }
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
        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = i + 1; j < 3; ++j)
            {
                std::swap(m[j][i], m[i][j]);
            }
        }
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
		return *this;
	}

	template <typename T>
    inline Matrix3T<T> Matrix3T<T>::Inverse() const
	{
		Matrix3T inverse = *this;
		return inverse;
	}

	template <typename T>
    inline T Matrix3T<T>::Det() const
	{
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
		for (size_t i = 0; i < 4; i++)
        {
            m[i][i] = val;
        }
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
		for (size_t i = 0; i < 4; ++i)
        {
            for (size_t j = i + 1; j < 4; ++j)
            {
                std::swap(m[j][i], m[i][j]);
            }
        }
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
		return *this;
	}

	template <typename T>
    inline Matrix4T<T> Matrix4T<T>::Inverse() const
	{
		Matrix4T inverse = *this;
		return inverse;
	}

	template <typename T>
    inline T Matrix4T<T>::Det() const
	{
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
		Matrix4T<T> result;
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                result[i][j] = m[i][j] * n[j][i];
            }
        }
        return result;
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
		Matrix4T<T> result;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                result[i][j] = m[i][j] * n[j][i];
            }
        }
        return result;
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