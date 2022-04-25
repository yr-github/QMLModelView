#include "todomodel.h"
#include <iostream>
ToDoModel::ToDoModel(QObject *parent)
    : QAbstractListModel(parent),
      m_List(nullptr)
{
    std::cout<<"ToDoModel constructer"<<std::endl;
}

int ToDoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid()||!m_List)
        return 0;

    return m_List->Item().size();
}

QVariant ToDoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()||!m_List)
        return QVariant();
    switch (role) {
    case DoneRole:
        return QVariant(m_List->Item().at(index.row()).bDone);
    case DescriptionRole:
        return QVariant(m_List->Item().at(index.row()).sDescription);
    }

    return QVariant();
}

bool ToDoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_List)
        return false;
    ToDoStruct item;
    switch (role) {
    case DoneRole:
        item.bDone = value.toBool();
    case DescriptionRole:
        item.sDescription = value.toString();
    }
    if (m_List->SetItemAt(item,index.row())){

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ToDoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ToDoModel::roleNames() const
{
    QHash<int, QByteArray> name;
    name[DoneRole]="done";
    name[DescriptionRole]="description";
    return name;
}

ToDoList *ToDoModel::list() const
{
    return m_List;
}

void ToDoModel::setList(ToDoList *newList)
{
    beginResetModel();
    if(m_List)
        m_List->disconnect(this);
    m_List = newList;
    if(m_List){
        connect(m_List,&ToDoList::preItemAppended,this,[=](){
            const int index = m_List->Item().size();
            beginInsertRows(QModelIndex(),index,index);
        });
        connect(m_List,&ToDoList::postItemAppended,this,[=](){
            endInsertRows();
        });
        connect(m_List,&ToDoList::preItemRemoved,this,[=](int index){
            beginRemoveRows(QModelIndex(),index,index);
        });
        connect(m_List,&ToDoList::postItemRemoved,this,[=](){
            endRemoveRows();
        });

    }
    endResetModel();
    std::cout<<"setting list"<<std::endl;
}

void ToDoModel::addToDoItem()
{
    if(m_List)
        m_List->AppendItem();
}

void ToDoModel::deleteCompleted()
{
    if(m_List)
        m_List->RemoveComplate();
}

void ToDoModel::logSomething(QString log)
{
    std::cout<<log.toStdString()<<std::endl;
}


