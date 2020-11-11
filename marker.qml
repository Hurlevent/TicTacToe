import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import TicTocTable 1.0

Item {
    Rectangle{
        id: _chooseMarker
        anchors.fill: parent

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
            source: "BlueCross.png"
            fillMode: Image.PreserveAspectFit

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _model.player_set_piece(1);
                    _ldr.source = "game.qml";
                    _gameIsShowing = true;
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
                    _ldr.source = "game.qml";
                    _gameIsShowing = true;
                }
            }
        }
    }
}
