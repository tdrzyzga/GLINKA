#ifndef DIALOGCURSORSBOX_H
#define DIALOGCURSORSBOX_H

#include <QtGui>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QDialog>
#include <QGridLayout>

class DialogCursorsBox : public QDialog
{
		Q_OBJECT
	private:
		QCheckBox *m_VoltageCursorFirst;
		QCheckBox *m_TimeCursorFirst;

		QCheckBox *m_VoltageReconstruction;
		QCheckBox *m_TimeReconstruction;

		QCheckBox *m_VoltageCursorSecond;
		QCheckBox *m_TimeCursorSecond;

	public:
		explicit DialogCursorsBox(QWidget *parent,  Qt::WindowFlags f = Qt::WindowFlags());

		QCheckBox &returnsVoltageCursorFirst()const{return *m_VoltageCursorFirst;}
		QCheckBox &returnsTimeCursorFirst()const{return *m_TimeCursorFirst;}

		QCheckBox &returnsVoltageReconstruction()const{return *m_VoltageReconstruction;}
		QCheckBox &returnsTimeReconstruction()const{return *m_TimeReconstruction;}

		QCheckBox &returnsVoltageCursorSecond()const{return *m_VoltageCursorSecond;}
		QCheckBox &returnsTimeCursorSecond()const{return *m_TimeCursorSecond;}
};

#endif // DIALOGCURSORSBOX_H
