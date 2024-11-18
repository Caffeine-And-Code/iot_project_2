let severityFluid = false;
let severityTemp = false;
let storicoTemp = [];
let storicoLevel = [];

let notifications = [];

function addNotification(type, message) {
  let notification = document.createElement("div");
  notification.classList.add("notification");
  notification.classList.add(type);
  notification.style.top = `${notifications.length * 55 + 92}px`;
  notification.innerText = message;
  document.getElementById("notifications").appendChild(notification);
  notifications.push(notification);
  setTimeout(() => {
    notification.remove();
    notifications = notifications.filter((n) => n !== notification);
  }, 5000);
}

function setFluidSeverity(val) {
  severityFluid = val;
  document.getElementById("BtnLevel").style.display = severityFluid
    ? "block"
    : "none";
}

const units = {
  Celcius: "°C",
  Fahrenheit: "°F",
};

const config = {
  minTemp: -20,
  maxTemp: 50,
  unit: "Celcius",
};

// Funzione per interpolare due colori HEX
function interpolateColor(color1, color2, factor) {
  if (factor === undefined) factor = 0.5;

  // Converti i colori HEX in RGB
  const hexToRgb = (hex) => {
    const bigint = parseInt(hex.slice(1), 16);
    return {
      r: (bigint >> 16) & 255,
      g: (bigint >> 8) & 255,
      b: bigint & 255,
    };
  };

  const rgbToHex = (r, g, b) => {
    return (
      "#" +
      ((1 << 24) + (r << 16) + (g << 8) + b).toString(16).slice(1).toUpperCase()
    );
  };

  const c1 = hexToRgb(color1);
  const c2 = hexToRgb(color2);

  // Interpolazione lineare tra i colori
  const r = Math.round(c1.r + factor * (c2.r - c1.r));
  const g = Math.round(c1.g + factor * (c2.g - c1.g));
  const b = Math.round(c1.b + factor * (c2.b - c1.b));

  return rgbToHex(r, g, b);
}

// Funzione per calcolare il colore dal valore
function changeColorBasedOnTemperature(value) {
  // Normalizza il valore tra 0 e 1
  const normalized =
    (value - config.minTemp) / (config.maxTemp - config.minTemp);
  return interpolateColor("#00bbff", "#f83715", normalized);
}
//on load actions
document.addEventListener("DOMContentLoaded", function () {
  adjustPositions();
  document.getElementById("updateBtn").addEventListener("click", () => {
    updateTempCharts();
    updateLevelChart();
  });
});

// Chart Logic
let Temp = new Chart("TempChart", {
  type: "line",
  data: {},
});

let Level = new Chart("LevelChart", {
  type: "line",
  data: {},
});

function updateTempCharts() {
  Temp.data.labels = storicoTemp.map((_, i) => i);
  Temp.data.datasets = [
    {
      label: "Temperatura",
      data: storicoTemp,
      borderColor: "#f9866e",
      fill: false,
    },
  ];
  Temp.update();
}
function updateLevelChart() {
  Level.data.labels = storicoLevel.map((_, i) => i);
  Level.data.datasets = [
    {
      label: "Livello del Liquido",
      data: storicoLevel,
      borderColor: "#e1f96e",
      fill: false,
    },
  ];
  Level.update();
}

var myWave;
let bridge;

function initializeWebChannel() {
  new QWebChannel(qt.webChannelTransport, function (channel) {
    bridge = channel.objects.bridge;

    // Listen for messages from Python
    bridge.sendToJs.connect(function (message) {
      updateValue({
        fluidLevel: getFluidLevelFromJson(message),
        temperature: getTemperatureFromJson(message),
      });
    });
  });
}

// Get & Set data from python backend

function getDataFromJson(pyData) {
  return pyData;
}

function getFluidLevelFromJson(pyData) {
  return getDataFromJson(pyData).fluidLevel;
}

function getTemperatureFromJson(pyData) {
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
    temperature: getTemperatureFromJson(message),
  });
}

document.addEventListener("DOMContentLoaded", initializeWebChannel);

function updateValue(value) {
  let oldValue = storicoLevel[storicoLevel.length - 1];
  if (oldValue != value.fluidLevel) {
    storicoLevel.push(value.fluidLevel);
    let fluidLevel = value.fluidLevel;
    document.getElementById("liquidLevel").innerText = fluidLevel + "%";
    adjustPositions();

    if (fluidLevel == 100) {
      setFluidSeverity(true);
      addNotification("warning", "Fluid level is at 100%");
    } else {
      setFluidSeverity(false);
    }

    myWave && myWave.kill();
    myWave = wavify(document.querySelector("#myID"), {
      height: convertPercentageToValueForTheWave(fluidLevel),
      bones: 10,
      amplitude: 20,
      color: changeColorBasedOnTemperature(value.temperature),
      speed: 0.25,
    });
  }
  oldValue = storicoTemp[storicoTemp.length - 1];
  if (oldValue != value.temperature) {
    storicoTemp.push(value.temperature);

    let temperature = value.temperature;

    setTemperature(temperature);

    if (temperature >= 40) {
      severityTemp = true;
      addNotification("warning", "Temperature is above 40°C");
    } else {
      severityTemp = false;
    }
  }
}

function convertPercentageToValueForTheWave(percentage) {
  // Imposta l'intervallo dell'altezza, dove 0% = 200 e 100% = -200

  let minHeight = 650; // Altezza minima (quando la percentuale è al 0%)

  let reversedPercentage = 100 - percentage;
  let maxHeight = -190 + percentage * 3; // Altezza massima (quando la percentuale è allo 100%)

  if (percentage == 0) {
    maxHeight += 100;
  } else if (percentage <= 5) {
    maxHeight += 80;
  } else if (percentage <= 10) {
    maxHeight += 20;
  } else if (percentage <= 25) {
    maxHeight -= 20;
  } else if (percentage <= 40) {
    maxHeight -= 30;
  } else if (percentage <= 65) {
    maxHeight -= 50;
  } else if (percentage <= 80) {
    maxHeight -= 70;
  } else if (percentage <= 90) {
    maxHeight -= 90;
  } else if (percentage <= 95) {
    maxHeight -= 95;
  } else if (percentage <= 100) {
    maxHeight -= 100;
  }

  console.log(maxHeight);
  let calc = Math.abs((reversedPercentage * minHeight) / 100 + maxHeight);

  return calc;
}

function askValue() {
  sendMessageToPython("value needed");
}

function askLoop() {
  setTimeout(() => {
    askValue();
    askLoop();
  }, 2000);
}

function setTemperature(value) {
  const temperature = document.getElementById("temperature");
  temperature.style.height =
    ((value - config.minTemp) / (config.maxTemp - config.minTemp)) * 100 + "%";
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
}
askLoop();
