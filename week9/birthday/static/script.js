/* I haven't written this*/

function init() {
    let editButtons = document.querySelectorAll('.edit-btn');
    for (let btn of editButtons) {
        btn.addEventListener('click', function() {
            let row = this.closest('tr');
            let nameCell = row.cells[0];
            let birthdayCell = row.cells[1];
            let editCell = row.cells[2];

            // Get current values
            let currentName = nameCell.innerHTML;
            let birthdayParts = birthdayCell.innerHTML.split('/');
            let currentMonth = birthdayParts[0].trim();
            let currentDay = birthdayParts[1].trim();
            let id = this.dataset.id;

            // Replace cells with inputs
            nameCell.innerHTML = `<input type="text" name="name" value="${currentName}">`;
            birthdayCell.innerHTML = `<input type="number" name="month" value="${currentMonth}" min="1" max="12">
                                      <input type="number" name="day" value="${currentDay}" min="1" max="31">`;

            // Replace edit button with save button
            editCell.innerHTML = `<button class="save-btn" data-id="${id}">Save</button>`;

            // Add save listener
            editCell.querySelector('.save-btn').addEventListener('click', function() {
                let name = nameCell.querySelector('input[name="name"]').value;
                let month = nameCell.closest('tr').cells[1].querySelector('input[name="month"]').value;
                let day = nameCell.closest('tr').cells[1].querySelector('input[name="day"]').value;

                let form = document.createElement('form');
                form.method = 'post';
                form.action = '/update';
                form.innerHTML = `
                    <input type="hidden" name="id" value="${id}">
                    <input type="hidden" name="name" value="${name}">
                    <input type="hidden" name="month" value="${month}">
                    <input type="hidden" name="day" value="${day}">
                `;
                document.body.appendChild(form);
                form.submit();
            });
        });
    }
}

document.addEventListener("DOMContentLoaded", init);