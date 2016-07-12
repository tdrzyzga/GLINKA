#include "customplot.h"

CustomPlot::CustomPlot(QWidget *parent): QWidget(parent), m_Test()
{
	createCustomPlot();
	createAction();
	createPlotBar();

	createWidget();
}
CustomPlot::CustomPlot(const Test &ts, QWidget *parent): QWidget(parent)
{
	m_Test = ts;

	createCustomPlot();
}
void CustomPlot::createAction()
{
	m_ChangeNameGraphAction = new QAction(QIcon(":/icons/icons/legend.png"), tr("&Nazwa wykresu"), this);
	m_ChangeNameGraphAction->setStatusTip(tr("Zmień nazwę wykresu"));
	connect (m_ChangeNameGraphAction, SIGNAL(triggered()), this, SLOT(changeNameGraph()));

	m_CursorsAction = new QAction(QIcon(":/icons/icons/cursors.png"), tr("&Kursory"), this);
	m_CursorsAction->setStatusTip(tr("Kursory"));
	//connect (m_Cursors, SIGNAL(triggered()), this, SLOT(moveCursors()));

	m_ChangeRangeAction = new QAction(QIcon(":/icons/icons/legend.png"), tr("&Zakresy"), this);
	m_ChangeRangeAction->setStatusTip(tr("Zmień zakresy wykresu"));
	connect (m_ChangeRangeAction, SIGNAL(triggered()), this, SLOT(changeRangeGraph()));
}
void CustomPlot::createPlotBar()
{
	m_PlotBar = new QToolBar(this);

	m_PlotBar->addAction(m_ChangeNameGraphAction);
	m_PlotBar->addAction(m_CursorsAction);
	m_PlotBar->addAction(m_ChangeRangeAction);

	m_PlotBar->setOrientation(Qt::Vertical);
}

void CustomPlot::createWidget()
{
	QScrollArea *scroll= new QScrollArea(this);
	scroll->setWidgetResizable(true);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scroll->setWidget(m_CustomPlot);

	m_MainBox = new QHBoxLayout(this);

	m_MainBox->addWidget(m_PlotBar);
	m_MainBox->addWidget(scroll);
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

	connect(m_CustomPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
	connect(m_CustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
	connect(m_CustomPlot, SIGNAL(axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)), this, SLOT(axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)));

	m_CustomPlot->setMinimumSize(1000, 400);

	m_CustomPlot->replot();
}
void CustomPlot::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
	QCPPlottableLegendItem *plotTableLegendItem = qobject_cast<QCPPlottableLegendItem*>(item);

	bool ok;

	QString newName = QInputDialog::getText(this, tr(""), tr("Nazwa wykresu:"), QLineEdit::Normal, plotTableLegendItem->plottable()->name(), &ok);
	if (ok)
	{
	  plotTableLegendItem->plottable()->setName(newName);
	  m_CustomPlot->replot();
	}
  }
}
void CustomPlot::changeNameGraph()
{
	emit(legendDoubleClick(m_CustomPlot->legend, m_CustomPlot->legend->item(0)));
}
void CustomPlot::mousePress(QMouseEvent* event)
{
	QCustomPlot *customPlot=m_CustomPlot;
		static QCPItemLine *hCursor, *vCursor;

	double x=customPlot->xAxis->pixelToCoord(event->pos().x());
	double y=customPlot->yAxis->pixelToCoord(event->pos().y());

	if(hCursor) customPlot->removeItem(hCursor);
		hCursor = new QCPItemLine(customPlot);

		customPlot->addItem(hCursor);
		hCursor->start->setCoords(QCPRange::minRange, y);
		hCursor->end->setCoords(QCPRange::maxRange, y);

	if(vCursor) customPlot->removeItem(vCursor);
		vCursor = new QCPItemLine(customPlot);

		customPlot->addItem(vCursor);
		vCursor->start->setCoords( x, QCPRange::minRange);
		vCursor->end->setCoords( x, QCPRange::maxRange);

	customPlot->replot();
}
void CustomPlot::changeRangeGraph()
{
	QDialog *range = new QDialog(this, Qt::Dialog);

	QLabel *xAxis = new QLabel(tr("Oś X"), this);
	QLineEdit *xLine = new QLineEdit(this);
	QPushButton *ok = new QPushButton(this);

	QHBoxLayout *vBox = new QHBoxLayout;
	vBox->addWidget(xAxis);
	vBox->addWidget(xLine);
	vBox->addWidget(ok);
	range->setLayout(vBox);

	range->show();
}

void CustomPlot::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
	QDialog *range = new QDialog(this, Qt::Dialog);

	QLabel *xAxis = new QLabel(tr("Oś X"), this);
	QLineEdit *xLine = new QLineEdit(this);
	QPushButton *ok = new QPushButton(this);

	QHBoxLayout *vBox = new QHBoxLayout(this);
	vBox->addWidget(xAxis);
	vBox->addWidget(xLine);
	vBox->addWidget(ok);
	range->setLayout(vBox);

	range->show();
}
