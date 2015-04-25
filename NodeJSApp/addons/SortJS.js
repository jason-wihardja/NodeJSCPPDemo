module.exports = {
    sort: function (numbers) {
        Array.prototype.swap = function (index_A, index_B) {
            var temp = this[index_A];
            this[index_A] = this[index_B];
            this[index_B] = temp;
        };
        
        // Bubble Sort
        var swapped;
        do {
            swapped = false;
            for (var i = 1; i < numbers.length; i++) {
                if (numbers[i] < numbers[i - 1]) {
                    numbers.swap(i, i - 1);
                    swapped = true;
                }
            }
        } while(swapped);
        
        return numbers;
    }
};