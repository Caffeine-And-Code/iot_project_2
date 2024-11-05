clear 
@echo off

REM Definisci il percorso dell'ambiente virtuale
set "AMBIENTE_VIRTUALE=venv"

REM Controlla se la cartella dell'ambiente virtuale esiste e attivalo
if exist %AMBIENTE_VIRTUALE% (
    call %AMBIENTE_VIRTUALE%\Scripts\activate.bat
    REM installa i pacchetti presenti nel file requirements.txt
    pip install -r requirements.txt

    echo Ambiente virtuale attivato.
    python3 main.py
) else (
    echo Errore: L'ambiente virtuale non esiste.
)