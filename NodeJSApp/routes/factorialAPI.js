module.exports = function (express) {
    // EXPRESS ROUTER
    var router = express.Router({ mergeParams: true });

    router.get('/:number', function (request, response, next) {
        var factorialCallbackAddon = require('../addons/CallbackFunctionDemo');
        
        factorialCallbackAddon.factorial(parseInt(request.params.number), function (result) {
            response.render('IndexView', {
                title: "Factorial",
                content1: "Result = " + result
            });
        });
    });

    return router;
}