#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));

	//ratingWidget = new RatingWidget(this);

	createFileActions();
	createMenus();
	createStatusBar();
	createToolBar();

	setMinimumSize(1000, 600);
	resize(1000, 700);

	/*tabWidget = new QTabWidget(this);
	for (int i=0; i<2; ++i)
	{
		ratingWidget.push_back(new RatingWidget(this));
		tabWidget->addTab(ratingWidget[i], tr("Napięcie odbudowy"));
	}
	setCentralWidget(tabWidget);*/
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
void MainWindow::news()
{
	bool ok;
	int numberWindings = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
									 tr("Podaj ilość uzwojeń:"), 2, 0, 100, 1, &ok);
	if (ok)
	{
		if (!m_VectorRatingWidget.isEmpty())
		{
			m_TabWidget->clear();
			m_VectorRatingWidget.clear();
		}
		m_Motor = new Motor(numberWindings);
		m_TabWidget = new QTabWidget(this);


		for (int i=0; i<numberWindings; ++i)
		{
			m_VectorRatingWidget.push_back(new RatingWidget(this));
			m_Motor->returnsRatingInsulation(i) = m_VectorRatingWidget[i]->returnsm_Rate();
			m_TabWidget->addTab(m_VectorRatingWidget[i], (m_VectorRatingWidget[i]->returnsNameWinding()+" %1").arg(i+1));
		}
		m_MotorWidget = new MotorWidget(m_TabWidget->tabBar(), m_VectorRatingWidget, numberWindings, this);
		m_TabWidget->addTab(m_MotorWidget, tr("Silnik"));

		setCentralWidget(m_TabWidget);
	}
}
void MainWindow::save()
{
	//ratingWidget->save();
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
	//ratingWidget->open();
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


