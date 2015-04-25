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
    
    var randomNumbers = [687, 357, 6087, 6561, 3487, 1092, 757, 3971, 5316, 6496, 4083, 6790, 7191, 2026, 2060, 1675, 7135, 463, 1110, 539, 3041, 1021, 7452, 2760, 9961, 4579, 9502, 5858, 1898, 9401, 8040, 8696, 1026, 5024, 4336, 1584, 4434, 4219, 5444, 6889, 7452, 7934, 228, 958, 1357, 3750, 9179, 1774, 1294, 1513, 1604, 186, 6038, 5151, 5979, 5310, 3138, 321, 6001, 3635, 2919, 913, 5364, 6260, 1942, 2811, 9759, 4432, 8338, 7482, 8237, 7184, 1295, 6573, 7812, 6778, 9899, 8827, 1263, 8069, 6369, 1302, 972, 269, 4411, 7100, 6424, 7049, 6680, 9459, 2216, 5947, 9295, 6086, 7433, 2232, 1235, 7435, 2154, 9433, 7639, 4520, 872, 609, 6708, 2709, 7978, 9008, 2264, 1570, 1871, 5304, 8017, 6588, 5429, 1406, 1115, 8973, 5131, 9906, 4694, 3410, 2089, 9154, 7371, 5777, 494, 3916, 9648, 5930, 8618, 2419, 266, 1437, 4302, 804, 9267, 8876, 7472, 2842, 7229, 7682, 3779, 8878, 6534, 7445, 8487, 7411, 124, 2568, 2124, 6465, 3154, 9669, 5165, 8352, 7283, 3305, 8315, 9272, 7030, 3103, 7383, 726, 7939, 5729, 389, 6529, 8118, 9228, 3101, 6046, 753, 2564, 6211, 3777, 9623, 6184, 2025, 3605, 8134, 6615, 9412, 8894, 5444, 7972, 8284, 7372, 4654, 8918, 1112, 3075, 6172, 2610, 3978, 4889, 8937, 7357, 5750, 8896, 882, 156, 7273, 6821, 6429, 4079, 7607, 2871, 9628, 9502, 3525, 1276, 3938, 9538, 5449, 7248, 5125, 2439, 6655, 7088, 4437, 7024, 2781, 3526, 8971, 3116, 9529, 2485, 4261, 7672, 6217, 1368, 4290, 2437, 7996, 7638, 2265, 8715, 5623, 4153, 767, 9102, 7762, 8751, 9048, 3920, 676, 6704, 4861, 9431];
    var sortRouter = express.Router({ mergeParams: true });
    sortRouter.get('/', function (request, response, next) {
        var beginning = moment();

        var jsSorted = require('../addons/SortJS').sort(randomNumbers.slice(0));
        var afterJS = moment();

        var cppSorted = require('../addons/SortCPP').sort(randomNumbers.slice(0));
        var afterCPP = moment();

        var jsTime = afterJS - beginning;
        var cppTime = afterCPP - afterJS;

        response.render('IndexView', {
            title: "Bubble Sort",
            content1: "Result = " + JSON.stringify(cppSorted),
            content2: "JS Time = " + jsTime,
            content3: "C++ Time = " + cppTime
        });
    });
    sortRouter.get('/cpp', function (request, response, next) {
        var before = moment();
        var cppSorted = require('../addons/SortCPP').sort(randomNumbers.slice(0));
        var after = moment();
        
        response.render('IndexView', {
            title: "Bubble Sort",
            content1: "Result = " + JSON.stringify(cppSorted),
            content2: "Time = " + (after - before)
        });
    });
    sortRouter.get('/js', function (request, response, next) {
        var before = moment();
        var jsSorted = require('../addons/SortJS').sort(randomNumbers.slice(0));
        var after = moment();
        
        response.render('IndexView', {
            title: "Bubble Sort",
            content1: "Result = " + JSON.stringify(jsSorted),
            content2: "Time = " + (after - before)
        });
    });
    router.use('/sort', sortRouter);
    
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