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
    invoice_tracker_core
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
    invoice_tracker_core
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
    invoice_tracker_core
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
    invoice_tracker_core
)
add_test(NAME ExpenseTableModelTests COMMAND test_model_expense)

# -----------------------
# Dialogs tests
# -----------------------
add_executable(test_expense_dialog
    test_expense_dialog.cpp
)
target_link_libraries(test_expense_dialog
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
    invoice_tracker_ui
)
add_test(NAME ExpenseDialogTests COMMAND test_expense_dialog)

add_executable(test_invoice_dialog
    test_invoice_dialog.cpp
)
target_link_libraries(test_invoice_dialog
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
    invoice_tracker_ui
)
add_test(NAME InvoiceDialogTests COMMAND test_invoice_dialog)

# -----------------------
# Export tests
# -----------------------
add_executable(test_export_service
    test_export_service.cpp
)
target_link_libraries(test_export_service
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME ExportServiceTests COMMAND test_export_service)

add_executable(test_csv_exporter
    test_csv_exporter.cpp
)
target_link_libraries(test_csv_exporter
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME CsvExporterTests COMMAND test_csv_exporter)

add_executable(test_json_exporter
    test_json_exporter.cpp
)
target_link_libraries(test_json_exporter
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME JsonExporterTests COMMAND test_json_exporter)

# -----------------------
# Import tests
# -----------------------
add_executable(test_csv_importer
    test_csv_importer.cpp
)
target_link_libraries(test_csv_importer
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME CsvImporterTests COMMAND test_csv_importer)

add_executable(test_apply_import
    test_apply_import.cpp
)
target_link_libraries(test_apply_import
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME ApplyImportTests COMMAND test_apply_import)

add_executable(test_json_importer
    test_json_importer.cpp
)
target_link_libraries(test_json_importer
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME JsonImporterTests COMMAND test_json_importer)

# -----------------------
# UI Utils(CRUD) tests
# -----------------------
add_executable(test_create_item
    test_create_item.cpp
)
target_link_libraries(test_create_item
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME CreateItemTests COMMAND test_create_item)

add_executable(test_delete_selected
    test_delete_selected.cpp
)
target_link_libraries(test_delete_selected
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME DeleteSelectedTests COMMAND test_delete_selected)

add_executable(test_edit_utils
    test_edit_utils.cpp
)
target_link_libraries(test_edit_utils
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME EditSelectedRowTests COMMAND test_edit_utils)

add_executable(test_generic_search_proxy
    test_generic_search_proxy.cpp
)
target_link_libraries(test_generic_search_proxy
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
    invoice_tracker_ui
)
add_test(NAME GenericSearchProxyTests COMMAND test_generic_search_proxy)

add_executable(test_paid_delegate
    test_paid_delegate.cpp
)
target_link_libraries(test_paid_delegate
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
    invoice_tracker_ui
)
add_test(NAME PaidDelegateTests COMMAND test_paid_delegate)

add_executable(test_read_selected
    test_read_selected.cpp
)
target_link_libraries(test_read_selected
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME ReadSelectedTests COMMAND test_read_selected)

add_executable(test_bind_search
    test_bind_search.cpp
)
target_link_libraries(test_bind_search
    Qt6::Test
    Qt6::Widgets
    invoice_tracker_core
)
add_test(NAME BindSearchTests COMMAND test_bind_search)




