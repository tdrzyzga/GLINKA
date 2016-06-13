#include "motor.h"

Motor::Motor(int numberWindings)
{
	m_RatedData.m_Name = "---";
	m_RatedData.m_Type = "---";
	m_RatedData.m_Number = "---";
	m_RatedData.m_Power = 0.0;
	for (int i=0; i<numberWindings; ++i)
		m_VectorWindings.push_back(new RatingInsulation());
}
RatingInsulation & Motor::returnsRatingInsulation(int numberWinding)
{
	return *m_VectorWindings[numberWinding];
}
