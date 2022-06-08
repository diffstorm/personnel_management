#ifndef MONTHLY_H
#define MONTHLY_H

#include "person.h"

class Monthly : public Person
{
    Q_OBJECT

    Q_PROPERTY(double monthlyCompensation READ monthlyCompensation WRITE setMonthlyCompensation NOTIFY monthlyCompensationChanged)

signals:
    void monthlyCompensationChanged();

public:
    Monthly(QObject *parent = 0);

    virtual QString type() const;

    double monthlyCompensation() const;
    void setMonthlyCompensation(double);

    virtual double salary() const;

    virtual void read(const QJsonObject&);
    virtual void write(QJsonObject&);

    static const QString TYPE;

protected:
    double m_MonthlyCompensation;
};

#endif // MONTHLY_H
