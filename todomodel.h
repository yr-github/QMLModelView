#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>
#include "todolist.h"
class ToDoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    Q_PROPERTY(ToDoList* list READ list WRITE setList)
    explicit ToDoModel(QObject *parent = nullptr);

    enum{
        DoneRole = Qt::UserRole,
        DescriptionRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ToDoList *list() const;
    void setList(ToDoList *newList);

    Q_INVOKABLE void addToDoItem();
    Q_INVOKABLE void deleteCompleted();
    Q_INVOKABLE static void logSomething(QString log);
private:
    ToDoList* m_List;
};

#endif // TODOMODEL_H
