//Go to https://mrcoles.com/bookmarklet to convert this into a bookmarklet
var request = {
  url: window.location.href,
  title: document.title
};

window.fetch("http://localhost:1234/bookmarks", {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify(request)
  })
  .then(response => {
    if (response.status === 201) {
      alert("Added to mylinks!");
    } else if (response.status === 409) {
      alert("Link already exists in mylinks");
    } else {
      alert("Couldn't add link to mylinks :(. Error: " + response.status);
    }
  })
  .catch(err => {
    alert("Couldn't add link to mylinks :(. Are you sure mylinkserver is running?");
  });
