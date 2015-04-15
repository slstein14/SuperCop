import QtQuick 2.0
import QtQuick.Controls 1.2

Item
{
    width: 300
    height: 300
    Rectangle
    {
        anchors.fill: parent
        color: "white"
    }

    AnimatedSprite
    {
        id: sprite
        width: 246
        height: 233
        anchors.verticalCenterOffset: 1
        anchors.horizontalCenterOffset: 0
        z: 1
        currentFrame: 0
        anchors.centerIn: parent
        source: "../SuperCop/Images/CopRoll.png"

        frameCount: 8
        frameRate: 30
        frameWidth: 246
        frameHeight: 233
        focus: true
        loops: 1

        Keys.onPressed:
        {
            if(event.key === Qt.Key_Down)
                sprite.restart();
        }
    }
}

