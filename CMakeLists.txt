cmake_minimum_required(VERSION 3.16)
project(invoice-tracker LANGUAGES CXX)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt automoc/uic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Enable CTest for unit testing
enable_testing()

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

# -----------------------
# Models library
# -----------------------
add_library(models_core
    src/models/Invoice.cpp
    src/models/Expense.cpp
    src/models/InvoiceTableModel.cpp
    src/models/ExpenseTableModel.cpp
)

target_include_directories(models_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(models_core
    Qt6::Widgets
)

# -----------------------
# Main application
# -----------------------
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
    src/ui/PaidDelegate.cpp
)

target_include_directories(invoice-tracker PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(invoice-tracker
    Qt6::Widgets
    models_core
)

# -----------------------
# Add tests
# -----------------------
add_subdirectory(tests)