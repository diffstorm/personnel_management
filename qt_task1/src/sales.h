#ifndef SALES_H
#define SALES_H

#include "monthly.h"

class Sales : public Monthly
{
    Q_OBJECT

    Q_PROPERTY(double bonusPercent READ bonusPercent WRITE setBonusPercent NOTIFY bonusPercentChanged)
    Q_PROPERTY(double outcomeClaim READ outcomeClaim WRITE setOutcomeClaim NOTIFY outcomeClaimChanged)
    Q_PROPERTY(double realizedOutcome READ realizedOutcome WRITE setRealizedOutcome NOTIFY realizedOutcomeChanged)

signals:
    void bonusPercentChanged();
    void realizedOutcomeChanged();
    void outcomeClaimChanged();

public:
    Sales(QObject *parent = 0);

    virtual QString type() const;

    double bonusPercent() const;
    void setBonusPercent(double);

    double realizedOutcome() const;
    void setRealizedOutcome(double);

    double outcomeClaim() const;
    void setOutcomeClaim(double);

    virtual double salary() const;

    virtual void read(const QJsonObject&);
    virtual void write(QJsonObject&);

    static const QString TYPE;

protected:
    double m_BonusPercent;
    double m_RealizedOutcome;
    double m_OutcomeClaim;

};

#endif // SALES_H
