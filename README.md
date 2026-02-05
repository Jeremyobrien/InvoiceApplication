# InvoiceApplication

A C++/Qt application for managing invoices and expenses, featuring a comprehensive Qt Test suite and integrated code coverage reporting.

## Table of Contents
* [Prerequisites](#prerequisites-)
* [Build Instructions](#build-instructions-)
* [Run the Application](#run-the-application-)
* [Run Tests](#run-tests-)
* [Generate Code Coverage](#generate-code-coverage-)
* [Project Structure](#project-structure-)

---

## Prerequisites ✅

Ensure you have the following installed on your system:
* **Windows 10/11**
* **Visual Studio 2022** (Desktop development with C++ & CMake support)
* **Qt 6.x** (Ensure `Qt6_DIR` is in your system environment variables)
* **OpenCppCoverage** (Required for generating code coverage reports)

---

## Build Instructions 🏗️

Using the Visual Studio Developer Command Prompt or PowerShell, run the following commands from the project root to ensure a clean build and consistent output:

```powershell
# Configure CMake
cmake -S . -B out/build/x64-Debug

# Clean any existing artifacts and rebuild all targets
cmake --build out/build/x64-Debug --target clean
cmake --build out/build/x64-Debug --config Debug
Run the Application ▶️
Via Command Line
Navigate to the binary directory from the project root and execute the tracker:

PowerShell
cd .\out\build\x64-Debug\bin
.\invoice-tracker.exe
Via Visual Studio
Open the CMake Targets View in the Solution Explorer.

Locate the invoice-tracker executable.

Right-click it and select Set As Startup Item.

Press F5 or click the Start button.

Run Tests 🧪
Individual Test Execution
To run a specific test manually and view detailed qDebug() output or failure line numbers, execute the binary directly from the bin folder:

PowerShell
cd .\out\build\x64-Debug\bin
.\test_apply_import.exe
Run All Tests via CTest
To run the full suite and view a pass/fail summary for all modules:

PowerShell
ctest --test-dir out/build/x64-Debug -C Debug --output-on-failure
Generate Code Coverage 📊
This project uses a custom Visual Studio target to automate the test execution and coverage merging process.

In Visual Studio, locate the Startup Item dropdown (near the Start button).

Select RunCoverage.

Click the Start button (or press F5).

This triggers the RunAllTests.ps1 script, which:

Automatically discovers all test executables in the bin folder.

Executes them through OpenCppCoverage.

Merges the results into a single HTML report located at: out/build/x64-Debug/CoverageReport/HtmlReport/index.html

Project Structure 🗂️
The project follows a modular architecture separating data, logic, and UI components:

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