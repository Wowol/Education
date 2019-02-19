import tkinter as tk
import tkinter.messagebox as tkmsg
import sys
import threading
from socket import *
from random import *
from tkinter import END

debug = False

sock = socket(AF_INET, SOCK_STREAM)
sock.connect(('localhost', 12345))
myName = sys.argv[1]


class Msgs():
    def __init__(self, name, master):
        self.master = master
        self.master.rowconfigure(0, weight=1)
        self.master.columnconfigure(0, weight=1)
        self.name = name
        self.createWidgets()

    def createWidgets(self):
        self.master.title("Chat: " + self.name)
        self.master.minsize(450, 350)
        self.textChat = tk.Text(self.master, width=40,
                                height=12, relief=tk.GROOVE)
        self.textChat.grid(row=0, column=0, sticky=tk.N +
                           tk.S + tk.E + tk.W, padx=4, pady=4)
        self.textChat.config(state=tk.DISABLED)

        self.userList = tk.Listbox(self.master)
        self.userList.grid(row=0, column=1, sticky=tk.N +
                           tk.S + tk.E + tk.W, padx=4, pady=4)
        self.userList.config(exportselection=False,
                             selectmode=tk.SINGLE, activestyle='none')
        self.userList.insert(0, "ALL")
        self.userList.selection_set(0)

        self.textMsg = tk.Text(self.master, width=40,
                               height=7, relief=tk.GROOVE)
        self.textMsg.grid(row=1, column=0, sticky=tk.N +
                          tk.S + tk.E + tk.W, padx=4, pady=4)

        self.sendMsg = tk.Button(
            self.master, text="Send message", relief=tk.GROOVE)
        self.sendMsg.grid(row=2, column=0, columnspan=2,
                          sticky=tk.N + tk.S + tk.E + tk.W)
        self.sendMsg.bind("<Button-1>", lambda event: self.sendMessage())

        self.sendMsg = tk.Button(
            self.master, text="Exit", height=4, relief=tk.GROOVE)
        self.sendMsg.grid(row=2, column=1, columnspan=2,
                          sticky=tk.N + tk.S + tk.E + tk.W)
        self.sendMsg.bind("<Button-1>", lambda event: self.exitProgram())

        self.master.rowconfigure(0, weight=8)
        self.master.rowconfigure(1, weight=1)

        self.master.bind_all('<Return>', lambda event: self.sendMessage())

    def sendMessage(self):
        global sock
        msg = self.textMsg.get("1.0", "1.end")
        if not msg or not msg.strip():
            tkmsg.showinfo("Warning", "There is no message to send!")
            self.textMsg.delete("0.0", tk.END)

        else:
            if len(self.userList.curselection()) == 0:
                self.userList.selection_set(0)
            selectedUserIndex = self.userList.curselection()[0]
            userName = self.userList.get(
                selectedUserIndex) if selectedUserIndex != 0 else "__ALL__"
            command = f"SENDMESSAGE~ {userName}|{msg}"
            sock.send(bytes(command, 'UTF-8'))
            self.textMsg.delete("0.0", tk.END)

    def exitProgram(self):
        global sock
        sock.close()
        sys.exit()

    def printMessage(self, fromWho, toWho, message):
        toWho = toWho if toWho != "__ALL__" else "ALL"
        self.textChat.config(state=tk.NORMAL)
        self.textChat.insert(tk.END, f"{fromWho} => {toWho}:\n{message}\n")
        self.textChat.yview_pickplace(tk.END)
        self.textChat.config(state=tk.DISABLED)

    def printUsers(self, users):
        global myName
        self.userList.delete(1, tk.END)
        for user in users:
            if user and user != myName:
                self.userList.insert(END, user)


class Client:
    def __init__(self, name, master):
        self.name = name
        self.master = master
        self.gui = Msgs(self.name, self.master)
        self.__initializeOptions__()

        threading.Thread(target=self.readMessages, args=()).start()

    def __initializeOptions__(self):
        self.options = {"MESSAGE": self.gotMessage,
                        "USER_LIST": self.gotUsers
                        }

    def readMessages(self):
        global sock
        running = True
        while running:
            try:
                data = sock.recv(1024)
                if debug:
                    print("{0}".format(data.decode('UTF-8')))

                s = data.decode('UTF-8')

                for d in s.split('%'):
                    if d:
                        splitted = d.split('~ ')
                        command, content = (splitted[0], splitted[1])

                        if command in self.options:
                            self.options[command](content)

            except Exception as c:
                running = False
                if not sock._closed:
                    if debug:
                        print(str(c))
                    sock.close()

    def gotMessage(self, content):
        args = content.split('|')
        fromWho, toWho, message = args[0], args[1], args[2]
        self.gui.printMessage(fromWho, toWho, message)

    def gotUsers(self, content):
        self.gui.printUsers(content.split('|'))


def on_closing():
    sock.close()
    root.destroy()

sock.send(bytes(f'SENDNAME~ {myName}', 'UTF-8'))
root = tk.Tk()
root.protocol("WM_DELETE_WINDOW", on_closing)
client = Client(myName, root)
root.mainloop()