const ledOnButton = document.querySelector('.led-on-js');
const ledOffButton = document.querySelector('.led-off-js');

ledOnButton.addEventListener('click', async ()=> {
    await fetch("/controlLed?command=1")
    .catch(error => console.error('Error:', error));
});

ledOffButton.addEventListener('click', async ()=> {
    await fetch("/controlLed?command=0")
    .catch(error => console.error('Error:', error));
});