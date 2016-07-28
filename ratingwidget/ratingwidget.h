#ifndef RATINGWIDGET_H
#define RATINGWIDGET_H

//#include <QtGui>
//#include <iterator>
//#include <memory>

//#include "qcustomplot/qcustomplot.h"
#include "glinka2/glinka2.h"
#include "customplot/customplot.h"

class RatingWidget : public QWidget
{
		Q_OBJECT
	private:
		QVBoxLayout *m_MainBox;
		QGroupBox *m_LineEdit;
		QGroupBox *m_LineEditRate;

		QLineEdit *m_LineMaxVoltage;
		QLineEdit *m_LineTimeReconstruction;
		QLineEdit *m_LineRatedVoltage;
		QLineEdit *m_LineTestVoltage;
		QLineEdit *m_LineResistanceAfter60s;
		QLineEdit *m_LineResistanceAfter15s;
		QLineEdit *m_LineTimeShortCircuit;

		QLineEdit *m_LineResistance60sDivTestVoltage;
		QLineEdit *m_LineRateResistance60sDivTestVoltage;
		QLineEdit *m_LineTimeShortCircuitR;
		QLineEdit *m_LineRateTimeShortCircuit;
		QLineEdit *m_LineMaxVoltageDivTestVoltage;
		QLineEdit *m_LineRateMaxVoltageDivTestVoltage;
		QLineEdit *m_LineTimeReconstructionR;
		QLineEdit *m_LineRateTimeReconstruction;
		QLineEdit *m_LineResistance60DivResistance15s;
		QLineEdit *m_LineRateResistance60DivResistance15s;
		QLineEdit *m_LineRateTotal;

		CustomPlot *m_CustomPlot;

		//std::shared_ptr<Test> m_Test;
		std::shared_ptr<RatingInsulation> m_Rate;
		QLocale poland;
		QString m_NameWinding;

		void createWidget();
		void createLineEditWidget();
		void createLineEditWidgetRate();

		void setLineEditWidget();
		void setLineEditWidgetRate();


	private slots:
		void rate();
		void restoreInitialValue();
		void setPlotValue();

	public:
		explicit RatingWidget(QWidget *parent = 0);
		explicit RatingWidget(QString nameWinding, std::shared_ptr<RatingInsulation> rate, QWidget *parent = 0);

		std::shared_ptr<RatingInsulation> returnsm_Rate();
		QString &returnsNameWinding(){return m_NameWinding;}

		void news();
		void setRatingWidget();
		void getLineRatingWidget();

		~RatingWidget(){}
};

#endif // RATINGWIDGET_H
