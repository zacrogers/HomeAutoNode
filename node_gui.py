from tkinter import *
from tkinter import ttk
from tkinter import scrolledtext
from home_node import home_node as node

node = node('192.168.20.100', 'bedroom')

root = Tk()

main_frame = Frame(root)

label = Label(main_frame, text = "Light Controller").pack(fill=X)
btn1  = Button(main_frame, command = lambda: node.set_relay_old("1"), text = "1").pack(fill=X)
btn2  = Button(main_frame, command = lambda: node.set_relay_old("2"), text = "2").pack(fill=X)
btn3  = Button(main_frame, command = lambda: node.set_relay_old("3"), text = "3").pack(fill=X)
btn4  = Button(main_frame, command = lambda: node.set_relay_old("4"), text = "4").pack(fill=X)

main_frame.pack(fill = X)

root.mainloop()