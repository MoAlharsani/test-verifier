@echo off
set "printer=HP DeskJet 3700 series"
set "sumatraPath=C:\Program Files\SumatraPDF\SumatraPDF.exe"

:run_loop

REM setting the printer connection
echo Waiting for the ID...
wmic printer where "Name='%printer%'" get Name /value | findstr /i "Name" > nul
if errorlevel 1 (
    echo Printer '%printer%' is not connected or not found.
    echo Please make sure the printer is connected and try again.
    pause
    exit /b 1
)

REM invoking the python script to get the directory 
python "C:pathto\get_directory.py" 

REM store the directory at the specifed text file at directory_path
set /p directory_path=<"C:\pathto\output.txt"

if not exist "%directory_path%" (
    echo Directory '%directory_path%' does not exist.
    echo Please make sure the directory path is correct.
    pause
    exit /b 1
)

REM sending the path of the pdf file to the printer
echo Printing "%directory_path%" to "%printer%"
"%sumatraPath%" -print-to-default "%directory_path%"

goto run_loop
