#include "motorwidget.h"

MotorWidget::MotorWidget(Motor *motor, QTabBar *tabBar, QVector<RatingWidget *> &vectorRatingWidget, int numberButton, QWidget *parent) : QWidget(parent)
{
	m_VectorRatingWidget = vectorRatingWidget;
	m_NumberButton = numberButton;
	m_TabBar = tabBar;
	m_Motor = motor;

	createRatedData();

	createLabelButton();
	createMainWidget();
}
void MotorWidget::createLabelButton()
{
	QSignalMapper *mapper = new QSignalMapper(this);

	QFont fontLine("Arial", 10);

	for (int i=0; i<m_NumberButton; ++i)
	{
		QLineEdit *tempLineEdit = new QLineEdit(this);
		tempLineEdit->setFont(fontLine);
		tempLineEdit->setText(tr("Wpisz nazwę uzwojenia"));

		QPushButton *tempButton = new QPushButton(tr("Dodaj dane uzwojenia"));

		m_VectorLabelButton.push_back(qMakePair(tempLineEdit, tempButton));

		QHBoxLayout *hBox = new QHBoxLayout(this);
		hBox->addWidget(m_VectorLabelButton[i].first);
		hBox->addWidget(m_VectorLabelButton[i].second);

		QGroupBox *tempGrBox = new QGroupBox(tr("Uzwojenie"), this);
		tempGrBox->setFont(QFont("Arial", 12, QFont::Bold));
		tempGrBox->setStyleSheet("QGroupBox{border:1px; border-style:outset; border-color: gray; margin:10px} "
									"QGroupBox::title{subcontrol-origin: margin; subcontrol-position:top left}");
		tempGrBox->setLayout(hBox);

		m_VectorTempWindingBox.push_back(tempGrBox);

		mapper->setMapping (m_VectorLabelButton[i].second, i);
		connect(m_VectorLabelButton[i].second, SIGNAL(clicked()), mapper, SLOT(map()));
	}

	connect(mapper, SIGNAL(mapped(int)), this, SLOT(addDateReconstruction(int)));
}
void MotorWidget::addDateReconstruction(int i)
{
		m_TabBar->setTabText(i, m_VectorLabelButton[i].first->text());
		m_VectorNameWindings.push_back(m_VectorLabelButton[i].first->text());
		m_VectorRatingWidget[i]->news();
}
void MotorWidget::createRatedData()
{
	QFont fontLine("Arial", 10);

	m_LineName = new QLineEdit(this);
	m_LineName->setFont(fontLine);

	m_LineType = new QLineEdit(this);
	m_LineType->setFont(fontLine);

	m_LineNumber = new QLineEdit(this);
	m_LineNumber->setFont(fontLine);

	m_LinePower = new QLineEdit(this);
	m_LinePower->setFont(fontLine);

	QFont fontLabel("Arial", 10);

	QLabel *labelName = new QLabel(tr("Nazwa maszyny:"), this);
	labelName->setFont(fontLabel);

	QLabel *labelType = new QLabel(tr("Typ:"), this);
	labelType->setFont(fontLabel);

	QLabel *labelNumber = new QLabel(tr("Number fabryczny:"), this);
	labelNumber->setFont(fontLabel);

	QLabel *labelPower = new QLabel(tr("Moc znamionowa:"), this);
	labelPower->setFont(fontLabel);

	QGridLayout *gBox = new QGridLayout(this);
	gBox->addWidget(labelName, 0, 0);
	gBox->addWidget(labelType, 1, 0);
	gBox->addWidget(labelNumber, 1, 2);
	gBox->addWidget(labelPower, 2, 0);

	gBox->addWidget(m_LineName, 0, 1);
	gBox->addWidget(m_LineType, 1, 1);
	gBox->addWidget(m_LineNumber, 1, 3);
	gBox->addWidget(m_LinePower, 2, 1);

	m_RatedData = new QGroupBox(tr("Dane znamionowe"), this);
	m_RatedData->setFont(QFont("Arial", 12, QFont::Bold));
	m_RatedData->setStyleSheet("QGroupBox{border:1px; border-style:outset; border-color: gray; margin:10px} "
								"QGroupBox::title{subcontrol-origin: margin; subcontrol-position:top left}");
	m_RatedData->setLayout(gBox);
	//m_RatedData->setMinimumWidth(350);
	//m_RatedData->setMaximumWidth(350);
}
void MotorWidget::createMainWidget()
{
	QVBoxLayout *vBox= new QVBoxLayout(this);
	for (auto x: m_VectorTempWindingBox)
		vBox->addWidget(x);

	m_WindingData = new QGroupBox(this);
	m_WindingData->setFont(QFont("Arial", 12, QFont::Bold));
	m_WindingData->setStyleSheet("QGroupBox{border:1px; border-style:outset; border-color: gray; margin:10px} ");
	m_WindingData->setLayout(vBox);

	QVBoxLayout *vMainBox= new QVBoxLayout(this);
	vMainBox->addWidget(m_RatedData);
	vMainBox->addWidget(m_WindingData);
}
void MotorWidget::getLineMotorWidget()
{
	m_Motor->setRatedData().m_Name = m_LineName->text().toStdString();

	m_Motor->setRatedData().m_Type = m_LineType->text().toStdString();

	m_Motor->setRatedData().m_Number = m_LineNumber->text().toStdString();

	m_Motor->setRatedData().m_Power = m_LinePower->text().toFloat();

	for (int i=0; i<m_VectorNameWindings.size(); ++i)
		m_Motor->setVectorNameWinding().push_back(m_VectorNameWindings[i].toStdString());
}
void MotorWidget::setLineMotorWidget()
{
	m_LineName->setText(QString::fromStdString(m_Motor->setRatedData().m_Name));

	m_LineType->setText(QString::fromStdString(m_Motor->setRatedData().m_Type));

	m_LineNumber->setText(QString::fromStdString(m_Motor->setRatedData().m_Number));

	m_LinePower->setText(QString::number(m_Motor->setRatedData().m_Power));



}
