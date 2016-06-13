#ifndef MOTOR_H
#define MOTOR_H

#include "glinka2/glinka2.h"

class Motor
{
	private:
		struct RatedData
		{
			std::string m_Name;
			std::string m_Type;
			std::string m_Number;
			float m_Power;
		};
		RatedData m_RatedData;
		std::vector<RatingInsulation *> m_VectorWindings;

	public:
		Motor(int numberWindings);
		RatingInsulation &returnsRatingInsulation(int numberWinding);
		std::string &returnsName() {return m_RatedData.m_Name;}
		std::string &returnsType() {return m_RatedData.m_Type;}
		std::string &returnsNumber(){return m_RatedData.m_Number;}
		float &retunsPower() {return m_RatedData.m_Power;}
		~Motor(){}
};

#endif // MOTOR_H
