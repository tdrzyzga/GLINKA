#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));

	ratingWidget = new RatingWidget(this);

	createFileActions();
	createMenus();
	createStatusBar();
	createToolBar();

	setMinimumSize(1000, 600);
	resize(1000, 700);

	setCentralWidget(ratingWidget);
}
void MainWindow::createFileActions()
{
	m_NewAction = new QAction(QIcon(":/icons/icons/new.png"), tr("&Nowy"), this);
	m_NewAction->setStatusTip(tr("Nowy plik"));
	m_NewAction->setShortcut(QKeySequence::New);
	connect (m_NewAction, SIGNAL(triggered()), this, SLOT(news()));

	m_OpenAction = new QAction(QIcon(":/icons/icons/open.png"), tr("&Otwórz"), this);
	m_OpenAction->setStatusTip(tr("Otwórz istniejący plik"));
	m_OpenAction->setShortcut(QKeySequence::Open);
	connect (m_OpenAction, SIGNAL(triggered()), this, SLOT(open()));

	m_SaveAction = new QAction(QIcon(":/icons/icons/save.png"), tr("&Zapisz"), this);
	m_SaveAction->setStatusTip(tr("Zapisz plik"));
	m_SaveAction->setShortcut(QKeySequence::Save);
	connect (m_SaveAction, SIGNAL(triggered()), this, SLOT(save()));

	m_QuitAction = new QAction(tr("&Wyjście"), this);
	m_QuitAction->setStatusTip(tr("Wyjdź z programu"));
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

	m_HelpMenu = new QMenu(tr("&Pomoc"), this);
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
}
void MainWindow::createLineEditWidget()
{
	QFont fontLine("Arial", 10);

	QLineEdit *lineMaxVoltage = new QLineEdit;
	lineMaxVoltage->setReadOnly(true);
	lineMaxVoltage->setFont(fontLine);
	lineMaxVoltage->setText(poland.toString(m_Test.returnsMaxVoltage(), 'f', 2));

	QLineEdit *lineTimeReconstruction = new QLineEdit;
	lineTimeReconstruction->setReadOnly(true);
	lineTimeReconstruction->setFont(fontLine);
	lineTimeReconstruction->setText(poland.toString(m_Test.returnsTimeReconstruction(), 'f', 2));

	m_LineRatedVoltage = new QLineEdit;
	m_LineRatedVoltage->setFont(fontLine);
	if (m_Test.returnsRatedVoltage() !=0)
		m_LineRatedVoltage->setText(poland.toString(m_Test.returnsRatedVoltage()));

	m_LineTestVoltage = new QLineEdit;
	m_LineTestVoltage->setFont(fontLine);
	if (m_Test.returnsTestVoltage() !=0)
		m_LineTestVoltage->setText(poland.toString(m_Test.returnsTestVoltage()));

	m_LineResistanceAfter60s = new QLineEdit;
	m_LineResistanceAfter60s->setFont(fontLine);
	if (m_Test.returnsResistanceAfter60s() != 0)
		m_LineResistanceAfter60s->setText(poland.toString(m_Test.returnsResistanceAfter60s()));

	m_LineResistanceAfter15s = new QLineEdit;
	m_LineResistanceAfter15s->setFont(fontLine);
	if (m_Test.returnsResistanceAfter15s() != 0)
		m_LineResistanceAfter15s->setText(poland.toString(m_Test.returnsResistanceAfter15s()));

	m_LineTimeShortCircuit = new QLineEdit;
	m_LineTimeShortCircuit->setFont(fontLine);
	if (m_Test.returnsTimeShortCircuit() != 0)
		m_LineTimeShortCircuit->setText(poland.toString(m_Test.returnsTimeShortCircuit()));

	QFont fontLabel("Arial", 10);

	QLabel *labelMaxVoltage = new QLabel(tr("Napięcie odbudowy [V]:"));
	labelMaxVoltage->setFont(fontLabel);

	QLabel *labelTimeReconstruction = new QLabel(tr("Czas odbudowy [s]:"));
	labelTimeReconstruction->setFont(fontLabel);

	QLabel *labelRatedVoltage = new QLabel(tr("Napięcie znamionowe [V]:"));
	labelRatedVoltage->setFont(fontLabel);

	QLabel *labelTestVoltage = new QLabel(tr("Napięcie probiercze [V]:"));
	labelTestVoltage->setFont(fontLabel);

	QLabel *labelResistanceAfter60s = new QLabel(tr("Rezystancja po 60 sekundach [MΩ]:"));
	labelResistanceAfter60s->setFont(fontLabel);

	QLabel *labelResistanceAfter15s = new QLabel(tr("Rezystancja po 15 sekundach [MΩ]:"));
	labelResistanceAfter15s->setFont(fontLabel);

	QLabel *labelTimeShortCircuit = new QLabel(tr("Czas zwarcia [s]:"));
	labelTimeShortCircuit->setFont(fontLabel);

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
	QFont fontLine("Arial", 10);

	QLineEdit *lineResistance60sDivTestVoltage = new QLineEdit;
	lineResistance60sDivTestVoltage->setReadOnly(true);
	lineResistance60sDivTestVoltage->setFont(fontLine);
	lineResistance60sDivTestVoltage->setText(poland.toString(m_Rate.returnsResistance60sDivTestVoltage(), 'f', 2));

	QLineEdit *lineRateResistance60sDivTestVoltage = new QLineEdit;
	lineRateResistance60sDivTestVoltage->setReadOnly(true);
	lineRateResistance60sDivTestVoltage->setFont(fontLine);
	lineRateResistance60sDivTestVoltage->setText(poland.toString(m_Rate.returnsRateResistance60sDivTestVoltage()));

	QLineEdit *lineTimeShortCircuit = new QLineEdit;
	lineTimeShortCircuit->setReadOnly(true);
	lineTimeShortCircuit->setFont(fontLine);
	lineTimeShortCircuit->setText(poland.toString(m_Rate.returnsTTimeShortCircuit(), 'f', 2));

	QLineEdit *lineRateTimeShortCircuit = new QLineEdit;
	lineRateTimeShortCircuit->setReadOnly(true);
	lineRateTimeShortCircuit->setFont(fontLine);
	lineRateTimeShortCircuit->setText(poland.toString(m_Rate.returnsRateTimeShortCircuit()));

	QLineEdit *lineMaxVoltageDivTestVoltage = new QLineEdit;
	lineMaxVoltageDivTestVoltage->setReadOnly(true);
	lineMaxVoltageDivTestVoltage->setFont(fontLine);
	lineMaxVoltageDivTestVoltage->setText(poland.toString(m_Rate.returnsMaxVoltageDivTestVoltage(), 'f', 2));

	QLineEdit *lineRateMaxVoltageDivTestVoltage = new QLineEdit;
	lineRateMaxVoltageDivTestVoltage->setReadOnly(true);
	lineRateMaxVoltageDivTestVoltage->setFont(fontLine);
	lineRateMaxVoltageDivTestVoltage->setText(poland.toString(m_Rate.returnsRateMaxVoltageDivTestVoltage()));

	QLineEdit *lineTimeReconstruction = new QLineEdit;
	lineTimeReconstruction->setReadOnly(true);
	lineTimeReconstruction->setFont(fontLine);
	lineTimeReconstruction->setText(poland.toString(m_Rate.returnsTTimeReconstruction(), 'f', 2));

	QLineEdit *lineRateTimeReconstruction = new QLineEdit;
	lineRateTimeReconstruction->setReadOnly(true);
	lineRateTimeReconstruction->setFont(fontLine);
	lineRateTimeReconstruction->setText(poland.toString(m_Rate.returnsRateTimeReconstruction()));

	QLineEdit *lineResistance60DivResistance15s = new QLineEdit;
	lineResistance60DivResistance15s ->setReadOnly(true);
	lineResistance60DivResistance15s->setFont(fontLine);
	lineResistance60DivResistance15s ->setText(poland.toString(m_Rate.returnsResistance60DivResistance15s(), 'f', 2));

	QLineEdit *lineRateResistance60DivResistance15s = new QLineEdit;
	lineRateResistance60DivResistance15s->setReadOnly(true);
	lineRateResistance60DivResistance15s->setFont(fontLine);
	lineRateResistance60DivResistance15s->setText(poland.toString(m_Rate.returnsRateResistance60DivResistance15s()));

	QLineEdit *lineRateTotal = new QLineEdit;
	lineRateTotal->setReadOnly(true);
	lineRateTotal->setFont(fontLine);
	lineRateTotal->setText(poland.toString(m_Rate.returnsRateTotal(), 'f', 1));

	QFont fontLabel("Arial", 10);

	QLabel *labelMaxVoltageDivTestVoltage = new QLabel(tr("Rezystancja R60 przez napięcie probiercze [kΩ/V]"));
	labelMaxVoltageDivTestVoltage->setFont(fontLabel);

	QLabel *labelTimeShortCircuit= new QLabel(tr("Czas zwarcia [s]:"));
	labelTimeShortCircuit->setFont(fontLabel);

	QLabel *labelResistance60sDivTestVoltage = new QLabel(tr("Napięcie odbudowy przez napięcie probiercze:"));
	labelResistance60sDivTestVoltage->setFont(fontLabel);

	QLabel *labelTimeReconstruction= new QLabel(tr("Czas odbudowy [s]:"));
	labelTimeReconstruction->setFont(fontLabel);

	QLabel *labelResistance60DivResistance15s = new QLabel(tr("Rezystancja R60 przez R15:"));
	labelResistance60DivResistance15s->setFont(fontLabel);

	QLabel *labelTotal = new QLabel(tr("Ocena ogólna:"));
	labelTotal->setFont(fontLabel);

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
	m_Test.returnsRatedVoltage()=poland.toDouble(ratedVoltage);

	QString testVoltage = m_LineTestVoltage->text();
	m_Test.returnsTestVoltage() = poland.toDouble(testVoltage);

	QString resistanceAfter60s = m_LineResistanceAfter60s->text();
	m_Test.returnsResistanceAfter60s() = poland.toDouble(resistanceAfter60s);

	QString resistanceAfter15s = m_LineResistanceAfter15s->text();
	m_Test.returnsResistanceAfter15s() = poland.toDouble(resistanceAfter15s);

	QString timeShortCircuit = m_LineTimeShortCircuit->text();
	m_Test.returnsTimeShortCircuit() = poland.toDouble(timeShortCircuit);

	m_Rate = m_Test;
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

	QPushButton	*button = new QPushButton(tr("Oceń"), this);
	button->setDefault(true);
	//button->setAutoDefault(true);
	button->setShortcut(QKeySequence(Qt::Key_Return));

	//QShortcut *enterShortcut= new QShortcut(QKeySequence(tr("CTR+T")), button);
	//connect(enterShortcut, SIGNAL(activated()), button, SIGNAL(clicked()));
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

	QScrollArea *scroll= new QScrollArea;
	scroll->setWidgetResizable(true);
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scroll->setWidget(groupBox);

	setCentralWidget(m_GroupBox);
}*/
void MainWindow::news()
{
	ratingWidget->news();
	/*QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki txt (*.txt)"));

	if (m_GroupBox != nullptr && m_BottomWidget != nullptr && !fileName.isEmpty())
	{
		delete m_CustomPlot;
		delete m_GroupBox;
		delete m_BottomWidget;

		m_Test.resetTest();
		m_Rate.resetRate();
	}
	if (!fileName.isEmpty())
	{
		m_Test.reconstruction(fileName.toStdString());
		createCentralWidget();
		createBottomWidget();
	}*/
	setCentralWidget(ratingWidget);
}
/*void MainWindow::rate()
{
	getLineData();
	m_Rate.rateTotal();
	m_Rate.showRate();
	createCentralWidget();
}*/
void MainWindow::save()
{
	ratingWidget->save();
		//QString fileName = QFileDialog::getSaveFileName(this,tr("Zapisz plik jako..."), "/home/*.glinka", tr("Pliki txt (*.glinka)"));

		//if (!fileName.isEmpty())
		//{
		//	if (m_Rate.returnsRateTotal()== 0.0)
		//		getLineData();
		//	m_Rate.writeRatingInsulation(fileName.toStdString());
		//}
		//m_Test = m_Rate.returnsTest();
		//m_Test.writeTest(fileName.toStdString());
	//setCentralWidget(ratingWidget);
}
void MainWindow::open()
{
	ratingWidget->open();
	/*QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki glinka (*.glinka)"));
	if (m_GroupBox != nullptr && m_BottomWidget != nullptr && !fileName.isEmpty())
	{
		delete m_CustomPlot;
		delete m_GroupBox;
		delete m_BottomWidget;

		m_Test.resetTest();
		m_Rate.resetRate();
	}
	if (!fileName.isEmpty())
	{
		m_Rate.getRatingInsulation(fileName.toStdString());
		m_Test = m_Rate.returnsTest();
		//m_Test.getTest(fileName.toStdString());
		createCentralWidget();
		createBottomWidget();
	}*/

}


