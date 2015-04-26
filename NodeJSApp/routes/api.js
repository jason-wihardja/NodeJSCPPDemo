module.exports = function (express) {
    // EXPRESS ROUTER
    var router = express.Router({ mergeParams: true });
    
    router.get('/', function (request, response, next) {
        var helloAddon = require('../addons/HelloAddon');
        
        response.render('IndexView', {
            title: helloAddon.hello(),
            content1: helloAddon.hello('MSP Rocks!')
        });
    });
    
    router.use('/factorial', require('./factorialAPI.js')(express));
    router.use('/prime', require('./primeAPI.js')(express));
    
    return router;
}