#include "todolist.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    m_Item.append({true,QStringLiteral("123")});
    m_Item.append({false,QStringLiteral("456")});
}

bool ToDoList::SetItemAt(const ToDoStruct &item, int index)
{
    bool result = false;

    do {
        if(index<0||index>=m_Item.size()){
            result = false;
            break;
        }
        ToDoStruct lastItem = m_Item[index];
        if(lastItem.bDone==item.bDone&&lastItem.sDescription==item.sDescription){
            result = false;
            break;
        }else {
            m_Item[index]=item;
            result = true;
            break;
        }

    } while (0);
    return result;
}

void ToDoList::AppendItem()
{
    emit preItemAppended();
    m_Item.append({false,""});
    emit postItemAppended();
}

void ToDoList::RemoveComplate()
{
    for(int i = 0; i < m_Item.size() ; ){
        if(m_Item.at(i).bDone){
            emit preItemRemoved(i);
            m_Item.removeAt(i);
            emit postItemRemoved();
        }else {
            i++;
        }
    }
}

const QVector<ToDoStruct> &ToDoList::Item() const
{
    return m_Item;
}
