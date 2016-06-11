#include "motor.h"

Motor::Motor(int numberWindings)
{
	for (int i=0; i<numberWindings; ++i)
		m_VectorWindings.push_back(new RatingInsulation());
}
RatingInsulation & Motor::returnsRatingInsulation(int numberWinding)
{
	return *m_VectorWindings[numberWinding];
}
