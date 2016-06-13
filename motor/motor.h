#ifndef MOTOR_H
#define MOTOR_H

#include "glinka2/glinka2.h"
struct RatedData
{
	std::string m_Name;
	std::string m_Type;
	std::string m_Number;
	float m_Power;
};
class Motor
{
	private:
		RatedData m_RatedData;
		std::vector<std::string> m_VectorNameWindings;
		std::vector<RatingInsulation *> m_VectorWindings;

	public:
		Motor(int numberWindings);
		Motor(int numberWindings, RatedData &ratedData);
		Motor(int numberWindings, RatedData &ratedData, std::vector<RatingInsulation *> &vectorWindings, std::vector<std::string> vectorNameWindings);
		RatingInsulation &returnsRatingInsulation(int numberWinding);
		RatedData &returnsStructRatedData() {return m_RatedData;}
		~Motor(){}
};

#endif // rn
