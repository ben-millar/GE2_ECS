#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	float x, y;
	Vector2(int t_x = 0.0f, int t_y = 0.0f) : x(t_x), y(t_y) {}

	Vector2& operator+=(const Vector2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	////////////////////////////////////////////////////////////

	Vector2 operator+(const Vector2& rhs)
	{
		return Vector2(this->x + rhs.x, this->y + rhs.y);
	}

	////////////////////////////////////////////////////////////

	Vector2 operator*(const float& rhs)
	{
		return Vector2(this->x * rhs, this->y * rhs);
	}
};

#endif