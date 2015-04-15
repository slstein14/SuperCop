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
        frameRate: 0
        anchors.centerIn: parent
        source: "../SuperCop/Images/CopRunSprite_modified.png"

        frameCount: 3
        frameSync: true
        frameWidth: 246
        frameHeight: 233
        focus: true
        paused: true;
        Keys.onRightPressed: sprite.advance(1);
        Keys.onLeftPressed: sprite.advance(-1);
    }
}

