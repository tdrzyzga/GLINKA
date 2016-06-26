#include "motor.h"

Motor::Motor()
{
	m_RatedData.m_Name = "---";
	m_RatedData.m_Type = "---";
	m_RatedData.m_Number = "---";
	m_RatedData.m_Power = 0.0;
	m_NumberWindings = 0;
}
Motor::Motor(RatedData &ratedData)
{
	m_RatedData.m_Name = ratedData.m_Name;
	m_RatedData.m_Type = ratedData.m_Type;
	m_RatedData.m_Number = ratedData.m_Number;
	m_RatedData.m_Power = ratedData.m_Power;
	m_NumberWindings = 0;
}
Motor::Motor(RatedData &ratedData, std::vector<std::shared_ptr<RatingInsulation>> &vectorWindings, std::vector<std::string> vectorNameWindings)
{
	m_RatedData.m_Name = ratedData.m_Name;
	m_RatedData.m_Type = ratedData.m_Type;
	m_RatedData.m_Number = ratedData.m_Number;
	m_RatedData.m_Power = ratedData.m_Power;
	m_NumberWindings = 0;

	m_VectorNameWindings = vectorNameWindings;

	m_VectorWindings = vectorWindings;
}

void Motor::setVectorWindings(std::shared_ptr<RatingInsulation> rate)
{
	m_VectorWindings.push_back(rate);
	++m_NumberWindings;
}
std::shared_ptr<RatingInsulation> Motor::returnsRatingInsulation(int i)
{
	return m_VectorWindings[i];
}

void Motor::writeMotor(const std::string &name)const
{
	using namespace std;

	ofstream outFile;
	outFile.open(name, ios_base::out | ios_base::binary | ios_base::trunc);

	if (!outFile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}

	outFile.write((char*) &m_NumberWindings, sizeof m_NumberWindings);
	outFile.close();

	for (auto x:m_VectorWindings)
		x->writeRatingInsulation(name);

	outFile.open(name, ios_base::out | ios_base::app);// | ios_base::binary);

	if (!outFile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}

	outFile<<m_RatedData.m_Name<<" ";
	outFile<<m_RatedData.m_Type<<" ";
	outFile<<m_RatedData.m_Number<<" ";
	outFile<<m_RatedData.m_Power<<" ";

	for (auto x:m_VectorNameWindings)
		outFile<<x<<" ";

	outFile.close();
}
void Motor::getMotor(const std::string &name)
{
	using namespace std;

	streampos place = 0;

	ifstream inFile;
	inFile.open(name, ios_base::in | ios_base::binary);

	if (!inFile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}

	inFile.read((char*) &m_NumberWindings, sizeof m_NumberWindings);
	place = inFile.tellg();
	inFile.close();

	std::shared_ptr<RatingInsulation> tempRatingInsulation;

	for (int i=0; i<m_NumberWindings; ++i)
	{
		tempRatingInsulation.reset(new RatingInsulation());
		place = tempRatingInsulation->getRatingInsulation(name, place);
		m_VectorWindings.push_back(tempRatingInsulation);
	}
	inFile.open(name, ios_base::in);

	if (!inFile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}
	inFile.seekg(place);

	inFile>>m_RatedData.m_Name;
	inFile>>m_RatedData.m_Type;
	inFile>>m_RatedData.m_Number;
	inFile>>m_RatedData.m_Power;

	string tempString;
	for (int i=0; i<m_NumberWindings; ++i)
	{
		inFile>>tempString;
		m_VectorNameWindings.push_back(tempString);
	}

	inFile.close();
}
