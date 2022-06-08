#include "hourly.h"

const QString Hourly::TYPE = QString("Hourly");

Hourly::Hourly(QObject *parent)
    : Person(parent)
    , m_HourlyCompensation(0)
    , m_DoneHours(0)
{
}

QString Hourly::type() const
{
    return Hourly::TYPE;
}

double Hourly::hourlyCompensation() const
{
    return m_HourlyCompensation;
}

void Hourly::setHourlyCompensation(double hourlyCompensation)
{
    m_HourlyCompensation = hourlyCompensation;
    emit hourlyCompensationChanged();
    emit salaryChanged();
}

double Hourly::doneHours() const
{
    return m_DoneHours;
}

void Hourly::setDoneHours(double doneHours)
{
    m_DoneHours = doneHours;
    emit doneHoursChanged();
    emit salaryChanged();
}

double Hourly::salary() const
{
    return m_DoneHours * m_HourlyCompensation;
}

void Hourly::read(const QJsonObject &json)
{
    Person::read(json);
    m_HourlyCompensation = json["hourlyCompensation"].toDouble();
    m_DoneHours = json["doneHours"].toDouble();
}

void Hourly::write(QJsonObject &json)
{
    Person::write(json);
    json["hourlyCompensation"] = m_HourlyCompensation;
    json["doneHours"] = m_DoneHours;
}
