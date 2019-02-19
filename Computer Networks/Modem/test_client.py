import sys
import wave
import math
import time
import re
from DecoderEncoder import *
from config import *
import random
import string

import pulseaudio as pa
import numpy as np

frames = []
strings = []

for i in range(number_of_tests):
    strings.append((random.randrange(256), random.randrange(256), ''.join(random.choices(string.ascii_uppercase + string.digits + string.ascii_lowercase, k=string_length))))

for packet in strings:
    bits = decode(packet[0], packet[1], packet[2])

    print(packet)

    hz_array = [hz_non_signal if i == '0' else hz_signal for i in bits]

    for hz in hz_array:
        for i in range(int(sending_seconds*framerate)):
            frames.append(math.sin(2*hz*math.pi*i/framerate)*volume)

with pa.simple.open(direction=pa.STREAM_PLAYBACK, format=pa.SAMPLE_S16LE, rate=framerate, channels=number_of_channels) as player:
    player.write(frames)
    player.drain()