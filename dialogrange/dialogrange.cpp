#include "dialogrange.h"

DialogRange::DialogRange(QWidget *parent, Qt::WindowFlags f): QDialog(parent, f), poland(QLocale::Polish, QLocale::Poland)
{
	//m_Range = new QDialog(this, Qt::Dialog);
	//m_Range->setAttribute(Qt::WA_DeleteOnClose, true);

	QLabel *minimum = new QLabel(QString("Min:"), this);
	QLabel *maksimum = new QLabel(tr("Maks:"), this);

	m_XAxis = new QLabel(tr(""), this);
	m_XLineMin = new QLineEdit(this);
	m_XLineMax = new QLineEdit(this);

	m_YAxis = new QLabel(tr(""), this);
	m_YLineMin = new QLineEdit(this);
	m_YLineMax = new QLineEdit(this);

	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
									 | QDialogButtonBox::Cancel);

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	QGridLayout *gBox = new QGridLayout;

	gBox->addWidget(minimum, 0, 1);
	gBox->addWidget(maksimum, 0, 2);

	gBox->addWidget(m_XAxis, 1, 0);
	gBox->addWidget(m_XLineMin, 1, 1);
	gBox->addWidget(m_XLineMax, 1, 2);

	gBox->addWidget(m_YAxis, 2, 0);
	gBox->addWidget(m_YLineMin, 2, 1);
	gBox->addWidget(m_YLineMax, 2, 2);

	gBox->addWidget(buttonBox, 3, 2);

	setLayout(gBox);
}
