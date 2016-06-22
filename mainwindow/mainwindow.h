#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QLocale>
/*
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QMainWindow>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QFile>
#include <QDataStream>
#include <QPushButton>
#include <QWidget>
#include <QDockWidget>
#include <QGroupBox>
#include <QFileDialog>
#include <QString>
#include <QLocale>
#include <QStyle>
#include <QSpacerItem>
#include <iterator>*/

#include "qcustomplot/qcustomplot.h"
//#include "glinka/glinka.h"
#include "glinka2/glinka2.h"
#include "ratingwidget/ratingwidget.h"
#include "motor/motor.h"
#include "motorwidget/motorwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	private:
		QMenu *m_FileMenu;
		QAction *m_NewAction;
		QAction *m_OpenAction;
		QAction *m_SaveAction;
		QAction *m_QuitAction;
		QAction *m_ButtonAction;

		QMenu	 *m_HelpMenu;
		QToolBar *m_FileToolBar;

		QVector<RatingWidget *> m_VectorRatingWidget;
		Motor *m_Motor;
		QTabWidget *m_TabWidget;
		MotorWidget *m_MotorWidget;

		void createFileActions();
		void createMenus();
		void createStatusBar();
		void createToolBar();
		void createTabWidgetSave(int numberWindings);
		void createTabWidgetOpen(QString fileName);

	private slots:
		void news();
		void save();
		void open();

	public:
		MainWindow(QWidget *parent=0);
		~MainWindow(){}
};

#endif // MAINWINDOW_H
