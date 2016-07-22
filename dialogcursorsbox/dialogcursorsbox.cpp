#include "dialogcursorsbox.h"

DialogCursorsBox::DialogCursorsBox(QWidget *parent, Qt::WindowFlags f): QDialog(parent, f)
{
	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
									 | QDialogButtonBox::Cancel);

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


	voltageCursorFirst = new QCheckBox(tr("napięcie U1"), this);
	timeCursorFirst = new QCheckBox(tr("czas t1"), this);

	voltageReconstruction = new QCheckBox(tr("napięcie Uodb"), this);
	timeReconstruction = new QCheckBox(tr("czas todb"), this);

	voltageCursorSecond = new QCheckBox(tr("napięcie U2"), this);
	timeCursorSecond = new QCheckBox(tr("czas t2"), this);

	QGridLayout *gBox = new QGridLayout;

	gBox->addWidget(voltageCursorFirst, 0, 0);
	gBox->addWidget(timeCursorFirst, 1, 0);


	gBox->addWidget(voltageReconstruction, 0, 1);
	gBox->addWidget(timeReconstruction, 1, 1);

	gBox->addWidget(voltageCursorSecond, 0, 2);
	gBox->addWidget(timeCursorSecond, 1, 2);

	gBox->addWidget(buttonBox, 2, 2);

	setLayout(gBox);
}
