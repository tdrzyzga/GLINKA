#ifndef MOTOR_H
#define MOTOR_H

#include <memory>

#include "glinka2/glinka2.h"
//
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
		std::vector<std::shared_ptr<RatingInsulation>> m_VectorWindings;
		int m_NumberWindings;
	public:
		Motor();
		Motor(RatedData &ratedData);
		Motor(RatedData &ratedData, std::vector<std::shared_ptr<RatingInsulation>> &vectorWindings, std::vector<std::string> vectorNameWindings);

		void writeMotor(const std::string &name)const;
		void getMotor(const std::string &name);

		void setVectorWindings(std::shared_ptr<RatingInsulation> rate);
		std::shared_ptr<RatingInsulation> returnsRatingInsulation(int i);

		RatedData &setRatedData(){return m_RatedData;}
		int returnsm_NumberWindings()const{return m_NumberWindings;}

		std::string &returnsNameWinding(int i){return m_VectorNameWindings[i];}
		std::vector<std::string> &setVectorNameWinding(){return m_VectorNameWindings;}
		~Motor(){}
};

#endif // rn
