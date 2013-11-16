#ifndef _ERPOINT_H_
#define _ERPOINT_H_

class ERPoint
{
public:
	ERPoint();
	ERPoint(float x, float y);
	~ERPoint();
	void setPoint(float x, float y);
	float getX();
	float getY();

private:
	float _x;
	float _y;
};

#endif