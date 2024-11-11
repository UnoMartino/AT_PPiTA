async function getData() {
    const url = "https://znacznikowe-serwer.onrender.com/api/v1/products";
    try {
      const response = await fetch(url);
      if (!response.ok) {
        throw new Error(`Response status: ${response.status}`);
      }
  
      const json = await response.json();
      console.log(json);
    } catch (error) {
      console.error(error.message);
    }
  }



async function request1() {
      const request1 = new Request("https://znacznikowe-serwer.onrender.com/api/v1/auth/register", {
        method: "POST",
        headers: { "content-type": "application/json", "accept": "application/json"},
        body: JSON.stringify({ name: "madaniu", email: "sdfa@madanowicz.pl", password: "secret" })
      });
      
      const response1 = await fetch(request1);
      console.log(response1.status);
      
      console.log( await response1.json());
}

async function request2() {
    fetch(
        "https://znacznikowe-serwer.onrender.com/api/v1/auth/register", {
            "method": "POST",
            "headers": {
              "content-type": "application/json",
              "accept": "application/json"
            },
            "body": JSON.stringify({
                name: "madaniu", 
                email: "marcin@madanowicz.pl", 
                password: "secret"
            })
    })
    .then(response => response.json())
    .then(response => {
        console.log(response);
    })
    .catch(err => {
        console.error(err);
    });
}