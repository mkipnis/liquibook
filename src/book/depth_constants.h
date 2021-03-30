// Copyright (c) 2012 - 2017 Object Computing, Inc.
// All rights reserved.
// See the file license.txt for licensing information.
#pragma once

#include "types.h"

namespace liquibook { namespace book {

namespace {
// Constants used in liquibook
//const Price INVALID_LEVEL_PRICE(UINT32_MAX);
const Price INVALID_LEVEL_PRICE(INT32_MIN);
const Price MARKET_ORDER_BID_SORT_PRICE(INT32_MAX);
const Price MARKET_ORDER_ASK_SORT_PRICE(INT32_MIN);
}

}}
