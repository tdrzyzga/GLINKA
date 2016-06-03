#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), m_Test(), m_Rate()
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));

	createFileActions();

	m_ButtonAction = nullptr;
	m_GroupBox = nullptr;

	m_LineEdit = nullptr;
	m_LineEditRate = nullptr;

	m_LineRatedVoltage = nullptr;
	m_LineTestVoltage = nullptr;
	m_LineResistanceAfter60s = nullptr;
	m_LineResistanceAfter15s = nullptr;
	m_LineTimeShortCircuit = nullptr;

	m_BottomWidget = nullptr;
	m_CustomPlot = nullptr;

	createMenus();
	createStatusBar();
	createToolBar();

	setMinimumSize(1000, 600);
	resize(1000, 700);
}

void MainWindow::createFileActions()
{
	m_NewAction = new QAction(QIcon(":/icons/icons/new.png"), tr("&Nowy"), this);
	m_NewAction->setStatusTip(tr("Nowy plik."));
	m_NewAction->setShortcut(QKeySequence::New);
	connect (m_NewAction, SIGNAL(triggered()), this, SLOT(news()));

	m_OpenAction = new QAction(QIcon(":/icons/icons/open.png"), tr("&Otwórz"), this);
	m_OpenAction->setStatusTip(tr("Otwórz istniejący plik."));
	m_OpenAction->setShortcut(QKeySequence::Open);

	m_SaveAction = new QAction(QIcon(":/icons/icons/save.png"), tr("&Zapisz"), this);
	m_SaveAction->setStatusTip(tr("Zapisz plik."));
	m_SaveAction->setShortcut(QKeySequence::Save);

	m_QuitAction = new QAction(tr("&Wyjście"), this);
	m_QuitAction->setStatusTip(tr("Wyjdź z programu."));
	m_QuitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
	connect (m_QuitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createMenus()
{
	m_FileMenu = new QMenu(tr("&Plik"), this);
	menuBar()->addMenu(m_FileMenu);

	m_FileMenu->addAction(m_NewAction);
	m_FileMenu->addAction(m_OpenAction);
	m_FileMenu->addSeparator();
	m_FileMenu->addAction(m_SaveAction);
	m_FileMenu->addSeparator();
	m_FileMenu->addAction(m_QuitAction);

	m_HelpMenu = new QMenu(tr("P&omoc"), this);
	menuBar()->addMenu(m_HelpMenu);

	m_HelpMenu->addAction(tr("O &Qt"), qApp, SLOT(aboutQt()));
}

void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Gotowy"));
}

void MainWindow::createToolBar()
{
	m_FileToolBar = new QToolBar(this);

	m_FileToolBar->addAction(m_NewAction);
	m_FileToolBar->addAction(m_OpenAction);
	m_FileToolBar->addAction(m_SaveAction);

	addToolBar(m_FileToolBar);
}

/*void MainWindow::createTableWidget()
{
	tableWidget = new QTableWidget(3, 2, centralWidget());

	QStringList horizontalHeaders=(QStringList()<<"Napięcie\n[V]"<<"Czas\n[s]");
	tableWidget->setHorizontalHeaderLabels(horizontalHeaders);

	QStringList verticalHeaders=(QStringList()<<"Rozpoczęcie odbudowy napięcia"<<"Maksymalne napięcie odbudowy"<<"Czas odbudowy");
	tableWidget->setVerticalHeaderLabels(verticalHeaders);

	QTableWidgetItem *timeReconstruction= new QTableWidgetItem(tr("%1").arg(test.TimeReconstruction()));
	tableWidget->setItem(2, 1, timeReconstruction);
	QTableWidgetItem *maxVoltage= new QTableWidgetItem(tr("%1").arg(test.MaxVoltage()));
	tableWidget->setItem(1, 0, maxVoltage);
}*/

void MainWindow::createLineEditWidget()
{
	QLineEdit *lineMaxVoltage = new QLineEdit;
	lineMaxVoltage->setReadOnly(true);
	lineMaxVoltage->setFont(QFont("Arial", 9));
	lineMaxVoltage->setText(QString::number(m_Test.returnsMaxVoltage(), 'f', 2));
	QLineEdit *lineTimeReconstruction = new QLineEdit;
	lineTimeReconstruction->setReadOnly(true);
	lineTimeReconstruction->setFont(QFont("Arial", 9));
	lineTimeReconstruction->setText(QString::number(m_Test.returnsTimeReconstruction(), 'f', 2));

	m_LineRatedVoltage = new QLineEdit;
	m_LineRatedVoltage->setFont(QFont("Arial", 9));
	if (m_Test.returnsRatedVoltage() !=0)
		m_LineRatedVoltage->setText(QString::number(m_Test.returnsRatedVoltage()));

	m_LineTestVoltage = new QLineEdit;
	m_LineTestVoltage->setFont(QFont("Arial", 9));
	if (m_Test.returnsTestVoltage() !=0)
		m_LineTestVoltage->setText(QString::number(m_Test.returnsTestVoltage()));

	m_LineResistanceAfter60s = new QLineEdit;
	m_LineResistanceAfter60s->setFont(QFont("Arial", 9));
	if (m_Test.returnsResistanceAfter60s() != 0)
		m_LineResistanceAfter60s->setText(QString::number(m_Test.returnsResistanceAfter60s()));

	m_LineResistanceAfter15s = new QLineEdit;
	m_LineResistanceAfter15s->setFont(QFont("Arial", 9));
	if (m_Test.returnsResistanceAfter15s() != 0)
		m_LineResistanceAfter15s->setText(QString::number(m_Test.returnsResistanceAfter15s()));

	m_LineTimeShortCircuit = new QLineEdit;
	m_LineTimeShortCircuit->setFont(QFont("Arial", 9));
	if (m_Test.returnsTimeShortCircuit() != 0)
		m_LineTimeShortCircuit->setText(QString::number(m_Test.returnsTimeShortCircuit()));

	QLabel *labelMaxVoltage = new QLabel(tr("Napięcie odbudowy [V]:"));
	labelMaxVoltage->setFont(QFont ( "Arial", 10));
	QLabel *labelTimeReconstruction = new QLabel(tr("Czas odbudowy [s]:"));
	labelTimeReconstruction->setFont(QFont("Arial", 10));
	QLabel *labelRatedVoltage = new QLabel(tr("Napięcie znamionowe [V]:"));
	labelRatedVoltage->setFont(QFont("Arial", 10));
	QLabel *labelTestVoltage = new QLabel(tr("Napięcie probiercze [V]:"));
	labelTestVoltage->setFont(QFont("Arial", 10));
	QLabel *labelResistanceAfter60s = new QLabel(tr("Rezystancja po 60 sekundach [MΩ]:"));
	labelResistanceAfter60s->setFont(QFont("Arial", 10));
	QLabel *labelResistanceAfter15s = new QLabel(tr("Rezystancja po 15 sekundach [MΩ]:"));
	labelResistanceAfter15s->setFont(QFont("Arial", 10));
	QLabel *labelTimeShortCircuit = new QLabel(tr("Czas zwarcia [s]:"));
	labelTimeShortCircuit->setFont(QFont("Arial", 10));

	QGridLayout *vBox = new QGridLayout;
	vBox->addWidget(lineMaxVoltage, 0, 1);
	vBox->addWidget(lineTimeReconstruction, 1, 1);
	vBox->addWidget(m_LineRatedVoltage, 2, 1);
	vBox->addWidget(m_LineTestVoltage, 3, 1);
	vBox->addWidget(m_LineResistanceAfter60s, 4, 1);
	vBox->addWidget(m_LineResistanceAfter15s, 5, 1);
	vBox->addWidget(m_LineTimeShortCircuit, 6, 1);


	vBox->addWidget(labelMaxVoltage, 0, 0);
	vBox->addWidget(labelTimeReconstruction, 1, 0);
	vBox->addWidget(labelRatedVoltage, 2, 0);
	vBox->addWidget(labelTestVoltage, 3, 0);
	vBox->addWidget(labelResistanceAfter60s, 4, 0);
	vBox->addWidget(labelResistanceAfter15s, 5, 0);
	vBox->addWidget(labelTimeShortCircuit, 6, 0);

	m_LineEdit = new QGroupBox(tr("Dane techniczne"));
	m_LineEdit->setFont(QFont("Arial", 12, QFont::Bold));
	m_LineEdit->setStyleSheet("QGroupBox{border:1px; border-style:outset; border-color: gray; margin:10px} "
							"QGroupBox::title{subcontrol-origin: margin; subcontrol-position:top left}");
	m_LineEdit->setLayout(vBox);
	m_LineEdit->setMinimumWidth(350);
	m_LineEdit->setMaximumWidth(350);
}
void MainWindow::createLineEditWidgetRate()
{
	QLineEdit *lineResistance60sDivTestVoltage = new QLineEdit;
	lineResistance60sDivTestVoltage->setReadOnly(true);
	lineResistance60sDivTestVoltage->setFont(QFont("Arial", 10));
	lineResistance60sDivTestVoltage->setText(QString::number(m_Rate.returnsResistance60sDivTestVoltage(), 'f', 2));
	QLineEdit *lineRateResistance60sDivTestVoltage = new QLineEdit;
	lineRateResistance60sDivTestVoltage->setReadOnly(true);
	lineRateResistance60sDivTestVoltage->setFont(QFont("Arial", 10));
	lineRateResistance60sDivTestVoltage->setText(QString::number(m_Rate.returnsRateResistance60sDivTestVoltage()));

	QLineEdit *lineTimeShortCircuit = new QLineEdit;
	lineTimeShortCircuit->setReadOnly(true);
	lineTimeShortCircuit->setFont(QFont("Arial", 10));
	lineTimeShortCircuit->setText(QString::number(m_Rate.returnsTTimeShortCircuit(), 'f', 2));
	QLineEdit *lineRateTimeShortCircuit = new QLineEdit;
	lineRateTimeShortCircuit->setReadOnly(true);
	lineRateTimeShortCircuit->setFont(QFont("Arial", 10));
	lineRateTimeShortCircuit->setText(QString::number(m_Rate.returnsRateTimeShortCircuit()));

	QLineEdit *lineMaxVoltageDivTestVoltage = new QLineEdit;
	lineMaxVoltageDivTestVoltage->setReadOnly(true);
	lineMaxVoltageDivTestVoltage->setFont(QFont("Arial", 10));
	lineMaxVoltageDivTestVoltage->setText(QString::number(m_Rate.returnsMaxVoltageDivTestVoltage(), 'f', 2));
	QLineEdit *lineRateMaxVoltageDivTestVoltage = new QLineEdit;
	lineRateMaxVoltageDivTestVoltage->setReadOnly(true);
	lineRateMaxVoltageDivTestVoltage->setFont(QFont("Arial", 10));
	lineRateMaxVoltageDivTestVoltage->setText(QString::number(m_Rate.returnsRateMaxVoltageDivTestVoltage()));

	QLineEdit *lineTimeReconstruction = new QLineEdit;
	lineTimeReconstruction->setReadOnly(true);
	lineTimeReconstruction->setFont(QFont("Arial", 10));
	lineTimeReconstruction->setText(QString::number(m_Rate.returnsTTimeReconstruction(), 'f', 2));
	QLineEdit *lineRateTimeReconstruction = new QLineEdit;
	lineRateTimeReconstruction->setReadOnly(true);
	lineRateTimeReconstruction->setFont(QFont("Arial", 10));
	lineRateTimeReconstruction->setText(QString::number(m_Rate.returnsRateTimeReconstruction()));

	QLineEdit *lineResistance60DivResistance15s = new QLineEdit;
	lineResistance60DivResistance15s ->setReadOnly(true);
	lineResistance60DivResistance15s->setFont(QFont("Arial", 10));
	lineResistance60DivResistance15s ->setText(QString::number(m_Rate.returnsResistance60DivResistance15s(), 'f', 2));
	QLineEdit *lineRateResistance60DivResistance15s = new QLineEdit;
	lineRateResistance60DivResistance15s->setReadOnly(true);
	lineRateResistance60DivResistance15s->setFont(QFont("Arial", 10));
	lineRateResistance60DivResistance15s->setText(QString::number(m_Rate.returnsRateResistance60DivResistance15s()));

	QLineEdit *lineRateTotal = new QLineEdit;
	lineRateTotal->setReadOnly(true);
	lineRateTotal->setFont(QFont("Arial", 10));
	lineRateTotal->setText(QString::number(m_Rate.returnsRateTotal(), 'f', 1));

	QLabel *labelMaxVoltageDivTestVoltage = new QLabel(tr("Rezystancja R60 przez napięcie probiercze [kΩ/V]"));
	labelMaxVoltageDivTestVoltage->setFont(QFont("Arial", 10));
	QLabel *labelTimeShortCircuit= new QLabel(tr("Czas zwarcia [s]:"));
	labelTimeShortCircuit->setFont(QFont("Arial", 10));
	QLabel *labelResistance60sDivTestVoltage = new QLabel(tr("Napięcie odbudowy przez napięcie probiercze:"));
	labelResistance60sDivTestVoltage->setFont(QFont("Arial", 10));
	QLabel *labelTimeReconstruction= new QLabel(tr("Czas odbudowy [s]:"));
	labelTimeReconstruction->setFont(QFont("Arial", 10));
	QLabel *labelResistance60DivResistance15s = new QLabel(tr("Rezystancja R60 przez R15:"));
	labelResistance60DivResistance15s->setFont(QFont("Arial", 10));
	QLabel *labelTotal = new QLabel(tr("Ocena ogólna:"));
	labelTotal->setFont(QFont("Arial", 10));

	QGridLayout *gBox = new QGridLayout;

	gBox->addWidget(labelMaxVoltageDivTestVoltage, 0 , 0);
	gBox->addWidget(labelTimeShortCircuit, 1 , 0);
	gBox->addWidget(labelResistance60sDivTestVoltage, 2 , 0);
	gBox->addWidget(labelTimeReconstruction, 3, 0);
	gBox->addWidget(labelResistance60DivResistance15s, 4 , 0);
	gBox->addWidget(labelTotal, 5, 0);

	gBox->addWidget(lineResistance60sDivTestVoltage, 0 , 1);
	gBox->addWidget(lineTimeShortCircuit, 1 , 1);
	gBox->addWidget(lineMaxVoltageDivTestVoltage, 2 , 1);
	gBox->addWidget(lineTimeReconstruction, 3 , 1);
	gBox->addWidget(lineResistance60DivResistance15s, 4 , 1);
	gBox->addWidget(lineRateTotal, 5, 1);

	gBox->addWidget(lineRateResistance60sDivTestVoltage, 0 , 2);
	gBox->addWidget(lineRateTimeShortCircuit, 1 , 2);
	gBox->addWidget(lineRateMaxVoltageDivTestVoltage, 2 , 2);
	gBox->addWidget(lineRateTimeReconstruction, 3 , 2);
	gBox->addWidget(lineRateResistance60DivResistance15s, 4 , 2);

	m_LineEditRate = new QGroupBox(tr("Ocena"));
	m_LineEditRate->setFont(QFont("Arial", 12, QFont::Bold));
	m_LineEditRate->setStyleSheet("QGroupBox{border:1px; border-style:outset; border-color: gray; margin:10px;} "
							"QGroupBox::title{subcontrol-origin: margin; subcontrol-position:top left}");

	m_LineEditRate->setLayout(gBox);
}

void MainWindow::getLineData()
{
	QString ratedVoltage = m_LineRatedVoltage->text();
	m_Test.returnsRatedVoltage()=ratedVoltage.toDouble();

	QString testVoltage = m_LineTestVoltage->text();
	m_Test.returnsTestVoltage() = testVoltage.toDouble();

	QString resistanceAfter60s = m_LineResistanceAfter60s->text();
	m_Test.returnsResistanceAfter60s() = resistanceAfter60s.toDouble();

	QString resistanceAfter15s = m_LineResistanceAfter15s->text();
	m_Test.returnsResistanceAfter15s() = resistanceAfter15s.toDouble();

	QString timeShortCircuit = m_LineTimeShortCircuit->text();
	m_Test.returnsTimeShortCircuit() = timeShortCircuit.toDouble();

	m_Rate=m_Test;
}

void MainWindow::createBottomWidget()
{
	m_BottomWidget = new QDockWidget(tr("Wykres napięcia odbudowy"), this);
	//bottomWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
	m_BottomWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);

	createCustomPlot();

	QScrollArea *scroll= new QScrollArea;
	scroll->setWidgetResizable(true);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scroll->setWidget(m_CustomPlot);

	m_BottomWidget->setWidget(scroll);

	addDockWidget(Qt::BottomDockWidgetArea, m_BottomWidget);
}

void MainWindow::createCustomPlot()
{
	m_CustomPlot = new QCustomPlot;

	std::multimap<double, double> glinka(m_Test.returnsGlinka());
	QVector<double> x;
	QVector<double> y;
	for (auto i:glinka)
	{
		y.push_back(i.first);
		x.push_back(i.second);

	}
	m_CustomPlot->addGraph();
	m_CustomPlot->graph(0)->setData(x, y);
	m_CustomPlot->graph(0)->setName(tr("Napięcie odbudowy [V]"));
	m_CustomPlot->xAxis->setLabel(tr("Czas [s]"));
	//m_CustomPlot->yAxis->setLabel(tr("Napięcie odbudowy [V]"));
	m_CustomPlot->xAxis->setRange(0, *(std::max_element(x.begin(), x.end())));
	m_CustomPlot->yAxis->setRange(0, *(std::max_element(y.begin(), y.end())));
	m_CustomPlot->setMinimumSize(1000, 500);
	m_CustomPlot->legend->setVisible(true);
	m_CustomPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
	m_CustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
	m_CustomPlot->setInteraction(QCP::iSelectPlottables, true);

	m_CustomPlot->replot();
}

void MainWindow::createCentralWidget()
{
	createLineEditWidget();
	createLineEditWidgetRate();

	QPushButton	*button = new QPushButton(tr("Oceń"));
	connect(button, SIGNAL(clicked()), this, SLOT(rate()));

	QGridLayout *gridBox = new QGridLayout;
	//gridBox->addWidget(tableWidget, 0, 0);
	//gridBox->addWidget( label, 0, 0);
	gridBox->addWidget(m_LineEdit, 0, 0);
	gridBox->addWidget(m_LineEditRate, 0, 1);
	gridBox->addWidget(button, 1, 0);

	m_GroupBox= new QGroupBox;
	m_GroupBox->setLayout(gridBox);
	m_GroupBox->setMinimumSize(1000, 260);
	m_GroupBox->setMaximumSize(1366, 260);

	/*QScrollArea *scroll= new QScrollArea;
	scroll->setWidgetResizable(true);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scroll->setWidget(groupBox);*/

	setCentralWidget(m_GroupBox);
}

void MainWindow::news()
{
	if (m_GroupBox != nullptr && m_BottomWidget != nullptr)
	{
		m_Test.resetTest();
		m_Rate.resetRate();
	}
	QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/qtworkspac", tr("Pliki txt (*.txt)"));
	if (!fileName.isEmpty())
	{
		m_Test.reconstruction(fileName.toStdString());
		createCentralWidget();
		createBottomWidget();
	}
}

void MainWindow::rate()
{
	getLineData();
	m_Rate.showRate();
	m_Rate.rateTotal();

	createCentralWidget();
}
