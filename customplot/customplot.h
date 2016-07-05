#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include <QtGui>
#include <memory>

#include "qcustomplot/qcustomplot.h"
#include "glinka2/glinka2.h"

class CustomPlot : public QCustomPlot
{
	private:
		std::shared_ptr<RatingInsulation> m_Rate;

	public:
		explicit CustomPlot();
		explicit CustomPlot(std::shared_ptr<RatingInsulation> rate);

		void setCustomPlot();

		~CustomPlot(){}
};

#endif // CUSTOMPLOT_H
