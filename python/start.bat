@echo off
REM Check if .env.example exists and copy it as .env if .env does not exist
IF EXIST ".env.example" (
    IF NOT EXIST ".env" (
        echo .env file not found. Creating one from .env.example...
        copy ".env.example" ".env"
    ) ELSE (
        echo .env file already exists. Skipping creation.
    )
) ELSE (
    echo .env.example not found. Please ensure it is present in the root directory.
    pause
    exit /b
)

REM Check if virtual environment folder exists
IF NOT EXIST "venv" (
    echo Virtual environment not found. Creating one...
    python -m venv venv
)

REM Activate the virtual environment
call venv\Scripts\activate.bat

REM Install required Python packages from requirements.txt
IF EXIST requirements.txt (
    echo Installing dependencies from requirements.txt...
    pip install -r requirements.txt
) ELSE (
    echo No requirements.txt found, skipping dependency installation.
)

REM Run the main.py script
echo Running main.py...
python main.py

REM Deactivate the virtual environment after running
deactivate

pause
