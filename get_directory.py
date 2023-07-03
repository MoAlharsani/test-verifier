import serial
import time
import openpyxl

def get_directory_path(excel_file, id):
    workbook = openpyxl.load_workbook(excel_file)
    worksheet = workbook.active

    for row in worksheet.iter_rows(values_only=True):
        if row[0] == id:
            return row[3]

    return None

# Main script

# this excel file will have the path for each pdf to be printed
excel_file = "C:\\pathto\\directory_mapping.xlsx" 

# specify the serial which the python script will communicate with
ser = serial.Serial('COM3', 9600)

id = 0
while id == 0:
    # Wait for new data
    while ser.in_waiting == 0:
        time.sleep(0.01)

    id = int(ser.readline().decode().strip())
    print("Received ID:", id)

# the path that will be printed will be stored at directory_path
directory_path = get_directory_path(excel_file, id)

if directory_path:
    # write the path to a text file so the the batch script can read it.
    with open("C:\\pathto\\output.txt", "w") as file:
        file.write(directory_path)
else:
    print("ID not found in the mapping file.")
