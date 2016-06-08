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

		QGroupBox *m_GroupBox;
		QGroupBox *m_LineEdit;
		QGroupBox *m_LineEditRate;

		QLineEdit *m_LineRatedVoltage;
		QLineEdit *m_LineTestVoltage;
		QLineEdit *m_LineResistanceAfter60s;
		QLineEdit *m_LineResistanceAfter15s;
		QLineEdit *m_LineTimeShortCircuit;

		QDockWidget *m_BottomWidget;
		QCustomPlot *m_CustomPlot;

		Test m_Test;
		RatingInsulation m_Rate;
		QLocale poland;

		void createFileActions();
		void createMenus();
		void createStatusBar();
		void createToolBar();

		void createCentralWidget();
		void createLineEditWidget();
		void createLineEditWidgetRate();
		void createCustomPlot();
		void createBottomWidget();
		void getLineData();

	private slots:
		void news();
		void rate();
		void save();
		void open();


	public:
		MainWindow(QWidget *parent=0);
		~MainWindow(){}
};

#endif // MAINWINDOW_H
