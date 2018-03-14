
@echo off
IF NOT EXIST ".\nuget.exe" (
        rem file exists
)
else (
    @Echo Azure IoT C SDK Lite needs to download nuget.exe from https://www.nuget.org/nuget.exe 
    @Echo https://www.nuget.org 
    choice /C yn /M "Do you want to download and run nuget.exe?" 
    @Echo downloading nuget.exe..
    rem if nuget.exe is not found, then ask user

    Powershell.exe wget -outf nuget.exe https://nuget.org/nuget.exe
        if not exist .\nuget.exe (
            echo nuget does not exist
            exit /b 1
        )
    )
)
nuget pack Paloukari.Azure.IoT.Lite.C.nuspec -OutputDirectory .\packaging

:eof