#!/bin/bash

# Build the server and client
echo "Compiling server and client..."
gcc multiplication_server.c -o server || { echo "Server compilation failed!"; exit 1; }
gcc multiplication_client.c -o client || { echo "Client compilation failed!"; exit 1; }

echo "Starting server..."
./server &
SERVER_PID=$!
sleep 1  # Give server time to start

echo "Running tests..."
TEST_CASES=(
    "5 7"
    "-3 8"
    "0 10"
    "100000 100000"
    "-999 -999"
    "2147483647 2"
    "-2147483648 -1"
    "abc 123"
    "5"
    "5 7 9"
)

TOTAL_TIME=0
COUNT=0

for TEST in "${TEST_CASES[@]}"; do
    echo -n "Testing: ./client $TEST -> "
    START=$(date +%s%N)
    OUTPUT=$(./client $TEST 2>&1)
    END=$(date +%s%N)
    TIME_TAKEN=$(( (END - START) / 1000000 ))  # Convert ns to ms
    TOTAL_TIME=$((TOTAL_TIME + TIME_TAKEN))
    COUNT=$((COUNT + 1))
    echo "$OUTPUT (Time: ${TIME_TAKEN}ms)"
done

AVG_TIME=$((TOTAL_TIME / COUNT))
echo "Average execution time: ${AVG_TIME}ms"

echo "Stopping server..."
kill $SERVER_PID
