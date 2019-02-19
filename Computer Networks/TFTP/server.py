import socket
import time
from struct import pack, unpack
import random
import hashlib
import sys
import numpy as np
import argparse


def encode_request_packet(packet):
    arr = packet.split(b'\x00')
    op_code = unpack('>b', arr[1][:1])[0]
    file_name = arr[1][1:].decode("utf-8")
    blocks = 1
    if len(arr) == 6:
        blocks = int(arr[4].decode("utf-8"))
    return op_code, file_name, blocks


def decode_data_packet(block_idx, data):
    op_code_and_block_idx = pack(">hh", 3, block_idx)
    return op_code_and_block_idx + data


def encode_ack_packet(packet):
    return unpack(">hh", packet)


HOST = ''


DATA_SIZE = 512


parser = argparse.ArgumentParser(description='Server TFTP-7440')
parser.add_argument('directory_name', type=str,
                    help='directory name to provide files from')
parser.add_argument('-p', '--port', type=int, default=69, help='port number')
parser.add_argument('-t', '--timeout', type=float,
                    default=5.0, help='timeout time')
parser.add_argument('-a', '--attempts', type=int,
                    default=20, help='max attempts before quit')

args = parser.parse_args()


TIMEOUT_TIME = args.timeout
MAX_ATTEMPTS = args.attempts
ONE_SHORT = np.int16(1)
PORT = args.port
PATH = args.directory_name


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((HOST, PORT))

while True:
    msg, addr = sock.recvfrom(4096)
    if len(msg) > 4:
        client_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        client_sock.bind((HOST, random.randrange(1000, 2000)))
        client_sock.settimeout(TIMEOUT_TIME)

        op_code, file_name, blocks = encode_request_packet(msg)
        try:
            with open(PATH+"/"+file_name, "rb") as f:
                data = f.read()
                l = len(data)

                current_data_idx = 0
                current_block_idx = ONE_SHORT
                next_data_idx = min(current_data_idx + DATA_SIZE, l)
                times_tried = 0
                while current_data_idx < l:
                    next_data_idx = min(current_data_idx + DATA_SIZE, l)

                    err = False
                    for times_tried in range(MAX_ATTEMPTS):
                        if times_tried == MAX_ATTEMPTS - 1:
                            err = True
                            break
                        try:
                            old_block_idx = np.int16(current_block_idx)
                            new_current_data_idx = current_data_idx
                            new_next_data_idx = next_data_idx
                            for i in range(blocks):
                                if new_current_data_idx >= l:
                                    break
                                client_sock.sendto(decode_data_packet(
                                    np.int16(current_block_idx), data[new_current_data_idx:new_next_data_idx]), addr)

                                new_current_data_idx = new_next_data_idx
                                new_next_data_idx = min(
                                    new_current_data_idx + DATA_SIZE, l)
                                current_block_idx += ONE_SHORT

                            msg, addr = client_sock.recvfrom(4096)
                            break
                        except socket.timeout:
                            current_block_idx = old_block_idx
                            continue
                        except ConnectionResetError:
                            err = True
                            break
                    if err:
                        break

                    op_code, block_idx_received = encode_ack_packet(msg)

                    minus = np.int16(abs((current_block_idx -
                                          np.int16(block_idx_received)) - ONE_SHORT)) * DATA_SIZE

                    current_block_idx = np.int16(block_idx_received) + 1
                    current_data_idx = new_current_data_idx - minus
                    next_data_idx = new_next_data_idx - minus

        except:
            pass
