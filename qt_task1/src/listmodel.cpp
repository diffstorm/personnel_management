#include <QLocale>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "person.h"
#include "monthly.h"
#include "hourly.h"
#include "sales.h"
#include "listmodel.h"

#define JSON_DATA_FILE "data.json"

enum Roles {
    rpersonType = Qt::UserRole,
    rName,
    rSsn,
    rSalary,
    rMonthlyCompensation,
    rHourlyCompensation,
    rDoneHours,
    rBonusPercent,
    rRealizedOutcome,
    rOutcomeClaim
};

ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

QStringList ListModel::personTypes()
{
    QStringList a;
    a << "Select";
    a << Monthly::TYPE;
    a << Hourly::TYPE;
    a << Sales::TYPE;
    return a;
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid()) ? 0 : m_PeopleList.size();
}

bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        Person* person = m_PeopleList.at(index.row());
        if (person == nullptr)
            return false;

        QVector<int> modifyList;
        switch (role)
        {
        case rpersonType:
            qDebug() << "type: " << value;
        case rSalary:
            return false;
        case rName:
            person->setName(value.toString());
            break;
        case rSsn:
            person->setSsn(value.toString());
            break;
        case rMonthlyCompensation:
            if(person->type() == Monthly::TYPE || person->type() == Sales::TYPE)
            {
                ((Monthly*) person)->setMonthlyCompensation(value.toDouble());
                modifyList << rSalary;
            }
            break;
        case rHourlyCompensation:
            if(person->type() == Hourly::TYPE)
            {
                ((Hourly*) person)->setHourlyCompensation(value.toDouble());
                modifyList << rSalary;
            }
            break;
        case rDoneHours:
            if(person->type() == Hourly::TYPE)
            {
                ((Hourly*) person)->setDoneHours(value.toDouble());
                modifyList << rSalary;
            }
            break;
        case rBonusPercent:
            if(person->type() == Sales::TYPE)
            {
                ((Sales*) person)->setBonusPercent(value.toDouble());
                modifyList << rSalary;
            }
            break;
        case rRealizedOutcome:
            if(person->type() == Sales::TYPE)
            {
                ((Sales*) person)->setRealizedOutcome(value.toDouble());
                modifyList << rSalary;
            }
            break;
        case rOutcomeClaim:
            if(person->type() == Sales::TYPE)
            {
                ((Sales*) person)->setOutcomeClaim(value.toDouble());
                modifyList << rSalary;
            }
            break;
        }

        emit dataChanged(index, index, modifyList << role);
        return true;
    }
    return false;
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0)
        return QVariant();

    Person* person = m_PeopleList.at(index.row());
    if (person == nullptr)
        return QVariant();

    QVariant ret;
    switch (role)
    {
    case rpersonType:
        ret.setValue(person->type());
        break;
    case rName:
        ret.setValue(person->name());
        break;
    case rSsn:
        ret.setValue(person->ssn());
        break;
    case rSalary:
        ret.setValue(person->salary());
        break;
    case rMonthlyCompensation:
        if(person->type() == Monthly::TYPE || person->type() == Sales::TYPE)
            ret.setValue(((Monthly*) person)->monthlyCompensation());
        break;
    case rHourlyCompensation:
        if(person->type() == Hourly::TYPE)
            ret.setValue(((Hourly*) person)->hourlyCompensation());
        break;
    case rDoneHours:
        if(person->type() == Hourly::TYPE)
            ret.setValue(((Hourly*) person)->doneHours());
        break;
    case rBonusPercent:
        if(person->type() == Sales::TYPE)
            ret.setValue(((Sales*) person)->bonusPercent());
        break;
    case rRealizedOutcome:
        if(person->type() == Sales::TYPE)
            ret.setValue(((Sales*) person)->realizedOutcome());
        break;
    case rOutcomeClaim:
        if(person->type() == Sales::TYPE)
            ret.setValue(((Sales*) person)->outcomeClaim());
        break;
    }

    return ret;
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    return {
        { rpersonType, "type" },
        { rName, "name" },
        { rSsn, "ssn"},
        { rSalary, "salary"},
        { rMonthlyCompensation, "monthlyCompensation" },
        { rHourlyCompensation, "hourlyCompensation" },
        { rDoneHours, "doneHours" },
        { rBonusPercent, "bonusPercent" },
        { rRealizedOutcome, "realizedOutcome" },
        { rOutcomeClaim, "outcomeClaim" }
    };
}

int ListModel::size()
{
    return m_PeopleList.size();
}

void ListModel::addperson(const QString& personType)
{
    qDebug() << "Add " << personType;
    const int index = m_PeopleList.size();
    beginInsertRows(QModelIndex(), index, index);

    Person* person = nullptr;

    if (personType == Monthly::TYPE)
        person = new Monthly(this);
    else if (personType == Hourly::TYPE)
        person = new Hourly(this);
    else if (personType == Sales::TYPE)
        person = new Sales(this);

    m_PeopleList.append(person);

    endInsertRows();
}

void ListModel::removeperson(int index)
{
    qDebug() << "Remove " << index;
    beginRemoveRows(QModelIndex(), index, index);

    m_PeopleList.removeAt(index);

    endRemoveRows();
}

void ListModel::load()
{
    qDebug("Loaded");

    QFile* file = new QFile(JSON_DATA_FILE, this);
    if (!file->open(QIODevice::ReadOnly))
    {
        qWarning("Error: open file");
        return;
    }

    QByteArray personData = file->readAll();
    file->close();

    QJsonParseError jsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(personData, &jsonParseError);

    if (doc.isNull() || doc.isEmpty() || jsonParseError.error != QJsonParseError::NoError)
    {
        qWarning("Error: JSON parse - %s", qPrintable(jsonParseError.errorString()));
        return;
    }

    QJsonObject rootObject = doc.object();
    QVector<Person*> newPeople;
    QJsonArray PeopleJson = rootObject["People"].toArray();
    for(const QJsonValue &personJsonValue : qAsConst(PeopleJson))
    {
        QJsonObject personJson = personJsonValue.toObject();
        Person* newperson = nullptr;
        QString personType = personJson["type"].toString();
        if (personType == Monthly::TYPE)
            newperson = new Monthly(this);
        else if (personType == Hourly::TYPE)
            newperson = new Hourly(this);
        else if (personType == Sales::TYPE)
            newperson = new Sales(this);
        else
        {
            qWarning("Error: wrong type");
            return;
        }

        newperson->read(personJson);
        newPeople.append(newperson);
    }

    beginResetModel();
    m_PeopleList = newPeople;
    endResetModel();
}

void ListModel::save()
{
    qDebug("Saved");

    QJsonObject PeopleJson;
    QJsonArray personArray;
    for (Person* person : qAsConst(m_PeopleList))
    {
        QJsonObject json;
        json["type"] = person->type();
        person->write(json);
        personArray.append(json);
    }
    PeopleJson["People"] = personArray;

    QJsonDocument jsonDocument(PeopleJson);
    QFile* file = new QFile(JSON_DATA_FILE, this);
    if (!file->open(QIODevice::WriteOnly))
    {
        qWarning("Error: open file");
        return;
    }

    QByteArray jsonBytes = jsonDocument.toJson();
    file->write(jsonBytes);
    file->close();
}
