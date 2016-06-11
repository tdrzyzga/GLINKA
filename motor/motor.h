#ifndef MOTOR_H
#define MOTOR_H

#include "glinka2/glinka2.h"

class Motor
{
	private:
		std::vector<RatingInsulation *> m_VectorWindings;

	public:
		Motor(int numberWindings);
		RatingInsulation &returnsRatingInsulation(int numberWinding);
		~Motor(){}
};

#endif // MOTOR_H
