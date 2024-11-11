var myWave

let bridge;

function initializeWebChannel() {
    new QWebChannel(qt.webChannelTransport, function(channel) {
        bridge = channel.objects.bridge;

        // Listen for messages from Python
        bridge.sendToJs.connect(function(message) {
            updateValue(Number(message))
        });
    });
}

function sendMessageToPython(message) {
    if (bridge) {
        bridge.receiveFromJs(message);
    }
}

function receiveMessageFromPython(message) {
    updateValue(message)
}

document.addEventListener("DOMContentLoaded", initializeWebChannel);

function updateValue(value) {
    //TODO: delete this row when implementing the serial
    document.getElementById('data').innerText = value;
            myWave && myWave.kill();
            myWave = wavify(document.querySelector("#myID"), {
                height: convertPercentageToValueForTheWave(value),
                bones: 10,
                amplitude: 20,
                color: "rgba(150, 97, 255, .8)",
                speed: 0.25,
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

askLoop()