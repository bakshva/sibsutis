let num = 222;
let str = "aa";
let bool = true;
let n = null;
let und;
let person = {
    name: "Ivan",
    age: 47,
};

const alf = {
    a: 1,
    b: 2,
};
const num1 = 1;
const str1 = 'bbb';
const bool1 = '0';

function mainFunction() {
    let a = 1;
    const b = 'ccc';
}

function otherFunction() {
    if (typeof num !== 'undefined') {
        alert('Переменная num, определенная в документе - Доступна');
    } else {
        alert('Переменная num, определенная в документе - Недоступна');
    }

    if (typeof str !== 'undefined') {
        alert('Переменная str, определенная в документе - Доступна');
    } else {
        alert('Переменная str, определенная в документе - Недоступна');
    }

    if (typeof bool !== 'undefined') {
        alert('Переменная bool, определенная в документе - Доступна');
    } else {
        alert('Переменная bool, определенная в документе - Недоступна');
    }


    if (typeof n !== 'undefined') {
        alert('Переменная n, определенная в документе - Доступна');
    } else {
        alert('Переменная n, определенная в документе - Недоступна');
    }


    if (typeof und === 'undefined') {
        alert('Переменная und, определенная в документе - Недоступна');
    } else {
        alert('Переменная und, определенная в документе - Доступна');
    }


    if (typeof a !== 'undefined') {
        alert('Переменная a, определенная в документе - Доступна');
    } else {
        alert('Переменная a, определенная в документе - Недоступна');
    }

    if (typeof b !== 'undefined') {
        alert('Переменная b, определенная в документе - Доступна');
    } else {
        alert('Переменная b, определенная в документе - Недоступна');
    }
}
otherFunction();

function a1() {
    let a = '100';
    let b = 50;

    alert('Тип переменной a: ' + typeof a);
    alert('Тип переменной b: ' + typeof b);


    a = Number(a); // Преобразуем строку в число
    b = String(b); // Преобразуем число в строку

    alert('Тип переменной a: ' + typeof a);
    alert('Тип переменной b: ' + typeof b);

    // Преобразование в логический тип
    a = Boolean(a);
    b = Boolean(b);

    alert('Тип переменной a: ' + typeof a);
    alert('Тип переменной b: ' + typeof b);


    let a1 = 5;
    alert('a1 = ' + a1);

    let a2 = ++a1;
    alert('Префиксный инкремент a1: ' + a2);

    let a3 = a1++;
    alert('Постфиксный инкремент a1: ' + a3);

    let a4 = +a1;
    alert('Приведение a1 к числу: ' + a4);

    // Ввод имени пользователя
    let userName = prompt("Введите ваше имя:");
    alert("Привет, " + userName + "!");

    // Проверка возраста
    let isAdult = confirm("Вам есть 18 лет?");
    if (isAdult) {
        alert("Добро пожаловать!");
    } else {
        alert("К сожалению, доступ запрещен.");
    }

    // Цикл for
    for (let i = 0; i < 5; i++) {
        alert("Цикл for: шаг " + i);
    }

    // Цикл while
    let counter = 0;
    while (counter < 3) {
        alert("Цикл while: шаг " + counter);
        counter++;
    }

    // Цикл do...while
    let numb = 0;
    do {
        alert("Цикл do...while: значение " + numb);
        numb++;
    } while (numb < 3);

    // Оператор switch
    let color = prompt("Введите цвет (красный, синий, зеленый):");

    switch (color) {
        case 'красный':
            alert("Вы выбрали красный.");
            break;
        case 'синий':
            alert("Вы выбрали синий.");
            break;
        case 'зеленый':
            alert("Вы выбрали зеленый.");
            break;
        default:
            alert("Такого цвета нет.");
    }

    // Функция приветствия
    const greetUser = function (name) {
        return "Привет, " + name + "!";
    };

    let useName = prompt("Введите ваше имя:");
    alert(greetUser(useName));
}
a1();