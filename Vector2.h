#pragma once
#include <cmath>

struct Vector2
{
public:
	float X{ 0 };
	float Y{ 0 };


	/**
	 * Creates a Vector2 struct with the default values 0,0
	 */
	Vector2() = default;
	/**
	 * Creates a Vector2 struct with the input values
	 */
	Vector2(const float p_xInput, const float p_yInput)
	{
		X = p_xInput;
		Y = p_yInput;
	}

	void Clear()
	{
		X = 0;
		Y = 0;
	}
	/**
	 * Returns a copy of the two vectors added together
	 * @param p_vectorB Vector to add to this
	 * @return Finished operation
	 */
	Vector2 operator+(Vector2 const& p_vectorB) const
	{
		return {X + p_vectorB.X, Y + p_vectorB.Y};
	}

	// Overload the += operator
	void operator+=(const Vector2& p_vectorB)
	{
		//Adding two vectors is like placing them end to end and ending up in a point from the origin equalling the two
		X += p_vectorB.X;
		Y += p_vectorB.Y;
	}


	float operator%(const Vector2& p_vectorB) const
	{
		//Formula for cross product in 2d space AxB = X1 * Y2 - Y1 * X2 resulting in scalar
		//AxB > 0 B is counterclockwise from A
		//AxB < 0 B is clockwise from A
		//AxB == 0 A and B are collinear
		return X * p_vectorB.Y - Y * p_vectorB.X;
	}
	/**
	 * Subtracts another Vector from this Vector
	 * @param p_vectorB Vector to subtract from this
	 * @return Finished operation
	 */
	Vector2 operator-(Vector2 const& p_vectorB) const
	{
		return {X - p_vectorB.X, Y - p_vectorB.Y};
	}

	/**
	 * 
	 * @return Inverse version of the vector
	 */
	Vector2 operator-() const
	{
		return {-X,-Y};
	}

	void AddScaledVector(const Vector2& p_VectorB, const float p_scalar)
	{
		X += p_VectorB.X * p_scalar;
		Y += p_VectorB.Y * p_scalar;

	}


	/**
	* Multiplies both axis by the input scalar value
	* @param p_scalar Multiplier
	*/
	void operator*=(float const p_scalar) 
	{
		//Multiplies the vector by a scalar (x,y) * k = (kx,ky) k being the scalar value
		//Basically just multiply all component values by the scalar

		//Just changes the magnitude by multiplying by scalar but not the direction so ka = (k*|a|)*n^
		X = X * p_scalar;
		Y = Y * p_scalar;
	}


	/**
	 * Returns a copy of this vector scaled by the given value
	 * @param p_scalar Multiplier
	 * @return Finished operation
	 */
	Vector2 operator*(float const p_scalar) const
	{
		//Multiplies the vector by a scalar (x,y) * k = (kx,ky) k being the scalar value
		//Basically just multiply all component values by the scalar 
		return { X * p_scalar, Y * p_scalar };
	}

	float operator*(Vector2 const p_vectorB) const
	{
		//Dot /Scalar product formula
		//a.b = (ax,ay).(bx,by) = (ax*bx)+(ay*by) 
		//Scalar product or commonly know as dot product due to A.B being the notation  
		return { (X * p_vectorB.X) + (Y * p_vectorB.Y) }; 
	}
	/**
	 * Compares two vectors to check whether they are equal
	 * @param p_vectorB Vector to compare
	 * @return 
	 */
	bool operator==(const Vector2& p_vectorB) const
	{
		return (X == p_vectorB.X && Y == p_vectorB.Y);
	}

	/**
	 * Divides the vector by the denominator input
	 * @return Copy of this vector divided by input
	 */
	Vector2 operator/(const float p_denominator) const
	{
		//Same as multiplication you just divide each component (numerators) by the scalar (denominator) = (x/k, y/k) k being scalar value
		return { X / p_denominator, Y / p_denominator };
	}

	/**
	 * Calculates and returns a component product of this vector with a given vector
	 * @return Copy of this vector component product
	 */
	Vector2 ComponentProduct(const Vector2& p_vectorB) const
	{
		return { X * p_vectorB.X, Y * p_vectorB.Y };
	}

	/**
	* Calculates and returns a component product of this vector with a given vector
	* and updates the values of this vector to its result
	*/
	void ComponentProductUpdate(const Vector2& p_vectorB)
	{
		X *= p_vectorB.X;
		Y *= p_vectorB.Y;
	}
	Vector2 Inverse() const
	{
		//Formula for inverse ->-a = -1 * a = (-1x,-1y)
		Vector2 inverse = { X,Y };
		inverse = inverse * -1;
		return inverse;
	}
	/**
	 * @return The magnitude of the vector
	 */
	float Magnitude() const
	{
		//|V| = sqrt(a^2 + b^2)
		//To get magnitude square both components and add them then find sqrt
		return std::sqrt(X * X + Y * Y);
		
	}

	/**
	 * @return A normalized Vector2
	 */
	Vector2 Normalize() const
	{
		//Normalized vector or the unit vector (kinda)
		//To get normalized vector divide each component by its magnitude

		//Formula for normalization = 
		const float mag = Magnitude();
		return { X / mag, Y / mag };
	}

	static Vector2 Zero()
	{
		return { 0,0 };
	}
	void Lerp(const Vector2& p_vectorB, const float p_factor) 
	{
		X = (X * (1.0f - p_factor) + (p_vectorB.X * p_factor));
		Y = (Y * (1.0f - p_factor) + (p_vectorB.Y * p_factor));

	}


	/**
	 * Finds the distance between two input vectors
	 * @return Distance in floating point
	 */
	static inline float Distance(const Vector2& p_vectorA, const Vector2& p_vectorB)
	{
		// Correct formula: square of the differences
		const float deltaX = p_vectorA.X - p_vectorB.X;
		const float deltaY = p_vectorA.Y - p_vectorB.Y;

		// Now apply the correct distance formula
		const float distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));

		return distance;
	}

	

	static inline float Angle(const Vector2& p_vectorA, const Vector2& p_vectorB)
	{
		const float dot = p_vectorA * p_vectorB;

		const float magA = p_vectorA.Magnitude();
		const float magB = p_vectorB.Magnitude();

		const float angleInRadians = acos(dot / (magA * magB));

		const float angleInDegrees = angleInRadians * 57.29 ; // 
		return angleInDegrees;
	}

	

};


