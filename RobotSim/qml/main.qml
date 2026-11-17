import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import diy 1.0

ApplicationWindow {
    id: root
    width: 860
    height: 660
    visible: true
    title: "Eilik Z-Axis (Yaw) Servo Simulator"
    color: "#1b1d23"

    // --- 4 Servo Angle Properties (in degrees) ---
    property real servoHead: 0       // Head yaw turn (-45 to +45 deg)
    property real servoBody: 0       // Body yaw turn (-35 to +35 deg)
    property real servoLeftArm: 0   // Left arm swing (-90 to 150 deg)
    property real servoRightArm: 0 // Right arm swing (-90 to 150 deg)

    // --- Single Function to Update All Servo Angles ---
    function updateServoAngles(head, body, leftArm, rightArm) {
        root.servoHead = Math.max(-45, Math.min(45, head))
        root.servoBody = Math.max(-35, Math.min(35, body))
        root.servoLeftArm = Math.max(-90, Math.min(150, leftArm))
        root.servoRightArm = Math.max(-90, Math.min(150, rightArm))
    }

    // Smooth servo motor easing
    Behavior on servoHead { NumberAnimation { duration: 350; easing.type: Easing.OutBack } }
    Behavior on servoBody { NumberAnimation { duration: 350; easing.type: Easing.OutQuad } }
    Behavior on servoLeftArm { NumberAnimation { duration: 300; easing.type: Easing.OutBack } }
    Behavior on servoRightArm { NumberAnimation { duration: 300; easing.type: Easing.OutBack } }

    // --- Robot Kinematic Structure ---
    Item {
        id: robotBase
        width: 300
        height: 360
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -40

        // Fixed Base Pedestal
        Rectangle {
            width: 140
            height: 24
            radius: 12
            color: "#3a404d"
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Servo 2: Body Assembly (Rotates around vertical Z/Yaw axis)
        Item {
            id: bodyJoint
            width: 260
            height: 320
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter

            transform: Rotation {
                origin.x: bodyJoint.width / 2
                origin.y: bodyJoint.height / 2
                axis { x: 0; y: 1; z: 0 } // Vertical Z-yaw axis in screen space
                angle: root.servoBody
            }

            // Servo 3: Left Arm (Depth-shifts when body turns)
            Rectangle {
                width: 30
                height: 100
                radius: 15
                color: "#cfd7e3"
                z: root.servoBody > 0 ? 2 : -1
                x: 28 - Math.sin(root.servoBody * Math.PI / 180) * 18
                y: 165
                transformOrigin: Item.Top
                rotation: root.servoLeftArm
            }

            // Servo 4: Right Arm (Depth-shifts when body turns)
            Rectangle {
                width: 30
                height: 100
                radius: 15
                color: "#cfd7e3"
                z: root.servoBody < 0 ? 2 : -1
                x: 202 - Math.sin(root.servoBody * Math.PI / 180) * 18
                y: 165
                transformOrigin: Item.Top
                rotation: -root.servoRightArm
            }

            // Torso Shell
            Rectangle {
                width: 150
                height: 135
                radius: 30
                color: "#f4f6fa"
                border.color: "#cbd2df"
                border.width: 2
                anchors.horizontalCenter: parent.horizontalCenter
                y: 155
                z: 0

                // Center Chest Marker (visualizes body yaw rotation)
                Rectangle {
                    width: 28
                    height: 10
                    radius: 5
                    color: "#9aa5b8"
                    y: 45
                    x: (parent.width - width) / 2 + Math.sin(root.servoBody * Math.PI / 180) * 35
                }
            }

            // Servo 1: Head Assembly (Inherits body yaw + adds own head yaw)
            Item {
                id: headJoint
                width: 195
                height: 145
                anchors.horizontalCenter: parent.horizontalCenter
                y: 15
                z: 3

                transform: Rotation {
                    origin.x: headJoint.width / 2
                    origin.y: headJoint.height / 2
                    axis { x: 0; y: 1; z: 0 } // Vertical Z-yaw axis in screen space
                    angle: root.servoHead
                }

                // Head Shell
                Rectangle {
                    anchors.fill: parent
                    radius: 42
                    color: "white"
                    border.color: "#cbd2df"
                    border.width: 2
                }

                // OLED Face Visor (Shifts horizontally with head yaw for 3D depth)

                Rectangle {
                    width: 128
                    height: 64
                    color: "black"
                    y: (parent.height - height) / 2
                    x: (parent.width - width) / 2 + Math.sin(root.servoHead * Math.PI / 180) * 22
                    VideoRender {
                        id: videoRender
                        anchors.fill: parent
                    }
                }
            }
        }
    }

    // --- Control Buttons Calling updateServoAngles(head, body, leftArm, rightArm) ---
    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 25
        RowLayout {
            Button {
                text: "Start"
                onClicked:  mainProcess.startService();
            }
            Button {
                text: "Pause"
                onClicked:  mainProcess.pause(true);
            }
            Button {
                text: "Go"
                onClicked:  mainProcess.pause(false);
            }
            Slider {
                from: -45
                to: 45
                onValueChanged: {
                    root.servoHead = value
                }
            }
            spacing: 10
            Slider {
                from: -30
                to: 30
                onValueChanged: {
                    root.servoBody = value
                }
            }
        }

        RowLayout {
            spacing: 10
            Button {
                text: "Center"
                onClicked: root.updateServoAngles(0, 0, 15, 15)
            }
            Button {
                text: "Turn Left"
                onClicked: root.updateServoAngles(10, -10, 30, -10)
            }
            Button {
                text: "Turn Right"
                onClicked: root.updateServoAngles(-10, 10, -10, 30)
            }
            Button {
                text: "Left Arm"
                onClicked: root.updateServoAngles(0, 0, 90, 0)
            }
            Button {
                text: "Right Arm"
                onClicked: root.updateServoAngles(0, 0, 0, -90)
            }
            Button {
                text: "Head Scan"
                onClicked: root.updateServoAngles(42, -15, 95, -95)
            }
        }
        RowLayout {
            spacing: 10
            Button {
                text: "Start Up"
                onClicked: mainProcess.changeEmotion(0)
            }
            Button {
                text: "Idle"
                onClicked: mainProcess.changeEmotion(1)
            }
            Button {
                text: "Happy"
                onClicked: mainProcess.changeEmotion(2)
            }
            Button {
                text: "Angry"
                onClicked: mainProcess.changeEmotion(3)
            }
            Button {
                text: "Tickled"
                onClicked: mainProcess.changeEmotion(4)
            }
            Button {
                text: "Supprised"
                onClicked: mainProcess.changeEmotion(5)
            }
        }
    }
    MainProcess {
        id: mainProcess
        onListAngleChanged: {
            root.updateServoAngles(listAngle[0],
                                   listAngle[1],
                                   listAngle[2],
                                   listAngle[3]);
        }
    }
    Component.onCompleted: {
        mainProcess.setRender(videoRender);
    }
}
