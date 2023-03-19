# Copyright (c) Mike Kipnis
import liquibook
from liquibook import pretty_print
import time

class DepthListener(liquibook.DepthListener):

    def __init__(self):
        print("DepthListener")
        liquibook.DepthListener.__init__(self)

    def on_depth_change(self, book, depth):
        print('Depth change:[' + book.symbol() + ']')
        print(liquibook.pretty_print.depth_header)
        print(liquibook.pretty_print.depth_header_separator)
        pretty_depth = liquibook.pretty_print.depth(depth)
        print(pretty_depth)
        print('\n')


class OrderListener(liquibook.OrderListener):

    def __init__(self):
        print("OrderListener")
        liquibook.OrderListener.__init__(self)

    def on_accept(self, order):
        print('Order accepted: [' + str(order.order_id_) + ']')
        order_string = liquibook.pretty_print.order(order)
        print(liquibook.pretty_print.order_header)
        print(liquibook.pretty_print.order_header_separator)
        print(order_string)
        print('\n')


    def on_cancel(self, order):
        print('Order cancelled: [' + str(order.order_id_) + ']')
        order_string = liquibook.pretty_print.order(order)
        print(liquibook.pretty_print.order_header)
        print(liquibook.pretty_print.order_header_separator)
        print(order_string)
        print('\n')

    def on_fill(self, passive_order, aggressive_order, fill_qty, fill_cost):

        passive_order.fill(fill_qty, fill_cost,0)
        aggressive_order.fill(fill_qty, fill_cost,0)

        print(liquibook.pretty_print.order_header)
        print(liquibook.pretty_print.order_header_separator)
        aggressive_order_string = liquibook.pretty_print.order(passive_order)
        passive_order_order_string = liquibook.pretty_print.order(aggressive_order)
        print(aggressive_order_string)
        print(passive_order_order_string+'\n')


class BBOListener(liquibook.DepthOrderBookBboListener):

    def __init__(self):
        print("BBO Listener")
        liquibook.DepthOrderBookBboListener.__init__(self)

    def on_bbo_change(self, book, depth):
        print('Best bid/offer change: [' + book.symbol() + ']')
        print(liquibook.pretty_print.depth_header)
        print(liquibook.pretty_print.depth_header_separator)
        bid_price_size_tuple = liquibook.pretty_print.depth_level(depth.bids())
        ask_price_size_tuple = liquibook.pretty_print.depth_level(depth.asks())

        top_level_out = liquibook.pretty_print.depth_header_format.\
                format(bid=bid_price_size_tuple, ask=ask_price_size_tuple)
        print(top_level_out+'\n')


if __name__ == '__main__':

    order_book_listener = DepthListener()
    bbo_listener = BBOListener()
    order_listener = OrderListener()

    simple_order_book = liquibook.DepthOrderBook()
    simple_order_book.set_bbo_listener(bbo_listener)
    simple_order_book.set_depth_listener(order_book_listener)
    simple_order_book.set_order_listener(order_listener)
    simple_order_book.set_symbol('AAPL')

    transaction_seprator="="*len(liquibook.pretty_print.order_header)

    print(transaction_seprator)
    buy_order_1 = liquibook.SimpleOrder(True, 100, 10)
    print('Submitting Buy - Price : {:<7} Size: {:<7}'.format(buy_order_1.price(), buy_order_1.order_qty()))
    time.sleep(2)
    simple_order_book.add(buy_order_1)
    print(transaction_seprator)

    buy_order_2 = liquibook.SimpleOrder(True, 110, 10)
    print('Submitting Buy - Price : {:<7} Size: {:<7}'.format(buy_order_2.price(), buy_order_2.order_qty()))
    time.sleep(3)
    simple_order_book.add(buy_order_2)
    print(transaction_seprator)

    sell_order_1 = liquibook.SimpleOrder(False, 120, 30)
    print('Submitting Sell - Price : {:<7} Size: {:<7}'.format(sell_order_1.price(), sell_order_1.order_qty()))
    time.sleep(3)
    simple_order_book.add(sell_order_1)
    print(transaction_seprator)

    print('Cancelling Sell - Price : {:<7} Size: {:<7}'.format(sell_order_1.price(), sell_order_1.order_qty()))
    time.sleep(3)
    simple_order_book.cancel(sell_order_1)
    print(transaction_seprator)

    sell_order_2 = liquibook.SimpleOrder(False, 100, 20)
    print('Submitting Sell - Price : {:<7} Size: {:<7}'.format(sell_order_1.price(), sell_order_1.order_qty()))
    time.sleep(3)
    simple_order_book.add(sell_order_2)
    print(transaction_seprator)

