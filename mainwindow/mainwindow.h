#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QLocale>

#include "qcustomplot/qcustomplot.h"
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
		std::shared_ptr<Motor> m_Motor;
		QTabWidget *m_TabWidget;
		MotorWidget *m_MotorWidget;
		QString m_fileNameOpen;

		void createFileActions();
		void createMenus();
		void createStatusBar();
		void createToolBar();
		void createTabWidgetNew(int numberWindings);
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
