var myWave

function fetchData() {
    //TODO: delete this row when implementing the serial
    let extractedNumber = Math.floor(Math.random() * 100);
    fetch('/api/data')
        .then(response => response.json())
        .then(data => {
            document.getElementById('data').innerText = data.data || extractedNumber;
            myWave && myWave.kill();
            myWave = wavify(document.querySelector("#myID"), {
                height: convertPercentageToValueForTheWave(data.data || extractedNumber),
                bones: 10,
                amplitude: 20,
                color: "rgba(150, 97, 255, .8)",
                speed: 0.25,
              });
        })
        .catch(error => {
            console.error("Errore nel recupero dei dati:", error);
        });
}

function convertPercentageToValueForTheWave(percentage) {
    // Imposta l'intervallo dell'altezza, dove 0% = 200 e 100% = -200
    
    let minHeight = 650;  // Altezza minima (quando la percentuale è al 0%)
    const maxHeight = 0;   // Altezza massima (quando la percentuale è allo 100%)

    let reversedPercentage = 100 - percentage;
    let calc = Math.abs((reversedPercentage * (minHeight) / 100));

    console.log(calc)
    return calc;
}

// Aggiorna ogni secondo
setInterval(fetchData, 5000);
