# test-verifier

## Description
This project consists of a batch script and a Python script that work together to print files based on an ID obtained from an Arduino or serial device. The batch script handles the printer connection and invokes the Python script to retrieve the corresponding file directory path. The Python script reads an Excel file for mapping IDs to directory paths and writes the path to an output file.

## Usage
1. Ensure that the printer named "HP DeskJet 3700 series" (or what ever your printer name is) is connected and accessible.
2. Install SumatraPDF and make sure the executable is located at "C:\Program Files\SumatraPDF\SumatraPDF.exe".
3. Modify the paths in the batch script and Python script according to your system configuration.
4. Place the Excel file containing the ID-to-directory mappings at "C:\pathto\directory_mapping.xlsx".
5. Connect the Arduino or serial device to receive the ID input.
6. Run the batch script "print.bat" to start the printing process (In our case, each fingerprint is corresponding to an ID number).
7. The script will wait for an ID to be received from the Arduino or serial device.
8. The Python script will be invoked to retrieve the corresponding directory path based on the ID.
9. If the directory path exists, the file will be printed using the SumatraPDF print-to-default command.
10. If the directory path does not exist or an error occurs, appropriate messages will be displayed.
11. After printing, the script will wait for the next ID and repeat the process until manually stopped.

## Requirements
- Windows operating system
- Python 3.x installed
- Required Python packages: openpyxl, pyserial (install using pip)
- Arduino or serial device for ID input. Could use an biometric sensor and link it with an ID. However, only the id number can be send to the serial.
- Printer connected and accessible
- SumatraPDF installed and executable located at "C:\Program Files\SumatraPDF\SumatraPDF.exe"

## Notes
- Ensure proper file paths are set in the batch script and Python script.
- Verify the correct printer name and SumatraPDF executable path in the batch script.
- The Excel file should have the ID-to-directory mappings in the first worksheet.
- The ID is read continuously from the Arduino or serial device until a valid ID is received.
- If the mapping for the ID is not found or the directory path is invalid, an appropriate error message is displayed.
- Feel free to customize the scripts according to your specific needs.

