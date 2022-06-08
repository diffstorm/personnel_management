#include "monthly.h"

const QString Monthly::TYPE = QString("Monthly");

Monthly::Monthly(QObject *parent)
    : Person(parent)
    , m_MonthlyCompensation(0)
{
}

QString Monthly::type() const
{
    return Monthly::TYPE;
}

double Monthly::monthlyCompensation() const
{
    return m_MonthlyCompensation;
}

void Monthly::setMonthlyCompensation(double monthlyCompensation)
{
    m_MonthlyCompensation = monthlyCompensation;
    emit monthlyCompensationChanged();
    emit salaryChanged();
}

double Monthly::salary() const
{
    return m_MonthlyCompensation;
}

void Monthly::read(const QJsonObject &json)
{
    Person::read(json);
    m_MonthlyCompensation = json["monthlyCompensation"].toDouble();
}

void Monthly::write(QJsonObject &json)
{
    Person::write(json);
    json["monthlyCompensation"] = m_MonthlyCompensation;
}
