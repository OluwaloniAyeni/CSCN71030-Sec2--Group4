#include <stdlib.h>
#include "recommendation.h"

float getRatingScore(Item item) {

	return item.rating;
}

float getPriceValue(Item item) {
	return item.price;
}