#include "ratingwidget.h"

RatingWidget::RatingWidget(QWidget *parent) : QWidget(parent), m_Test(), m_Rate(), poland(QLocale::Polish, QLocale::Poland)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));
	m_NameWinding = tr("Uzwojenie");

	createWidget();
}
void RatingWidget::createLineEditWidget()
{
	QFont fontLine("Arial", 10);

	m_LineMaxVoltage = new QLineEdit(this);
	m_LineMaxVoltage->setReadOnly(true);
	m_LineMaxVoltage->setFont(fontLine);

	m_LineTimeReconstruction = new QLineEdit(this);
	m_LineTimeReconstruction->setReadOnly(true);
	m_LineTimeReconstruction->setFont(fontLine);

	m_LineRatedVoltage = new QLineEdit(this);
	m_LineRatedVoltage->setFont(fontLine);

	m_LineTestVoltage = new QLineEdit(this);
	m_LineTestVoltage->setFont(fontLine);

	m_LineResistanceAfter60s = new QLineEdit(this);
	m_LineResistanceAfter60s->setFont(fontLine);

	m_LineResistanceAfter15s = new QLineEdit(this);
	m_LineResistanceAfter15s->setFont(fontLine);

	m_LineTimeShortCircuit = new QLineEdit(this);
	m_LineTimeShortCircuit->setFont(fontLine);

	QFont fontLabel("Arial", 10);

	QLabel *labelMaxVoltage = new QLabel(tr("Napięcie odbudowy [V]:"), this);
	labelMaxVoltage->setFont(fontLabel);

	QLabel *labelTimeReconstruction = new QLabel(tr("Czas odbudowy [s]:"), this);
	labelTimeReconstruction->setFont(fontLabel);

	QLabel *labelRatedVoltage = new QLabel(tr("Napięcie znamionowe [V]:"), this);
	labelRatedVoltage->setFont(fontLabel);

	QLabel *labelTestVoltage = new QLabel(tr("Napięcie probiercze [V]:"), this);
	labelTestVoltage->setFont(fontLabel);

	QLabel *labelResistanceAfter60s = new QLabel(tr("Rezystancja po 60 sekundach [MΩ]:"), this);
	labelResistanceAfter60s->setFont(fontLabel);

	QLabel *labelResistanceAfter15s = new QLabel(tr("Rezystancja po 15 sekundach [MΩ]:"), this);
	labelResistanceAfter15s->setFont(fontLabel);

	QLabel *labelTimeShortCircuit = new QLabel(tr("Czas zwarcia [s]:"), this);
	labelTimeShortCircuit->setFont(fontLabel);

	QGridLayout *gBox = new QGridLayout(this);
	gBox->addWidget(m_LineMaxVoltage, 0, 1);
	gBox->addWidget(m_LineTimeReconstruction, 1, 1);
	gBox->addWidget(m_LineRatedVoltage, 2, 1);
	gBox->addWidget(m_LineTestVoltage, 3, 1);
	gBox->addWidget(m_LineResistanceAfter60s, 4, 1);
	gBox->addWidget(m_LineResistanceAfter15s, 5, 1);
	gBox->addWidget(m_LineTimeShortCircuit, 6, 1);

	gBox->addWidget(labelMaxVoltage, 0, 0);
	gBox->addWidget(labelTimeReconstruction, 1, 0);
	gBox->addWidget(labelRatedVoltage, 2, 0);
	gBox->addWidget(labelTestVoltage, 3, 0);
	gBox->addWidget(labelResistanceAfter60s, 4, 0);
	gBox->addWidget(labelResistanceAfter15s, 5, 0);
	gBox->addWidget(labelTimeShortCircuit, 6, 0);

	m_LineEdit = new QGroupBox(tr("Dane techniczne"), this);
	m_LineEdit->setFont(QFont("Arial", 12, QFont::Bold));
	m_LineEdit->setStyleSheet("QGroupBox{border:1px; border-style:outset; border-color: gray; margin:10px} "
								"QGroupBox::title{subcontrol-origin: margin; subcontrol-position:top left}");
	m_LineEdit->setLayout(gBox);
	m_LineEdit->setMinimumWidth(350);
	m_LineEdit->setMaximumWidth(350);
}
void RatingWidget::setLineEditWidget()
{
	m_LineMaxVoltage->setText(poland.toString(m_Test.returnsMaxVoltage(), 'f', 2));
	m_LineTimeReconstruction->setText(poland.toString(m_Test.returnsTimeReconstruction(), 'f', 2));
	m_LineRatedVoltage->setText(poland.toString(m_Test.returnsRatedVoltage()));
	m_LineTestVoltage->setText(poland.toString(m_Test.returnsTestVoltage()));
	m_LineResistanceAfter60s->setText(poland.toString(m_Test.returnsResistanceAfter60s()));
	m_LineResistanceAfter15s->setText(poland.toString(m_Test.returnsResistanceAfter15s()));
	m_LineTimeShortCircuit->setText(poland.toString(m_Test.returnsTimeShortCircuit()));
}

void RatingWidget::createLineEditWidgetRate()
{
	QFont fontLine("Arial", 10);

	m_LineResistance60sDivTestVoltage = new QLineEdit(this);
	m_LineResistance60sDivTestVoltage->setReadOnly(true);
	m_LineResistance60sDivTestVoltage->setFont(fontLine);

	m_LineRateResistance60sDivTestVoltage = new QLineEdit(this);
	m_LineRateResistance60sDivTestVoltage->setReadOnly(true);
	m_LineRateResistance60sDivTestVoltage->setFont(fontLine);

	m_LineTimeShortCircuitR = new QLineEdit(this);
	m_LineTimeShortCircuitR->setReadOnly(true);
	m_LineTimeShortCircuitR->setFont(fontLine);

	m_LineRateTimeShortCircuit = new QLineEdit(this);
	m_LineRateTimeShortCircuit->setReadOnly(true);
	m_LineRateTimeShortCircuit->setFont(fontLine);

	m_LineMaxVoltageDivTestVoltage = new QLineEdit(this);
	m_LineMaxVoltageDivTestVoltage->setReadOnly(true);
	m_LineMaxVoltageDivTestVoltage->setFont(fontLine);

	m_LineRateMaxVoltageDivTestVoltage = new QLineEdit(this);
	m_LineRateMaxVoltageDivTestVoltage->setReadOnly(true);
	m_LineRateMaxVoltageDivTestVoltage->setFont(fontLine);

	m_LineTimeReconstructionR = new QLineEdit(this);
	m_LineTimeReconstructionR->setReadOnly(true);
	m_LineTimeReconstructionR->setFont(fontLine);

	m_LineRateTimeReconstruction = new QLineEdit(this);
	m_LineRateTimeReconstruction->setReadOnly(true);
	m_LineRateTimeReconstruction->setFont(fontLine);

	m_LineResistance60DivResistance15s = new QLineEdit(this);
	m_LineResistance60DivResistance15s ->setReadOnly(true);
	m_LineResistance60DivResistance15s->setFont(fontLine);

	m_LineRateResistance60DivResistance15s = new QLineEdit(this);
	m_LineRateResistance60DivResistance15s->setReadOnly(true);
	m_LineRateResistance60DivResistance15s->setFont(fontLine);

	m_LineRateTotal = new QLineEdit(this);
	m_LineRateTotal->setReadOnly(true);
	m_LineRateTotal->setFont(fontLine);

	QFont fontLabel("Arial", 10);

	QLabel *labelMaxVoltageDivTestVoltage = new QLabel(tr("Rezystancja R60 przez napięcie probiercze [kΩ/V]"), this);
	labelMaxVoltageDivTestVoltage->setFont(fontLabel);

	QLabel *labelTimeShortCircuit= new QLabel(tr("Czas zwarcia [s]:"), this);
	labelTimeShortCircuit->setFont(fontLabel);

	QLabel *labelResistance60sDivTestVoltage = new QLabel(tr("Napięcie odbudowy przez napięcie probiercze:"), this);
	labelResistance60sDivTestVoltage->setFont(fontLabel);

	QLabel *labelTimeReconstruction= new QLabel(tr("Czas odbudowy [s]:"), this);
	labelTimeReconstruction->setFont(fontLabel);

	QLabel *labelResistance60DivResistance15s = new QLabel(tr("Rezystancja R60 przez R15:"), this);
	labelResistance60DivResistance15s->setFont(fontLabel);

	QLabel *labelTotal = new QLabel(tr("Ocena ogólna:"), this);
	labelTotal->setFont(fontLabel);

	QGridLayout *gBox = new QGridLayout(this);

	gBox->addWidget(labelMaxVoltageDivTestVoltage, 0 , 0);
	gBox->addWidget(labelTimeShortCircuit, 1 , 0);
	gBox->addWidget(labelResistance60sDivTestVoltage, 2 , 0);
	gBox->addWidget(labelTimeReconstruction, 3, 0);
	gBox->addWidget(labelResistance60DivResistance15s, 4 , 0);
	gBox->addWidget(labelTotal, 5, 0);

	gBox->addWidget(m_LineResistance60sDivTestVoltage, 0 , 1);
	gBox->addWidget(m_LineTimeShortCircuitR, 1 , 1);
	gBox->addWidget(m_LineMaxVoltageDivTestVoltage, 2 , 1);
	gBox->addWidget(m_LineTimeReconstructionR, 3 , 1);
	gBox->addWidget(m_LineResistance60DivResistance15s, 4 , 1);
	gBox->addWidget(m_LineRateTotal, 5, 1);

	gBox->addWidget(m_LineRateResistance60sDivTestVoltage, 0 , 2);
	gBox->addWidget(m_LineRateTimeShortCircuit, 1 , 2);
	gBox->addWidget(m_LineRateMaxVoltageDivTestVoltage, 2 , 2);
	gBox->addWidget(m_LineRateTimeReconstruction, 3 , 2);
	gBox->addWidget(m_LineRateResistance60DivResistance15s, 4 , 2);

	m_LineEditRate = new QGroupBox(tr("Ocena"), this);
	m_LineEditRate->setFont(QFont("Arial", 12, QFont::Bold));
	m_LineEditRate->setStyleSheet("QGroupBox{border:1px; border-style:outset; border-color: gray; margin:10px;} "
							"QGroupBox::title{subcontrol-origin: margin; subcontrol-position:top left}");

	m_LineEditRate->setLayout(gBox);
}
void RatingWidget::setLineEditWidgetRate()
{
	m_LineResistance60sDivTestVoltage->setText(poland.toString(m_Rate.returnsResistance60sDivTestVoltage(), 'f', 2));
	m_LineRateResistance60sDivTestVoltage->setText(poland.toString(m_Rate.returnsRateResistance60sDivTestVoltage()));
	m_LineTimeShortCircuitR->setText(poland.toString(m_Rate.returnsTTimeShortCircuit(), 'f', 2));
	m_LineRateTimeShortCircuit->setText(poland.toString(m_Rate.returnsRateTimeShortCircuit()));
	m_LineMaxVoltageDivTestVoltage->setText(poland.toString(m_Rate.returnsMaxVoltageDivTestVoltage(), 'f', 2));
	m_LineRateMaxVoltageDivTestVoltage->setText(poland.toString(m_Rate.returnsRateMaxVoltageDivTestVoltage()));
	m_LineTimeReconstructionR->setText(poland.toString(m_Rate.returnsTTimeReconstruction(), 'f', 2));
	m_LineRateTimeReconstruction->setText(poland.toString(m_Rate.returnsRateTimeReconstruction()));
	m_LineResistance60DivResistance15s ->setText(poland.toString(m_Rate.returnsResistance60DivResistance15s(), 'f', 2));
	m_LineRateResistance60DivResistance15s->setText(poland.toString(m_Rate.returnsRateResistance60DivResistance15s()));
	m_LineRateTotal->setText(poland.toString(m_Rate.returnsRateTotal(), 'f', 1));
}

void RatingWidget::getLineData()
{
	QString ratedVoltage = m_LineRatedVoltage->text();
	m_Test.setRatedVoltage(poland.toDouble(ratedVoltage));

	QString testVoltage = m_LineTestVoltage->text();
	m_Test.setTestVoltage(poland.toDouble(testVoltage));

	QString resistanceAfter60s = m_LineResistanceAfter60s->text();
	m_Test.setResistanceAfter60s(poland.toDouble(resistanceAfter60s));

	QString resistanceAfter15s = m_LineResistanceAfter15s->text();
	m_Test.setResistanceAfter15s(poland.toDouble(resistanceAfter15s));

	QString timeShortCircuit = m_LineTimeShortCircuit->text();
	m_Test.setTimeShortCircuit(poland.toDouble(timeShortCircuit));

	m_Rate = m_Test;
}
void RatingWidget::createCustomPlot()
{
	m_CustomPlot = new QCustomPlot(this);
	m_CustomPlot->addGraph();
	m_CustomPlot->graph(0)->setName(tr("Napięcie odbudowy [V]"));
	m_CustomPlot->xAxis->setLabel(tr("Czas [s]"));
	m_CustomPlot->setMinimumSize(1000, 400);

	m_CustomPlot->replot();
}
void RatingWidget::setCustomPlot()
{
	std::multimap<double, double> glinka(m_Test.returnsGlinka());
	QVector<double> x;
	QVector<double> y;
	for (auto i:glinka)
	{
		y.push_back(i.first);
		x.push_back(i.second);

	}
	//m_CustomPlot->addGraph();
	m_CustomPlot->graph(0)->setData(x, y);
	//m_CustomPlot->graph(0)->setName(tr("Napięcie odbudowy [V]"));
	//m_CustomPlot->xAxis->setLabel(tr("Czas [s]"));
	//m_CustomPlot->yAxis->setLabel(tr("Napięcie odbudowy [V]"));
	m_CustomPlot->xAxis->setRange(0, *(std::max_element(x.begin(), x.end())));
	m_CustomPlot->yAxis->setRange(0, *(std::max_element(y.begin(), y.end())));
	//m_CustomPlot->setMinimumSize(1000, 500);
	m_CustomPlot->legend->setVisible(true);
	m_CustomPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
	m_CustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
	m_CustomPlot->setInteraction(QCP::iSelectPlottables, true);
	m_CustomPlot->replot();
}
void RatingWidget::createWidget()
{
	createLineEditWidget();
	createLineEditWidgetRate();
	createCustomPlot();

	QScrollArea *scroll= new QScrollArea(this);
	scroll->setWidgetResizable(true);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scroll->setWidget(m_CustomPlot);

	QPushButton	*button = new QPushButton(tr("Oceń"), this);
	button->setDefault(true);
	//button->setAutoDefault(true);
	button->setShortcut(QKeySequence(Qt::Key_Return));

	connect(button, SIGNAL(clicked()), this, SLOT(rate()));

	QGridLayout *gBox = new QGridLayout(this);
	gBox->addWidget(m_LineEdit, 0, 0);
	gBox->addWidget(m_LineEditRate, 0, 1);
	gBox->addWidget(button, 1, 0);

	QGroupBox *groupBox = new QGroupBox(this);
	groupBox->setLayout(gBox);
	groupBox->setMinimumHeight(260);
	groupBox->setMaximumHeight(260);

	m_MainBox = new QVBoxLayout(this);
	m_MainBox->addWidget(groupBox);
	m_MainBox->addWidget(scroll);
}
void RatingWidget::news()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki txt (*.txt)"));

	if (m_Test.returnsMaxVoltage() && !fileName.isEmpty())
	{
		m_Test.resetTest();
		m_Rate.resetRate();
	}
	if (!fileName.isEmpty())
	{
		m_Test.reconstruction(fileName.toStdString());
		setLineEditWidget();
		setLineEditWidgetRate();
		setCustomPlot();
	}
}
void RatingWidget::rate()
{
	getLineData();
	m_Rate.rateTotal();
	m_Rate.showRate();
	setLineEditWidget();
	setLineEditWidgetRate();
}
void RatingWidget::save()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("Zapisz plik jako..."), "/home/*.glinka", tr("Pliki txt (*.glinka)"));

	if (!fileName.isEmpty())
	{
		if (m_Rate.returnsRateTotal()== 0.0)
			getLineData();
		m_Rate.writeRatingInsulation(fileName.toStdString());
	}
}
void RatingWidget::open()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki glinka (*.glinka)"));
	if (m_Test.returnsMaxVoltage() && !fileName.isEmpty())
	{
		m_Test.resetTest();
		m_Rate.resetRate();
	}
	if (!fileName.isEmpty())
	{
		m_Rate.getRatingInsulation(fileName.toStdString());
		m_Test = m_Rate.returnsTest();
		setLineEditWidget();
		setLineEditWidgetRate();
		setCustomPlot();
	}
}
RatingInsulation & RatingWidget::returnsm_Rate()
{
	return m_Rate;
}
