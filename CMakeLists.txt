cmake_minimum_required(VERSION 3.16)
project(invoice-tracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(invoice-tracker
    src/main.cpp
    src/MainWindow.cpp
    src/Invoice.cpp
    src/Expense.cpp
    src/InvoiceDialog.cpp
)

target_link_libraries(invoice-tracker Qt6::Widgets)