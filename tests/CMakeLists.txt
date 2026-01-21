# Find Qt6 Test module
find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

# Include models for tests
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

# -----------------------
# Invoice tests
# -----------------------
add_executable(test_invoice
    test_invoice.cpp
)
target_link_libraries(test_invoice
    Qt6::Test
    Qt6::Widgets
    models_core
)
add_test(NAME InvoiceTests COMMAND test_invoice)

# -----------------------
# Expense tests
# -----------------------
add_executable(test_expense
    test_expense.cpp
)
target_link_libraries(test_expense
    Qt6::Test
    Qt6::Widgets
    models_core
)
add_test(NAME ExpenseTests COMMAND test_expense)

# -----------------------
# InvoiceTableModel tests
# -----------------------
add_executable(test_model_invoice
    test_model_invoice.cpp
)
target_link_libraries(test_model_invoice
    Qt6::Test
    Qt6::Widgets
    models_core
)
add_test(NAME InvoiceTableModelTests COMMAND test_model_invoice)

# -----------------------
# ExpenseTableModel tests
# -----------------------
add_executable(test_model_expense
    test_model_expense.cpp
)
target_link_libraries(test_model_expense
    Qt6::Test
    Qt6::Widgets
    models_core
)
add_test(NAME ExpenseTableModelTests COMMAND test_model_expense)