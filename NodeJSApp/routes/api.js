module.exports = function (express, addon) {
    var _ = require('underscore');
    
    // EXPRESS ROUTER
    var router = express.Router();

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