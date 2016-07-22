#include "dialogcursorsbox.h"

DialogCursorsBox::DialogCursorsBox(QWidget *parent, Qt::WindowFlags f): QDialog(parent, f)
{
	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
									 | QDialogButtonBox::Cancel);

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


	m_VoltageCursorFirst = new QCheckBox(tr("napięcie U1"), this);
	m_TimeCursorFirst = new QCheckBox(tr("czas t1"), this);

	m_VoltageReconstruction = new QCheckBox(tr("napięcie Uodb"), this);
	m_TimeReconstruction = new QCheckBox(tr("czas todb"), this);

	m_VoltageCursorSecond = new QCheckBox(tr("napięcie U2"), this);
	m_TimeCursorSecond = new QCheckBox(tr("czas t2"), this);

	QGridLayout *gBox = new QGridLayout;

	gBox->addWidget(m_VoltageCursorFirst, 0, 0);
	gBox->addWidget(m_TimeCursorFirst, 1, 0);


	gBox->addWidget(m_VoltageReconstruction, 0, 1);
	gBox->addWidget(m_TimeReconstruction, 1, 1);

	gBox->addWidget(m_VoltageCursorSecond, 0, 2);
	gBox->addWidget(m_TimeCursorSecond, 1, 2);

	gBox->addWidget(buttonBox, 2, 2);

	setLayout(gBox);
}
