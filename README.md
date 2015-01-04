raspberry-touchtable
====================

# Softwares

## nm-touchtable

This is the main application that display "cool stuff" on the table. The Raspberry that run this application should be connected to the table's video projector via HDMI. Default resolution is a 1280x800 window.

This application get objects informations (position and size) from a DeviceAcquisition:
* DeviceAcquisitionDemo: is a sample dummy that generate a small object that move in loop "drawing" a square.
* DeviceAcquisitionCamera: (deprecated) using opencv2 to take picture from the camera and detect objects.
* DeviceAcquisitionTcpServer: (recommanded) run a TcpServer listening that a client send him a json message with objects information.

The application should be compile and run with one device acquisition mode. (Default is "DeviceAcquisitionTcpServer")

## nm-touchtable-camera

This one is the TcpClient that should be run after you run "nm-touchtable (mode DeviceAcquisitionTcpServer).
The software use opencv2 to take picture from the camera and detect objects.

For each camera frame, a json message is sent to the server (aka "nm-touchtable") with detected objetcs information.


## DeviceAcquisitionTcpClient

A desktop application that allow to send information to "nm-touchtable" using a mouse (instead of a camera like with "nm-touchtable-camera"). The application display a 320x240 window (it's a fixed sensor area).
each time the user press, move or release the mouse cursor into this window, a json message is sent to the server.

## Json message

The message this sent from a client ("nm-touchtable-camera" or "DeviceAcquisitionTcpClient") to the server ("nm-touchtable").

The message look like that:
```json
{
  "id":2,
  "objects":[{"state":1, "x":121, "y":86, "width":20, "height":20}]
}

id: message id
objects: array with all detected object (empty if no object)
state: (WIP) unknown, press, move, release
x, y, width, height: objects information into an sensor area of dimension 320x240
```


