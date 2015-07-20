module.exports = function (express) {
    // EXPRESS ROUTER
    var router = express.Router({ mergeParams: true });
    
    // ADDON
    var performanceAddon = require('../addons/PerformanceDemo');
    
    router.get('/', function (request, response, next) {
        performanceAddon.getPerformanceData(function (data) {
            response.json(data);
        });
    });
    
    return router;
}