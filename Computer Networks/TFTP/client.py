import socket
import sys
from struct import pack, unpack
import hashlib
from random import random
import numpy as np
import time
import argparse


READ_REQUEST = 1
WRITE_REQUEST = 2
DATA = 3
ACK = 4
ERROR = 5

DATA_SIZE = 512
WINDOW_SIZE_STRING = bytes("window_size", 'utf-8')
ZERO_BYTES = b'\x00'
MODE_BYTES = bytes("octet", 'utf-8')
ONE_SHORT = np.int16(1)

np.seterr(all=None, over='ignore')


parser = argparse.ArgumentParser(description='Client TFTP-7440')
parser.add_argument('ip_server', type=str, help='server ip')
parser.add_argument('file_name', type=str, help='file name to download')
parser.add_argument('save_file_name', type=str, help='file name to save')
parser.add_argument('-p', '--port', type=int, default=69, help='port number')
parser.add_argument('-w', '--window', type=int, default=1, help='window size')
parser.add_argument('-t', '--timeout', type=float,
                    default=0.2, help='timeout time')
parser.add_argument('-a', '--attempts', type=int,
                    default=10, help='max attempts before quit')

args = parser.parse_args()

HOST = args.ip_server
PORT = args.port
BLOCKS = args.window
TIMEOUT_TIME = args.timeout
MAX_ATTEMPTS = args.attempts
SAVE_FILE_NAME = args.save_file_name


def encode_data_packet(packet):
    op_code = unpack('>h', packet[:2])[0]
    block_idx = unpack('>h', packet[2:4])[0]
    data = packet[4:]
    return op_code, block_idx, data


def decode_ack_packet(opcode, block_idx):
    packet = pack(">hh", opcode, block_idx)
    return packet


def decode_request_packet(file_name, read=True):
    opc_bytes = pack(">h", READ_REQUEST if read else WRITE_REQUEST)
    blocks_bytes = bytes(str(BLOCKS), 'utf-8')
    file_name_bytes = bytes(str(file_name), 'utf-8')
    return opc_bytes + file_name_bytes + ZERO_BYTES + MODE_BYTES + ZERO_BYTES + WINDOW_SIZE_STRING + ZERO_BYTES + blocks_bytes + ZERO_BYTES


host = sys.argv[1]
file_name = sys.argv[2]


def download_and_save_file(host, file_name, save_file_name):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(decode_request_packet(file_name), (host, PORT))

    last_block_idx_read = np.int16(0)
    sock.settimeout(TIMEOUT_TIME)

    f = open(save_file_name, 'wb')
    new_port = PORT
    error_attempts = 0
    while True:
        end = False
        for window_block in range(BLOCKS):
            for current_attempt in range(MAX_ATTEMPTS):
                try:
                    message, (host, new_port) = sock.recvfrom(DATA_SIZE + 4)
                    break
                except:
                    sock.sendto(decode_ack_packet(
                        ACK, last_block_idx_read), (host, new_port))
                    if current_attempt == MAX_ATTEMPTS - 1:
                        return None

            op_code, block_idx, data = encode_data_packet(message)

            if op_code == ERROR:
                return None

            if block_idx != last_block_idx_read + ONE_SHORT:
                if error_attempts % BLOCKS == 0:
                    sock.sendto(decode_ack_packet(
                        ACK, last_block_idx_read), (host, new_port))
                    error_attempts += 1
                break

            error_attempts = 0

            size = len(data)
            f.write(data)

            if size < DATA_SIZE:
                end = True
                break

            last_block_idx_read += ONE_SHORT

        sock.sendto(decode_ack_packet(ACK, block_idx), (host, new_port))

        if end:
            break

    f.close()


download_and_save_file(HOST, file_name, SAVE_FILE_NAME)
