import sys
import wave
import math
import time
import re
from DecoderEncoder import *
from config import *

import pulseaudio as pa
import numpy as np

frames = []

def bad_arguments():
    print(f"usage: {sys.argv[0]} SENDER RECEIVER")
    sys.exit(1)

if len(sys.argv) != 3:
   bad_arguments()

try:
    sender = int(sys.argv[1])
    receiver = int(sys.argv[2])
except:
    bad_arguments()


for line in sys.stdin:
    data = line[:-1]
    bits = decode(13, 45, data)

    #print(bits)

    hz_array = [hz_non_signal if i == '0' else hz_signal for i in bits]

    for hz in hz_array:
        for i in range(int(sending_seconds*framerate)):
            frames.append(math.sin(2*hz*math.pi*i/framerate)*volume)

with pa.simple.open(direction=pa.STREAM_PLAYBACK, format=pa.SAMPLE_S16LE, rate=framerate, channels=number_of_channels) as player:
    player.write(frames)
    player.drain()