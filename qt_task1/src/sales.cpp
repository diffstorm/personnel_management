#include "sales.h"

const QString Sales::TYPE = QString("Sales");

Sales::Sales(QObject *parent)
    : Monthly(parent)
    , m_BonusPercent(0)
    , m_RealizedOutcome(0)
    , m_OutcomeClaim(0)
{

}

QString Sales::type() const
{
    return Sales::TYPE;
}

double Sales::bonusPercent() const
{
    return m_BonusPercent;
}

void Sales::setBonusPercent(double bonusPercent)
{
    m_BonusPercent = bonusPercent;
    emit bonusPercentChanged();
}

double Sales::realizedOutcome() const
{
    return m_RealizedOutcome;
}

void Sales::setRealizedOutcome(double realizedOutcome)
{
    m_RealizedOutcome = realizedOutcome;
    emit realizedOutcomeChanged();
    emit salaryChanged();
}

double Sales::outcomeClaim() const
{
    return m_OutcomeClaim;
}

void Sales::setOutcomeClaim(double outcomeClaim)
{
    m_OutcomeClaim = outcomeClaim;
    emit outcomeClaimChanged();
    emit salaryChanged();
}

double Sales::salary() const
{
    double bonusPercent = (m_RealizedOutcome >= m_OutcomeClaim) ? m_BonusPercent : 0;
    return m_MonthlyCompensation + m_MonthlyCompensation*(bonusPercent/100);
}

void Sales::read(const QJsonObject &json)
{
    Monthly::read(json);
    m_BonusPercent = json["bonusPercent"].toDouble();
    m_RealizedOutcome = json["realizedOutcome"].toDouble();
    m_OutcomeClaim = json["outcomeClaim"].toDouble();
}

void Sales::write(QJsonObject &json)
{
    Monthly::write(json);
    json["bonusPercent"] = m_BonusPercent;
    json["outcomeClaim"] = m_OutcomeClaim;
    json["realizedOutcome"] = m_RealizedOutcome;
}
