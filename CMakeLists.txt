cmake_minimum_required(VERSION 3.22)
project(Banking_Application)

set(CMAKE_CXX_STANDARD 14)

add_executable(Banking_Application
        src/main.cpp
        src/AccountFund.h
        src/AccountFund.cpp
        src/Account.h
        src/Account.cpp
        src/Bank.h
        src/Bank.cpp
        src/BSTree.h
        src/BSTree.cpp
        src/Constants.h
        src/Transaction.h
        src/Transaction.cpp
        )
