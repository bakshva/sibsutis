const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const PORT = 3000;

app.use(express.static('public'));

const BUDGET_FILE_PATH = path.join(__dirname, 'budget.json');


if (!fs.existsSync(BUDGET_FILE_PATH)) {
    console.log('Файл budget.json отсутствует. Создаем новый файл...');
    fs.writeFileSync(BUDGET_FILE_PATH, JSON.stringify({
        currencies: [],
        expenseTypes: [],
        incomeTypes: [],
        expenses: [],
        incomes: []
    }, null, 2));
}


app.use(express.json());


app.get('/api/budget', (req, res) => {
    fs.readFile(BUDGET_FILE_PATH, 'utf8', (err, data) => {
        if (err) {
            console.error('Ошибка при чтении файла:', err);
            return res.status(500).json({ message: 'Ошибка при чтении файла' });
        }
        res.json(JSON.parse(data));
    });
});


app.post('/api/budget', (req, res) => {
    console.log('Получен POST-запрос:', req.body);

    const newRecord = req.body;

    if (!newRecord || !newRecord.record_Type || !newRecord.name || isNaN(newRecord.value) || !newRecord.date || !newRecord.currency) {
        console.error('Неверные данные:', newRecord);
        return res.status(400).json({ message: 'Неверные данные' });
    }

    fs.readFile(BUDGET_FILE_PATH, 'utf8', (err, data) => {
        if (err) {
            console.error('Ошибка при чтении файла:', err);
            return res.status(500).json({ message: 'Ошибка при чтении файла' });
        }

        let budgetData;
        try {
            budgetData = JSON.parse(data);
        } catch (parseErr) {
            console.error('Ошибка парсинга файла budget.json:', parseErr);
            return res.status(500).json({ message: 'Ошибка парсинга файла budget.json' });
        }

        if (newRecord.record_Type === 'income') {
            budgetData.incomes.push(newRecord);
        } else if (newRecord.record_Type === 'expense') {
            budgetData.expenses.push(newRecord);
        } else {
            console.error('Неизвестный тип записи:', newRecord.record_Type);
            return res.status(400).json({ message: 'Неизвестный тип записи' });
        }

        console.log('Обновленные данные бюджета:', budgetData);

        fs.writeFile(BUDGET_FILE_PATH, JSON.stringify(budgetData, null, 2), 'utf8', (err) => {
            if (err) {
                console.error('Ошибка при записи файла:', err);
                return res.status(500).json({ message: 'Ошибка при записи файла' });
            }
            res.status(200).json({ message: 'Запись добавлена!' });
        });
    });
});


app.listen(PORT, () => console.log(`Сервер запущен на http://localhost:${PORT}`));