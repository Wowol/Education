import numpy as np
import time
import sys
from DecoderEncoder import *
from config import *

import pulseaudio as pa

size = int(sending_seconds * framerate)

awesome_frame = None

messages_read = 0

def clear():
    global buffer
    global awesome_frame
    global binary_message
    global results_for_samples
    results_for_samples = []
    buffer = [0] * size
    awesome_frame = None
    binary_message = good_header
    for a in range(number_of_samples):
        results_for_samples.append([])

clear()

def read_message(buffer):
    global binary_message, messages_read
    begin_index = size * awesome_frame // number_of_samples
    fourier = np.absolute(np.fft.rfft(buffer[begin_index:begin_index+size]))
    arg_max = np.argmax(fourier)

    sig = 1 if fourier[int(hz_signal*sending_seconds)] > fourier[int(hz_non_signal*sending_seconds)] else 0
    binary_message += str(sig)
    
    message = encode(binary_message)
    if message != None:
        print(message)
        clear()
        messages_read += 1
        if end_server_after_receiving_tests and messages_read == number_of_tests:
            sys.exit(0)

        return True

def wait_for_header(buffer):
    for current_frame in range(number_of_samples):
        begin_index = size * current_frame // number_of_samples
        fourier = np.absolute(np.fft.rfft(buffer[begin_index:begin_index+size]))
        sig = 1 if fourier[int(hz_signal*sending_seconds)] > fourier[int(hz_non_signal*sending_seconds)] else 0
        results_for_samples[current_frame].append((sig, abs(fourier[int(hz_signal*sending_seconds)] - fourier[int(hz_non_signal*sending_seconds)])))

with pa.simple.open(direction=pa.STREAM_RECORD, format=pa.SAMPLE_S16LE, rate=framerate, channels=number_of_channels) as recorder:
    while(True):
        buffer.extend(recorder.read(size))

        if awesome_frame != None:
            if read_message(buffer):
                continue
        else:
            wait_for_header(buffer)
                
        buffer = buffer[size:]

        if awesome_frame == None:
            best_frame = None
            best_diff = 2**50
            for frame_index in range(len(results_for_samples)):
                frame = results_for_samples[frame_index]
                current_header = ""
                current_diff = 0

                for sample in frame:
                    current_header += str(sample[0])
                    current_diff += sample[1]

                if current_header[-len(good_header):] == good_header:
                    if (current_diff < best_diff):
                        best_frame = frame_index
                        best_diff = current_diff
            if best_frame != None:
                awesome_frame = best_frame