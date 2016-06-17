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
		int m_NumberWindings;
	public:
		Motor();
		Motor(RatedData &ratedData);
		Motor(RatedData &ratedData, std::vector<RatingInsulation *> &vectorWindings, std::vector<std::string> vectorNameWindings);
		void setVectorWindings(RatingInsulation *rate);
		RatingInsulation *returnsRatingInsulation(int i);
		RatedData *returnsm_RatedData(){return &m_RatedData;}
		void writeMotor(const std::string &name)const;
		void getMotor(const std::string &name);
		std::string &returnsNameWinding(int i){return m_VectorNameWindings[i];}
		int returnsm_NumberWindings()const{return m_NumberWindings;}
		std::vector<std::string> *returnsVectorNameWinding(){return &m_VectorNameWindings;}
		~Motor(){}
};

#endif // rn
