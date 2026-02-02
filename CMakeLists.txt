cmake_minimum_required(VERSION 3.16)
project(invoice-tracker LANGUAGES CXX)

# Force all executables and libraries into a single 'bin' folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ensure PDBs are generated in the same 'bin' folder for all configs
if(MSVC)
    set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG:FULL")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG:FULL")
    add_compile_options(/Zi /Od)
endif()

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
add_library(invoice_tracker_core
    src/models/Invoice.cpp
    src/models/Expense.cpp
    src/models/InvoiceTableModel.cpp
    src/models/ExpenseTableModel.cpp
    src/import/CsvImporter.cpp
    src/import/JsonImporter.cpp
    src/export/CsvExporter.cpp
    src/export/JsonExporter.cpp
    src/export/ExportService.cpp 
   )

target_include_directories(invoice_tracker_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(invoice_tracker_core
    Qt6::Widgets
)

add_library(invoice_tracker_ui
    src/dialogs/InvoiceDialog.cpp
    src/dialogs/ExpenseDialog.cpp
    src/ui/PaidDelegate.cpp
    src/ui/GenericSearchProxy.cpp
 )

target_link_libraries(invoice_tracker_ui
    Qt6::Widgets
    invoice_tracker_core
)

# -----------------------
# Main application
# -----------------------
add_executable(invoice-tracker
    src/main.cpp
    src/MainWindow.cpp
 )

target_include_directories(invoice-tracker PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(invoice-tracker
    Qt6::Widgets
    invoice_tracker_core
    invoice_tracker_ui
)

# -----------------------
# Add tests
# -----------------------
add_subdirectory(tests)

# 1. Find all test executables in the build directory automatically
file(GLOB_RECURSE FOUND_TESTS "${CMAKE_BINARY_DIR}/*test*.exe")

# 2. Configure the script with the source path AND the list of tests found
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/RunAllTests.ps1"
    "${CMAKE_CURRENT_BINARY_DIR}/RunAllTests.ps1"
    @ONLY
)

add_custom_target(RunCoverage
    COMMAND powershell.exe -ExecutionPolicy Bypass -File "${CMAKE_CURRENT_BINARY_DIR}/RunAllTests.ps1"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMENT "Running universal code coverage..."
    VERBATIM
)