#ifndef DIALOGRANGE_H
#define DIALOGRANGE_H
#include <QDialog>
#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>
#include <QDialogButtonBox>

class DialogRange : public QDialog
{
		Q_OBJECT
	private:
		QLabel *m_XAxis;
		QLabel *m_YAxis;
		QLineEdit *m_XLineMin;
		QLineEdit *m_XLineMax;
		QLineEdit *m_YLineMin;
		QLineEdit *m_YLineMax;

		QLocale poland;

	public:
		explicit DialogRange(QWidget *parent,  Qt::WindowFlags f = Qt::WindowFlags());

		void setXAxis(QString text){m_XAxis->setText(text);}
		void setYAxis(QString text){m_YAxis->setText(text);}

		QString returnsXLineMin()const{return m_XLineMin->text();}
		QString returnsXLineMax()const{return m_XLineMax->text();}
		QString returnsYLineMin()const{return m_YLineMin->text();}
		QString returnsYLineMax()const{return m_YLineMax->text();}
};

#endif // DIALOGRANGE_H
