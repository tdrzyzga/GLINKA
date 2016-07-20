#include "customplot.h"

CustomPlot::CustomPlot(QWidget *parent): QWidget(parent), m_Test(), poland(QLocale::Polish, QLocale::Poland)
{
	createCustomPlot();
	createAction();
	createPlotBar();

	m_Range = nullptr;

	createWidget();
}
CustomPlot::CustomPlot(const Test &ts, QWidget *parent): QWidget(parent), poland(QLocale::Polish, QLocale::Poland)
{
	m_Test = ts;

	createCustomPlot();
	createAction();
	createPlotBar();

	m_Range = nullptr;

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

	for (auto i:glinka)
	{
		m_VectorYAxis.push_back(i.first);
		m_VectorXAxis.push_back(i.second);

	}

	m_CustomPlot->addGraph();
	m_CustomPlot->graph(0)->setName(tr("Napięcie odbudowy"));
	m_CustomPlot->yAxis->setLabel(tr("Napięcie [V]"));
	m_CustomPlot->xAxis->setLabel(tr("Czas [s]"));
	m_CustomPlot->graph(0)->setData(m_VectorXAxis, m_VectorYAxis);

	m_CustomPlot->xAxis->setRange(0, *(std::max_element(m_VectorXAxis.begin(), m_VectorXAxis.end()))+10);
	m_CustomPlot->yAxis->setRange(0, *(std::max_element(m_VectorYAxis.begin(), m_VectorYAxis.end()))+10);

	m_CustomPlot->legend->setVisible(true);
	m_CustomPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
	m_CustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);

	m_CustomPlot->setInteractions(/*QCP::iRangeDrag | QCP::iSelectPlottables | QCP::iRangeZoom | QCP::iMultiSelect| QCP::iSelectAxes|*/ QCP::iSelectLegend);// | QCP::iSelectItems | QCP::iSelectOther);

	createCursors();

	m_CustomPlot->replot();
}
void CustomPlot::createCustomPlot()
{
	m_CustomPlot = new QCustomPlot(this);

	connect(m_CustomPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
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
		createQDialogRange();
	else
		setQDialogRange();

	if (m_Range->exec() == QDialog::Accepted)
	{
		m_CustomPlot->xAxis->setRange(poland.toDouble(m_XLineMin->text()), poland.toDouble(m_XLineMax->text()));
		m_CustomPlot->yAxis->setRange(poland.toDouble(m_YLineMin->text()), poland.toDouble(m_YLineMax->text()));
		m_CustomPlot->replot();
	}
}

void CustomPlot::createQDialogRange()
{
	m_Range = new QDialog(this, Qt::Dialog);
	//m_Range->setAttribute(Qt::WA_DeleteOnClose, true);

	QLabel *minimum = new QLabel(QString("Min:"), this);
	QLabel *maksimum = new QLabel(tr("Maks:"), this);

	m_XAxis = new QLabel(QString("  Oś X [s]:\n(0,0 - "+poland.toString(*m_VectorXAxis.rbegin(), 'f', 1)+")"), this);
	m_XLineMin = new QLineEdit(this);
	m_XLineMax = new QLineEdit(this);

	m_YAxis = new QLabel(QString("  Oś Y [V]:\n(0,0 - "+poland.toString(*m_VectorYAxis.rbegin(), 'f', 1)+")"), this);
	m_YLineMin = new QLineEdit(this);
	m_YLineMax = new QLineEdit(this);

	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
									 | QDialogButtonBox::Cancel);

	connect(buttonBox, SIGNAL(accepted()), m_Range, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), m_Range, SLOT(reject()));

	QGridLayout *gBox = new QGridLayout;

	gBox->addWidget(minimum, 0, 1);
	gBox->addWidget(maksimum, 0, 2);

	gBox->addWidget(m_XAxis, 1, 0);
	gBox->addWidget(m_XLineMin, 1, 1);
	gBox->addWidget(m_XLineMax, 1, 2);

	gBox->addWidget(m_YAxis, 2, 0);
	gBox->addWidget(m_YLineMin, 2, 1);
	gBox->addWidget(m_YLineMax, 2, 2);

	gBox->addWidget(buttonBox, 3, 2);

	m_Range->setLayout(gBox);
}
void CustomPlot::setQDialogRange()
{
	m_XAxis->setText(QString("  Oś X [s]:\n(0,0 - "+poland.toString(*m_VectorXAxis.rbegin(), 'f', 1)+")"));
	m_YAxis->setText(QString("  Oś Y [V]:\n(0,0 - "+poland.toString(*m_VectorYAxis.rbegin(), 'f', 1)+")"));
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
	//itemDemom_CursorFirst = m_CursorFirst; // so we can access it later in the bracketDataSlot for animation
	m_CursorFirst->setGraph(m_CustomPlot->graph(0));
	m_CursorFirst->setGraphKey(m_Test.returnsPairMinVoltageTime().second);
	m_GraphKeyCursorFirst = qFind(m_VectorXAxis.begin(), m_VectorXAxis.end(), m_Test.returnsPairMinVoltageTime().second);
	//m_CursorFirst->setInterpolating(true);
	m_CursorFirst->setStyle(QCPItemTracer::tsPlus);
	m_CursorFirst->setPen(QPen(Qt::red));
	m_CursorFirst->setBrush(Qt::red);
	m_CursorFirst->setSize(30);
	m_CursorFirst->setVisible(false);

	m_CursorSecond = new QCPItemTracer(m_CustomPlot);
	m_CustomPlot->addItem(m_CursorSecond);
	//itemDemom_CursorSecond = m_CursorSecond; // so we can access it later in the bracketDataSlot for animation
	m_CursorSecond->setGraph(m_CustomPlot->graph(0));
	m_CursorSecond->setGraphKey(m_Test.returnsPairMaxVoltageTime().second);
	m_GraphKeyCursorSecond = qFind(m_VectorXAxis.begin(), m_VectorXAxis.end(), m_Test.returnsPairMaxVoltageTime().second);
	//m_CursorSecond->setInterpolating(true);
	m_CursorSecond->setStyle(QCPItemTracer::tsPlus);
	m_CursorSecond->setPen(QPen(Qt::red));
	m_CursorSecond->setBrush(Qt::red);
	m_CursorSecond->setSize(30);
	m_CursorSecond->setVisible(false);
}
void CustomPlot::setCursors()
{
	if (m_CursorsAction->isChecked())
	{
		m_CursorFirst->setVisible(true);
		m_CursorSecond->setVisible(true);
	}
	else
	{
		m_CursorFirst->setVisible(false);
		m_CursorSecond->setVisible(false);
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
								if (event->modifiers() == Qt::ShiftModifier)
								{
									if (event->modifiers() == Qt::ControlModifier)
										m_CursorSecond->setGraphKey(*(m_GraphKeyCursorSecond = m_GraphKeyCursorSecond+10));
									else
										m_CursorSecond->setGraphKey(*(m_GraphKeyCursorSecond = m_GraphKeyCursorSecond+1));
								}
								else
								{
									if (event->modifiers() == Qt::ControlModifier)
										m_CursorFirst->setGraphKey(*(m_GraphKeyCursorFirst = m_GraphKeyCursorFirst+10));
									else
										m_CursorFirst->setGraphKey(*(m_GraphKeyCursorFirst = m_GraphKeyCursorFirst+1));
								}
								break;
			case Qt::Key_Left:
								if (event->modifiers() == Qt::ShiftModifier)
								{
									if (event->modifiers() == Qt::ControlModifier)
										m_CursorSecond->setGraphKey(*(m_GraphKeyCursorSecond = m_GraphKeyCursorSecond-10));
									else
										m_CursorSecond->setGraphKey(*(m_GraphKeyCursorSecond = m_GraphKeyCursorSecond-1));
								}
								else
								{
									if (event->modifiers() == Qt::ControlModifier)
										m_CursorFirst->setGraphKey(*(m_GraphKeyCursorFirst = m_GraphKeyCursorFirst-10));
									else
										m_CursorFirst->setGraphKey(*(m_GraphKeyCursorFirst = m_GraphKeyCursorFirst-1));
								}
								break;
			//case QKeySequence(Qt::CTRL + Qt::Key_Right): m_CursorSecond->setGraphKey((m_GraphKeyCursorSecond = m_GraphKeyCursorSecond+10));
				//										 break;
			//case QKeySequence(Qt::CTRL + Qt::Key_Left): m_CursorSecondt->setGraphKey((m_GraphKeyCursorSecond = m_GraphKeyCursorSecond-10));
			//											 break;

		}
		m_CustomPlot->replot();
	}
}
