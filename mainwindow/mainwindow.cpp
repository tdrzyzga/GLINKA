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
	int numberWindings;

	if(m_VectorRatingWidget.isEmpty())
	{
		numberWindings = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
									 tr("Podaj ilość uzwojeń:"), 2, 0, 100, 1, &ok);
		if (ok)
			createTabWidgetNew(numberWindings);
	}
	else
	{
		int ret = QMessageBox::warning(this, tr(""), tr("Zapisać plik?"),
									   QMessageBox::Ok | QMessageBox::Cancel,
									   QMessageBox::Ok);
		if (ret==QMessageBox::Ok)
			save();

		numberWindings = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
									 tr("Podaj ilość uzwojeń:"), 2, 0, 100, 1, &ok);
		if (ok)
		{
			//for (int i=0; i<m_TabWidget->count(); ++i)
			//{
			//	m_TabWidget->removeTab(i);
			//}
			m_TabWidget->clear();
			m_VectorRatingWidget.clear();
			m_MotorWidget->deleteLater();
			m_Motor.reset();

			createTabWidgetNew(numberWindings);
		}
	}

	if (ok)
		setCentralWidget(m_TabWidget);
}
void MainWindow::save()
{
	for (auto x: m_VectorRatingWidget)
		x->getLineRatingWidget();

	m_MotorWidget->getLineMotorWidget();

	QString fileName = QFileDialog::getSaveFileName(this,tr("Zapisz plik jako..."), "/home/*.glinka", tr("Pliki txt (*.glinka)"));

	if (!fileName.isEmpty())
		m_Motor->writeMotor(fileName.toStdString());
}
void MainWindow::open()
{
	QString fileName;

	if(m_VectorRatingWidget.isEmpty())
	{
		fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki glinka (*.glinka)"));

		if (!fileName.isEmpty())
			createTabWidgetOpen(fileName);
	}
	else
	{
		int ret = QMessageBox::warning(this, tr(""), tr("Zapisać plik?"),
									   QMessageBox::Ok | QMessageBox::Cancel,
									   QMessageBox::Ok);
		if (ret==QMessageBox::Ok)
			save();

		fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki glinka (*.glinka)"));

		if (!fileName.isEmpty())
		{
			m_TabWidget->clear();
			m_VectorRatingWidget.clear();
			m_MotorWidget->deleteLater();
			m_Motor.reset();

			createTabWidgetOpen(fileName);
		}
	}
	if (!fileName.isEmpty())
		setCentralWidget(m_TabWidget);
}
void MainWindow::createTabWidgetNew(int numberWindings)
{
	m_Motor.reset(new Motor());
	m_TabWidget = new QTabWidget(this);

	for (int i=0; i<numberWindings; ++i)
	{
		m_VectorRatingWidget.push_back(new RatingWidget(this));
		m_Motor->setVectorWindings(m_VectorRatingWidget[i]->returnsm_Rate());
		m_TabWidget->addTab(m_VectorRatingWidget[i], (m_VectorRatingWidget[i]->returnsNameWinding()+" %1").arg(i+1));
	}
	m_MotorWidget = new MotorWidget(m_Motor, m_TabWidget->tabBar(), m_VectorRatingWidget, numberWindings, this);
	m_TabWidget->addTab(m_MotorWidget, tr("Silnik"));
}
void MainWindow::createTabWidgetOpen(QString fileName)
{
	m_Motor.reset(new Motor());
	m_Motor->getMotor(fileName.toStdString());
	int numberWindings = m_Motor->returnsm_NumberWindings();
	std::cout<<"Liczba uzwojen "<<numberWindings<<std::endl;
	m_TabWidget = new QTabWidget(this);

	for (int i=0; i<numberWindings; ++i)
	{
		m_VectorRatingWidget.push_back(new RatingWidget(QString::fromStdString(m_Motor->returnsNameWinding(i)), m_Motor->returnsRatingInsulation(i), this));
		m_TabWidget->addTab(m_VectorRatingWidget[i], m_VectorRatingWidget[i]->returnsNameWinding());

		std::cout<<m_Motor->returnsNameWinding(i)<<std::endl;
		m_VectorRatingWidget[i]->returnsm_Rate()->showRate();
	}

	m_MotorWidget = new MotorWidget(m_Motor, m_TabWidget->tabBar(), m_VectorRatingWidget, numberWindings, this);
	m_TabWidget->addTab(m_MotorWidget, tr("Silnik"));

	for (int i=0; i<numberWindings; ++i)
		m_VectorRatingWidget[i]->setRatingWidget();

	m_MotorWidget->setLineMotorWidget();
}
