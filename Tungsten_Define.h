#ifndef _TUNGSTEN_DEFINE_H
#define _TUNGSTEN_DEFINE_H
#pragma once

#include <ctime>
#include <queue>
#include <opencv2/opencv.hpp>
#define UNIT_TRANSFORM 100000
#define PEXEL2MM_FACTOR -0.55f
#define VISION_COOR_RAD -0.0129852f
#define VISION_COOR_X -495.f
#define VISION_COOR_Y 0.f
#define HOME_X -110.594f
#define HOME_Y 539.505f


struct TgWorld;
struct TgPoint {
public:
	TgPoint() : x(0), y(0), z(0) {}
	TgPoint(int x, int y, int z) { set(x, y, z); }

	void set(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void setZ(int z) { this->z = z; }

	const int X() const { return x; }
	const int Y() const { return y; }
	const int Z() const { return z; }

	TgPoint& operator=(const TgPoint& ref)
	{
		this->x = ref.x;
		this->y = ref.y;
		this->z = ref.z;

		return *this;
	}

protected:
	int x;
	int y;
	int z;
};

struct TgWorld : TgPoint {
public:
	friend class ScRobot;
	TgWorld() : TgPoint(0, 0, 0), c(0) {}
	TgWorld(int x, int y, int z, int c) { set(x, y, z, c); }
	TgWorld(float x, float y, float z, float c) { set(x, y, z, c); }

	void set(int x, int y, int z, int c)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->c = c;
	}
	void set(float x, float y, float z, float c)
	{
		this->x = (int)(x * UNIT_TRANSFORM);
		this->y = (int)(y * UNIT_TRANSFORM);
		this->z = (int)(z * UNIT_TRANSFORM);
		this->c = (int)(c * UNIT_TRANSFORM);
	}
	void setX(float x) { this->x = (int)(x * UNIT_TRANSFORM); }
	void setY(float y) { this->y = (int)(y * UNIT_TRANSFORM); }
	void setZ(float z) { this->z = (int)(z * UNIT_TRANSFORM); }
	void setC(float c) { this->c = (int)(c * UNIT_TRANSFORM); }

	const float X() const { return (float)x / UNIT_TRANSFORM; }
	const float Y() const { return (float)y / UNIT_TRANSFORM; }
	const float Z() const { return (float)z / UNIT_TRANSFORM; }
	const float C() const { return (float)c / UNIT_TRANSFORM; }

	TgWorld& operator=(const TgWorld& ref)
	{
		this->x = ref.x;
		this->y = ref.y;
		this->z = ref.z;
		this->c = ref.c;

		return *this;
	}

private:
	int c;
};

TgPoint parseVisionCoordinate(const cv::Point& img_point, const cv::Mat& img);
TgWorld parseWorldCoordinate(TgPoint& vision_position);

struct TgObject
{
	int     id;
	time_t  time;
	TgPoint vision_point;
};

typedef std::queue<TgObject*> ObjectQueue;

#endif