#ifndef GLINKA2_H
#define GLINKA2_H
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
	struct TechnicalData
	{
			double m_RatedVoltage;
			double m_TestVoltage;
			double m_MaxVoltage;
			double m_ResistanceAfter60s;
			double m_ResistanceAfter15s;
			double m_TimeShortCircuit;
			double m_TimeReconstruction;
			std::pair<double, double> m_PairMinVoltageTime;
			std::pair<double, double> m_PairMaxVoltageTime;
	};
	TechnicalData m_TechnicalData;
	std::multimap<double, double> m_MMGlinkaVoltageTime;
public:
	Test();
	Test(const Test &ts);
	Test(double rV, double tV, double mV, double r60, double r15, double tSC, double tR, std::multimap<double, double> &gl,
		 std::pair<double, double> &pMaxV, std::pair<double, double> &pMinV);
	~Test(){}
	void reconstruction(const std::string &name);
	void restoreTestInitialValue();
	double returnsRatedVoltage()const{ return m_TechnicalData.m_RatedVoltage;}
	double returnsTestVoltage()const{ return m_TechnicalData.m_TestVoltage;}
	double returnsMaxVoltage()const{ return m_TechnicalData.m_MaxVoltage;}
	double returnsTimeReconstruction()const{return  m_TechnicalData.m_TimeReconstruction;}
	double returnsResistanceAfter60s()const{ return m_TechnicalData.m_ResistanceAfter60s;}
	double returnsResistanceAfter15s() const{return m_TechnicalData.m_ResistanceAfter15s;}
	double returnsTimeShortCircuit()const{return m_TechnicalData.m_TimeShortCircuit;}

	std::pair<double, double> returnsPairMinVoltageTime()const {return m_TechnicalData.m_PairMinVoltageTime;}
	std::pair<double, double> returnsPairMaxVoltageTime()const {return m_TechnicalData.m_PairMaxVoltageTime;}
	std::pair<double, double> &returnsPairMinVoltageTime(){return m_TechnicalData.m_PairMinVoltageTime;}
	std::pair<double, double> &returnsPairMaxVoltageTime(){return m_TechnicalData.m_PairMaxVoltageTime;}


	void setRatedVoltage(double rV){ m_TechnicalData.m_RatedVoltage = rV;}
	void setTestVoltage(double tV){ m_TechnicalData.m_TestVoltage = tV;}
	void setMaxVoltage(double mV){ m_TechnicalData.m_MaxVoltage = mV;}
	void setResistanceAfter60s(double r60){  m_TechnicalData.m_ResistanceAfter60s = r60;}
	void setResistanceAfter15s(double r15){ m_TechnicalData.m_ResistanceAfter15s = r15;}
	void setTimeShortCircuit(double tSC){ m_TechnicalData.m_TimeShortCircuit = tSC;}
	void setTimeReconstruction(double tR){ m_TechnicalData.m_TimeReconstruction = tR;}
	std::multimap<double, double> returnsm_MMGlinkaVoltageTime(){ return m_MMGlinkaVoltageTime;}

	void setTest();
	void writeTest(const std::string &name)const;
	std::streampos getTest(const std::string &name, std::streampos place = 0);
	void showTest()const;
	void resetTest();
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

	struct Rating
	{
		double m_Resistance60sDivTestVoltage;
		double m_MaxVoltageDivTestVoltage;
		double m_Resistance60sDivResistance15s;
		int m_RateResistance60sDivTestVoltage;
		int m_RateTimeShortCircuit;
		int m_RateTimeReconstruction;
		int m_RateMaxVoltageDivTestVoltage;
		int m_RateResistance60DivResistance15s;
		double m_RateTotal;
	};
	Rating m_Rating;
	int rateResistance60sDivTestVoltage();
	int rateTimeShortCircuit();
	int rateTimeReconstruction();
	int	rateMaxVoltageDivTestVoltage();
	int rateResistance60DivResistance15s();
public:
	RatingInsulation();
	RatingInsulation(const Test &ts);
	RatingInsulation(const Test &ts, double r60DivTV, double mVdivTV, double r60Divr15);
	RatingInsulation(RatingInsulation &rI);
	~RatingInsulation(){}

	double returnsTTimeShortCircuit()const {return Test::returnsTimeShortCircuit();}
	double returnsTTimeReconstruction()const {return Test::returnsTimeReconstruction();}
	double returnsResistance60sDivTestVoltage()const {return m_Rating.m_Resistance60sDivTestVoltage;}
	double returnsMaxVoltageDivTestVoltage()const {return m_Rating.m_MaxVoltageDivTestVoltage;}
	double returnsResistance60DivResistance15s()const {return m_Rating.m_Resistance60sDivResistance15s;}

	int returnsRateResistance60sDivTestVoltage()const {return m_Rating.m_RateResistance60sDivTestVoltage;}
	int returnsRateTimeShortCircuit()const {return m_Rating.m_RateTimeShortCircuit;}
	int returnsRateTimeReconstruction()const {return m_Rating.m_RateTimeReconstruction;}
	int returnsRateMaxVoltageDivTestVoltage()const {return m_Rating.m_RateMaxVoltageDivTestVoltage;}
	int returnsRateResistance60DivResistance15s()const {return m_Rating.m_RateResistance60DivResistance15s;}
	Test &returnsTest();
	double returnsRateTotal()const {return m_Rating.m_RateTotal;}

	void restoreRateInitialValue();
	void resetPlotRate();

	void writeRatingInsulation(const std::string &name)const;
	std::streampos getRatingInsulation(const std::string &name, std::streampos place = 0);
	void showRate()const;
	double rateTotal();
	void resetRate();
};
#endif // GLINKA2_H
