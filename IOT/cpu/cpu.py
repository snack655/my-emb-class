import os
import time
import tkinter

window = tkinter.Tk()
window.title("CPU TEMP")
window.geometry("480x100")
window.resizable(False, False)

temp = os.popen(" vcgencmd measure_temp ").readline()
print(temp)
label = tkinter.Label(window, text=temp[5:], font=('Arial', 30, "bold"))
label.pack()

window.mainloop()
