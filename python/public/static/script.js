//on load actions 
document.addEventListener("DOMContentLoaded", function() {
    adjustPositions();
    // inizialize the local storage
    localStorage.setItem("storicoTemp", JSON.stringify([]));
    localStorage.setItem("storicoLevel", JSON.stringify([]));
});

// Chart Logic
let Temp = new Chart("TempChart",{
    type: "line",
    data:{

    }
})

let Level = new Chart("LevelChart",{
    type: "line",
    data:{

    }
})

function updateCharts(){
    let TempStorico = JSON.parse(localStorage.getItem("storicoTemp")) || [];
    let LevelStorico = JSON.parse(localStorage.getItem("storicoLevel")) || [];
    Temp.data.labels = TempStorico.map((_, i) => i);
    Temp.data.datasets = [{
        label: "Temperature",
        data: TempStorico,
        borderColor: "red",
        fill: false
    }];
    Temp.update();
    Level.data.labels = LevelStorico.map((_, i) => i);
    Level.data.datasets = [{
        label: "Fluid Level",
        data: LevelStorico,
        borderColor: "blue",
        fill: false
    }];
    Level.update();
}

var myWave
let bridge;

function initializeWebChannel() {
    new QWebChannel(qt.webChannelTransport, function(channel) {
        bridge = channel.objects.bridge;

        // Listen for messages from Python
        bridge.sendToJs.connect(function(message) {
            updateValue({
                fluidLevel: getFluidLevelFromJson(message),
                temperature: getTemperatureFromJson(message)
            });
        });
    });
}

// Get & Set data from python backend

function getDataFromJson(pyData){
    return pyData;
}

function getFluidLevelFromJson(pyData){
    return getDataFromJson(pyData).fluidLevel;
}

function getTemperatureFromJson(pyData){
    return getDataFromJson(pyData).temperature;
}

function sendMessageToPython(message) {
    if (bridge) {
        bridge.receiveFromJs(message);
    }
}

function receiveMessageFromPython(message) {
    updateValue({
        fluidLevel: getFluidLevelFromJson(message),
        temperature: getTemperatureFromJson(message)
    });
}

document.addEventListener("DOMContentLoaded", initializeWebChannel);

function saveDataIntoStorico(value){
    let storico = JSON.parse(localStorage.getItem("storicoTemp")) || [];
    storico.push(value.temperature);
    localStorage.setItem("storicoTemp", JSON.stringify(storico));
    storico = JSON.parse(localStorage.getItem("storicoLevel")) || [];
    storico.push(value.fluidLevel);
    localStorage.setItem("storicoLevel", JSON.stringify(storico));
}

function updateValue(value) {
    saveDataIntoStorico(value);
    let fluidLevel = value.fluidLevel;
    document.getElementById('liquidLevel').innerText = fluidLevel + "%";
    adjustPositions();
    
    myWave && myWave.kill();
    myWave = wavify(document.querySelector("#myID"), {
        height: convertPercentageToValueForTheWave(fluidLevel),
        bones: 10,
        amplitude: 20,
        color: "rgba(150, 97, 255, .8)",
        speed: 0.25,
      });
    let temperature = value.temperature;

    setTemperature(temperature);


    updateCharts();
}

function convertPercentageToValueForTheWave(percentage) {
    // Imposta l'intervallo dell'altezza, dove 0% = 200 e 100% = -200
    
    let minHeight = 650;  // Altezza minima (quando la percentuale è al 0%)
    let maxHeight = 0;   // Altezza massima (quando la percentuale è allo 100%)

    let reversedPercentage = 100 - percentage;
    let calc = Math.abs((reversedPercentage * (minHeight) / 100)+maxHeight);

    console.log(calc)
    return calc;
}

function askValue()
{
    sendMessageToPython("value needed")
}

function askLoop()
{
    setTimeout(() => {
        askValue()
        askLoop()
    }, 2000);   
}

const units = {
	Celcius: "°C",
	Fahrenheit: "°F"
};

const config = {
	minTemp: -20,
	maxTemp: 50,
	unit: "Celcius"
};

const temperature = document.getElementById("temperature");

function setTemperature(value) {
	temperature.style.height = (value - config.minTemp) / (config.maxTemp - config.minTemp) * 100 + "%";
	temperature.dataset.value = value + units[config.unit];
}

function adjustPositions() {
    let text = document.getElementById("liquidLevel");
    let wave = document.getElementById("svgWaves");
    let waveContainer = document.getElementById("svgLiquid");

    // position the test in the middle of the wave

    // get the height of the wave
    let waveHeight = wave.clientHeight;
    let textHeight = text.clientHeight;
    let waveContainerWidth = waveContainer.clientWidth;

    // calculate the top position of the text
    let topPosition = Math.floor((waveHeight - textHeight) / 2);

    // set the top position of the text
    text.style.top = `${topPosition}px`;

    // calculate the left position of the text
    let waveWidth = wave.clientWidth;
    let textWidth = text.clientWidth;

    let leftPosition = waveWidth / 2;
    let marginLeft = (waveContainerWidth - waveWidth) / 2;

    leftPosition += marginLeft - textWidth / 2;

    text.style.left = `${leftPosition}px`;

    let coverage = document.getElementById("coverage");

    // set the top position of the coverage
    coverage.style.height = "40px";
    coverage.style.width = waveWidth + 11 + "px";

    // set the left position of the coverage

    let coverageLeftPosition =
        Math.floor((waveContainerWidth - waveWidth) / 2) - 5;
    coverage.style.left = `${coverageLeftPosition}px`;

    coverage.style.top = `100px`;
}
askLoop()



