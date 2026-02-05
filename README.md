# InvoiceApplication

A C++/Qt application for managing invoices and expenses, featuring a comprehensive Qt Test suite and integrated code coverage reporting.

## Table of Contents
* [Prerequisites](#prerequisites-)
* [Build Instructions](#build-instructions-)
* [Run the Application](#run-the-application-)
* [Run Tests](#run-tests-)
* [Code Coverage](#generate-code-coverage-)
* [Project Structure](#project-structure-)

---

## Prerequisites ✅

Ensure you have the following installed:
* **Windows 10/11**
* **Visual Studio 2022** (Desktop development with C++ & CMake support)
* **Qt 6.x** (Ensure `Qt6_DIR` is in your environment variables)
* **OpenCppCoverage** (Required for the `RunCoverage` target)

---

## Build Instructions 🏗️

Using the Visual Studio Developer Command Prompt or PowerShell, run the following commands from the project root:

```powershell
# Configure CMake
cmake -S . -B out/build/x64-Debug

# Build the project (Clean and Rebuild all targets)
cmake --build out/build/x64-Debug --target clean
cmake --build out/build/x64-Debug --config Debug
Run the Application ▶️
Via Command Line
From the project root, navigate to the binary directory:

PowerShell
cd .\out\build\x64-Debug\bin
.\invoice-tracker.exe
Via Visual Studio
Open the CMake Targets View in the Solution Explorer.

Locate the invoice-tracker executable.

Right-click it and select Set As Startup Item.

Press F5 or the Start button.

Run Tests 🧪
To run an individual test manually and view detailed output/logging:

PowerShell
cd .\out\build\x64-Debug\bin
.\test_apply_import.exe
Run All Tests via CTest
To run the full suite and see a summary of results:

PowerShell
ctest --test-dir out/build/x64-Debug -C Debug --output-on-failure
Generate Code Coverage 📊
This project uses a custom Visual Studio task to automate the coverage lifecycle.

In Visual Studio, locate the Startup Item dropdown (near the Start button).

Select RunCoverage.

Click the Start button.

This triggers the RunAllTests.ps1 script, which executes all test modules in the bin folder and generates a merged HTML report at: out/build/x64-Debug/CoverageReport/HtmlReport/index.html

Project Structure 🗂️
Plaintext
InvoiceApplication/
├── src/
│   ├── data/           # Core Data Classes (Expense.h, Invoice.h)
│   ├── dialogs/        # UI Dialogs (ExpenseDialog, InvoiceDialog)
│   ├── models/         # Table Models (ExpenseTableModel, InvoiceTableModel)
│   ├── import/         # Import logic (ImportUtils.h, CsvImporter)
│   ├── export/         # Export logic (ExportService, JsonExporter)
│   └── ui/             # Views and Custom Delegates (PaidDelegate)
├── tests/              # Qt Unit Tests (test_apply_import.cpp, etc.)
├── out/                # Build output
│   └── build/          # Compiled binaries and artifacts
└── CMakeLists.txt      # Root configuration
