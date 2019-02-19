import socket
import sys
import threading
import signal

debug = False

class ChatServer:
    def __init__(self, host, port):
        self.clients = []
        self.open_socket(host, port)

    def open_socket(self, host, port):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((host, port))
        self.server.listen(5)

    def run(self):
        while True:
            clientSocket, clientAddr = self.server.accept()
            if debug:
                print(
                    "SERVER LOG: Zgłoszenie klienta, adres: {0}".format(clientAddr))
            newClient = Client(clientSocket, clientAddr, self)
            self.clients.append(newClient)
            if debug:
                self.print_number_of_clients()

            newClient.start()

    def print_number_of_clients(self):
        print("Liczba klientów: {0}".format(len(self.clients)))

    def clean_client(self, client):
        if client in self.clients:
            try:
                self.clients.remove(client)
                client.socket.close()
                if debug:
                    self.print_number_of_clients()
            except:
                if debug:
                    print("Exception: usuwanie klienta")

    def clean_clients(self, err):
        for client in err:
            self.clean_client(client)

    def checkAlive(self):
        err = []
        for client in self.clients:
            try:
                client.sendToClient("KEEPALIVE~ NULL")
            except:
                err.append(client)

        self.clean_clients(err)

    def propagate_names(self):
        message = "USER_LIST~ "

        self.checkAlive()

        for client in self.clients:
            message += client.name + "|"

        for client in self.clients:
            client.sendToClient(message)


class Client(threading.Thread):
    def __init__(self, clientSocket, clientAddr, server):
        threading.Thread.__init__(self)
        self.socket = clientSocket
        self.addr = clientAddr
        self.server = server
        self.name = "NEW CLIENT"
        self.__initializeOptions__()

    def __initializeOptions__(self):
        self.options = {"SENDMESSAGE": self.clientSentMessage,
                        "SENDNAME": self.clientSentName
                        }

    def sendToClient(self, message):
        messageBytes = bytes(message + "%", 'UTF-8')
        self.socket.send(messageBytes)

    def sendMessage(self, fromWho, toWho, message):
        self.sendToClient(f"MESSAGE~ {fromWho}|{toWho}|{message}")

    def clientSentMessage(self, content):
        args = content.split('|')
        toWho, message = args[0], args[1]
        if toWho == '__ALL__':
            for client in self.server.clients:
                client.sendMessage(self.name, toWho, message)
        else:
            try:
                c = next(
                    client for client in self.server.clients if client.name == toWho)
                c.sendMessage(self.name, toWho, message)
                self.sendMessage(self.name, toWho, message)
            except Exception as e:
                if debug:
                    print(f"Client doesnt exists!: {str(e)}")

    def clientSentName(self, name):
        self.name = name
        self.server.propagate_names()

    def run(self):
        running = True
        while running:
            data = b''
            try:
                data = self.socket.recv(1024)
                if data:
                    s = data.decode('UTF-8')
                    splitted = s.split('~ ')
                    command, content = (splitted[0], splitted[1])
                    if debug:
                        print(f"Got command: {s} from user: {self.name}")

                    self.options[command](content)

                else:
                    running = False
                    self.server.propagate_names()
                    if debug:
                        print("IF clause: {0}".format(data))
                    break

            except Exception as e:
                self.server.propagate_names()
                running = False
                if debug:
                    print(f"EXCEPT {str(e)}")
                break


def signal_handler(sig, frame):
    server.checkAlive()
    for client in server.clients:
        client.socket.close()
    server.server.close()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

server = ChatServer('', 12345)
server.run()
