#include "customplot.h"

CustomPlot::CustomPlot(QWidget *parent): QWidget(parent), m_Test()
{
	createCustomPlot();
}
CustomPlot::CustomPlot(const Test &ts, QWidget *parent): QWidget(parent)
{
	m_Test = ts;

	createCustomPlot();
}
void CustomPlot::setCustomPlot(const Test &ts)
{
	m_Test = ts;
	std::multimap<double, double> glinka(m_Test.returnsm_MMGlinkaVoltageTime());
	QVector<double> x;
	QVector<double> y;

	//QVector<double> minX(m_Test.returnsPairMinVoltageTime().second);
	//QVector<double> minY(m_Test.returnsPairMinVoltageTime().first);

	//QVector<double> maxX(m_Test.returnsPairMaxVoltageTime().second);
	//QVector<double> maxY(m_Test.returnsPairMaxVoltageTime().first);

	for (auto i:glinka)
	{
		y.push_back(i.first);
		x.push_back(i.second);

	}
/*
	for (int i=0; i<=m_Test.returnsPairMaxVoltageTime().first; ++i)
	{
		minX.push_back(m_Test.returnsPairMinVoltageTime().second);
		minY.push_back(i);
	}

	for (int i=0; i<=m_Test.returnsPairMaxVoltageTime().first; ++i)
	{
		maxX.push_back(m_Test.returnsPairMaxVoltageTime().second);
		maxY.push_back(i);
	}*/

	m_CustomPlot->addGraph();
	m_CustomPlot->graph(0)->setName(tr("Napięcie odbudowy [V]"));
	m_CustomPlot->xAxis->setLabel(tr("Czas [s]"));
	m_CustomPlot->graph(0)->setData(x, y);

	//addGraph();
	//graph(1)->setData(minX, minY);
	//graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

	//addGraph();
	//graph(2)->setData(maxX, maxY);

	m_CustomPlot->xAxis->setRange(0, *(std::max_element(x.begin(), x.end())));
	m_CustomPlot->yAxis->setRange(0, *(std::max_element(y.begin(), y.end())));

	m_CustomPlot->legend->setVisible(true);
	m_CustomPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
	m_CustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);

	m_CustomPlot->setInteractions(QCP::iRangeDrag | QCP::iSelectPlottables| QCP::iRangeZoom | QCP::iMultiSelect| QCP::iSelectAxes| QCP::iSelectLegend | QCP::iSelectItems | QCP::iSelectOther);

	m_CustomPlot->replot();
}
void CustomPlot::createCustomPlot()
{
	m_CustomPlot = new QCustomPlot(this);

	m_CustomPlot->setMinimumSize(1000, 400);

	m_CustomPlot->replot();
}
