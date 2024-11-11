function getInfo() {
    const url = 'https://restcountries.com/v3.1/name/';
    const country = document.getElementById('country').value;

    fetch(url + country)
    .then(response => response.json())
    .then(data => {
        const countries = data.map(country => {
            return {
                countryName: country.name.common,
                countryFullName: country.name.official,
                continent: country.region,
                population: country.population,
                capital: country.capital[0],
                flag: country.flags.png,
                coatOfArms: country.coatOfArms.png
            }
        });
        console.log(countries);
        document.getElementById('countryName').innerText = countries[0].countryName;
        document.getElementById('countryFullName').innerText = countries[0].countryFullName;
        document.getElementById('continent').innerText = countries[0].continent;
        document.getElementById('capital').innerText = countries[0].capital;
        document.getElementById('population').innerText = countries[0].population;
        document.getElementById('flag').src = countries[0].flag;
        document.getElementById('coatOfArms').src = countries[0].coatOfArms;
    })
    .catch(error => console.error(error));
}