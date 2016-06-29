# -*- coding: utf-8 -*-
"""
Created on Thu Jun 09 14:27:26 2016

@author: Christian
"""

import serial
import numpy as np
import matplotlib.pyplot as plt
import time

data = []
count = 0
plt.ion()
fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

with serial.Serial('COM3', 9600) as ser:
    while True:
        val = ser.readline()
        val = str.split(val, ",")
        del val[50:]

        ax1.clear()
        ax1.plot(val)
        plt.pause(0.001)
        count += 1