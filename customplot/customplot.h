
#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

//#include <QtGui>
//#include <memory>
#include <QtAlgorithms>

#include "qcustomplot/qcustomplot.h"
#include "glinka2/glinka2.h"
#include "dialogrange/dialogrange.h"
#include "dialogcursorsbox/dialogcursorsbox.h"

class CustomPlot : public QWidget
{
		Q_OBJECT
	private:
		Test m_Test;
		std::multimap<double, double>m_GlinkaTimeVoltage;
		QCustomPlot *m_CustomPlot;

		QVector<double> m_VectorXAxis;
		QVector<double> m_VectorYAxis;

		QAction *m_ChangeNameGraphAction;
		QAction *m_CursorsAction;
		QAction *m_ChangeRangeAction;
		QAction *m_CopyToClipboard;

		QToolBar *m_PlotBar;
		QHBoxLayout *m_MainBox;

		DialogRange *m_Range;

		DialogCursorsBox *m_CursorsBox;
		QCPItemTracer *m_CursorFirst;
		QCPItemTracer *m_CursorSecond;
		QVector<double>::iterator m_GraphKeyCursorFirst;
		QVector<double>::iterator m_GraphKeyCursorSecond;
		QCPItemText *m_CursorFirstText;

		QLocale poland;

		void createAction();
		void createPlotBar();
		void createWidget();

		void createDialogRange();
		void setDialogRange();

		void createCursors();
		void setCursorsText();

		void keyPressEvent(QKeyEvent *event);

	private slots:
		void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
		void changeNameGraph();
		//void mousePress(QMouseEvent* event);
		void changeRangeGraph();
		//void axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
		void copyToClipboard();
		void setCursors();

	public:
		explicit CustomPlot(QWidget *parent = 0);
		explicit CustomPlot(const Test &ts, QWidget *parent = 0);

		void createCustomPlot();

		void setCustomPlot(const Test &ts);

		QCustomPlot * returnsCustomPlot(){return m_CustomPlot;}

		~CustomPlot(){}

};

#endif // CUSTOMPLOT_H
