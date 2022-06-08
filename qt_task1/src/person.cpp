#include "person.h"

const QString Person::TYPE = QString("Person");

Person::Person(QObject *parent)
    : QObject(parent)
{
}

QString Person::type() const
{
    return Person::TYPE;
}

QString Person::name() const
{
    return m_Name;
}

void Person::setName(const QString& name)
{
    m_Name = name;
    emit nameChanged();
}

QString Person::ssn() const
{
    return m_SSN;
}

void Person::setSsn(const QString& ssn)
{
    m_SSN = ssn;
    emit ssnChanged();
}

void Person::read(const QJsonObject &json)
{
    m_Name = json["name"].toString();
    m_SSN = json["ssn"].toString();
}

void Person::write(QJsonObject &json)
{
    json["name"] = m_Name;
    json["ssn"] = m_SSN;
}
