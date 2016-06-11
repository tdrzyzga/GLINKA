#include "motorwidget.h"

MotorWidget::MotorWidget(QVector<RatingWidget *> &vectorRatingWidget, int numberButton, QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *vBox = new QVBoxLayout(this);
	QSignalMapper *mapper = new QSignalMapper(this);

	m_VectorRatingWidget = vectorRatingWidget;

	for (int i=0; i<numberButton; ++i)
	{
		m_VectorButton.push_back(new QPushButton(tr("Dodaj dane uzwojenia"), this));
		vBox->addWidget(m_VectorButton[i]);

		mapper->setMapping (m_VectorButton[i], i);
		connect(m_VectorButton[i], SIGNAL(clicked()), mapper, SLOT(map()));
	}
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(addDateReconstruction(int)));
}
void MotorWidget::addDateReconstruction(int i)
{
		m_VectorRatingWidget[i]->news();
}
