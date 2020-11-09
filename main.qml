import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import TicTocTable 1.0

Window {
    id: _window
    property int appWidth: 600
    property int appHeight: _gameArea.height + _chooseMarker.height

    width: appWidth
    height: appHeight
    visible: true
    title: qsTr("TicTacToe")

    Rectangle{
        id: _chooseMarker
        anchors.top: parent.top
        anchors.bottom: _gameArea.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 400

        visible: !_model.started

        Label {
            id: _msg
            text: _model.message;
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: label.top
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 34
        }

        Label {
            id: label
            text: qsTr("Choose a marker")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: _msg.bottom
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 34
            anchors.topMargin: 20
        }

        Image {
            id: image
            width: parent.width / 2
            anchors.left: parent.left
            anchors.top: label.bottom
            anchors.bottom: parent.bottom
            source: "RedCross.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _model.player_set_piece(1);
                    playerHasChosenMarker = true;
                }
            }
        }

        Image {
            id: image1
            width: parent.width / 2
            anchors.left: image.right
            anchors.right: parent.right
            anchors.top: label.bottom
            anchors.bottom: parent.bottom
            source: "RedCircle.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _model.player_set_piece(2);
                    playerHasChosenMarker = true;
                }
            }
        }
    }

    Rectangle {
        id: _gameArea
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: _chooseMarker.bottom
        anchors.bottom: parent.bottom
        width: appWidth
        height: 600

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
