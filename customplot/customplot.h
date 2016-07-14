
#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include <QtGui>
#include <memory>

#include "qcustomplot/qcustomplot.h"
#include "glinka2/glinka2.h"

class CustomPlot : public QWidget
{
		Q_OBJECT
	private:
		Test m_Test;
		QCustomPlot *m_CustomPlot;

		QVector<double> m_XAxis;
		QVector<double> m_YAxis;

		QAction *m_ChangeNameGraphAction;
		QAction *m_CursorsAction;
		QAction *m_ChangeRangeAction;

		QToolBar *m_PlotBar;
		QHBoxLayout *m_MainBox;

		QDialog *m_Range;
		QLineEdit *m_XLineMin;
		QLineEdit *m_XLineMax;
		QLineEdit *m_YLineMin;
		QLineEdit *m_YLineMax;

		QLocale poland;

		void createAction();
		void createPlotBar();
		void createWidget();
		void createQDialogRange();



	private slots:
		void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
		void changeNameGraph();
		void mousePress(QMouseEvent* event);
		void changeRangeGraph();
		void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
		//void moveCursors();


	public:
		explicit CustomPlot(QWidget *parent = 0);
		explicit CustomPlot(const Test &ts, QWidget *parent = 0);

		void createCustomPlot();

		void setCustomPlot(const Test &ts);

		QCustomPlot * returnsCustomPlot(){return m_CustomPlot;}

		~CustomPlot(){}

};

#endif // CUSTOMPLOT_H
