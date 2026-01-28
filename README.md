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

Prerequisites

Before building and running the project, make sure you have the following installed:

Windows 10/11

Visual Studio 2022 (Community or higher) with:

C++ Desktop Development

CMake support

Qt 6.x (tested with Qt 6.7)

CMake ≥ 3.24

Qt 6 (matching your Visual Studio configuration)

OpenCppCoverage (for code coverage)

Git (for cloning the repository)

Clone the Repository
git clone https://github.com/Jeremyobrien/InvoiceApplication.git
cd InvoiceApplication

Build Instructions

Create a build directory and configure CMake:

cmake -S . -B build -G "Visual Studio 17 2022"


Build the project in Debug configuration:

cmake --build build --config Debug


This will build the main application and all test executables.

Run the Application

After building:

build\Debug\InvoiceApplication.exe


(Adjust path if your Visual Studio configuration is different.)

Run Tests

To run the Qt test suite:

cd build\tests\Debug
.\test_invoice.exe
.\test_expense.exe
.\test_model_invoice.exe
.\test_model_expense.exe
# ... or run all tests using CTest
cd ../../..
ctest --test-dir build --output-on-failure

Generate Code Coverage

⚠️ Important: OpenCppCoverage requires modules and sources to be absolute paths.

Make sure Visual Studio is closed (locks .vs folder prevent coverage).

Run OpenCppCoverage on all test executables. Example for a single test:

OpenCppCoverage.exe --modules "$(Resolve-Path build\Debug\test_invoice.exe)" --sources "$(Resolve-Path src)" -- build\Debug\test_invoice.exe


To cover the entire solution, repeat for each test executable, e.g.:

$tests = @("test_invoice.exe", "test_expense.exe", "test_model_invoice.exe", "test_model_expense.exe")
foreach ($t in $tests) {
    OpenCppCoverage.exe --modules "$(Resolve-Path build\Debug\$t)" --sources "$(Resolve-Path src)" -- "build\Debug\$t"
}


Open the generated HTML coverage report:

start build\CoverageReport-*\index.html


Tip: Avoid putting .vs inside build to prevent locked files.

Project Structure
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

Contributing

Fork the repository.

Create a new branch: git checkout -b feature/my-feature

Commit changes: git commit -am 'Add new feature'

Push branch: git push origin feature/my-feature

Open a Pull Request.
