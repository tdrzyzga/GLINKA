#include "customplot.h"

CustomPlot::CustomPlot(QWidget *parent): QWidget(parent), m_Test(), poland(QLocale::Polish, QLocale::Poland)
{
	createCustomPlot();
	createAction();
	createPlotBar();

	m_Range = nullptr;
	//m_CursorsBox = nullptr;

	createWidget();
}
CustomPlot::CustomPlot(const Test &ts, QWidget *parent): QWidget(parent), poland(QLocale::Polish, QLocale::Poland)
{
	m_Test = ts;

	createCustomPlot();
	createAction();
	createPlotBar();

	m_Range = nullptr;
	//m_CursorsBox = nullptr;

	createWidget();
}
void CustomPlot::createAction()
{
	m_ChangeNameGraphAction = new QAction(QIcon(":/icons/icons/legend.png"), tr("&Nazwa wykresu"), this);
	m_ChangeNameGraphAction->setStatusTip(tr("Zmień nazwę wykresu"));
	connect (m_ChangeNameGraphAction, SIGNAL(triggered()), this, SLOT(changeNameGraph()));

	m_CursorsAction = new QAction(QIcon(":/icons/icons/cursors.png"), tr("&Kursory"), this);
	m_CursorsAction->setStatusTip(tr("Kursory"));
	m_CursorsAction->setCheckable(true);
	connect (m_CursorsAction, SIGNAL(changed()), this, SLOT(setCursors()));

	m_ChangeRangeAction = new QAction(QIcon(":/icons/icons/scope.png"), tr("&Zakresy"), this);
	m_ChangeRangeAction->setStatusTip(tr("Zmień zakresy wykresu"));
	connect (m_ChangeRangeAction, SIGNAL(triggered()), this, SLOT(changeRangeGraph()));

	m_CopyToClipboard = new QAction(QIcon(":/icons/icons/copy.png"), tr("&Kopiuj wykres"), this);
	m_CopyToClipboard->setStatusTip(tr("Kopiuj wykres do schowka"));
	connect (m_CopyToClipboard, SIGNAL(triggered()), this, SLOT(copyToClipboard()));
}
void CustomPlot::createPlotBar()
{
	m_PlotBar = new QToolBar(this);

	m_PlotBar->addAction(m_ChangeNameGraphAction);
	m_PlotBar->addAction(m_CursorsAction);
	m_PlotBar->addAction(m_ChangeRangeAction);
	m_PlotBar->addAction(m_CopyToClipboard);

	m_PlotBar->setOrientation(Qt::Vertical);
}

void CustomPlot::createWidget()
{
	QScrollArea *scroll= new QScrollArea(this);
	scroll->setWidgetResizable(true);
	scroll->setFocusPolicy(Qt::NoFocus);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scroll->setWidget(m_CustomPlot);

	m_MainBox = new QHBoxLayout(this);

	m_MainBox->addWidget(m_PlotBar);
	m_MainBox->addWidget(scroll);
}
void CustomPlot::setCustomPlot(const Test &ts)
{
	m_Test = ts;
	std::multimap<double, double>glinka(m_Test.returnsm_MMGlinkaVoltageTime());

	for (auto i:glinka)
	{
		m_VectorYAxis.push_back(i.first);
		m_VectorXAxis.push_back(i.second);
		m_GlinkaTimeVoltage.insert(std::make_pair(i.second, i.first));
	}

	m_CustomPlot->addGraph();
	m_CustomPlot->graph(0)->setName(tr("Napięcie odbudowy"));
	m_CustomPlot->yAxis->setLabel(tr("Napięcie [V]"));
	m_CustomPlot->xAxis->setLabel(tr("Czas [s]"));
	m_CustomPlot->graph(0)->setData(m_VectorXAxis, m_VectorYAxis);

	QPen penGraph;
	penGraph.setColor(Qt::darkBlue);
	penGraph.setStyle(Qt::SolidLine);
	penGraph.setWidth(1);

	m_CustomPlot->graph(0)->setPen(penGraph);

	m_CustomPlot->xAxis->setRange(0, *(std::max_element(m_VectorXAxis.begin(), m_VectorXAxis.end()))+10);
	m_CustomPlot->yAxis->setRange(0, *(std::max_element(m_VectorYAxis.begin(), m_VectorYAxis.end()))+10);

	m_CustomPlot->setInteractions(/*QCP::iRangeDrag | QCP::iSelectPlottables | QCP::iRangeZoom | QCP::iMultiSelect| QCP::iSelectAxes|*/ QCP::iSelectLegend | QCP::iSelectItems);// | QCP::iSelectOther);

	qSort(m_VectorXAxis);
	//qSort(m_VectorYAxis);

	QPen penBorder;
	penBorder.setColor(Qt::darkBlue);
	penBorder.setStyle(Qt::SolidLine);
	penBorder.setWidth(2);

	m_CustomPlot->legend->setVisible(true);
	m_CustomPlot->legend->setSelectedBorderPen(penBorder);
	m_CustomPlot->legend->setSelectedTextColor(Qt::darkBlue);
	m_CustomPlot->legend->setSelectedIconBorderPen(penBorder);
	m_CustomPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));

	m_CustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);

	createCursors();

	m_CustomPlot->replot();
}
void CustomPlot::createCustomPlot()
{
	m_CustomPlot = new QCustomPlot(this);

	connect(m_CustomPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
	connect(m_CustomPlot, SIGNAL(itemDoubleClick(QCPAbstractItem*,QMouseEvent*)), this, SLOT(itemDoubleClick(QCPAbstractItem *)));
	//connect(m_CustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
	//connect(m_CustomPlot, SIGNAL(axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)), this, SLOT(axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)));

	m_CustomPlot->setMinimumSize(1000, 400);

	m_CustomPlot->replot();
}
void CustomPlot::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  Q_UNUSED(legend)

  if (item)
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

void CustomPlot::changeRangeGraph()
{
	if (!m_Range)
		createDialogRange();
	else
		setDialogRange();

	if (m_Range->exec() == QDialog::Accepted)
	{
		m_CustomPlot->xAxis->setRange(poland.toDouble(m_Range->returnsXLineMin()), poland.toDouble(m_Range->returnsXLineMax()));
		m_CustomPlot->yAxis->setRange(poland.toDouble(m_Range->returnsYLineMin()), poland.toDouble(m_Range->returnsYLineMax()));
		m_CustomPlot->replot();
	}
}

void CustomPlot::createDialogRange()
{
	m_Range = new DialogRange(this, Qt::Dialog);
	m_Range->setXAxis(QString("  Oś X [s]:\n(0,0 - "+poland.toString(*m_VectorXAxis.rbegin(), 'f', 1)+")"));
	m_Range->setYAxis(QString("  Oś Y [V]:\n(0,0 - "+poland.toString(*m_VectorYAxis.rbegin(), 'f', 1)+")"));
}
void CustomPlot::setDialogRange()
{
	m_Range->setXAxis(QString("  Oś X [s]:\n(0,0 - "+poland.toString(*m_VectorXAxis.rbegin(), 'f', 1)+")"));
	m_Range->setYAxis(QString("  Oś Y [V]:\n(0,0 - "+poland.toString(*m_VectorYAxis.rbegin(), 'f', 1)+")"));
}

//void CustomPlot::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
//{

//}

void CustomPlot::copyToClipboard()
{
	QClipboard * clipboard = QApplication::clipboard();
	QPixmap pixmap= m_CustomPlot->toPixmap(500, 300);
	clipboard->setPixmap(pixmap);
}

void CustomPlot::createCursors()
{
	m_CursorFirst = new QCPItemTracer(m_CustomPlot);
	m_CustomPlot->addItem(m_CursorFirst);
	m_CursorFirst->setGraph(m_CustomPlot->graph(0));
	m_CursorFirst->setGraphKey(m_Test.returnsPairMinVoltageTime().second);
	m_GraphKeyCursorFirst = qFind(m_VectorXAxis.begin(), m_VectorXAxis.end(), m_Test.returnsPairMinVoltageTime().second);
	m_CursorFirst->setStyle(QCPItemTracer::tsPlus);
	m_CursorFirst->setPen(QPen(Qt::black));
	m_CursorFirst->setBrush(Qt::black);
	m_CursorFirst->setSize(30);
	m_CursorFirst->setVisible(false);

	QPen penText;
	penText.setColor(Qt::black);
	penText.setStyle(Qt::SolidLine);
	penText.setWidth(1);

	QPen penSelectedText;
	penSelectedText.setColor(Qt::darkBlue);
	penSelectedText.setStyle(Qt::SolidLine);
	penSelectedText.setWidth(2);

	m_CursorText = new QCPItemText(m_CustomPlot);
	m_CustomPlot->addItem(m_CursorText);
	m_CursorText->setPositionAlignment(Qt::AlignTop | Qt::AlignCenter);
	m_CursorText->setPen(penText);
	m_CursorText->setSelectedPen(penSelectedText);
	m_CursorText->setSelectedColor(Qt::darkBlue);
	m_CursorText->setPadding(QMargins(5, 5, 5, 5));
	m_CursorText->setBrush((QColor(255,255,255,230)));

	m_CursorText->position->setType(QCPItemPosition::ptAxisRectRatio);
	m_CursorText->position->setCoords(0.5, 0.5);
	m_CursorText->setVisible(false);
	m_CursorsBox = new DialogCursorsBox(this, Qt::Dialog);

	m_CursorSecond = new QCPItemTracer(m_CustomPlot);
	m_CustomPlot->addItem(m_CursorSecond);
	m_CursorSecond->setGraph(m_CustomPlot->graph(0));
	m_CursorSecond->setGraphKey(m_Test.returnsPairMaxVoltageTime().second);
	m_GraphKeyCursorSecond = qFind(m_VectorXAxis.begin(), m_VectorXAxis.end(), m_Test.returnsPairMaxVoltageTime().second);
	m_CursorSecond->setStyle(QCPItemTracer::tsPlus);
	m_CursorSecond->setPen(QPen(Qt::black));
	m_CursorSecond->setBrush(Qt::black);
	m_CursorSecond->setSize(30);
	m_CursorSecond->setVisible(false);

	QPen penFirstSecond;
	penFirstSecond.setStyle(Qt::DashLine);
	penFirstSecond.setColor(Qt::darkGreen);
	penFirstSecond.setWidth(2);

	m_CursorLineFirst = new QCPItemLine(m_CustomPlot);
	m_CustomPlot->addItem(m_CursorLineFirst);
	m_CursorLineFirst->setPen(penFirstSecond);
	m_CursorLineFirst->start->setCoords(*m_GraphKeyCursorFirst, QCPRange::minRange);
	m_CursorLineFirst->end->setCoords(*m_GraphKeyCursorFirst, QCPRange::maxRange);
	m_CursorLineFirst->setVisible(false);

	m_CursorLineSecond = new QCPItemLine(m_CustomPlot);
	m_CustomPlot->addItem(m_CursorLineSecond);
	m_CursorLineSecond->setPen(penFirstSecond);
	m_CursorLineSecond->start->setCoords(*m_GraphKeyCursorSecond, QCPRange::minRange);
	m_CursorLineSecond->end->setCoords(*m_GraphKeyCursorSecond, QCPRange::maxRange);
	m_CursorLineSecond->setVisible(false);

	auto voltageFirst = m_GlinkaTimeVoltage.find(*m_GraphKeyCursorFirst);
	auto voltageSecond = m_GlinkaTimeVoltage.find(*m_GraphKeyCursorSecond);

	QPen pen;
	pen.setStyle(Qt::DashDotLine);
	pen.setColor(Qt::darkGreen);
	pen.setWidth(2);

	m_CursorsLine = new QCPItemLine(m_CustomPlot);
	m_CustomPlot->addItem(m_CursorsLine);
	m_CursorsLine->setPen(pen);
	m_CursorsLine->start->setCoords(*m_GraphKeyCursorFirst, voltageFirst->second);
	m_CursorsLine->end->setCoords(*m_GraphKeyCursorSecond, voltageSecond->second);
	m_CursorsLine->setVisible(false);
}
void CustomPlot::setCursors()
{
	if (m_CursorsAction->isChecked())
	{
		m_CursorsBox->setVisible(true);

		m_CursorFirst->setVisible(true);
		m_CursorSecond->setVisible(true);

		if (m_CursorsBox->exec() == QDialog::Accepted)
			setCursorsText();
		m_CursorText->setVisible(true);

		m_CursorLineFirst->setVisible(true);
		m_CursorLineSecond->setVisible(true);
		m_CursorsLine->setVisible(true);
	}
	else
	{
		m_CursorsBox->setVisible(false);
		m_CursorFirst->setVisible(false);

		m_CursorSecond->setVisible(false);
		m_CursorText->setVisible(false);

		m_CursorLineFirst->setVisible(false);
		m_CursorLineSecond->setVisible(false);
		m_CursorsLine->setVisible(false);
	}


	m_CustomPlot->replot();
}
void CustomPlot::keyPressEvent(QKeyEvent *event)
{
	if (m_CursorsAction->isChecked())
	{

		switch (event->key())
		{
			case Qt::Key_Right:
								if (event->modifiers().testFlag(Qt::ControlModifier)  && event->modifiers().testFlag(Qt::ShiftModifier))
								{
									m_CursorSecond->setGraphKey(*(m_GraphKeyCursorSecond = m_GraphKeyCursorSecond+10));
									setCursorsLine(m_CursorLineSecond, m_GraphKeyCursorSecond);
								}
								else if (event->modifiers().testFlag(Qt::ShiftModifier))
								{
									m_CursorSecond->setGraphKey(*(m_GraphKeyCursorSecond = m_GraphKeyCursorSecond+1));
									setCursorsLine(m_CursorLineSecond, m_GraphKeyCursorSecond);
								}
								else if (event->modifiers().testFlag(Qt::ControlModifier)  && !event->modifiers().testFlag(Qt::ShiftModifier))
								{
									m_CursorFirst->setGraphKey(*(m_GraphKeyCursorFirst = m_GraphKeyCursorFirst+10));
									setCursorsLine(m_CursorLineFirst, m_GraphKeyCursorFirst);
								}
								else if (!event->modifiers().testFlag(Qt::ControlModifier)  && !event->modifiers().testFlag(Qt::ShiftModifier))
								{
									m_CursorFirst->setGraphKey(*(m_GraphKeyCursorFirst = m_GraphKeyCursorFirst+1));
									setCursorsLine(m_CursorLineFirst, m_GraphKeyCursorFirst);
								}
								setCursorsText();
								break;
			case Qt::Key_Left:
								if (event->modifiers().testFlag(Qt::ControlModifier)  && event->modifiers().testFlag(Qt::ShiftModifier))
								{
									m_CursorSecond->setGraphKey(*(m_GraphKeyCursorSecond = m_GraphKeyCursorSecond-10));
									setCursorsLine(m_CursorLineSecond, m_GraphKeyCursorSecond);
								}
								else if (event->modifiers().testFlag(Qt::ShiftModifier))
								{
									m_CursorSecond->setGraphKey(*(m_GraphKeyCursorSecond = m_GraphKeyCursorSecond-1));
									setCursorsLine(m_CursorLineSecond, m_GraphKeyCursorSecond);
								}
								else if (event->modifiers().testFlag(Qt::ControlModifier)  && !event->modifiers().testFlag(Qt::ShiftModifier))
								{
									m_CursorFirst->setGraphKey(*(m_GraphKeyCursorFirst = m_GraphKeyCursorFirst-10));
									setCursorsLine(m_CursorLineFirst, m_GraphKeyCursorFirst);
								}
								else if (!event->modifiers().testFlag(Qt::ControlModifier)  && !event->modifiers().testFlag(Qt::ShiftModifier))
								{
									m_CursorFirst->setGraphKey(*(m_GraphKeyCursorFirst = m_GraphKeyCursorFirst-1));
									setCursorsLine(m_CursorLineFirst, m_GraphKeyCursorFirst);
								}
								setCursorsText();
								break;

		}
		m_CustomPlot->replot();
	}
}
void CustomPlot::setCursorsText()
{
	auto voltageFirst = m_GlinkaTimeVoltage.find(*m_GraphKeyCursorFirst);
	auto voltageSecond = m_GlinkaTimeVoltage.find(*m_GraphKeyCursorSecond);
	int fieldWidth = -1;

	QString voltage1("U1 = %1 [V];");
	voltage1 = voltage1.arg(voltageFirst->second, fieldWidth, 'f', 2);
	QString time1("t1 = %1 [s];");
	time1 = time1.arg(*m_GraphKeyCursorFirst, fieldWidth, 'f', 2);

	QString voltageReconstruction("Uodb = %1 [V];");
	voltageReconstruction = voltageReconstruction.arg(voltageSecond->second, fieldWidth, 'f', 2);
	QString timeReconstruction("todb = %1 [s];");
	timeReconstruction = timeReconstruction.arg(*m_GraphKeyCursorSecond-*m_GraphKeyCursorFirst, fieldWidth, 'f', 2);

	QString voltage2("U2 = %1 [V];");
	voltage2 = voltage2.arg(voltageSecond->second, fieldWidth, 'f', 2);
	QString time2("t2 = %1 [s];");
	time2 = time2.arg(*m_GraphKeyCursorSecond, fieldWidth, 'f', 2);

	if (m_CursorsBox->returnsVoltageCursorFirst().checkState() != Qt::Checked)
		voltage1 = QString("%1").arg("", fieldWidth);
	if (m_CursorsBox-> returnsTimeCursorFirst().checkState() != Qt::Checked)
		time1 = QString("%1").arg("", fieldWidth);

	if (m_CursorsBox->returnsVoltageReconstruction().checkState() != Qt::Checked)
		voltageReconstruction = QString("%1").arg("", fieldWidth);
	if (m_CursorsBox->returnsTimeReconstruction().checkState() != Qt::Checked)
		timeReconstruction = QString("%1").arg("", fieldWidth);

	if (m_CursorsBox->returnsVoltageCursorSecond().checkState() != Qt::Checked)
		voltage2 = QString("%1").arg("", fieldWidth);
	if (m_CursorsBox->returnsTimeCursorSecond().checkState() != Qt::Checked)
		time2 = QString("%1").arg("", fieldWidth);


	m_CursorText->setText(voltage1+"\t"+voltageReconstruction+"\t"+voltage2+"\n"
							   +time1+"\t"+timeReconstruction+"\t"+time2);
}
void CustomPlot::itemDoubleClick(QCPAbstractItem * item)
{
	Q_UNUSED(item)
	setCursors();
}
void CustomPlot::setCursorsLine(QCPItemLine *cursorLine, QVector<double>::iterator graphKey)
{
	cursorLine->start->setCoords(*graphKey, QCPRange::minRange);
	cursorLine->end->setCoords(*graphKey, QCPRange::maxRange);

	auto voltageFirst = m_GlinkaTimeVoltage.find(*m_GraphKeyCursorFirst);
	auto voltageSecond = m_GlinkaTimeVoltage.find(*m_GraphKeyCursorSecond);

	m_CursorsLine->start->setCoords(*m_GraphKeyCursorFirst, voltageFirst->second);
	m_CursorsLine->end->setCoords(*m_GraphKeyCursorSecond, voltageSecond->second);
}
