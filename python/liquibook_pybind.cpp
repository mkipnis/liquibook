// Copyright (c) Mike Kipnis

#include <memory>
#include <map>
#include <vector>
#include <cstdint>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <book/types.h>
#include <book/depth_constants.h>
#include <book/order_tracker.h>
#include <book/comparable_price.h>
#include <book/order.h>
#include <book/order_listener.h>
#include <book/logger.h>
#include <book/depth.h>
#include <book/depth_level.h>
#include <book/order_book_listener.h>
#include <book/order_book.h>
#include <book/bbo_listener.h>
#include <book/depth_listener.h>
#include <book/depth_order_book.h>

#include <simple/simple_order.h>
#include <simple/simple_order_book.h>

namespace py = pybind11;

namespace {

constexpr int DEPTH = 5;

using OrderPtr = std::shared_ptr<liquibook::simple::SimpleOrder>;

using DepthBook =
    liquibook::book::DepthOrderBook<OrderPtr, DEPTH>;

using SimpleBook =
    liquibook::simple::SimpleOrderBook<DEPTH>;

using GenericOrderBook =
    liquibook::book::OrderBook<OrderPtr>;

using DepthType =
    liquibook::book::Depth<DEPTH>;

using OrderListenerType =
    liquibook::book::OrderListener<OrderPtr>;

using DepthListenerType =
    liquibook::book::DepthListener<DepthBook>;

using DepthBookListenerType =
    liquibook::book::OrderBookListener<DepthBook>;

using SimpleBookListenerType =
    liquibook::book::OrderBookListener<SimpleBook>;

using BboListenerType =
    liquibook::book::BboListener<DepthBook>;

using OrderTrackerType =
    liquibook::book::OrderTracker<OrderPtr>;

using OrderTrackerMap =
    std::multimap<
        liquibook::book::ComparablePrice,
        OrderTrackerType
    >;

std::vector<liquibook::book::DepthLevel*>
get_bid_levels(DepthType& depth)
{
    std::vector<liquibook::book::DepthLevel*> result;
    auto level = depth.bids();

    for (int i = 0; i < DEPTH; ++i) {
        result.push_back(level++);
    }

    return result;
}

std::vector<liquibook::book::DepthLevel*>
get_ask_levels(DepthType& depth)
{
    std::vector<liquibook::book::DepthLevel*> result;
    auto level = depth.asks();

    for (int i = 0; i < DEPTH; ++i) {
        result.push_back(level++);
    }

    return result;
}

} // namespace

PYBIND11_MODULE(liquibook, m)
{
    m.doc() = "Python bindings for LiquiBook";

    // ---------------------------------------------------------
    // Primitive types / constants
    // ---------------------------------------------------------

    m.attr("DEPTH") = DEPTH;

    // ---------------------------------------------------------
    // ComparablePrice
    // ---------------------------------------------------------

    py::class_<liquibook::book::ComparablePrice>(
        m, "ComparablePrice"
    );

    // ---------------------------------------------------------
    // DepthLevel
    // ---------------------------------------------------------

    py::class_<liquibook::book::DepthLevel>(
        m, "DepthLevel"
    );

    // ---------------------------------------------------------
    // Depth<5>
    // ---------------------------------------------------------

    py::class_<DepthType>(m, "Depth")
        .def("get_bid_levels", [](DepthType& self) {
            return get_bid_levels(self);
        })
        .def("get_ask_levels", [](DepthType& self) {
            return get_ask_levels(self);
        });


    // ---------------------------------------------------------
    // SimpleOrder
    //
    // shared_ptr holder preserves SWIG's shared ownership intent.
    // ---------------------------------------------------------

    py::class_<liquibook::simple::SimpleOrder,
               OrderPtr>(m, "SimpleOrder")
        .def(py::init<bool, const double&,
                      liquibook::book::Quantity>())
        .def("is_buy",
             &liquibook::simple::SimpleOrder::is_buy)
        .def("price",
             &liquibook::simple::SimpleOrder::price)
        .def("order_qty",
             &liquibook::simple::SimpleOrder::order_qty);

    // ---------------------------------------------------------
    // Listener and order-book classes
    //
    // Bind the concrete template specializations explicitly.
    // Add callback trampolines before exposing Python subclasses.
    // ---------------------------------------------------------

    py::class_<OrderListenerType>(m, "OrderListener");

    py::class_<DepthListenerType>(m, "DepthListener");

    py::class_<DepthBookListenerType>(
        m, "DepthOrderBookListener"
    );

    py::class_<SimpleBookListenerType>(
        m, "SimpleOrderBookListener"
    );

    py::class_<BboListenerType>(
        m, "DepthOrderBookBboListener"
    );

    // ---------------------------------------------------------
    // OrderTracker
    // ---------------------------------------------------------

    py::class_<OrderTrackerType>(m, "OrderTracker");

    // ---------------------------------------------------------
    // Generic OrderBook<shared_ptr<SimpleOrder>>
    // ---------------------------------------------------------

    py::class_<GenericOrderBook>(m, "OrderBook");

    // ---------------------------------------------------------
    // DepthOrderBook<shared_ptr<SimpleOrder>, 5>
    // ---------------------------------------------------------

    py::class_<DepthBook, GenericOrderBook>(
        m, "DepthOrderBook"
    )
        .def(py::init<>());

    // ---------------------------------------------------------
    // SimpleOrderBook<5>
    // ---------------------------------------------------------

    py::class_<SimpleBook>(m, "SimpleOrderBook")
        .def(py::init<>());

    // OrderTrackerMap is a C++ implementation container.
    // Expose it only if Python code needs to construct or inspect it.
}
