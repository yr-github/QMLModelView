#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>

struct ToDoStruct{
  bool bDone;
  QString sDescription;
};

class ToDoList : public QObject
{
    Q_OBJECT
public:
    explicit ToDoList(QObject *parent = nullptr);
    bool SetItemAt(const ToDoStruct &item,int index);
    void AppendItem();
    void RemoveComplate();

    const QVector<ToDoStruct> &Item() const;

private:
    QVector<ToDoStruct> m_Item;
signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(int index);
    void postItemRemoved();
};

#endif // TODOLIST_H
