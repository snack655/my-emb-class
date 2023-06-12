import requests
import re
import tkinter

url = "http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2771025600"

response = requests.get(url)

temp = re.findall(r'<temp>(.+)</temp>', response.text)
humi = re.findall(r'<reh>(.+)</reh>', response.text)

window = tkinter.Tk()
window.title("TEMP HUMI DISPLAY")
window.geometry("480x100")
window.resizable(False, False)

label = tkinter.Label(window, text=temp[0]+"C   " + humi[0]+"%", font=('Arial', 30, 'bold'))
label.pack()

window.mainloop()

print(temp)
print(humi)
