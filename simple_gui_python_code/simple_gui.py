# import needed modules
import time
from tkinter import *
import math
import serial


# create a variable to hold the serial connection to arduino
try:
    arduino = serial.Serial(port='/dev/cu.usbmodem1101', baudrate=9600, timeout=.1)
except:
    print("Check serial connection")


# create a variable to hold the class TK()
# maybe later change set up to a class system
tk = Tk()
N = 96  # number of wells
numbers = list(range(1, N + 1))  # create a list from 1 - 96 to correlate to wells
str_num = [str(x) for x in numbers]  # create list of the numbers in string format
dic_check_var = {}  # create empty dictionary to hold check variables
dic_check_widget = {}  # create empty dictionary to hold the widget
# create empty list
pin_list = []
# for loop that cycles through the list of numbers in string format
# the string will be added to both dic as keys
for string in str_num:
    key = string
    dic_check_var[key] = IntVar()  # this is the dic to hold the check variables of the check button
    dic_check_widget[key] = None  # this is the dic that will hold the


def read_from_arduino():
    while arduino.in_waiting:
        line = arduino.readline().decode('utf-8').rstrip()
        print("Received from Arduino:", line)


# define function to gather check variables on button click and print values
def on_button_click():
    serial_str = ""
    for key1 in dic_check_var.keys():

        if dic_check_var[key1].get() == 1:

            if serial_str == "":
                serial_str = "<" + "1" + ","
            else:
                serial_str = serial_str + "1" + ","


        else:
            if serial_str == "":
                serial_str = "<" + "0" + ","
            else:
                serial_str = serial_str + "0" + ","

    serial_str = serial_str + ">"
    send_in_chunks(serial_str)
    read_from_arduino()


def send_in_chunks(serial_str, chunk_size=20):
    for i in range(0, len(serial_str), chunk_size):
        chunk = serial_str[i:i + chunk_size]
        print("Sending chunk:", chunk)
        arduino.write(chunk.encode())
        time.sleep(0.1)  # Give some time for Arduino to process the chunk

        # Wait for confirmation from Arduino
        while True:
            if arduino.in_waiting > 0:
                response = arduino.readline().decode('utf-8').rstrip()
                print("Received from Arduino:", response)
                if response == "ACK":
                    break  # Move to the next chunk


def readarduino(ser):
    did = True
    while ser.inWaiting():  # Check number of characters left in buffer
        if did and ser.inWaiting() < 490:  # Select last 500 characters in buffer
            for i in range(6):
                print(ser.readline())  # Print 6 lines in buffer
            did = False
        ser.readline()  # Clear buffer line by line until ser.inWaiting goes to 0


#
# def widget_creator(int):
#     label = tk.Label(root, text="Enter your name:")
#     label.pack()

# Create the main window
root = tk
root.title("Simple GUI")

# for loop that creates check buttons and stores them in dictionary
for key in dic_check_widget:
    row = math.ceil(int(key) / 12)  # limits the output to 12
    column = ((int(key) - 1) % 12) + 1  # limits the output to 12
    dic_check_widget[key] = Checkbutton(root, variable=dic_check_var[key])
    dic_check_widget[key].grid(row=row - 1, column=column)  # grids each button in a 8x12 grid

# create test box for frequency in milliseconds
entry1 = Entry(root)
entry1.grid(column=13, row=3)
# label for entry
label1 = Label(root, text="Enter Freq in ms")
label1.grid(column=13, row=4)

# Create a button that on click reads the check variables and if on stores the key(grid index) in a list
button = Button(root, text="Submit", command=on_button_click)
button.grid(column=13, row=6)

# Run the application
root.mainloop()

# junk
# # import needed modules
# import time
# from tkinter import *
# import math
# import serial
#
# x = 0
# # create a variable to hold the serial connection to arduino
# arduino = serial.Serial(port='/dev/cu.usbmodem1101', baudrate=9600, timeout=.1)
# # create a variable to hold the class TK()
# # maybe later change set up to a class system
# tk = Tk()
# # create a dictionary to hold values of
# N = 96
# numbers = list(range(1, N + 1))
# # create list of the numbers in string format
# str_num = [str(x) for x in numbers]
# # create empty dictionaries
# dic_check_var = {}
# dic_check_widget = {}
# # create empty list
# pin_list = []
# # for loop that cycles through the list of numbers in string format
# # the string will be added to both dic as keys
# for string in str_num:
#     key = string
#     dic_check_var[key] = IntVar()  # this is the dic to hold the check variables of the check button
#     dic_check_widget[key] = None  # this is the dic that will hold the
#
#
# # define function to gather check variables on button click and print values
# def on_button_click():
#     byte_array = bytearray(12)
#     if not arduino.isOpen():
#         arduino.open()
#     for key1 in dic_check_var.keys():
#         key_int = int(key1)
#         i = (key_int - 1) // 12 + 1  # Row
#         j = key_int % 12  # Column
#
#         if dic_check_var[key1].get() == 1:
#             print(j)
#             print(9 - i)
#             byte_array[j-1] |= 1 << (8-i)
#
#
#     print(byte_array)
#
#     # arduino.write(str_1.encode())
#     arduino.write(byte_array)
#     time.sleep(1)
#     arduino.close()
#
#
# #
# # def widget_creator(int):
# #     label = tk.Label(root, text="Enter your name:")
# #     label.pack()
#
# # Create the main window
# root = tk
# root.title("Simple GUI")
#
# # for loop that creates check buttons and stores them in dictionary
# for key in dic_check_widget:
#     row = math.ceil(int(key) / 12)  # limits the output to 12
#     column = ((int(key) - 1) % 12) + 1  # limits the output to 12
#     dic_check_widget[key] = Checkbutton(root, variable=dic_check_var[key])
#     dic_check_widget[key].grid(row=row - 1, column=column)  # grids each button in a 8x12 grid
#
# # Create a button that on click reads the check variables and if on stores the key(grid index) in a list
# button = Button(root, text="Submit", command=on_button_click)
# button.grid(column=13, row=0)
#
# # Run the application
# root.mainloop()
#
#
# #
# #
# # # import needed modules
# # import time
# # from tkinter import *
# # import math
# # import serial
# #
# # x = 0
# # # create a variable to hold the serial connection to arduino
# # arduino = serial.Serial(port='/dev/cu.usbmodem1101', baudrate=9600, timeout=.1)
# # # create a variable to hold the class TK()
# # # maybe later change set up to a class system
# # tk = Tk()
# # # create a dictionary to hold values of
# # N = 96
# # numbers = list(range(1, N + 1))
# # # create list of the numbers in string format
# # str_num = [str(x) for x in numbers]
# # # create empty dictionaries
# # dic_check_var = {}
# # dic_check_widget = {}
# # # create empty list
# # pin_list = []
# # # for loop that cycles through the list of numbers in string format
# # # the string will be added to both dic as keys
# # for string in str_num:
# #     key = string
# #     dic_check_var[key] = IntVar()  # this is the dic to hold the check variables of the check button
# #     dic_check_widget[key] = None  # this is the dic that will hold the
# #
# #
# # # define function to gather check variables on button click and print values
# # def on_button_click():
# #     byte_array = bytearray(12)
# #     if not arduino.isOpen():
# #         arduino.open()
# #     for key1 in dic_check_var.keys():
# #         key_int = int(key1)
# #         i = (key_int - 1) // 12 + 1  # Row
# #         j = key_int % 12  # Column
# #
# #         if dic_check_var[key1].get() == 1:
# #             print(j)
# #             print(9 - i)
# #             byte_array[j-1] |= 1 << (8-i)
# #
# #
# #     print(byte_array)
# #
# #     # arduino.write(str_1.encode())
# #     arduino.write(byte_array)
# #     time.sleep(1)
# #     arduino.close()
# #
# #
# # #
# # # def widget_creator(int):
# # #     label = tk.Label(root, text="Enter your name:")
# # #     label.pack()
# #
# # # Create the main window
# # root = tk
# # root.title("Simple GUI")
# #
# # # for loop that creates check buttons and stores them in dictionary
# # for key in dic_check_widget:
# #     row = math.ceil(int(key) / 12)  # limits the output to 12
# #     column = ((int(key) - 1) % 12) + 1  # limits the output to 12
# #     dic_check_widget[key] = Checkbutton(root, variable=dic_check_var[key])
# #     dic_check_widget[key].grid(row=row - 1, column=column)  # grids each button in a 8x12 grid
# #
# # # Create a button that on click reads the check variables and if on stores the key(grid index) in a list
# # button = Button(root, text="Submit", command=on_button_click)
# # button.grid(column=13, row=0)
# #
# # # Run the application
# # root.mainloop()
