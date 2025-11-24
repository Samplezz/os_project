#!/bin/bash

# Define base directory
BASE_DIR="./bank"

# Create directories
echo "Creating directory structure..."
mkdir -p "$BASE_DIR/admin"
mkdir -p "$BASE_DIR/employees"
mkdir -p "$BASE_DIR/customers"

# Create some dummy files for testing
echo "Creating dummy files..."
touch "$BASE_DIR/admin/system_config.conf"
touch "$BASE_DIR/admin/users.db"
echo "Log entry 1" > "$BASE_DIR/employees/transaction.log"
echo "Customer Data" > "$BASE_DIR/employees/customer_list.txt"
echo "My Transaction History" > "$BASE_DIR/customers/my_history.txt"

# Set permissions (Simulated for the assignment)
# Admin: rwx (700) - Only admin
# Employees: rwx for owner, rx for group (750)
# Customers: rwx for owner (700)

echo "Setting permissions..."
chmod 700 "$BASE_DIR/admin"
chmod 750 "$BASE_DIR/employees"
chmod 700 "$BASE_DIR/customers"

echo "Setup complete. Directory structure created at $BASE_DIR"
