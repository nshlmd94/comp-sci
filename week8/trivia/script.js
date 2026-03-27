function init() {
    let input = document.querySelectorAll('.select-button');
    for (let button of input) {
        button.addEventListener('click', function() {
            if(button.value === '1 person per 6 sheep') {
                button.style.backgroundColor = 'lightgreen';
                let output = document.querySelector('.output1');
                output.innerHTML = 'Correct!';
                output.style.color = 'green';
            }
            else {
                button.style.backgroundColor = 'lightcoral';
                let output = document.querySelector('.output1');
                output.innerHTML = 'Incorrect!';
                output.style.color = 'red';
            }
            for (btn of input) {
                btn.disabled = true;
            }
        }) 
    }

    let response = document.querySelector('#check-box');
    response.addEventListener('click', function() {
        if(document.querySelector('#text-field').value === 'Switzerland') {
            let output = document.querySelector('.output2');
            output.innerHTML = 'Correct!';
            output.style.color = 'green';
        }
        else {
            let output = document.querySelector('.output2');
            output.innerHTML = 'Incorrect!';
            output.style.color = 'red';
        }
    })
}

document.addEventListener('DOMContentLoaded', init)