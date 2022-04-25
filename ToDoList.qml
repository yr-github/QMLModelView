import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import ToDo 1.0

ColumnLayout {
    Frame{
        ListView{
            implicitWidth: 250//有讲究的 TODO：
            implicitHeight: 250
            clip: true
            model: ToDoModel{//可以理解为创建对象
                id:todomodel
                list: toDoList
            }

            delegate: RowLayout{
                width: parent.width
                CheckBox{
                    checked: model.done
                    onClicked: model.done = checked
                }
                TextField{
                    Layout.fillWidth: true
                    text: model.description
                    onEditingFinished: model.description=text
                }
            }
            Component.onCompleted: {
                console.log("ListView Completed")
            }

        }

    }
    RowLayout{
        id: buttonRow
        Button{
            id:addOne
            text: qsTr("添加一项新任务")
            Layout.fillWidth: true
            onClicked: todomodel.addToDoItem()

        }
        Button{
            id:deleteC
            text: qsTr("删除完成的任务")
            Layout.fillWidth: true
            onClicked: todomodel.deleteCompleted()
        }
    }
}

