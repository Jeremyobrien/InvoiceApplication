InvoiceApplication

A C++ / Qt desktop application for managing invoices and expenses, featuring a comprehensive Qt Test suite and integrated code coverage reporting using OpenCppCoverage.

📚 Table of Contents

Prerequisites

Build Instructions

Run the Application

Run Tests

Generate Code Coverage

Project Structure

✅ Prerequisites

Windows 10 / 11

Visual Studio 2022

Desktop development with C++

CMake tools for Windows

Qt 6.x

Ensure Qt6_DIR is set in your environment variables

OpenCppCoverage

Required for the RunCoverage utility target

🏗️ Build Instructions
Via Visual Studio

Open Visual Studio 2022

Click Folder View and select the root project directory

This action automatically initiates CMake configuration and generation

Once generation completes, open the Select Startup Item dropdown

Select:

invoice-tracker.exe (bin\invoice-tracker.exe)


Click the green Run arrow or press F5

This triggers a build (if required) and launches the application.

▶️ Run the Application
Via Visual Studio

(If invoice-tracker.exe did not load automatically)

Open Select Startup Item

Choose invoice-tracker.exe (bin\invoice-tracker.exe)

Press F5 or click Start

Via Command Line
cd .\out\build\x64-Debug\bin
.\invoice-tracker.exe

🧪 Run Tests
Run an Individual Test
cd .\out\build\x64-Debug\bin
.\test_apply_import.exe

Run All Tests via CTest

Note: Run this command from the project root directory

ctest --test-dir out/build/x64-Debug -C Debug --output-on-failure

📊 Generate Code Coverage

This project includes a custom CMake utility target that automates test execution and coverage generation.

Steps (Visual Studio)

Click Build → Rebuild All

Click Switch between solutions and available views

Select CMake Targets View

Expand the invoice-tracker project

Right-click RunCoverage

Select Build RunCoverage

What This Does

Executes all unit test binaries

Collects coverage data using OpenCppCoverage

Merges results into a single HTML report

📍 Coverage report location:

out/build/x64-Debug/CoverageReport/HtmlReport/index.html


This should automatically open in your browser

You can also open the report manually by navigating to the path above or by executing the coverage script from the project root directory

🗂️ Project Structure
InvoiceApplication/
├── src/
│   ├── data/           # Core data classes (Expense, Invoice)
│   ├── dialogs/        # UI dialogs (ExpenseDialog, InvoiceDialog)
│   ├── models/         # Qt table models
│   ├── import/         # Import logic (ImportUtils, CsvImporter)
│   ├── export/         # Export logic (ExportService, JsonExporter)
│   └── ui/             # Views and custom delegates (PaidDelegate)
├── tests/              # Qt unit tests
├── out/
│   └── build/          # Build output and binaries
└── CMakeLists.txt      # Root CMake configuration
