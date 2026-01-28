InvoiceApplication

A C++/Qt application for managing invoices and expenses, with a test suite and code coverage support.

Table of Contents

Prerequisites

Clone the Repository

Build Instructions

Run the Application

Run Tests

Generate Code Coverage

Project Structure

Contributing

Prerequisites ✅

Before building and running the project, make sure you have:

Windows 10/11

Visual Studio 2022 (Community or higher) with:

Desktop development with C++

CMake support

Qt 6.x (tested with Qt 6.7)

CMake ≥ 3.24

Qt 6 (matching your Visual Studio configuration)

OpenCppCoverage (for code coverage)

Git

Clone the Repository ⬇️
git clone https://github.com/Jeremyobrien/InvoiceApplication.git
cd InvoiceApplication

Build Instructions 🏗️

Create a build directory and configure CMake:

cmake -S . -B build -G "Visual Studio 17 2022"


Build the project in Debug configuration:

cmake --build build --config Debug


This will build the main application and all test executables.

Run the Application ▶️

After building:

build\Debug\InvoiceApplication.exe


(Adjust path if your Visual Studio configuration is different.)

Run Tests 🧪

You can run individual Qt test executables:

cd build\tests\Debug
.\test_invoice.exe
.\test_expense.exe
.\test_model_invoice.exe
.\test_model_expense.exe


Or run all tests with CTest:

cd ../../..
ctest --test-dir build --output-on-failure

Generate Code Coverage 📊

⚠️ Important: OpenCppCoverage requires absolute paths and Visual Studio must be closed (locks .vs folder).

Run OpenCppCoverage for each test executable:

OpenCppCoverage.exe --modules "$(Resolve-Path build\Debug\test_invoice.exe)" --sources "$(Resolve-Path src)" -- build\Debug\test_invoice.exe


To cover all tests:

$tests = @("test_invoice.exe", "test_expense.exe", "test_model_invoice.exe", "test_model_expense.exe")
foreach ($t in $tests) {
    OpenCppCoverage.exe --modules "$(Resolve-Path build\Debug\$t)" --sources "$(Resolve-Path src)" -- "build\Debug\$t"
}


Open the HTML coverage report:

start build\CoverageReport-*\index.html


Tip: Avoid putting .vs inside build to prevent locked files.

Project Structure 🗂️
InvoiceApplication/
│
├─ src/               # Application source files
│  ├─ models/
│  ├─ dialogs/
│  └─ services/
│
├─ tests/             # Qt Test files
│
├─ build/             # Build output (ignored in Git)
│
└─ README.md
