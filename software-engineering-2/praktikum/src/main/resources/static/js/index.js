$(document).ready(domReady);

function domReady() {
    window.navigator.geolocation.getCurrentPosition(geolocationSuccess);

    $("input").powerTip();
    $("textarea").powerTip();

    setCounter($("#text").val().length);

    $("#text").keyup(function() {
        setCounter($(this).val().length);
    });
}

function setCounter(counter) {
    $("#text-counter").html(counter);
}

function geolocationSuccess(position) {
    const coords = position.coords;
    const url = 'https://nominatim.openstreetmap.org/reverse?format=jsonv2&lat=' +
        coords.latitude + '&lon=' + coords.longitude;

    fetch(url).then(function(response) {
        return response.json();
    }).then(function(json) {
        const city = json.address.city || json.address.town || json.address.village;
        $("#location").val(city);
    });
}
