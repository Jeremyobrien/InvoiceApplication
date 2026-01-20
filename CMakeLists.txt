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
    src/import/CsvImporter.cpp
    src/import/JsonImporter.cpp
    src/export/CsvExporter.cpp
    src/export/JsonExporter.cpp
    src/export/ExportService.cpp 
    src/dialogs/InvoiceDialog.cpp
    src/dialogs/ExpenseDialog.cpp
    src/models/Invoice.cpp
    src/models/Expense.cpp
    src/models/InvoiceTableModel.cpp
    src/models/ExpenseTableModel.cpp
    src/ui/PaidDelegate.cpp
)

target_include_directories(invoice-tracker PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/import
    ${CMAKE_CURRENT_SOURCE_DIR}/src/export
)

target_link_libraries(invoice-tracker Qt6::Widgets)