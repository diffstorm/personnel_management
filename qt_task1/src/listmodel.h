#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>

class Person;

class ListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList personTypes READ personTypes CONSTANT)

public slots:
    int size();
    void addperson(const QString&);
    void removeperson(int);
    void load();
    void save();

public:
    explicit ListModel(QObject *parent = nullptr);
    QStringList personTypes();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

protected:
    QVector<Person*> m_PeopleList;
};

#endif // LISTMODEL_H
