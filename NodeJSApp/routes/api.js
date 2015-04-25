module.exports = function (express, addon) {
    var _ = require('underscore');
    var moment = require('moment');
    
    // EXPRESS ROUTER
    var router = express.Router();
    
    router.get('/hello', function (request, response, next) {
        var helloAddon = require('../addons/HelloAddon');
        
        response.render('IndexView', {
            title: helloAddon.hello(),
            content1: helloAddon.hello('MSP Rocks!')
        });
    });
    
    router.get('/factorial/:number', function (request, response, next) {
        var factorialCallbackAddon = require('../addons/CallbackFunctionDemo');
        
        factorialCallbackAddon.factorial(parseInt(request.params.number), function (result) {
            response.render('IndexView', {
                title: "Factorial",
                content1: "Result = " + result
            });
        });
    });
    
    var primeRouter = express.Router({ mergeParams: true });
    primeRouter.get('/:number', function (request, response, next) {
        var number = parseInt(request.params.number);

        var before = moment();

        var primeNumbersJS = require('../addons/PrimeJS').findPrime(number);
        var afterJS = moment();

        var primeNumbersCPP = require('../addons/PrimeCPP').findPrime(number);
        var afterCPP = moment();

        var jsTime = afterJS - before;
        var cppTime = afterCPP - afterJS;

        response.render('IndexView', {
            title: "Prime Numbers",
            content1: "Result = " + JSON.stringify(primeNumbersCPP),
            content2: "JS Time = " + jsTime + " ms",
            content3: "C++ Time = " + cppTime + " ms"
        });
    });
    primeRouter.get('/cpp/:number', function (request, response, next) {
        var number = parseInt(request.params.number);

        var before = moment();
        
        var primeNumbersCPP = require('../addons/PrimeCPP').findPrime(number);
        var afterCPP = moment();
        
        var cppTime = afterCPP - before;
        
        response.render('IndexView', {
            title: "Prime Numbers",
            content1: "Result = " + JSON.stringify(primeNumbersCPP),
            content2: "C++ Time = " + cppTime
        });
    });
    primeRouter.get('/js/:number', function (request, response, next) {
        var number = parseInt(request.params.number);

        var before = moment();
        
        var primeNumbersJS = require('../addons/PrimeJS').findPrime(number);
        var afterJS = moment();
        
        var jsTime = afterJS - before;
        
        response.render('IndexView', {
            title: "Prime Numbers",
            content1: "Result = " + JSON.stringify(primeNumbersJS),
            content2: "JS Time = " + jsTime
        });
    });
    router.use('/prime', primeRouter);
    
    router.get('/test', function (request, response, next) {
        addon.getTestData(request.query.dbName, function (err, result) {
            if (_.isEmpty(err)) {
                response.type('json');
                response.send(JSON.stringify(result));
            } else {
                var error = new Error('Bad Request');
                error.http_code = error.status = 400;
                error.stack = err;
                next(error);
            }
        });
    });
    
    return router;
}