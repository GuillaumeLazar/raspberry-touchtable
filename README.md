raspberry-touchtable
====================

# Softwares

## nm-touchtable

This is the main application that display "cool stuff" on the table. The Raspberry that run this application should be connected to the table's video projector via HDMI.

This application get objects informations (position and size) from a DeviceAcquisition:
* DeviceAcquisitionDemo: is a sample dummy that generate a small object that move in loop "drawing" a square.
* DeviceAcquisitionCamera: (deprecated) using opencv to take picture from the camera and detect objects.
* DeviceAcquisitionTcpServer: (recommanded) run a TcpServer listening that a client send him objects information in Json.

## nm-touchtable-camera

## DeviceAcquisitionTcpClient

TODO: should be rename with a better name
