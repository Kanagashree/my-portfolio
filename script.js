const apiKey = "https://api.openweathermap.org/data/2.5/weather?q=";
const yourAPIKey = "e304e3706d328dbaa4b767a70151c6e5"; 

function getWeather() {
  const city = document.getElementById("cityInput").value;
  const url = `${apiKey}${city}&appid=${yourAPIKey}&units=metric`;

  fetch(url)
    .then((response) => response.json())
    .then((data) => {
      if (data.cod === 200) {
        const weather = `
          <p><strong>${data.name}, ${data.sys.country}</strong></p>
          <p>🌡️ Temp: ${data.main.temp}°C</p>
          <p>🌥️ Condition: ${data.weather[0].main}</p>
        `;
        document.getElementById("weatherResult").innerHTML = weather;
      } else {
        document.getElementById("weatherResult").innerHTML = "City not found.";
      }
    })
    .catch((error) => {
      document.getElementById("weatherResult").innerHTML = "Error fetching weather.";
    });
}
