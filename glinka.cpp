/*
 * glinka.cpp
 *
 *  Created on: 28-04-2016
 *      Author: teodor
 */

#include "glinka.h"
#include "mainwindow.h"


void Test::reconstruction(const std::string &name)
{
	using namespace std;
	ifstream infile;
	infile.open(name, std::ios::in);

	if (!infile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}

	//multimap<double, double> glinka;
	pair<double, double> temp_glinka;
	pair<double, double> min;
	bool min_get = false;
	while (infile >> temp_glinka.second && infile >> temp_glinka.first)
	{
		if (temp_glinka.first >= 0.09 && !min_get)
		{
			min = temp_glinka;
			min_get = true;
		}
		glinka.insert(temp_glinka);
	}
	infile.close();

	multimap<double, double>::reverse_iterator max=glinka.rbegin();

/*	cout <<left<<setw(50)<< "Rozpoczecie odbudowy napiecia: " << fixed << setprecision(1)
			<<setw(7)<<right<< min.first << " V"<<left << " Czas: " << setw(6)<<setprecision(2) <<right<< min.second
			<< " s" << endl;
	cout <<left<<setw(50)<< "Maksymalne napiecie odbudowy: " << fixed << setprecision(1)
			<<setw(7)<<right<< max->first << " V" <<left<< " Czas: " << setw(6)<< setprecision(2) <<right<< max->second
			<< " s" << endl;
	cout <<left<<setw(50)<< "Czas odbudowy napiecia: " << fixed  << setprecision(2)
			<<setw(7)<<right<< max->second - min.second << " s" << endl;
*/
	m_TimeReconstruction=max->second-min.second;
	m_MaxVoltage=max->first;
	//gl.insert(glinka.begin(), glinka.end());

}

Test::Test()
{
	m_RatedVoltage = 0.0;
	m_TestVoltage = 0.0;
	m_MaxVoltage = 0.0;
	m_ResistanceAfter60s = 0.0;
	m_ResistanceAfter15s = 0.0;
	m_TimeShortCircuit = 0.0;
	m_TimeReconstruction = 0.0;
}
void Test::setTest()
{
	using std::cout;
	using std::cin;
	std::string name;
	cout << "Podaj nazwę pliku do przetworzenia: ";
	getline(cin, name);
	//std::pair<double, double> temp;
	//temp=Reconstruction(name);
	//m_TimeReconstruction = temp.second;
	//max_voltage = temp.first;
	cout << "Napięcie znamonowe [V]: ";
	cin >> m_RatedVoltage;
	cout << "Napięcie probiercze [V]: ";
	cin >> m_TestVoltage;
	//cout<<"Maksymalne napięcie odbudowy: ";
	//cin>>max_voltage;
	cout << "Rezystancja po 60 sekundach [kOhm]: ";
	cin >> m_ResistanceAfter60s;
	cout << "Rezystancja po 15 sekundach [kOhm]: ";
	cin >> m_ResistanceAfter15s;
	cout << "Czas zwarcia [s]: ";
	cin >> m_TimeShortCircuit;
	//cout<<"Czas odbudowy napięcia [s]: ";
	//cin>>m_TimeReconstruction;
}
void Test::showTest() const
{
	using std::cout;
	using std::endl;
	using std::fixed;
	using std::setprecision;
	using std::left;
	using std::right;
	using std::setw;
	const int wt=50;
	const int wt2=12;

	cout  << fixed << setprecision(2);
	cout <<setw(wt)<<left<< "Napiecie znamonowe: " << setw(wt2)<<right
			<< m_RatedVoltage<< " V" << endl;
	cout <<setw(wt)<<left<< "Napiecie probiercze: " << setw(wt2)<<right
			<< m_TestVoltage<< " V" << endl;
	cout <<setw(wt)<<left<< "Maksymalne napiecie odbudowy: " << setw(wt2)<<right
			<< m_MaxVoltage << " V" << endl;
	cout <<setw(wt)<<left<< "Rezystancja po 60 sekundach: " << setw(wt2)<<right
			<< m_ResistanceAfter60s << " kOhm" << endl;
	cout <<setw(wt)<<left<< "Rezystancja 15 sekundach: " << setw(wt2)<<right
			<< m_ResistanceAfter15s << " kOhm" << endl;
	//cout<<"Czas zwarcia: "<<fixed<<setprecision(2)<<m_TimeShortCircuit<<" s"<<endl;
	//cout<<"Czas odbudowy napięcia: "<<fixed<<setprecision(2)<<m_TimeReconstruction<<" s"<<endl;
}

std::map<int, int> RatingInsulation::s_CriteriaResistance60sDivTestVoltageSN = {
		{ 50, 5 },
		{ 20, 4 },
		{ 10, 3 },
		{ 3, 0 }
};
std::map<int, int> RatingInsulation::s_CriteriaResistance60sDivTestVoltagenN =
{
		{ 50, 5 },
		{ 20, 4 },
		{ 10, 3 },
		{ 3, 2 },
		{ 2, 1 },
		{ 1, 0 }
};
std::map<int, int> RatingInsulation::s_CriteriaTimeReconstructionSN =
{
		{ 240, 5 },
		{ 120, 4 },
		{ 30, 3 },
		{ 10, 2 },
		{ 0, 1 }
};
std::map<int, int> RatingInsulation::s_CriteriaTimeReconstructionnN =
{
		{ 120, 5 },
		{ 60, 4 },
		{ 15, 3 },
		{ 5, 2 },
		{ 0, 0 }
};
std::map<int, int> RatingInsulation::s_CriteriaTimeShortCircuitSN =
{
		{ 30, 5 },
		{ 1, 2 },
		{0, 0 }
};
std::map<int, int> RatingInsulation::s_CriteriaTimeShortCircuitnN =
{
		{ 10, 5 },
		{ 1, 2 },
		{ 0, 1 }
};
std::map<double, int> RatingInsulation::s_CriteriaMaxVoltageDivTestVoltage =
{
		{ 0.106, 5 },
		{ 0.100, 4 },
		{ 0.050, 3 },
		{ 0.010, 1 },
		{ 0.000, 0 }
};
std::map<double, int> RatingInsulation::s_CriteriaResistance60DivResistance15sSN =
{
		{ 1.5, 5 },
		{ 1.2,4 },
		{ 1.0, 3 },
};
std::map<double, int> RatingInsulation::s_CriteriaResistance60DivResistance15snN =
{
		{ 1.3, 5 },
		{ 1.1,4 },
		{ 1.0, 3 },
};
RatingInsulation::RatingInsulation() :Test::Test()
{
	m_Resistance60sDivTestVoltage = 0.0;
	m_MaxVoltageDivTestVoltage = 0.0;
	m_Resistance60sDivResistance15s = 0.0;
	m_RateResistance60sDivTestVoltage = 0;
	m_RateTimeShortCircuit = 0;
	m_RateTimeReconstruction = 0;
	m_RateMaxVoltageDivTestVoltage = 0;
	m_RateResistance60DivResistance15s = 0;
	m_RateTotal = 0.0;
}
RatingInsulation::RatingInsulation(const Test &ts) :Test(ts)
{
	m_Resistance60sDivTestVoltage = returnsResistanceAfter60s() *1000/ returnsTestVoltage();
	m_MaxVoltageDivTestVoltage = returnsMaxVoltage() / returnsTestVoltage();
	m_Resistance60sDivResistance15s = returnsResistanceAfter60s() / returnsResistanceAfter15s();
	m_RateResistance60sDivTestVoltage = 0;
	m_RateTimeShortCircuit = 0;
	m_RateTimeReconstruction = 0;
	m_RateMaxVoltageDivTestVoltage = 0;
	m_RateResistance60DivResistance15s = 0;
	m_RateTotal = 0.0;
}
int RatingInsulation::rateResistance60sDivTestVoltage()
{
	if (returnsRatedVoltage() >= SN) {
		if (m_Resistance60sDivTestVoltage >= 50)
			m_RateResistance60sDivTestVoltage = s_CriteriaResistance60sDivTestVoltageSN[50];
		else if (m_Resistance60sDivTestVoltage < 50	&& m_Resistance60sDivTestVoltage >= 20)
			m_RateResistance60sDivTestVoltage = s_CriteriaResistance60sDivTestVoltageSN[20];
		else if (m_Resistance60sDivTestVoltage < 20	&& m_Resistance60sDivTestVoltage >= 10 && returnsTimeShortCircuit() == 30)
			m_RateResistance60sDivTestVoltage = s_CriteriaResistance60sDivTestVoltageSN[10];
		else if (m_Resistance60sDivTestVoltage < 20	&& m_Resistance60sDivTestVoltage >= 10 && returnsTimeShortCircuit() == 1)
			m_RateResistance60sDivTestVoltage = s_CriteriaResistance60sDivTestVoltageSN[10] - 1;
		else if (m_Resistance60sDivTestVoltage < 3)
			m_RateResistance60sDivTestVoltage = s_CriteriaResistance60sDivTestVoltageSN[1];
	}
	else
	{
		auto temp=find_if(s_CriteriaResistance60sDivTestVoltagenN.rbegin(), s_CriteriaResistance60sDivTestVoltagenN.rend(),
				[=](std::pair<const int, int>  i){return i.first<=m_Resistance60sDivTestVoltage;});
		m_RateResistance60sDivTestVoltage=temp->second;
	}
	return m_RateResistance60sDivTestVoltage;
}
int RatingInsulation::rateTimeReconstruction()
{
	if (returnsRatedVoltage() >= SN)
	{
		if (returnsTimeReconstruction() >= 240)
			m_RateTimeReconstruction = s_CriteriaTimeReconstructionSN[240];
		else if (returnsTimeReconstruction() < 240 && returnsTimeReconstruction() >= 120)
			m_RateTimeReconstruction = s_CriteriaTimeReconstructionSN[120];
		else if (returnsTimeReconstruction() < 120 && returnsTimeReconstruction() >= 30)
			m_RateTimeReconstruction = s_CriteriaTimeReconstructionSN[30];
		else if (returnsTimeReconstruction() < 120 && returnsTimeReconstruction() >= 30)
			m_RateTimeReconstruction = s_CriteriaTimeReconstructionSN[30];
		else if (returnsTimeReconstruction() < 30 && returnsTimeReconstruction() >= 10)
			m_RateTimeReconstruction = s_CriteriaTimeReconstructionSN[10];
		else if (returnsTimeReconstruction() == 0 && returnsTimeShortCircuit() == 1)
			m_RateTimeReconstruction = s_CriteriaTimeReconstructionSN[0];
		else if (returnsTimeReconstruction() == 0 && returnsTimeShortCircuit() == 0)
			m_RateTimeReconstruction = s_CriteriaTimeReconstructionSN[0] - 1;
	}
	else
	{
		auto temp = find_if(s_CriteriaTimeReconstructionnN.rbegin(), s_CriteriaTimeReconstructionnN.rend(),
				[=](std::pair<const int, int>  i){return i.first<=returnsTimeReconstruction();});
		m_RateTimeReconstruction = temp->second;
	}
	return m_RateTimeReconstruction;
}
int RatingInsulation::rateTimeShortCircuit()
{
	if (returnsRatedVoltage() >= SN)
	{
		if (returnsTimeShortCircuit() == 30 && returnsTimeReconstruction() >= 240)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitSN[30];
		else if (returnsTimeShortCircuit() == 30 && returnsTimeReconstruction() < 240	&& returnsTimeReconstruction() >= 120)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitSN[30] - 1;
		else if (returnsTimeShortCircuit() == 30 && returnsTimeReconstruction() < 120	&& returnsTimeReconstruction() >= 30)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitSN[30] - 2;
		else if (returnsTimeShortCircuit() == 1 && returnsTimeReconstruction() < 30 && returnsTimeReconstruction() >= 10)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitSN[1];
		else if (returnsTimeShortCircuit() == 1 && returnsTimeReconstruction() == 0)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitSN[1] - 1;
		else if (returnsTimeShortCircuit() == 0)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitSN[0];
	}
	else
	{
		if (returnsTimeShortCircuit() == 10 && returnsTimeReconstruction() >= 120)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitnN[10];
		else if (returnsTimeShortCircuit() == 10 && returnsTimeReconstruction() < 120	&& returnsTimeReconstruction() >= 60)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitnN[10] - 1;
		else if (returnsTimeShortCircuit() == 10 && returnsTimeReconstruction() < 60)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitnN[10] - 2;
		else if (returnsTimeShortCircuit() == 1 && returnsTimeReconstruction() < 15 && returnsTimeReconstruction() >= 5)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitnN[1];
		else if (returnsTimeShortCircuit() == 0)
			m_RateTimeShortCircuit = s_CriteriaTimeShortCircuitnN[0];
	}
	return m_RateTimeShortCircuit;
}
int RatingInsulation::rateMaxVoltageDivTestVoltage()
{
	auto temp=find_if(s_CriteriaMaxVoltageDivTestVoltage.rbegin(), s_CriteriaMaxVoltageDivTestVoltage.rend(),
			[=](std::pair<const double, int>  i){return i.first<=m_MaxVoltageDivTestVoltage;});
	return m_RateMaxVoltageDivTestVoltage=temp->second;
}
int RatingInsulation::rateResistance60DivResistance15s()
{
	if (returnsRatedVoltage() >= SN)
	{
		if (m_Resistance60sDivResistance15s >= 1.5)
			m_RateResistance60DivResistance15s = s_CriteriaResistance60DivResistance15sSN[1.5];
		else if (m_Resistance60sDivResistance15s < 1.5 && m_Resistance60sDivResistance15s >= 1.2)
			m_RateResistance60DivResistance15s = s_CriteriaResistance60DivResistance15sSN[1.2];
		else if (m_Resistance60sDivResistance15s < 1.2 && m_Resistance60sDivResistance15s > 1.0)
			m_RateResistance60DivResistance15s = s_CriteriaResistance60DivResistance15sSN[1.0];
		else if (m_Resistance60sDivResistance15s == 1.0 && returnsTimeReconstruction() < 30 && returnsTimeReconstruction() >= 10)
			m_RateResistance60DivResistance15s = s_CriteriaResistance60DivResistance15sSN[1.0] - 1;
		else if (m_Resistance60sDivResistance15s == 1.0 && returnsTimeReconstruction() == 0)
			m_RateResistance60DivResistance15s = 0;
	}
	else
	{
		if (m_Resistance60sDivResistance15s >= 1.3)
			m_RateResistance60DivResistance15s = s_CriteriaResistance60DivResistance15snN[1.3];
		else if (m_Resistance60sDivResistance15s < 1.5 && m_Resistance60sDivResistance15s >= 1.1)
			m_RateResistance60DivResistance15s = s_CriteriaResistance60DivResistance15snN[1.1];
		else if (m_Resistance60sDivResistance15s < 1.1 && m_Resistance60sDivResistance15s > 1.0)
			m_RateResistance60DivResistance15s = s_CriteriaResistance60DivResistance15snN[1.0];
		else if (m_Resistance60sDivResistance15s == 1.0 && rateTimeShortCircuit()==0)
			m_RateResistance60DivResistance15s = 0;
	}
	return m_RateResistance60DivResistance15s;
}

double RatingInsulation::rateTotal()
{
	m_RateTotal += rateResistance60sDivTestVoltage();
	m_RateTotal += rateTimeReconstruction();
	m_RateTotal += rateTimeShortCircuit();
	m_RateTotal += rateMaxVoltageDivTestVoltage();
	m_RateTotal += rateResistance60DivResistance15s();
	m_RateTotal /= 5;

	return m_RateTotal;
}
void RatingInsulation::showRate() const
{
	using std::cout;
	using std::endl;
	using std::fixed;
	using std::setprecision;
	using std::setw;
	using std::left;
	using std::right;
	using std::setfill;
	const int wt = 50;
	const int wt2 = 12;
	const int wt3= 15;

	showTest();
	cout  << fixed << setprecision(2);
	cout  << setw(wt) << left << "Czas zwarcia: " << right
			<< setw(wt2) << returnsTimeShortCircuit() <<setw(7)<<left<<" s "
			<<right<< " Ocena: " << m_RateTimeShortCircuit << endl;
	cout << setw(wt) << left << "Czas odbudowy napiecia: "
			<< right  << setw(wt2) << returnsTimeReconstruction()<<setw(7)<<left<<" s "
			<<right<< " Ocena: "  << m_RateTimeReconstruction << endl;
	cout  << setw(wt) << left
			<< "Rezystancja po 60s przez napiecie probiercze: " << right
			<< setw(wt2) << m_Resistance60sDivTestVoltage<<" kOhm/V"
			<<setw(7)<< " Ocena: " << m_RateResistance60sDivTestVoltage << endl;
	cout  << setw(wt) << left
			<< "Napiecie odbudowy przez napiecie probiercze: " << right
			<< setw(wt2) << m_MaxVoltageDivTestVoltage
			<<setw(wt3)<< " Ocena: " << m_RateMaxVoltageDivTestVoltage << endl;
	cout << setw(wt) << left
			<< "Rezystancja po 60s przez rezystancje po 15s: " << right
			<< setw(wt2) << m_Resistance60sDivResistance15s
			<<setw(wt3)<< " Ocena: "<< m_RateResistance60DivResistance15s << endl;
	cout << setw(wt) << left << "Ocena koncowa: " << right
			 << setw(wt2) << m_RateTotal << endl;
}
