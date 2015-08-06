/* The MIT License:

Copyright (c) 2008-2015 Ivan Gagis <igagis@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */

// Home page: http://morda.googlecode.com

/**
 * @author Ivan Gagis <igagis@gmail.com>
 */

#pragma once


#ifdef DEBUG
#	include <iostream>
#endif

#include <ting/debug.hpp>
#include <ting/types.hpp>
#include <ting/math.hpp>

#include "../config.hpp"


namespace morda{



//forward declarations
template <class T> class Vector3;



/**
 * @brief Two-dimensional vector class.
 */
template <class T> class Vector2{
public:
	typedef T T_Component;
	
	/**
	 * @brief 0th vector component.
	 */
	T x;

	/**
	 * @brief 1th vector component.
	 */
	T y;

	/**
	 * @brief Get number of vector components.
     * @return Number of vector components.
     */
	size_t size()const{
		return 2;
	}
	
	/**
	 * @brief default constructor.
	 * It does not initialize vector components.
	 * Their values are undefined right after construction.
	 */
	constexpr Vector2()NOEXCEPT :
			x(0), y(0) //TODO: remove initialization list when C++14 is supported by all compilers
	{}

	/**
	 * @brief Create vector with given values.
	 * Creates a vector with all components initialized to a given value.
	 * @param xy - value to assign to all components of the vector.
	 */
	constexpr Vector2(T xy)NOEXCEPT :
			x(xy), y(xy)
	{}
	
	/**
	 * @brief Create vector with given values.
	 * @param x - x component of the vector.
	 * @param y - y component of the vector.
	 */
	constexpr Vector2(T x, T y)NOEXCEPT :
			x(x), y(y)
	{}

	//NOTE: copy constructor will be generated by compiler

	/**
	 * @brief Create Vector2 from Vector3
	 * Creates a 2 dimensional vector and initializes its x and y components
	 * from x and y of given 3 dimensional vector.
	 * @param vec - 3 dimensional vector to copy x and y from.
	 */
	Vector2(const Vector3<T>& vec)NOEXCEPT;

	
	template <class TT> explicit Vector2(const Vector2<TT>& v) :
			x(v.x),
			y(v.y)
	{}
	
	
	
	/**
	 * @brief Access vector components.
	 * @param i - index of the component, can be 0 or 1.
	 */
	T& operator[](unsigned i)NOEXCEPT{
		ASSERT(i < 2)
		ASSERT( &((&this->x)[0]) == &this->x)
		ASSERT( &((&this->x)[1]) == &this->y)
		return (&this->x)[i];
	}

	/**
	 * @brief Access vector components.
	 * @param i - index of the component, can be 0 or 1.
	 */
	const T& operator[](unsigned i)const NOEXCEPT{
		ASSERT(i < 2)
		ASSERT( &((&this->x)[0]) == &this->x)
		ASSERT( &((&this->x)[1]) == &this->y)
		return (&this->x)[i];
	}

	//NOTE: operator=() will be generated by compiler.

	/**
	 * @brief Assign value of given Vector3 object.
	 * Note, the z component of given Vector3 is ignored.
	 * @param vec - reference to the Vector3 object to assign value from.
	 * @return reference to this Vector2 object.
	 */
	Vector2& operator=(const Vector3<T>& vec)NOEXCEPT;

	/**
	 * @brief Add Vector2 and Vector3.
	 * Note, the z component of given Vector3 is ignored.
	 * @param vec - reference to the Vector3 object to add.
	 * @return instance of the resulting Vector2.
	 */
	Vector2 operator+(const Vector3<T>& vec)const NOEXCEPT;

	/**
	 * @brief Add and assign.
	 * Adds given Vector2 and this Vector2 and assigns the result to this Vector2.
	 * @param vec - reference to the Vector2 object to add.
	 * @return reference to this Vector2 object.
	 */
	Vector2& operator+=(const Vector2& vec)NOEXCEPT{
		this->x += vec.x;
		this->y += vec.y;
		return (*this);
	}

	/**
	 * @brief Add two Vector2 vectors.
	 * @param vec - reference to the Vector2 object to add.
	 * @return instance of the resulting Vector2.
	 */
	Vector2 operator+(const Vector2& vec)const NOEXCEPT{
		return (Vector2(*this) += vec);
	}


	/**
	 * @brief Subtract vector and assign.
	 * Subtracts given vector from this one and assigns result back to this vector.
     * @param vec - vector to subtract from this one.
     * @return Reference to this vector object.
     */
	Vector2& operator-=(const Vector2& vec)NOEXCEPT{
		this->x -= vec.x;
		this->y -= vec.y;
		return (*this);
	}

	/**
	 * @brief Subtract vector.
     * @param vec - vector to subtract from this one.
     * @return Vector resulting from subtraction of given vector from this vector.
     */
	Vector2 operator-(const Vector2& vec)const NOEXCEPT{
		return (Vector2(*this) -= vec);
	}

	/**
	 * @brief Subtract vector.
	 * Subtracts 3d vector from this 2d vector. 3rd component of subtracted vector is ignored, i.e.
	 * (this.x, this.y) - (x, y, z) = (this.x - x, this.y -y).
     * @param vec - vector to subtract from this one.
     * @return Resulting two-dimensional vector.
     */
	Vector2 operator-(const Vector3<T>& vec)const NOEXCEPT;
	
	/**
	 * @brief Unary minus.
	 * @return Vector resulting from negating this vector.
	 */
	Vector2 operator-()const NOEXCEPT{
		return Vector2(-this->x, -this->y);
	}

	/**
	 * @brief Multiply by scalar and assign.
	 * Multiplies this vector by scalar and assigns the result back to this vector.
     * @param num - scalar to multiply by.
     * @return Reference to this vector object.
     */
	Vector2& operator*=(T num)NOEXCEPT{
		this->x *= num;
		this->y *= num;
		return (*this);
	}

	/**
	 * @brief Multiply by scalar.
	 * @param num - scalar to multiply by.
	 * @return Vector resulting from multiplication of this vector by given scalar.
	 */
	Vector2 operator*(T num)const NOEXCEPT{
		return (Vector2(*this) *= num);
	}

	/**
	 * @brief Multiply scalar by vector.
     * @param num - scalar to multiply.
     * @param vec - vector to multiply by.
     * @return Vector resulting from multiplication of given scalar by given vector.
     */
	friend Vector2 operator*(T num, const Vector2& vec)NOEXCEPT{
		return vec * num;
	}

	/**
	 * @brief Divide by scalar and assign.
	 * Divides this vector by scalar and assigns the result back to this vector.
     * @param num - scalar to divide by.
     * @return Reference to this vector object.
     */
	Vector2& operator/=(T num)NOEXCEPT{
		ASSERT(num != 0)
		this->x /= num;
		this->y /= num;
		return (*this);
	}

	/**
	 * @brief Divide by scalar.
	 * @param num - scalar to divide this vector by.
	 * @return Vector resulting from dividing this vector by given scalar.
	 */
	Vector2 operator/(T num)const NOEXCEPT{
		ASSERT(num != 0)
		return (Vector2(*this) /= num);
	}

	/**
	 * @brief Dot product.
	 * Dot product of this vector and a given vector.
	 * @return Dot product of two vectors (x1 * x2 + y1 * y2).
	 */
	T operator*(const Vector2& vec)const NOEXCEPT{
		return (this->x * vec.x + this->y * vec.y);
	}

	/**
	 * @brief Check if this vector equals to the given vector.
	 * @param vec - vector to compare to.
	 * @return true if corresponding components of both vectors are equal.
	 * @return false otherwise.
	 */
	bool operator==(const Vector2& vec)const NOEXCEPT{
		return this->x == vec.x && this->y == vec.y;
	}

	/**
	 * @brief Check if this vector is not equal to the given vector.
	 * This is a logical NOT of result from operator==().
	 * @param vec - vector to compare to.
	 * @return true if any of corresponding components of two vectors are not equal.
	 * @return false otherwise.
	 */
	bool operator!=(const Vector2& vec)const NOEXCEPT{
		return !this->operator==(vec);
	}

	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of two vectors.
	 * Resulting vector is (x1 * x2, y1 * y2).
	 * The result of such operation is also vector.
     * @param vec - vector to multiply by.
     * @return Vector resulting from component-wise multiplication.
     */
	Vector2 CompMul(const Vector2& vec)const NOEXCEPT{
		return Vector2(
				this->x * vec.x,
				this->y * vec.y
			);
	}
	
	/**
	 * @brief Component-wise multiplication.
	 * Performs component-wise multiplication of this vector by another given vector.
	 * See CompMul() for details.
     * @param vec - vector to multiply by.
     * @return reference to this Vector2 instance.
     */
	Vector2& CompMulBy(const Vector2& vec)NOEXCEPT{
		this->x *= vec.x;
		this->y *= vec.y;
		return *this;
	}
	
	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of two vectors.
	 * Resulting vector is (x1 / x2, y1 / y2).
	 * The result of such operation is also vector.
     * @param v - vector to divide by.
     * @return Vector resulting from component-wise division.
     */
	Vector2 CompDiv(const Vector2& v)const NOEXCEPT{
		return Vector2(
				this->x / v.x,
				this->y / v.y
			);
	}
	
	/**
	 * @brief Component-wise division.
	 * Performs component-wise division of this vector by another given vector.
	 * See CompDiv() for details.
     * @param v - vector to divide by.
     * @return reference to this Vector2 instance.
     */
	Vector2& CompDivBy(const Vector2& v)NOEXCEPT{
		this->x /= v.x;
		this->y /= v.y;
		return *this;
	}

	/**
	 * @brief Check if both vector components are zero.
	 * @return true if both vector components are zero.
	 * @return false otherwise.
	 */
	bool IsZero()const NOEXCEPT{
		return this->x == 0 && this->y == 0;
	}

	/**
	 * @brief Check if both vector components are positive or zero.
	 * @return true if both vector components are positive or zero.
	 * @return false otherwise.
	 */
	bool IsPositiveOrZero()const NOEXCEPT{
		return this->x >= 0 && this->y >= 0;
	}
	
	/**
	 * @brief Check if both vector components are positive.
	 * @return true if both vector components are positive.
     * @return false otherwise.
     */
	bool IsPositive()const NOEXCEPT{
		return this->x > 0 && this->y > 0;
	}
	
	/**
	 * @brief Check if both vector components are negative.
	 * @return true if both vector components are negative.
     * @return false otherwise.
     */
	bool IsNegative()const NOEXCEPT{
		return this->x < 0 && this->y < 0;
	}

	/**
	 * @brief Negate this vector.
     * @return Reference to this vector object.
     */
	Vector2& Negate()NOEXCEPT{
		//NOTE: this should be faster than (*this) = -(*this);
		this->x = -this->x;
		this->y = -this->y;
		return (*this);
	}

	/**
	 * @brief Absolute vector value.
     * @return Vector2 holding absolute values of this vector's components.
     */
	Vector2 Abs()const NOEXCEPT{
		return Vector2(
				ting::math::Abs(this->x),
				ting::math::Abs(this->y)
			);
	}
	
	/**
	 * @brief Calculate power 2 of vector magnitude.
	 * @return Power 2 of this vector magnitude.
	 */
	T MagPow2()NOEXCEPT{
		return ting::math::Pow2(this->x) + ting::math::Pow2(this->y);
	}

	/**
	 * @brief Calculate magnitude of the vector.
	 * @return magnitude of this vector.
	 */
	T Magnitude()NOEXCEPT{
		return T(ting::math::Sqrt(this->MagPow2()));
	}

	/**
	 * @brief Normalize this vector.
	 * If the magnitude of vector is 0 then the result is vector (1, 0).
	 * @return Reference to this vector object.
	 */
	Vector2& Normalize()NOEXCEPT{
		T mag = this->Magnitude();
		if(mag == 0){
			this->x = 1;
			this->y = 0;
			return *this;
		}
		return (*this) /= this->Magnitude();
	}

	/**
	 * @brief Set both vector components to given value.
	 * @param val - value to set vector components to.
	 * @return Reference to this vector object.
	 */
	Vector2& SetTo(T val)NOEXCEPT{
		this->x = val;
		this->y = val;
		return (*this);
	}

	/**
	 * @brief Rotate vector.
	 * Rotate this vector around (0, 0, 1) axis. Direction of the rotation is
	 * determined by right-hand rule.
     * @param angle - angle of rotation in radians.
     * @return Reference to this vector object.
     */
	Vector2& Rotate(T angle)NOEXCEPT{
		T cosa = ting::math::Cos(angle);
		T sina = ting::math::Sin(angle);
		T tmp = this->x * cosa - this->y * sina;
		this->y = this->y * cosa + this->x * sina;
		this->x = tmp;
		return (*this);
	}

	/**
	 * @brief Rotation of vector.
	 * Calculate vector resulting from rotation this vector around (0, 0, 1) axis.
	 * Direction of the rotation is determined by right-hand rule.
	 * @param angle - angle of rotation in radians.
	 * @return Vector resulting from rotation of this vector.
	 */
	Vector2 Rotation(T angle)const NOEXCEPT{
		return Vector2(*this).Rotate(angle);
	}

	
	Vector2& Round()NOEXCEPT{
		this->x = ting::math::Round(this->x);
		this->y = ting::math::Round(this->y);
		return *this;
	}
	
	
	Vector2 Rounded()const NOEXCEPT{
		return Vector2(*this).Round();
	}
	
	
	
	/**
	 * @brief Convert to Vector2 with different type of component.
	 * Convert this Vector2 to a Vector2 whose component type is different from T.
	 * Components are converted using constructor of target type passing the source
	 * component as argument of the target type constructor.
     * @return converted Vector2.
     */
	template <class TS> Vector2<TS> to()const NOEXCEPT{
		return Vector2<TS>(TS(this->x), TS(this->y));
	}
	

	
#ifdef DEBUG  
	friend std::ostream& operator<<(std::ostream& s, const Vector2<T>& vec){
		s << "(" << vec.x << ", " << vec.y << ")";
		return s;
	}
#endif
};//~class Vector2



}//~namespace



#include "Vector3.hpp"



namespace morda{

//==========================
// functions implementation
//==========================

template <class T> Vector2<T>::Vector2(const Vector3<T>& vec)NOEXCEPT{
	this->operator=(vec);
}



template <class T> Vector2<T>& Vector2<T>::operator=(const Vector3<T>& vec)NOEXCEPT{
	this->x = vec.x;
	this->y = vec.y;
	return (*this);
}



template <class T> Vector2<T> Vector2<T>::operator+(const Vector3<T>& vec)const NOEXCEPT{
	return Vector2<T>(
				this->x + vec.x,
				this->y + vec.y
			);
}



template <class T> Vector2<T> Vector2<T>::operator-(const Vector3<T>& vec)const NOEXCEPT{
	return Vector2<T>(
				this->x - vec.x,
				this->y - vec.y
			);
}



//=====================
// Convenient typedefs
//=====================

typedef Vector2<bool> Vec2b;
static_assert(sizeof(Vec2b) == sizeof(bool) * 2, "size mismatch");

typedef Vector2<int> Vec2i;
static_assert(sizeof(Vec2i) == sizeof(int) * 2, "size mismatch");

typedef Vector2<unsigned> Vec2ui;
static_assert(sizeof(Vec2ui) == sizeof(unsigned) * 2, "size mismatch");

typedef Vector2<float> Vec2f;
static_assert(sizeof(Vec2f) == sizeof(float) * 2, "size mismatch");

typedef Vector2<double> Vec2d;
static_assert(sizeof(Vec2d) == sizeof(double) * 2, "size mismatch");

typedef Vector2<real> Vec2r;
static_assert(sizeof(Vec2r) == sizeof(real) * 2, "size mismatch");


}//~namespace
