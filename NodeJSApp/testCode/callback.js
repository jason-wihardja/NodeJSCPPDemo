var helloCallback = require('../addons/CallbackFunctionDemo');

helloCallback.factorial(5, function (result) {
    console.log('Result = ' + result);
});