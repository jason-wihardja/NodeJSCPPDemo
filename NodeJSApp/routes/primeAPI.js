module.exports = function (express) {
    // EXPRESS ROUTER
    var router = express.Router({ mergeParams: true });
    
    // ADDON
    var primeNumberJSAddon = require('../addons/PrimeJS');
    var primeNumberCPPAddon = require('../addons/PrimeCPP');
    
    /* SYNC METHOD */
    router.get('/:number', function (request, response, next) {
        var number = parseInt(request.params.number);
        
        var beforeJS = process.hrtime();
        var primeNumbersJS = primeNumberJSAddon.findPrime(number);
        var jsTime = process.hrtime(beforeJS);
        
        var beforeCPP = process.hrtime();
        var primeNumbersCPP = primeNumberCPPAddon.findPrime(number);
        var cppTime = process.hrtime(beforeCPP);
        
        response.render('IndexView', {
            title: "Prime Numbers",
            content1: "Result = " + JSON.stringify(primeNumbersCPP),
            content2: "JS Time = " + (jsTime[0] * 1e9 + jsTime[1]) + " nanoseconds",
            content3: "C++ Time = " + (cppTime[0] * 1e9 + cppTime[1]) + " nanoseconds"
        });
    });
    
    /* ASYNC METHOD */
    router.get('/cpp/:number', function (request, response, next) {
        var number = parseInt(request.params.number);
        
        var before = process.hrtime();
        primeNumberCPPAddon.findPrimeAsync(number, function (result) {
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
        primeNumberJSAddon.findPrimeAsync(number, function (result) {
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