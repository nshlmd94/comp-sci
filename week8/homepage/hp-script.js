function init() {
    let input = document.querySelectorAll('.box'); {
        for(let emoji of input) {
            emoji.addEventListener('click', function() {
                if(emoji.value === '😊') {
                    window.location.href = 'happy.html'
                }
                else if(emoji.value === '😇') {
                    window.location.href = 'calm.html'
                }
                else if(emoji.value === '😑') {
                    window.location.href = 'meh.html'
                }
                else if(emoji.value === '😞') {
                    window.location.href = 'sad.html'
                }
                else if(emoji.value === '😡') {
                    window.location.href = 'angry.html'
                }
                else if(emoji.value === '😴') {
                    window.location.href = 'sleepy.html'
                }
            })
        }
    }

    let timer = document.querySelector('.countdown');
    let intervalId = null;
    let startingTimer = 120;

    function restart() {
        clearInterval(intervalId);
        intervalId = null;
        startingTimer = 121;

        intervalId = setInterval(function () {
            startingTimer--;
            console.log(`${startingTimer}`);

            let minutes = Math.floor(startingTimer / 60);
            let seconds = startingTimer % 60;
            seconds = seconds < 10 ? `0${seconds}` : seconds;

            let output = document.querySelector('#countdown-text');
            output.innerHTML = `0${minutes}:${seconds}`;

            if (startingTimer === 0) {
                clearInterval(intervalId);
                console.log("00:00");
            }
        }, 1000)
    }

    timer.addEventListener('click', restart);
    document.addEventListener('mousemove', restart);

}

document.addEventListener('DOMContentLoaded', init)