#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include <QtGui>
#include <memory>

#include "qcustomplot/qcustomplot.h"
#include "glinka2/glinka2.h"

class CustomPlot : public QWidget
{
	private:
		Test m_Test;
		QCustomPlot *m_CustomPlot;

	public:
		explicit CustomPlot(QWidget *parent = 0);
		explicit CustomPlot(const Test &ts, QWidget *parent = 0);

		void createCustomPlot();

		void setCustomPlot(const Test &ts);

		//QCustomPlot * returnsCustomPlot(){return m_CustomPlot;}

		~CustomPlot(){}
};

#endif // CUSTOMPLOT_H
