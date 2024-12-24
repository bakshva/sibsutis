// Класс Валюта
class Currency {
    constructor(name) {
        this.name = name;
        this.rates = {}; // Массив дата => курс
    }

    addRate(date, rate) {
        this.rates[date] = rate;
    }

    getRate(date) {
        return this.rates[date];
    }
}

// Класс Тип расхода/дохода
class Type {
    constructor(name) {
        this.name = name;
    }
}

// Класс Расход
class Expense {
    constructor(name, value, type, date, currency) {
        this.name = name;
        this.value = value;
        this.type = type;
        this.date = date;
        this.currency = currency;
    }
}

// Класс Доход
class Income {
    constructor(name, value, type, date, currency) {
        this.name = name;
        this.value = value;
        this.type = type;
        this.date = date;
        this.currency = currency;
    }
}

// Класс Бюджет
class Budget {
    constructor() {
        this.currencies = [];
        this.expenseTypes = [];
        this.incomeTypes = [];
        this.expenses = [];
        this.incomes = [];
    }

    // Методы CRUD для валюты
    addCurrency(currency) {
        this.currencies.push(currency);
    }

    getCurrency(name) {
        return this.currencies.find((currency) => currency.name === name);
    }

    updateCurrency(name, newCurrency) {
        const index = this.currencies.findIndex((currency) => currency.name === name);
        if (index !== -1) {
            this.currencies[index] = newCurrency;
        }
    }

    deleteCurrency(name) {
        this.currencies = this.currencies.filter((currency) => currency.name !== name);
    }

    // Методы CRUD для типов расходов
    addExpenseType(type) {
        this.expenseTypes.push(type);
    }

    getExpenseType(name) {
        return this.expenseTypes.find((type) => type.name === name);
    }

    updateExpenseType(name, newType) {
        const index = this.expenseTypes.findIndex((type) => type.name === name);
        if (index !== -1) {
            this.expenseTypes[index] = newType;
        }
    }

    deleteExpenseType(name) {
        this.expenseTypes = this.expenseTypes.filter((type) => type.name !== name);
    }

    // Методы CRUD для типов доходов
    addIncomeType(type) {
        this.incomeTypes.push(type);
    }

    getIncomeType(name) {
        return this.incomeTypes.find((type) => type.name === name);
    }

    updateIncomeType(name, newType) {
        const index = this.incomeTypes.findIndex((type) => type.name === name);
        if (index !== -1) {
            this.incomeTypes[index] = newType;
        }
    }

    deleteIncomeType(name) {
        this.incomeTypes = this.incomeTypes.filter((type) => type.name !== name);
    }

    // Методы CRUD для расходов
    addExpense(expense) {
        this.expenses.push(expense);
    }

    getExpenses() {
        return this.expenses;
    }

    updateExpense(index, newExpense) {
        if (index >= 0 && index < this.expenses.length) {
            this.expenses[index] = newExpense;
        }
    }

    deleteExpense(index) {
        this.expenses.splice(index, 1);
    }

    // Методы CRUD для доходов
    addIncome(income) {
        this.incomes.push(income);
    }

    getIncomes() {
        return this.incomes;
    }

    updateIncome(index, newIncome) {
        if (index >= 0 && index < this.incomes.length) {
            this.incomes[index] = newIncome;
        }
    }

    deleteIncome(index) {
        this.incomes.splice(index, 1);
    }

    // Метод Баланс - расчет баланса за период
    getBalance(startDate, endDate, typeFilter = null) {
        let incomeTotal = 0;
        let expenseTotal = 0;

        this.incomes.forEach((income) => {
            if (income.date >= startDate && income.date <= endDate) {
                let incomeValue = income.value;
                if (income.currency.name.toLowerCase() === 'доллар' || income.currency.name.toLowerCase() === 'usd') {
                    incomeValue *= 100; // Преобразование доллара в рубли для итогового расчета
                }
                if (!typeFilter || income.type.name === typeFilter) {
                    incomeTotal += incomeValue;
                }
            }
        });

        this.expenses.forEach((expense) => {
            if (expense.date >= startDate && expense.date <= endDate) {
                let expenseValue = expense.value;
                if (expense.currency.name.toLowerCase() === 'доллар' || expense.currency.name.toLowerCase() === 'usd') {
                    expenseValue *= 100; // Преобразование доллара в рубли для итогового расчета
                }
                if (!typeFilter || expense.type.name === typeFilter) {
                    expenseTotal += expenseValue;
                }
            }
        });

        return incomeTotal - expenseTotal;
    }

    // Метод Фильтр - выбор доходов/расходов за период
    filterEntries(startDate, endDate, typeFilter = null) {
        const filteredIncomes = this.incomes.filter(
            (income) =>
                income.date >= startDate &&
                income.date <= endDate &&
                (!typeFilter || income.type.name === typeFilter)
        );

        const filteredExpenses = this.expenses.filter(
            (expense) =>
                expense.date >= startDate &&
                expense.date <= endDate &&
                (!typeFilter || expense.type.name === typeFilter)
        );

        return { incomes: filteredIncomes, expenses: filteredExpenses };
    }
}

// Связь интерфейса с логикой
const budget = new Budget();

// Загрузка данных из localStorage
function loadBudgetFromLocalStorage() {
    const savedData = localStorage.getItem('budgetData');
    if (savedData) {
        const parsedData = JSON.parse(savedData);
        Object.assign(budget, parsedData);

        // Восстановление классов для каждой записи
        budget.expenses = budget.expenses.map(exp => new Expense(exp.name, exp.value, new Type(exp.type.name), exp.date, new Currency(exp.currency.name)));
        budget.incomes = budget.incomes.map(inc => new Income(inc.name, inc.value, new Type(inc.type.name), inc.date, new Currency(inc.currency.name)));
    }
}

// Сохранение данных в localStorage
function saveBudgetToLocalStorage() {
    localStorage.setItem('budgetData', JSON.stringify(budget));
}

function addRecord() {
    const recordType = document.getElementById('recordType').value;
    const recordName = document.getElementById('recordName').value;
    let recordValue = parseFloat(document.getElementById('recordValue').value);
    const recordTypeField = document.getElementById('recordTypeField').value;
    const recordDate = document.getElementById('recordDate').value;
    const recordCurrency = document.getElementById('recordCurrency').value;

    let type = budget.getExpenseType(recordTypeField) || budget.getIncomeType(recordTypeField);
    if (!type) {
        type = new Type(recordTypeField);
        if (recordType === 'expense') {
            budget.addExpenseType(type);
        } else {
            budget.addIncomeType(type);
        }
    }

    const currency = budget.getCurrency(recordCurrency) || new Currency(recordCurrency);
    if (!budget.getCurrency(recordCurrency)) {
        budget.addCurrency(currency);
    }

    if (recordType === 'expense') {
        const expense = new Expense(recordName, recordValue, type, recordDate, currency);
        budget.addExpense(expense);
        alert('Расход успешно добавлен!');
    } else if (recordType === 'income') {
        const income = new Income(recordName, recordValue, type, recordDate, currency);
        budget.addIncome(income);
        alert('Доход успешно добавлен!');
    }

    // Сохранение в localStorage после добавления записи
    saveBudgetToLocalStorage();

    // Обновление интерфейса
    updateLists();
}

function updateLists() {
    const incomeList = document.getElementById('incomeList');
    incomeList.innerHTML = '';
    let totalIncome = 0;
    budget.getIncomes().forEach((income) => {
        let incomeValue = income.value;
        const displayedValue = incomeValue;
        if (income.currency.name.toLowerCase() === 'доллар' || income.currency.name.toLowerCase() === 'usd') {
            incomeValue *= 100; // Преобразование доллара в рубли для итогового расчета
        }
        const entry = document.createElement('div');
        entry.classList.add('list-group-item');
        entry.innerHTML = `<div class="d-flex w-100 justify-content-between"><h5 class="mb-1"><b>${income.name}</b></h5><small>${displayedValue} ${income.currency.name === 'рубль' ? '₽' : income.currency.name}</small></div><p class="mb-1">${income.type.name} | Дата: ${new Date(income.date).toLocaleDateString()}</p>`;
        incomeList.appendChild(entry);
        totalIncome += incomeValue;
    });
    if (totalIncome > 0) {
        const totalEntry = document.createElement('div');
        totalEntry.classList.add('list-group-item', 'font-weight-bold');
        totalEntry.innerHTML = `<div class="d-flex w-100 justify-content-between"><h5 class="mb-1">Итого</h5><small><b>${totalIncome} ₽</b></small></div>`;
        incomeList.appendChild(totalEntry);
    }

    const expenseList = document.getElementById('expenseList');
    expenseList.innerHTML = '';
    let totalExpense = 0;
    budget.getExpenses().forEach((expense) => {
        let expenseValue = expense.value;
        const displayedValue = expenseValue;
        if (expense.currency.name.toLowerCase() === 'доллар' || expense.currency.name.toLowerCase() === 'usd') {
            expenseValue *= 100; // Преобразование доллара в рубли для итогового расчета
        }
        const entry = document.createElement('div');
        entry.classList.add('list-group-item');
        entry.innerHTML = `<div class="d-flex w-100 justify-content-between"><h5 class="mb-1"><b>${expense.name}</b></h5><small>${displayedValue} ${expense.currency.name === 'рубль' ? '₽' : expense.currency.name}</small></div><p class="mb-1">${expense.type.name} | Дата: ${new Date(expense.date).toLocaleDateString()}</p>`;
        expenseList.appendChild(entry);
        totalExpense += expenseValue;
    });
    if (totalExpense > 0) {
        const totalEntry = document.createElement('div');
        totalEntry.classList.add('list-group-item', 'font-weight-bold');
        totalEntry.innerHTML = `<div class="d-flex w-100 justify-content-between"><h5 class="mb-1">Итого</h5><small><b>${totalExpense} ₽</b></small></div>`;
        expenseList.appendChild(totalEntry);
    }
}

// Загрузка данных при загрузке страницы
document.addEventListener('DOMContentLoaded', () => {
    loadBudgetFromLocalStorage();
    updateLists();
});