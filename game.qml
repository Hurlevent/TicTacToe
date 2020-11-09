import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import TicTocTable 1.0

Item {
    Rectangle {
        id: _gameArea
        anchors.fill: parent

        Flickable{
            id: _game
            anchors.fill: parent
            interactive: false

            TableView{
                anchors.fill: parent
                columnSpacing: 1
                rowSpacing: 1
                clip: true

                model: _model;

                delegate: Rectangle {
                    implicitWidth: _gameArea.width / 3
                    implicitHeight: _gameArea.height / 3
                    border.width: 2
                    border.color: "grey"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(mouse.button == Qt.LeftButton && _model.started)
                            {
                                _model.interact(row, column);
                            }
                        }
                    }

                    Image {
                        anchors.fill: parent
                        source: model.path
                    }
                }
            }
        }
    }
}
