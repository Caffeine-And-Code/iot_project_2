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

function updateValue(value) {
    let fluidLevel = value.fluidLevel;
    document.getElementById('liquidLevel').innerText = fluidLevel + "%";
    
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

askLoop()