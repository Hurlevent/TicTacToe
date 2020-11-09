import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import TicTocTable 1.0

Window {
    id: _window
    property int appWidth: 600
    property int appHeight: 700
    property bool _gameIsShowing: false
    property string _clickToRestartText: !_model.started && _gameIsShowing ? "(Click somewhere to restart)" : ""

    width: appWidth
    height: appHeight
    visible: true
    title: qsTr("TicTacToe")

    Label {
        id: _msg
        text: _model.message;
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: _clickToRestart.top
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 34
        height: 50
    }

    Label {
        id: _clickToRestart
        text: _clickToRestartText
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: _msg.bottom
        anchors.bottom: ldr.top
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 34
        height: 50
    }

    Loader {
        id: _ldr
        anchors.top: _clickToRestart.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        source: "marker.qml"
    }

    MouseArea {
        visible: !_model.started && _gameIsShowing
        anchors.fill: _ldr
        opacity: 0.5
        onClicked: {
            _model.reset_board();
            _ldr.source = "marker.qml";
            _gameIsShowing = false;
        }
    }
}
