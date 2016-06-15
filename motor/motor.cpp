#include "motor.h"

Motor::Motor(int numberWindings)
{
	m_RatedData.m_Name = "---";
	m_RatedData.m_Type = "---";
	m_RatedData.m_Number = "---";
	m_RatedData.m_Power = 0.0;
	m_NumberWindings = numberWindings;

	for (int i=0; i<m_NumberWindings; ++i)
		m_VectorNameWindings.push_back("---");

	for (int i=0; i<m_NumberWindings; ++i)
		m_VectorWindings.push_back(new RatingInsulation());
}
Motor::Motor(int numberWindings, RatedData &ratedData)
{
	m_RatedData.m_Name = ratedData.m_Name;
	m_RatedData.m_Type = ratedData.m_Type;
	m_RatedData.m_Number = ratedData.m_Number;
	m_RatedData.m_Power = ratedData.m_Power;
	m_NumberWindings = numberWindings;

	for (int i=0; i<m_NumberWindings; ++i)
		m_VectorNameWindings.push_back("---");

	for (int i=0; i<m_NumberWindings; ++i)
		m_VectorWindings.push_back(new RatingInsulation());
}
Motor::Motor(int numberWindings, RatedData &ratedData, std::vector<RatingInsulation *> &vectorWindings, std::vector<std::string> vectorNameWindings)
{
	m_RatedData.m_Name = ratedData.m_Name;
	m_RatedData.m_Type = ratedData.m_Type;
	m_RatedData.m_Number = ratedData.m_Number;
	m_RatedData.m_Power = ratedData.m_Power;
	m_NumberWindings = numberWindings;

	m_VectorNameWindings = vectorNameWindings;

	m_VectorWindings = vectorWindings;
}

RatingInsulation & Motor::returnsRatingInsulation(int numberWinding)
{
	return *m_VectorWindings[numberWinding];
}
