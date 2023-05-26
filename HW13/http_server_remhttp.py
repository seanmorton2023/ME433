import os
import time
import ipaddress
import wifi
import socketpool
import board
import microcontroller
import terminalio
from digitalio import DigitalInOut, Direction
from adafruit_httpserver.server import Server
from adafruit_httpserver.request import Request
from adafruit_httpserver.response import Response
# from adafruit_httpserver.methods import Method #obsolete. method=Method.POST has been replaced with method="POST"
from adafruit_httpserver.mime_types import MIMETypes