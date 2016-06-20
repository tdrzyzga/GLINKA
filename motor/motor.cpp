#include "motor.h"

Motor::Motor()
{
	m_RatedData.m_Name = "---";
	m_RatedData.m_Type = "---";
	m_RatedData.m_Number = "---";
	m_RatedData.m_Power = 0.0;
	m_NumberWindings = 0;

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
	m_NumberWindings = 0;
}
Motor::Motor(RatedData &ratedData, std::vector<RatingInsulation *> &vectorWindings, std::vector<std::string> vectorNameWindings)
{
	m_RatedData.m_Name = ratedData.m_Name;
	m_RatedData.m_Type = ratedData.m_Type;
	m_RatedData.m_Number = ratedData.m_Number;
	m_RatedData.m_Power = ratedData.m_Power;
	m_NumberWindings = 0;

	m_VectorNameWindings = vectorNameWindings;

	m_VectorWindings = vectorWindings;
}

void Motor::setVectorWindings(RatingInsulation *rate)
{
	m_VectorWindings.push_back(rate);
	++m_NumberWindings;
}
RatingInsulation *Motor::returnsRatingInsulation(int i)
{
	return m_VectorWindings[i];
}

void Motor::writeMotor(const std::string &name)const
{
	using namespace std;

	ofstream outFile;
	outFile.open(name, ios_base::out | ios_base::binary);

	if (!outFile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}

	outFile.write((char*) &m_NumberWindings, sizeof m_NumberWindings);
	outFile.close();

	for (auto x:m_VectorWindings)
		x->writeRatingInsulation(name);

	outFile.open(name, ios_base::out | ios_base::app | ios_base::binary);

	if (!outFile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}
	streampos placewrite= outFile.tellp();

	int sizeStruct;
	sizeStruct = m_RatedData.m_Name.size();
	outFile.write((char *) &sizeStruct, sizeof sizeStruct);
	outFile.write((char *) &m_RatedData.m_Name, sizeStruct);

	sizeStruct = m_RatedData.m_Type.size();
	outFile.write((char *) &sizeStruct, sizeof sizeStruct);
	outFile.write((char *) &m_RatedData.m_Type, sizeStruct);

	sizeStruct = m_RatedData.m_Number.size();
	outFile.write((char *) &sizeStruct, sizeof sizeStruct);
	outFile.write((char *) &m_RatedData.m_Number, sizeStruct);

	sizeStruct = sizeof m_RatedData.m_Power;
	outFile.write((char *) &sizeStruct, sizeof sizeStruct);
	outFile.write((char *) &m_RatedData.m_Power, sizeStruct);

	int sizeString;
	for (auto x:m_VectorNameWindings)
	{
		placewrite = outFile.tellp();
		sizeString = x.size();
		outFile.write((char *) &sizeString, sizeof sizeString);
		outFile.write((char *) &x, sizeString);
	}

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

	RatingInsulation *tempRatingInsulation;

	for (int i=0; i<m_NumberWindings; ++i)
	{
		tempRatingInsulation = new RatingInsulation();
		place = tempRatingInsulation->getRatingInsulation(name, place);
		m_VectorWindings.push_back(tempRatingInsulation);
	}
	inFile.open(name, ios_base::in | ios_base::binary);

	if (!inFile.is_open())
	{
		cerr << "Cannot open file: " << name << endl;
		exit(EXIT_FAILURE);
	}
	inFile.seekg(place);

//	int sizeStruct;
//	inFile.read((char *) &sizeStruct, sizeof sizeStruct);
	//inFile.read((char *) &m_RatedData, sizeStruct);

	int sizeStruct;

	inFile.read((char *) &sizeStruct, sizeof sizeStruct);
	inFile.read((char *) &m_RatedData.m_Name, sizeStruct);

	inFile.read((char *) &sizeStruct, sizeof sizeStruct);
	inFile.read((char *) &m_RatedData.m_Type, sizeStruct);

	inFile.read((char *) &sizeStruct, sizeof sizeStruct);
	inFile.read((char *) &m_RatedData.m_Number, sizeStruct);

	inFile.read((char *) &sizeStruct, sizeof sizeStruct);
	inFile.read((char *) &m_RatedData.m_Power, sizeStruct);

	int sizeString;
	string tempString;
	for (int i=0; i<m_NumberWindings; ++i)
	{
		inFile.read((char *) &sizeString, sizeof sizeString);
		inFile.read((char *) &tempString, sizeString);
		m_VectorNameWindings.push_back(tempString);
	}

	inFile.close();
}
