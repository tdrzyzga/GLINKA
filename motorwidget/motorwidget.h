#ifndef MOTORWIDGET_H
#define MOTORWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QPushButton>
//#inlcude <QGroupBox>
#include "ratingwidget/ratingwidget.h"
#include "motor/motor.h"

class MotorWidget : public QWidget
{
		Q_OBJECT
	private:
		QVector<QPair< QLineEdit *, QPushButton *>>m_VectorLabelButton;
		QVector<RatingWidget *>m_VectorRatingWidget;
		QGroupBox *m_RatedData;
		QLineEdit *m_LineName;
		QLineEdit *m_LineType;
		QLineEdit *m_LineNumber;
		QLineEdit *m_LinePower;

		int m_NumberButton;

		QVector<QGroupBox *>m_VectorTempWindingBox;
		QGroupBox *m_WindingData;

		RatedData m_rData;
		QVector<QString> m_VectorNameWindings;
		QTabBar *m_TabBar;

	private slots:
		void addDateReconstruction(int);
	public:
		explicit MotorWidget(QTabBar *tabBar, QVector<RatingWidget *> &vectorRatingWidget,int numberButton, QWidget *parent = 0);
		void createRatedData();
		void createLabelButton();
		void createMainWidget();
		void getLineWindings();
};

#endif // MOTORWIDGET_H
