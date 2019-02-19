import sys
import bitarray
import zlib

good_header = "10101011"

bbEncode = {
    "11110" : "0000",
    "01001" : "0001",
    "10100" : "0010",
    "10101" : "0011",
    "01010" : "0100",
    "01011" : "0101",
    "01110" : "0110",
    "01111" : "0111",
    "10010" : "1000",
    "10011" : "1001",
    "10110" : "1010",
    "10111" : "1011",
    "11010" : "1100",
    "11011" : "1101",
    "11100" : "1110",
    "11101" : "1111",
    }

bbDecode = {
    "0000" : "11110",
    "0001" : "01001",
    "0010" : "10100",
    "0011" : "10101",
    "0100" : "01010",
    "0101" : "01011",
    "0110" : "01110",
    "0111" : "01111",
    "1000" : "10010",
    "1001" : "10011",
    "1010" : "10110",
    "1011" : "10111",
    "1100" : "11010",
    "1101" : "11011",
    "1110" : "11100",
    "1111" : "11101",
    }


def binToString(bin):
    output = ''
    for x in range (0, len(bin), 8):
        i = int(bin[x:x+8], 2)
        output += chr(i)
    return output

def encodeFromNRZ(ramka):
    output = ''
    current = '1'
    for x in ramka:
        if x == current:
            output += '0'
        else:
            output += '1'
            if current == '1':
                current = '0'
            else:
                current = '1'
    return output

def encodeFrom4B5B(ramka):
    output = ''
    for x in range (0, len(ramka), 5):
        output+=bbEncode[ramka[x:x+5]]
    return output

def getSourceFromEncoded(ramka):
    binSource = ramka[8:16]
    source = int(binSource, 2)
    return source

def getTargetFromEncoded(ramka):
    binTarget = ramka[0:8]
    target = int(binTarget, 2)
    return target

def getLengthFromEncoded(ramka):
    binLength = ramka[16:24]
    length = int(binLength, 2)
    return length

def getDataFromEncoded(ramka, length):
    binData = ramka[24:24+length*8]
    data = binToString(binData)
    return data

def calculateCrc(ramka):
    i = int(ramka, 2)
    b = i.to_bytes((len(ramka) + 7) // 8, 'big')
    c = zlib.crc32(b)
    return c

def getCrcFromEncoded(ramka):
    s = ramka[-32:]
    return int(s, 2)

def decodeToNRZ(ramka):
    output = ''
    current = '1'
    for x in ramka:
        if x == '0':
            output += current
        else:
            if current == '1':
                current = '0'
            else:
                current = '1'
            output += current
    return output

def decodeTo4B5B(ramka):
    output = ''
    for x in range (0, len(ramka), 4):
        output+=bbDecode[ramka[x:x+4]]
    return output

def encode(inp):
    try:
        header = inp[0:8]
        if (header != good_header):
            return

        ramka = inp[8:]

        encodedRamka = encodeFromNRZ(ramka)

        encodedRamka = encodeFrom4B5B(encodedRamka)

        source = getSourceFromEncoded(encodedRamka)
        target = getTargetFromEncoded(encodedRamka)
        length = getLengthFromEncoded(encodedRamka)
        data = getDataFromEncoded(encodedRamka, length)
        bitesToCheck = encodedRamka[0:24+length*8]

        givenCrc = getCrcFromEncoded(encodedRamka)
        calcCrc = calculateCrc(bitesToCheck)
        if (givenCrc != calcCrc):
            return None

        return (source, target, data)
    except:
        return None

def decode(source, target, data):
    ba = bitarray.bitarray()
    ba.frombytes(data.encode('utf-8'))
    encodedData = ''.join(map(str, map(int, ba.tolist())))
    encodedSource = "{0:08b}".format(source)
    encodedTarget = "{0:08b}".format(target)

    length = len(encodedData)//8
    encodedLength = "{0:08b}".format(length)

    ramka = encodedTarget+encodedSource+encodedLength+encodedData
    ramka += "{0:032b}".format(calculateCrc(ramka))

    encodedRamka = decodeTo4B5B(ramka)
    encodedRamka = decodeToNRZ(encodedRamka)

    encodedRamka = good_header + encodedRamka

    return encodedRamka



# for line in sys.stdin:
#     s = line.split(" ")
#     if s[0] == 'E':
#         print (decode(int(s[1]), int(s[2]), ' '.join(s[3:])[:-1]))
#     if s[0] == 'D':
#         encoded = encode(s[1][:-1])
#         if encoded != None:
#             print(encoded[0], encoded[1], encoded[2])