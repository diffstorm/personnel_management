#ifndef HOURLY_H
#define HOURLY_H

#include "person.h"

class Hourly : public Person
{
    Q_OBJECT

    Q_PROPERTY(double doneHours READ doneHours WRITE setDoneHours NOTIFY doneHoursChanged)
    Q_PROPERTY(double hourlyCompensation READ hourlyCompensation WRITE setHourlyCompensation NOTIFY hourlyCompensationChanged)

signals:
    void hourlyCompensationChanged();
    void doneHoursChanged();

public:
    Hourly(QObject *parent = 0);

    virtual QString type() const;

    double hourlyCompensation() const;
    void setHourlyCompensation(double);

    double doneHours() const;
    void setDoneHours(double);

    virtual double salary() const;

    virtual void read(const QJsonObject&);
    virtual void write(QJsonObject&);

    static const QString TYPE;

protected:
    double m_HourlyCompensation;
    double m_DoneHours;
};

#endif // HOURLY_H
