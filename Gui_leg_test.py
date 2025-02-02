import tkinter as tk
from tkinter import ttk
import serial

# Initialize serial communication
ser = serial.Serial('COM13', 9600)  # Change 'COM3' to the correct port

def on_slider_change(event):
    value1 = int(slider1.get())
    value2 = int(slider2.get())
    value3 = int(slider3.get())
    label.config(text=f"Values: {value1}, {value2}, {value3}")
    ser.write(f"{value1},{value2},{value3}\n".encode())

# Create main window
root = tk.Tk()
root.title("Slider GUI")
root.geometry("300x200")

# Create sliders
slider1 = ttk.Scale(root, from_=0, to=210, orient="horizontal", command=on_slider_change)
slider1.pack(pady=10)

slider2 = ttk.Scale(root, from_=0, to=270, orient="horizontal", command=on_slider_change)
slider2.set(135)  # Set initial value to 135
slider2.pack(pady=10)

slider3 = ttk.Scale(root, from_=42, to=226, orient="horizontal", command=on_slider_change)
slider3.pack(pady=10)

# Label to display values
label = tk.Label(root, text="Values: 0, 0, 0")
label.pack(pady=10)

# Run the Tkinter event loop
root.mainloop()

# Close serial communication on exit
ser.close()
