#include "motor.h"

Motor::Motor()
{
	m_RatedData.m_Name = "---";
	m_RatedData.m_Type = "---";
	m_RatedData.m_Number = "---";
	m_RatedData.m_Power = 0.0;
	m_NumberWindings = 1;

	/*for (int i=0; i<m_NumberWindings; ++i)
		m_VectorNameWindings.push_back("---");

	for (int i=0; i<m_NumberWindings; ++i)
		m_VectorWindings.push_back(new RatingInsulation());*/
}
Motor::Motor(RatedData &ratedData)
{
	m_RatedData.m_Name = ratedData.m_Name;
	m_RatedData.m_Type = ratedData.m_Type;
	m_RatedData.m_Number = ratedData.m_Number;
	m_RatedData.m_Power = ratedData.m_Power;
	m_NumberWindings = 1;
}
Motor::Motor(RatedData &ratedData, std::vector<RatingInsulation *> &vectorWindings, std::vector<std::string> vectorNameWindings)
{
	m_RatedData.m_Name = ratedData.m_Name;
	m_RatedData.m_Type = ratedData.m_Type;
	m_RatedData.m_Number = ratedData.m_Number;
	m_RatedData.m_Power = ratedData.m_Power;
	m_NumberWindings = 1;

	m_VectorNameWindings = vectorNameWindings;

	m_VectorWindings = vectorWindings;
}

void Motor::setVectorWindings(RatingInsulation *rate)
{
	m_VectorWindings.push_back(rate);
	++m_NumberWindings;
}
