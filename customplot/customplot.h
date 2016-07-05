#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include <QtGui>
#include <memory>

#include "qcustomplot/qcustomplot.h"
#include "glinka2/glinka2.h"

class CustomPlot : public QCustomPlot
{
	private:
		Test m_Test;

	public:
		explicit CustomPlot(QWidget *parent = 0);
		explicit CustomPlot(const Test &ts, QWidget *parent = 0);

		void setCustomPlot(const Test &ts);

		~CustomPlot(){}
};

#endif // CUSTOMPLOT_H
