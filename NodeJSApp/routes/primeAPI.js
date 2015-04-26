module.exports = function (express) {
    // EXPRESS ROUTER
    var router = express.Router({ mergeParams: true });
    
    /* SYNC API */
    router.get('/:number', function (request, response, next) {
        var number = parseInt(request.params.number);
        
        var beforeJS = process.hrtime();
        var primeNumbersJS = require('../addons/PrimeJS').findPrime(number);
        var jsTime = process.hrtime(beforeJS);
        
        var beforeCPP = process.hrtime();
        var primeNumbersCPP = require('../addons/PrimeCPP').findPrime(number);
        var cppTime = process.hrtime(beforeCPP);
        
        response.render('IndexView', {
            title: "Prime Numbers",
            content1: "Result = " + JSON.stringify(primeNumbersCPP),
            content2: "JS Time = " + (jsTime[0] * 1e9 + jsTime[1]) + " nanoseconds",
            content3: "C++ Time = " + (cppTime[0] * 1e9 + cppTime[1]) + " nanoseconds"
        });
    });
    
    /* ASYNC API */
    router.get('/cpp/:number', function (request, response, next) {
        var number = parseInt(request.params.number);
        
        var before = process.hrtime();
        require('../addons/PrimeCPP').findPrimeAsync(number, function (result) {
            var cppTime = process.hrtime(before);
            
            response.render('IndexView', {
                title: "Prime Numbers",
                content1: "Result = " + JSON.stringify(result),
                content2: "C++ Time = " + (cppTime[0] * 1e9 + cppTime[1]) + " nanoseconds"
            });
        });
    });
    
    router.get('/js/:number', function (request, response, next) {
        var number = parseInt(request.params.number);
        
        var before = process.hrtime();
        require('../addons/PrimeJS').findPrimeAsync(number, function (result) {
            var jsTime = process.hrtime(before);
            
            response.render('IndexView', {
                title: "Prime Numbers",
                content1: "Result = " + JSON.stringify(result),
                content2: "JS Time = " + (jsTime[0] * 1e9 + jsTime[1]) + " nanoseconds"
            });
        });
    });
    
    return router;
}