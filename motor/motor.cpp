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
void Motor::writeMotor(const std::string &name)const
{
	using namespace std;

	ofstream outFile;
	outFile.open(name, ios_base::out | ios_base::app | ios_base::binary);

	if (!outFile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}

	outFile.write((char*) &m_NumberWindings, sizeof m_NumberWindings);
	outFile.close();

	for (auto x:m_VectorWindings)
		x->writeRatingInsulation(name);

	int sizeStruct = sizeof m_RatedData;
	outFile.write((char *) &sizeStruct, sizeof sizeStruct);
	outFile.write((char *) &m_RatedData, sizeStruct);

	int sizeVectorName = m_VectorNameWindings.size();
	outFile.write((char *) &sizeVectorName, sizeVectorName);
	for (auto x:m_VectorNameWindings)
		outFile.write((char *) &x, sizeof x);

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

	inFile.close();

	RatingInsulation tempRatingInsulation;

	for (int i=0; i<m_NumberWindings; ++i)
		m_VectorNameWindings(getRatingInsulation(name, place))
	for (auto x:m_VectorWindings)
		place = x.getRatingInsulation(name, place);

	inFile.seekg(place);
	int sizeStruct;
	inFile.read((char *) &sizeStruct, sizeof sizeStruct);
	inFile.read((char *) &m_RatedData, sizeStruct);

	inFile.read((char*) &m_NumberWindings, sizeof m_NumberWindings);

	int sizeVectorName;
	inFile.read((char *) &sizeVectorName, sizeof sizeVectorName);
	for (int i=0; i<sizeVectorName; ++i)

}