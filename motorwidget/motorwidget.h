#ifndef MOTORWIDGET_H
#define MOTORWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include "ratingwidget/ratingwidget.h"
#

class MotorWidget : public QWidget
{
		Q_OBJECT
	private:
		QVector<QPushButton *>m_VectorButton;
		QVector<RatingWidget *>m_VectorRatingWidget;
	private slots:
		void addDateReconstruction(int);
	public:
		explicit MotorWidget(QVector<RatingWidget *> &vectorRatingWidget,int numberButton, QWidget *parent = 0);
};

#endif // MOTORWIDGET_H
