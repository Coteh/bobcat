#pragma once
#include "Collider.h"

namespace bobcat {

	class BoxCollider : public Collider{
	private:
		float m_width, m_height, m_length;
	public:
		BoxCollider();
		~BoxCollider();
		virtual glm::vec3 getDimensions();
		virtual void setDimensions(float _width, float _height, float _length);
		virtual void setDimensions(glm::vec3 _dim);

		float getWidth();
		float getHeight();
		float getLength();
		void setWidth(float _width);
		void setHeight(float _height);
		void setLength(float _length);

		__declspec(property(get = getWidth, put = setWidth)) float width;
		__declspec(property(get = getHeight, put = setHeight)) float height;
		__declspec(property(get = getLength, put = setLength)) float length;
	};

}