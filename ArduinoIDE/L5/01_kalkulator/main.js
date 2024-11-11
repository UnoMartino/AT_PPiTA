let result = 0;
let lastOperation = '';
let operationLock = false;

function buttonPressed(value) {
    const windowElement = document.getElementById("window");
    const currentValue = parseInt(windowElement.value);

    switch (value) {
        case 'CE':
            windowElement.value = '';
            result = 0;
            lastOperation = '';
            operationLock = false;
            break;

        case '+':
            result += currentValue;
            lastOperation = '+';
            operationLock = true;
            windowElement.value = result;
            break;

        case '-':
            result = currentValue;
            lastOperation = '-';
            operationLock = true;
            windowElement.value = result;
            break;

        case 'x':
            result = currentValue;
            lastOperation = 'x';
            operationLock = true;
            break;

        case '/':
            result = currentValue;
            lastOperation = '/';
            operationLock = true;
            break;

        case '=':
            switch (lastOperation) {
                case '+':
                    result += currentValue;
                    break;
                case '-':
                    result -= currentValue;
                    break;
                case 'x':
                    result *= currentValue;
                    break;
                case '/':
                    if (currentValue === 0) {
                        windowElement.value = 'ERROR';
                        return;
                    } else {
                        result /= currentValue;
                    }
                    break;
            }
            operationLock = true;
            windowElement.value = result;
            break;

        default:
            if (!isNaN(parseInt(value))) {
                if (operationLock) {
                    windowElement.value = '';
                    operationLock = false;
                }
                windowElement.value += value;
            }
            break;
    }
}

