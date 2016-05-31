/*
 * glinka.h
 *
 *  Created on: 28-04-2016
 *      Author: teodor
 */

#ifndef RATINGINSULATION_H_
#define RATINGINSULATION_H_
#include<iostream>
#include<fstream>
#include<map>
#include<cstdlib>
#include<iomanip>
#include<iterator>
#include<algorithm>
#include<utility>
#include<cmath>

class Test
{
private:
	double m_RatedVoltage;
	double m_TestVoltage;
	double m_MaxVoltage;
	double m_ResistanceAfter60s;
	double m_ResistanceAfter15s;
	double m_TimeShortCircuit;
	double m_TimeReconstruction;
	std::multimap<double, double> glinka;
public:
	Test();
	virtual ~Test(){}
	void reconstruction(const std::string &name);
	double returnsRatedVoltage()const{ return m_RatedVoltage;}
	double returnsTestVoltage()const{ return m_TestVoltage;}
	double returnsMaxVoltage()const{ return m_MaxVoltage;}
	double returnsTimeReconstruction()const{return  m_TimeReconstruction;}
	double returnsResistanceAfter60s()const{ return m_ResistanceAfter60s;}
	double returnsResistanceAfter15s() const{return m_ResistanceAfter15s;}
	double returnsTimeShortCircuit()const{return m_TimeShortCircuit;}
	double &returnsRatedVoltage(){ return m_RatedVoltage;}
	double &returnsTestVoltage(){ return m_TestVoltage;}
	double &returnsMaxVoltage(){ return m_MaxVoltage;}
	double &returnsResistanceAfter60s(){ return m_ResistanceAfter60s;}
	double &returnsResistanceAfter15s(){return m_ResistanceAfter15s;}
	double &returnsTimeShortCircuit(){return m_TimeShortCircuit;}
	std::multimap<double, double> returnsGlinka(){return glinka;}
	void setTest();
	void showTest()const;
};
class RatingInsulation: private Test
{
private:
	static const int TOTAL=5;
	static const int SN=6000;
	static std::map<int, int> s_CriteriaResistance60sDivTestVoltageSN;
	static std::map<int, int> s_CriteriaResistance60sDivTestVoltagenN;
	static std::map<int, int> s_CriteriaTimeReconstructionSN;
	static std::map<int, int> s_CriteriaTimeReconstructionnN;
	static std::map<int, int> s_CriteriaTimeShortCircuitSN;
	static std::map<int, int> s_CriteriaTimeShortCircuitnN;
	static std::map<double, int> s_CriteriaMaxVoltageDivTestVoltage;
	static std::map<double, int> s_CriteriaResistance60DivResistance15sSN;
	static std::map<double, int> s_CriteriaResistance60DivResistance15snN;
	double m_Resistance60sDivTestVoltage;
	double m_MaxVoltageDivTestVoltage;
	double m_Resistance60sDivResistance15s;
	int m_RateResistance60sDivTestVoltage;
	int m_RateTimeShortCircuit;
	int m_RateTimeReconstruction;
	int m_RateMaxVoltageDivTestVoltage;
	int m_RateResistance60DivResistance15s;
	double m_RateTotal;
	int rateResistance60sDivTestVoltage();
	int rateTimeShortCircuit();
	int rateTimeReconstruction();
	int	rateMaxVoltageDivTestVoltage();
	int rateResistance60DivResistance15s();
public:
	RatingInsulation();
	RatingInsulation(const Test &ts);
	virtual ~RatingInsulation(){}
	double returnsTTimeShortCircuit()const {return returnsTimeShortCircuit();}
	double returnsTTimeReconstruction()const {return returnsTimeReconstruction();}
	double returnsResistance60sDivTestVoltage()const {return m_Resistance60sDivTestVoltage;}
	double returnsMaxVoltageDivTestVoltage()const {return m_MaxVoltageDivTestVoltage;}
	double returnsResistance60DivResistance15s()const {return m_Resistance60sDivResistance15s;}
	int returnsRateResistance60sDivTestVoltage()const {return m_RateResistance60sDivTestVoltage;}
	int returnsRateTimeShortCircuit()const {return m_RateTimeShortCircuit;}
	int returnsRateTimeReconstruction()const {return m_RateTimeReconstruction;}
	int returnsRateMaxVoltageDivTestVoltage()const {return m_RateMaxVoltageDivTestVoltage;}
	int returnsRateResistance60DivResistance15s()const {return m_RateResistance60DivResistance15s;}
	double rateTotal();
	double returnsRateTotal()const {return m_RateTotal;}
	void showRate()const;
};




#endif /* RATINGINSULATION_H_ */
