# -*- coding: utf-8 -*-
"""
forest_driver.py
Created on Thu Mar 27 05:40:16 2014
Original Author was AJC, modified by Averal,Karthik, and Aravind on 1/28/17
Use command "python status_lights_driver.py /dev/ttyUSB0" or something similar to get it going
@author: ajc
"""

from pyfirmata import ArduinoMega
import pyfirmata
import sys
import re
import time

class StatusLights():
    def __init__(self, lc, addr, debug=True):
        self.lc = lc
        self.board = None
        self.lights = []

        #
        # pin 53 used as placeholder because we don't support buzzers yet
        #                  (r,  y,  g,  b )
        self.lights.append((22, 23, 24, 53))
        self.lights.append((25, 26, 27, 53))
        self.lights.append((28, 29, 30, 53))
        self.lights.append((31, 32, 33, 53))
        self.lights.append((34, 35, 36, 53))
        self.lights.append((37, 38, 39, 53))
        self.lights.append((40, 41, 42, 53))
        self.lights.append((43, 44, 45, 53))
        if addr is not None:
            self.board = ArduinoMega(addr)
            for r, y, g, b in self.lights:
                self.board.digital[r].write(1)
                self.board.digital[y].write(1)
                self.board.digital[g].write(1)
                self.board.digital[b].write(1)

        self.debug = debug

    def set_lights(self, light, color, status):
        r, y, g, b = self.lights[light]
        if color == "red":
            control = r
        elif color == "yellow":
            control = y
        elif color == "green":
            control = g
        else:
            control = b
        self.board.digital[control].write(status)

lit = lambda x,y: int(x==y)

if __name__ == '__main__':
    print("starting status_lights.py")
    lights = StatusLights(None, sys.argv[1], False)
    print("Ready to receive commands")

    while True:
        #time.sleep(1)
        #select lights to turn on through command line
        for i in range(2,9):
            lights.set_lights(i-2,lit(i,"r"),lit(i,"y"),lit(i,"g"),0)
