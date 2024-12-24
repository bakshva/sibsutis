< !DOCTYPE html >
    <html lang="en">
        <head>
            <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
                        <title>Budget Management</title>
                    </head>
                    <body>
                        <div class="container mt-5">
                            <ul class="nav nav-tabs" id="myTab" role="tablist">
                                <li class="nav-item" role="presentation">
                                    <button class="nav-link active" id="balance-tab" data-bs-toggle="tab" data-bs-target="#balance" type="button" role="tab">Баланс</button>
                                </li>
                                <li class="nav-item" role="presentation">
                                    <button class="nav-link" id="income-tab" data-bs-toggle="tab" data-bs-target="#income" type="button" role="tab">Доходы</button>
                                </li>
                                <li class="nav-item" role="presentation">
                                    <button class="nav-link" id="expenses-tab" data-bs-toggle="tab" data-bs-target="#expenses" type="button" role="tab">Расходы</button>
                                </li>
                            </ul>
                            <div class="tab-content" id="myTabContent">
                                <!-- Balance Tab -->
                                <div class="tab-pane fade show active" id="balance" role="tabpanel">
                                    <div class="mt-4">
                                        <div class="row mb-3">
                                            <label for="dateFilter" class="form-label">Фильтр по дате</label>
                                            <input type="date" class="form-control w-25" id="dateFilter">
                                        </div>
                                        <div id="balanceChart" class="border p-3" style="height: 300px;">График баланса</div>
                                    </div>
                                </div>

                                <!-- Income Tab -->
                                <div class="tab-pane fade" id="income" role="tabpanel">
                                    <div class="mt-4">
                                        <div class="d-flex justify-content-between mb-3">
                                            <input type="date" class="form-control w-25" id="incomeDateFilter" placeholder="Фильтр по дате">
                                                <button class="btn btn-primary" id="addIncome">Добавить запись</button>
                                        </div>
                                        <table class="table table-striped">
                                            <thead>
                                                <tr>
                                                    <th scope="col">#</th>
                                                    <th scope="col">Название</th>
                                                    <th scope="col">Тип</th>
                                                    <th scope="col">Сумма</th>
                                                    <th scope="col">Дата</th>
                                                    <th scope="col">Действия</th>
                                                </tr>
                                            </thead>
                                            <tbody id="incomeTableBody">
                                                <!-- Записи о доходах -->
                                            </tbody>
                                        </table>
                                    </div>
                                </div>

                                <!-- Expenses Tab -->
                                <div class="tab-pane fade" id="expenses" role="tabpanel">
                                    <div class="mt-4">
                                        <div class="d-flex justify-content-between mb-3">
                                            <input type="date" class="form-control w-25" id="expensesDateFilter" placeholder="Фильтр по дате">
                                                <button class="btn btn-primary" id="addExpense">Добавить запись</button>
                                        </div>
                                        <table class="table table-striped">
                                            <thead>
                                                <tr>
                                                    <th scope="col">#</th>
                                                    <th scope="col">Название</th>
                                                    <th scope="col">Тип</th>
                                                    <th scope="col">Сумма</th>
                                                    <th scope="col">Дата</th>
                                                    <th scope="col">Действия</th>
                                                </tr>
                                            </thead>
                                            <tbody id="expensesTableBody">
                                                <!-- Записи о расходах -->
                                            </tbody>
                                        </table>
                                    </div>
                                </div>
                            </div>
                        </div>

                        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
                        <script>
                            class Kyrs {
                                constructor(buy = 0, sell = 0, dat = new Date()) {
                                this.buy = buy;
                            this.sell = sell;
                            this.dat = new Date(dat);
            }

                            create() {
                                this.buy = parseFloat(prompt('Введите курс покупки: ') || 0);
                            this.sell = parseFloat(prompt('Введите курс продажи: ') || 0);
                            this.dat = new Date(prompt('Введите дату (YYYY-MM-DD): ') || new Date());
            }

                            read() {
                return `Покупка: ${this.buy}, Продажа: ${this.sell}, Дата: ${this.dat.toISOString().split('T')[0]}`;
            }

                            update(buy, sell, dat) {
                                this.buy = buy || this.buy;
                            this.sell = sell || this.sell;
                            this.dat = dat ? new Date(dat) : this.dat;
            }

                            delete() {
                                this.buy = 0;
                            this.sell = 0;
                            this.dat = null;
            }
        }

                            class Rashod {
                                constructor(name = '', value = 0, type = '', dat = new Date(), valyuta = null) {
                                this.name = name;
                            this.value = value;
                            this.type = type;
                            this.dat = new Date(dat);
                            this.valyuta = valyuta;
            }

                            create() {
                                this.name = prompt('Введите название: ') || this.name;
                            this.value = parseFloat(prompt('Введите сумму: ') || 0);
                            this.type = prompt('Введите тип: ') || this.type;
                            this.dat = new Date(prompt('Введите дату (YYYY-MM-DD): ') || new Date());
                            this.valyuta = prompt('Введите валюту: ') || this.valyuta;
            }

                            read() {
                return `Название: ${this.name}, Сумма: ${this.value}, Тип: ${this.type}, Дата: ${this.dat.toISOString().split('T')[0]}, Валюта: ${this.valyuta}`;
            }

                            update(name, value, type, dat, valyuta) {
                                this.name = name || this.name;
                            this.value = value || this.value;
                            this.type = type || this.type;
                            this.dat = dat ? new Date(dat) : this.dat;
                            this.valyuta = valyuta || this.valyuta;
            }

                            delete() {
                                this.name = null;
                            this.value = 0;
                            this.type = null;
                            this.dat = null;
                            this.valyuta = null;
            }
        }

        document.getElementById('addIncome').addEventListener('click', () => {
            const income = new Rashod();
                            income.create();
                            const row = document.createElement('tr');
                            row.innerHTML = `
                            <th scope="row">${document.getElementById('incomeTableBody').children.length + 1}</th>
                            <td>${income.name}</td>
                            <td>${income.type}</td>
                            <td>${income.value}</td>
                            <td>${income.dat.toISOString().split('T')[0]}</td>
                            <td>
                                <button class="btn btn-warning btn-sm" onclick="editIncome(this)">Редактировать</button>
                                <button class="btn btn-danger btn-sm" onclick="deleteIncome(this)">Удалить</button>
                            </td>
                            `;
                            document.getElementById('incomeTableBody').appendChild(row);
        });

                            function editIncome(button) {
            const row = button.parentElement.parentElement;
                            const income = new Rashod(
                            row.children[1].innerText,
                            parseFloat(row.children[3].innerText),
                            row.children[2].innerText,
                            row.children[4].innerText
                            );
                            income.create();
                            row.children[1].innerText = income.name;
                            row.children[2].innerText = income.type;
                            row.children[3].innerText = income.value;
                            row.children[4].innerText = income.dat.toISOString().split('T')[0];
        }

                            function deleteIncome(button) {
            const row = button.parentElement.parentElement;
                            row.remove();
        }

        document.getElementById('addExpense').addEventListener('click', () => {
            const expense = new Rashod();
                            expense.create();
                            const row = document.createElement('tr');
                            row.innerHTML = `
                            <th scope="row">${document.getElementById('expensesTableBody').children.length + 1}</th>
                            <td>${expense.name}</td>
                            <td>${expense.type}</td>
                            <td>${expense.value}</td>
                            <td>${expense.dat.toISOString().split('T')[0]}</td>
                            <td>
                                <button class="btn btn-warning btn-sm" onclick="editExpense(this)">Редактировать</button>
                                <button class="btn btn-danger btn-sm" onclick="deleteExpense(this)">Удалить</button>
                            </td>
                            `;
                            document.getElementById('expensesTableBody').appendChild(row);
        });

                            function editExpense(button) {
            const row = button.parentElement.parentElement;
                            const expense = new Rashod(
                            row.children[1].innerText,
                            parseFloat(row.children[3].innerText),
                            row.children[2].innerText,
                            row.children[4].innerText
                            );
                            expense.create();
                            row.children[1].innerText = expense.name;
                            row.children[2].innerText = expense.type;
                            row.children[3].innerText = expense.value;
                            row.children[4].innerText = expense.dat.toISOString().split('T')[0];
        }

                            function deleteExpense(button) {
            const row = button.parentElement.parentElement;
                            row.remove();
        }
                        </script>
                    </body>
                </html>
