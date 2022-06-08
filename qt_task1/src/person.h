#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class Person : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString ssn READ ssn WRITE setSsn NOTIFY ssnChanged)
    Q_PROPERTY(QString type READ type CONSTANT)
    Q_PROPERTY(double salary READ salary NOTIFY salaryChanged)

signals:
    void nameChanged();
    void ssnChanged();
    void salaryChanged();

public:
    virtual QString type() const;

    QString name() const;
    void setName(const QString&);

    QString ssn() const;
    void setSsn(const QString&);

    virtual double salary() const = 0;

    virtual void read(const QJsonObject&);
    virtual void write(QJsonObject&);

    explicit Person(QObject *parent = 0);

    static const QString TYPE;

protected:
    QString m_Name;
    QString m_SSN;
};

#endif // PERSON_H
