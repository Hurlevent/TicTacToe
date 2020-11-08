import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import TicTocTable 1.0

Window {
    id: _window
    property int appWidth: 600
    property int appHeight: 600
    property bool playerHasChosenMarker: false

    width: appWidth
    height: appHeight
    visible: true
    title: qsTr("TicTacToe")


    Rectangle{
        id: _chooseMarker
        anchors.fill: parent
        visible: !playerHasChosenMarker

        Label {
            id: label
            text: qsTr("Choose a marker")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
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


    Flickable{
        anchors.fill: parent
        interactive: false
        visible: playerHasChosenMarker

        TableView{
            anchors.fill: parent
            columnSpacing: 1
            rowSpacing: 1
            clip: true

            model: _model;

            delegate: Rectangle {
                implicitWidth: appWidth / 3
                implicitHeight: appHeight / 3
                border.width: 2
                border.color: "grey"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(mouse.button == Qt.LeftButton)
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
