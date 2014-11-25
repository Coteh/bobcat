#pragma once
class Collider {
public:
	virtual ~Collider(){};
	virtual float getScale() = 0;
	virtual void setScale(float _scaleAmt) = 0;
	virtual void setDimensions(float _width, float _height, float _length) = 0;
	virtual void setDimensions(float _radius) = 0;
};

